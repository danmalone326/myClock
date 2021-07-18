
// For testing
#define  DELAYTIME  000  // in milliseconds

void debugPrintStr(char *current) {
  static char last[80];

  if (strcmp(last,current) != 0) {
    Serial.println(current);
    strcpy(last,current);
  }
}

void debugPrintUint(uint32_t current) {
  static uint32_t last;

  if (last != current) {
    Serial.println(current);
    last = current;
  }
}


// Framework 
#define TZ              -8       // (utc + TZ in hours)
#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_MN          60      // use 60 for summer time in some countries
#define DST_SEC         ((DST_MN)*60)
//#include <EwingsEsp8266Stack.h>
#include <EwingsEspStack.h>
bool wifiIsConnected = false;
void frameworkSetup() {
  EwStack.initialize();
  __nw_time_service.init_ntp_time();
  __event_service.add_event_listener(EVENT_WIFI_STA_GOT_IP,[&](void*sta_connected) {  wifiIsConnected = true; } );
  __event_service.add_event_listener(EVENT_WIFI_STA_DISCONNECTED, [&](void*sta_connected) {  wifiIsConnected = false; } );
}

// end Framework



#include <Timezone.h>   // https://github.com/JChristensen/Timezone
// US Pacific Time Zone (New York, Detroit)
TimeChangeRule myDST = {"PDT", Second, Sun, Mar, 2, -420};    // Daylight time = UTC - 7 hours
TimeChangeRule mySTD = {"PST", First, Sun, Nov, 2, -480};     // Standard time = UTC - 8 hours
Timezone myTZ(myDST, mySTD);
TimeChangeRule *tcr;        // pointer to the time change rule, use to get TZ abbrev

//#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

//#include "clockFont.h"
#include "threeByFiveFont.h"
#include "threeBySevenFont.h"
#include "fourBySixFont.h"
#include "boldFont.h"
#include "myFont.h"

#include <string.h>


// Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::DR1CR0RR1_HW //FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 15

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Found the function in MD_MAX72XX to get the character - getChar
//   uint8_t characterWidth = mx.getChar(character, characterBufferSize, characterBuffer);


// assumes result is big enough
// assumes width and height are the same for all
void transitionCharacter(uint8_t *result, uint8_t *current, uint8_t *target, uint8_t width, uint8_t height, float transitionPercent, uint8_t transitionType) {
  uint8_t heightMask = (uint8_t)(pow(2,height)-1) << (8-height);
  uint8_t transitionPosition = transitionPercent*height;
  uint8_t currentPart;
  uint8_t targetPart;

  switch (transitionType) {
    default:
      for(int i=0; i<width; i++) {
        currentPart = current[i] << transitionPosition;
        targetPart = target[i] >> (height-transitionPosition);
        result[i] = (currentPart | targetPart) & heightMask;
      }
      break;
  }
}

uint8_t overlayCustomCharacter(uint8_t *characterBuffer, uint8_t characterWidth, int8_t startColumn, int8_t startRow) {
  
  uint8_t currentColumn;
  uint8_t updatedColumn;
  uint8_t shiftedCharacter;

//  Serial.println(characterWidth);
  for (int relativeColumn = 0; relativeColumn < characterWidth; relativeColumn++) {
    currentColumn = startColumn + relativeColumn;
    shiftedCharacter = characterBuffer[relativeColumn];
    if (startRow > 0) {
      shiftedCharacter = shiftedCharacter << startRow;
    } else {
      shiftedCharacter = shiftedCharacter >> -startRow;
    }
    updatedColumn = mx.getColumn(currentColumn) | shiftedCharacter;

    mx.setColumn(currentColumn, updatedColumn);
  }

  return characterWidth;
}


#define characterBufferSize 8
uint8_t overlayCharacter(uint16_t character, int8_t startColumn, int8_t startRow) {
//  Serial.println("overlayCharacter");

  uint8_t characterBuffer[characterBufferSize];
  uint8_t characterWidth = mx.getChar(character, characterBufferSize, characterBuffer);

  return overlayCustomCharacter(characterBuffer, characterWidth, startColumn, startRow);
}

void printOver(char *str, int8_t startColumn, int8_t startRow) {
  uint8_t currentColumn = startColumn;
 
  for(int characterCounter=0; str[characterCounter]; characterCounter++) {
    currentColumn += overlayCharacter(str[characterCounter],currentColumn,startRow);
    currentColumn += 1;
  }
}

// end of font/print handling

//  Real Time Clock (rtc) handling
// Will assume UTC for rtc
#include <Wire.h>   // for I2C protocol
#include <ds3231.h>

bool rtcReadError = false;

void rtcSetup() {
  Wire.begin(); // starting I2C for RTC
  DS3231_init(DS3231_INTCN); //register the ds3231 at the default address
}

time_t rtcGet() {
  ts t;             // rtc time structure
  tmElements_t te;  // time elements structure
  time_t unixTime;  // unix timestamp

  DS3231_get(&t);

  te.Year = t.year - 1970;
  te.Month = t.mon;
  te.Day = t.mday;
  te.Hour = t.hour;
  te.Minute = t.min;
  te.Second = t.sec;

  if (t.year == 2165) { // Error reading rtc, use ntp time
    rtcReadError = true;
    unixTime = 0;
  } else {
    rtcReadError = false;
    unixTime = makeTime(te);
  }

  return unixTime;
}

bool rtcIsInSync() {
  time_t ntpTime;         // ntp timestamp
  time_t rtcTimeBefore;   // rtc timestamp before
  time_t rtcTimeAfter;    // rtc timestamp after
  long diffBefore;
  long diffAfter;

  rtcTimeBefore = rtcGet();
  ntpTime = __nw_time_service.get_ntp_time();
  rtcTimeAfter = rtcGet();

  diffBefore = abs(rtcTimeBefore - ntpTime);
  diffAfter = abs(rtcTimeAfter - ntpTime);

  return ((!rtcReadError) && ((diffBefore < 2) || (diffAfter < 2)));
}

void rtcSync() {
  time_t ntpTime;   // unix timestamp
  tmElements_t te;  // time elements structure
  static ts t;             // rtc time structure

  ntpTime = __nw_time_service.get_ntp_time();
  breakTime(ntpTime, te);
  
  t.year = te.Year + 1970;
  t.mon = te.Month;
  t.mday = te.Day;
  t.hour = te.Hour;
  t.min = te.Minute;
  t.sec = te.Second;

  DS3231_set(t);
}

float rtcTemperature() {
  return DS3231_get_treg();
}

time_t timeGet() {
  time_t unixTime;  // unix timestamp

  unixTime = rtcGet();

  if (rtcReadError && __nw_time_service.is_valid_ntptime()) { // Error reading rtc, use ntp time
    unixTime = __nw_time_service.get_ntp_time();
  }

  return unixTime;
}


// end rtc handling

// DHT Sensor 
#include <dhtnew.h>
#define dhtSensorPin D3
DHTNEW dhtSensor(dhtSensorPin);
#define dhtDelayMillis 2000

float dhtHumidity = 0.0;
float dhtTemperature = 0.0;
float dhtTemperatureF = 0.0;

void dhtRead() {
  static unsigned long dhtLastMillis = 0;
  if ((millis() >= dhtLastMillis + dhtDelayMillis) || (millis() < dhtLastMillis)) {
    dhtLastMillis = millis();
    int chk = dhtSensor.read();
    dhtHumidity = dhtSensor.getHumidity();
    dhtTemperature = dhtSensor.getTemperature();
    dhtTemperatureF = (dhtTemperature * 9 / 5) + 32;
  }
}

// end DHT Sensor

bool matrixTestComplete = false;
void matrixTest() {
  static unsigned long startMillis = millis();
  uint16_t testDuration = 1000;
  uint16_t rows;
  uint16_t columns;

  rows = 8;
  columns = mx.getColumnCount();

  uint16_t currentColumn = (millis() - startMillis) / (testDuration / columns);

  if (currentColumn >= columns) {
    matrixTestComplete = true;
  } else {
    mx.update(MD_MAX72XX::OFF);
  
    mx.clear();
    mx.setRow(currentColumn/(columns/rows),0xff);
    mx.setColumn(currentColumn,0xff);
    mx.update();
  
    mx.clear();
  }
}

// get current time in a format based on the parameters
void timeString(char *timeStr, 
                size_t maxsize,
                bool showLocalTime, 
                bool show24Hour, 
                bool showTimeZone, 
                bool showSeconds,
                bool showColons,
                bool flashColons,
                bool showAMPM) {
  time_t utcTime;
  time_t localTime;
  TimeChangeRule *tcr;        // pointer to the time change rule, use to get TZ abbrev
  struct tm *timeStruct;
  char timeZoneString[6];
  uint8_t currentSecond;
  unsigned long currentMilliSeconds;

//  utcTime = __nw_time_service.get_ntp_time();
  utcTime = timeGet();
  
  static uint8_t lastSecond = 60;
  static unsigned long millisLastSecondChange = 0;
  currentSecond = second(utcTime);
  if (currentSecond != lastSecond) {
    millisLastSecondChange = millis();
    lastSecond = currentSecond;
  }
  currentMilliSeconds = millis() - millisLastSecondChange;

  if (showLocalTime) {
    localTime = myTZ.toLocal(utcTime, &tcr);
    timeStruct = gmtime(&localTime);
    strncpy(timeZoneString, tcr -> abbrev, sizeof(timeZoneString)-1 );
  } else {
    timeStruct = gmtime(&utcTime);
    strncpy(timeZoneString, "UTC", sizeof(timeZoneString)-1 );
  }

// Now build a format string
  char timeFormatStr[20] = "";

  
  char colonChar[2] = "";
  if(showColons) {
    if (flashColons && (currentMilliSeconds < 500)) {
      strcat(colonChar," ");
    } else {
      strcat(colonChar,":");
    }
  }


  if (show24Hour) {
    strcat(timeFormatStr,"%H");
  } else {
    strcat(timeFormatStr,"%l");    
  }

  strcat(timeFormatStr,colonChar);
  strcat(timeFormatStr,"%M");

  if (showSeconds) {
    strcat(timeFormatStr,colonChar);
    strcat(timeFormatStr,"%S");
  }

  if (showAMPM) {
    strcat(timeFormatStr,"%p");
  }

// Print the time string
  strftime(timeStr, maxsize, timeFormatStr, timeStruct); 


// replace a leading space with our special mono-spaced space
  if(timeStr[0] == ' ') {
    timeStr[0] = 150;
  }

// append the timezone
  if (showTimeZone) {
    strcat(timeStr, timeZoneString);
  }
}

// Various Time/Temp Display functions
#define timeStringSize 20
#define scrollDuration 200
#define scrollGap 75

void displayScrollingTime() {
  static char currentTimeStr[timeStringSize];
  static char targetTimeStr[timeStringSize];
  static char previousTimeStr[timeStringSize];
  
  static uint8_t currentCharacterBuffer[characterBufferSize];
  static uint8_t previousCharacterBuffer[characterBufferSize];  
  static uint8_t transitionCharacterBuffer[characterBufferSize];  
  
  uint8_t characterWidth;
  uint8_t characterHeight;
  
  static unsigned long currentScrollStartTime = 0;
  unsigned long currentScrollDelta = 0;
  uint16_t thisSrollStart=0;
  float scrollPercent = 0.0;
  static bool scrolling;
  bool scrollingComplete;

  int displayColumn = 0;
  int displayRow = 0;


  if (currentScrollStartTime == 0) {  // first time only, fill with fixed space
    memset(previousTimeStr,150,timeStringSize);
  }
  
  strcpy(currentTimeStr,"");
  timeString(currentTimeStr, timeStringSize, true, true, false, true, false, true, false);
//  getTimeString(currentTimeStr, timeStringSize);

//      Serial.println("timeFormatLocal12");
//      mx.setFont(fourBySixFont);
//      displayColumn = -1;
  mx.setFont(threeByFiveFont);
  displayColumn = 0;
  displayRow = 0;
  characterHeight = mx.getFontHeight();


  if (!scrolling && (strcmp(currentTimeStr,previousTimeStr) != 0)) {
    strcpy(targetTimeStr,currentTimeStr);
    scrolling = true;
    currentScrollStartTime = millis();
  }
  currentScrollDelta = millis()-currentScrollStartTime;

  scrollingComplete = true;
  for (int i=0; i<strlen(targetTimeStr); i++) {
    if (targetTimeStr[i] == previousTimeStr[i]) {
      displayColumn += overlayCharacter(targetTimeStr[i],displayColumn,displayRow)+1;
    } else { 
      switch (i) {
        case 0:
          thisSrollStart=5*scrollGap;
          break;
        case 1:
          thisSrollStart=4*scrollGap;
          break;
        case 2:
          thisSrollStart=3.5*scrollGap;
          break;
        case 3:
          thisSrollStart=3*scrollGap;
          break;
        case 4:
          thisSrollStart=2*scrollGap;
          break;
        case 5:
          thisSrollStart=1.5*scrollGap;
          break;
        case 6:
          thisSrollStart=1*scrollGap;
          break;
        case 7:
          thisSrollStart=0*scrollGap;
          break;
      }
      scrollPercent = ((float)currentScrollDelta - thisSrollStart) / scrollDuration;
      if (scrollPercent < 1.0) { scrollingComplete = false; }
      
//          Serial.println(scrollPercent);
//          Serial.println(currentStartDelta);
//          Serial.println(scrollStartDelta);
//          Serial.println(scrollDuration);
      
      if (scrollPercent > 1.0) { 
        displayColumn += overlayCharacter(currentTimeStr[i],displayColumn,displayRow)+1;
      } else if (scrollPercent < 0.0) { 
        displayColumn += overlayCharacter(previousTimeStr[i],displayColumn,displayRow)+1;
      } else {
        characterWidth = mx.getChar(currentTimeStr[i], characterBufferSize, currentCharacterBuffer);
        mx.getChar(previousTimeStr[i], characterBufferSize, previousCharacterBuffer);
        transitionCharacter(transitionCharacterBuffer, previousCharacterBuffer, currentCharacterBuffer, characterWidth, characterHeight, scrollPercent, 1);              
        displayColumn += overlayCustomCharacter(transitionCharacterBuffer,characterWidth,displayColumn,displayRow)+1;
      }
    }
  }
  if (scrollingComplete) {
    strcpy(previousTimeStr,currentTimeStr);
    scrolling = false;
  }
}

// Displays the first 4 characters, assumed to be hour and minute, in big bold numbers
// Next 2 characters are displayed in smaller 3x5 font
void displayBoldTime(char *currentTimeStr) {
  
  uint8_t characterWidth;
  uint8_t characterHeight;
  
  int displayColumn = 0;
  int displayRow = 0;
  
  mx.setFont(boldFont);
  displayColumn = 0;
  displayRow = 0;
  characterHeight = mx.getFontHeight();

  for (int i=0; i<4; i++) {
    displayColumn += overlayCharacter(currentTimeStr[i],displayColumn,displayRow)+1;
  }
  
  mx.setFont(threeByFiveFont);
  characterHeight = mx.getFontHeight();
  for (int i=4; i<6; i++) {
    displayColumn += overlayCharacter(currentTimeStr[i],displayColumn,displayRow)+1;
  }
}

// Displays the string in big bold characters
void displayBold(char *str) {
  
  uint8_t characterWidth;
  uint8_t characterHeight;
  
  int displayColumn = 0;
  int displayRow = 0;

  mx.setFont(boldFont);
  displayColumn = 0;
  displayRow = 0;
  characterHeight = mx.getFontHeight();

  for (int i=0; i<strlen(str); i++) {
    displayColumn += overlayCharacter(str[i],displayColumn,displayRow)+1;
  }
}


// End of time/temp display functions


// Choose what to display based on settings/button
#include <OneButton.h>
#define buttonPin D4
OneButton button;

void buttonSetup() {
  button = OneButton(
    buttonPin,   // Input pin for the button
    true,        // Button is active LOW
    true         // Enable internal pull-up resistor
  );
  button.attachClick(menuSingleClick);
  button.attachLongPressStart(menuLongClick);
  button.attachDoubleClick(rtcSync);
}

uint8_t tempCounter = 0;

uint8_t menuState = 0;
#define menuStateNormal 0
#define menuStateDHT 1
#define menuStateSelect 2
#define menuStateCount 3

void menuSingleClick() {
  switch (menuState) {
    case menuStateNormal:
      menuState = menuStateDHT;
      break;
    case menuStateDHT:
      menuState = menuStateNormal;
      break;
    case menuStateSelect:
      timeFormatIncrement();
      break;
  }
  //TEMP
  tempCounter++;
}

void menuLongClick() {
  switch (menuState) {
    case menuStateNormal:
    case menuStateDHT:
      menuState = menuStateSelect;
      break;
    case menuStateSelect:
      menuState = menuStateNormal;
      break;
  }
}

uint8_t timeFormat = 0;
#define timeFormatLocalAMPM 0
#define timeFormatLocalSeconds 1
#define timeFormatLocalTimeZone 2
#define timeFormatLocal24Seconds 3
#define timeFormatLocal24TimeZone 4
#define timeFormatUTCSeconds 5
#define timeFormatUTCTimeZone 6
#define timeFormatScroll 7
#define timeFormatCount 8

void timeFormatIncrement() {
  timeFormat = (timeFormat + 1) % timeFormatCount;
}

void displayTimeString() {
  static char currentTimeStr[timeStringSize]; // needs to be static because we are passing ptr as parameter?

  switch (timeFormat) {
    case timeFormatLocalAMPM:
      timeString(currentTimeStr, timeStringSize, 
                  true,   // showLocalTime
                  false,  // show24Hour
                  false,  // showTimeZone
                  false,   // showSeconds
                  false,  // showColons
                  false,  // flashColons
                  true); // showAMPM
      displayBoldTime(currentTimeStr);
      break;
      
    case timeFormatLocalSeconds:
      timeString(currentTimeStr, timeStringSize, 
                  true,   // showLocalTime
                  false,  // show24Hour
                  false,  // showTimeZone
                  true,   // showSeconds
                  false,  // showColons
                  false,  // flashColons
                  false); // showAMPM
      displayBoldTime(currentTimeStr);
      break;

    case timeFormatLocalTimeZone:
      timeString(currentTimeStr, timeStringSize, 
                  true,   // showLocalTime
                  false,  // show24Hour
                  true,  // showTimeZone
                  false,   // showSeconds
                  false,  // showColons
                  false,  // flashColons
                  false); // showAMPM
      displayBoldTime(currentTimeStr);
      break;
      
    case timeFormatLocal24Seconds:
      timeString(currentTimeStr, timeStringSize, 
                  true,   // showLocalTime
                  true,  // show24Hour
                  false,  // showTimeZone
                  true,   // showSeconds
                  false,  // showColons
                  false,  // flashColons
                  false); // showAMPM
      displayBoldTime(currentTimeStr);
      break;

    case timeFormatLocal24TimeZone:
      timeString(currentTimeStr, timeStringSize, 
                  true,   // showLocalTime
                  true,  // show24Hour
                  true,  // showTimeZone
                  false,   // showSeconds
                  false,  // showColons
                  false,  // flashColons
                  false); // showAMPM
      displayBoldTime(currentTimeStr);
      break;
      
    case timeFormatUTCSeconds:
      timeString(currentTimeStr, timeStringSize, 
                  false,   // showLocalTime
                  true,  // show24Hour
                  false,  // showTimeZone
                  true,   // showSeconds
                  false,  // showColons
                  false,  // flashColons
                  false); // showAMPM
      displayBoldTime(currentTimeStr);
      break;
      
    case timeFormatUTCTimeZone:
      timeString(currentTimeStr, timeStringSize, 
                  false,   // showLocalTime
                  true,  // show24Hour
                  true,  // showTimeZone
                  false,   // showSeconds
                  false,  // showColons
                  false,  // flashColons
                  false); // showAMPM
      displayBoldTime(currentTimeStr);
      break;
      
    case timeFormatScroll:
      displayScrollingTime();
      
    default:
      break;
  }
}

// Display duration for temp and humidity in milliseconds
#define displayTempDuration 6000
#define temperatureStringSize 20
void displayTemperature() {
  static bool active = false;
  static unsigned long startMillis = 0;

  static char temperatureString[temperatureStringSize];
  bool isTemp;
  float temperature;
  char temperatureUnit;

  dhtRead();

  // start timer for short duration display
  if (!active) {
    active = true;
    startMillis = millis();
  }

  // This switches between the 2 states C and F, 3rd state is to reset the menu
  switch ((millis() - startMillis) / (displayTempDuration/2)) {
    case 0:
      temperature = dhtTemperature;
      temperatureUnit = 'C';
      isTemp = true;
      break;
    case 1:
      temperature = dhtTemperatureF;
      temperatureUnit = 'F';
      isTemp = true;
     break;
    case 2:
      temperature = (rtcTemperature() * 9 / 5) + 32;
      temperatureUnit = 'F';
      isTemp = true;
     break;
    case 3:
      sprintf(temperatureString,"%3.0f%%", dhtHumidity);      
      // replace a leading space with our special mono-spaced space
      if(temperatureString[0] == ' ') {
        temperatureString[0] = 150;
      }
      isTemp = false;
     break;
    default:
      active = false;
      menuState = menuStateNormal;
      return;
  }  

  if (isTemp) {
    if (temperature < 100.0) {
      sprintf(temperatureString,"%c%.0f%c%c", (char)150, temperature, (char)144, temperatureUnit);
    } else {
      sprintf(temperatureString,"%.0f%c%c", temperature, (char)144, temperatureUnit);      
    }
  } 

  displayBold(temperatureString);
}


void invertPoint(uint8_t r, uint8_t c) {
  mx.setPoint(r,c,!mx.getPoint(r,c));
}

void displayLoop() {
  mx.clear();
  
  char displayStr[20];
  strcpy(displayStr,"");
  switch (menuState) {
    case menuStateNormal:
      displayTimeString();
      break;
    case menuStateDHT:
      displayTemperature();
      break;
    case menuStateSelect:
      displayTimeString();
      break;
  }

  if (!wifiIsConnected) {
    invertPoint(0,30);
  }

  if (!__nw_time_service.is_valid_ntptime()) {
    invertPoint(0,29);    
  }

  if (!rtcIsInSync()) {
    invertPoint(0,28);
  }

  if (rtcReadError) {
    invertPoint(0,27);    
  }


  if (menuState == menuStateSelect) {
    invertPoint(0,0);
    invertPoint(0,31);
    invertPoint(7,0);
    invertPoint(7,31);
  }
  
  mx.update();
}

// End Display/button

// for OTA updates
#include <ArduinoOTA.h>

void arduinoOtaSetup() {
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// end of OTA handler


void tester() {
  unsigned long a = 1;
  unsigned long b = 2;
  long c;

  Serial.println("tester");
  
  Serial.println(a);
  Serial.println(b);
  c=abs(a-b);
  Serial.println(c);
  c=abs(b-a);
  Serial.println(c);
  
  Serial.println("tester");
}

void setup() {
  Serial.begin(115200);


  frameworkSetup();

//  tester();

  rtcSetup();

  // setup the matrix
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY,0);
  mx.setFont(fourBySixFont);

  buttonSetup();

  // This is at the end to give wifi time to connect
  arduinoOtaSetup();
}

void loop() {
  static unsigned long millisLastDisplay = 0;
  
  // handle all the libraries first
  // Handle OTA updates
  ArduinoOTA.handle();

  // Framework loop
  EwStack.serve();

  button.tick();

  // my code starts here
  if (matrixTestComplete) {
    if (millis() > millisLastDisplay + DELAYTIME) {
      millisLastDisplay = millis();
      displayLoop();
    }
  } else {
    matrixTest();
  }
}
