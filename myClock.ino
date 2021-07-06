
#include <Wire.h>   // for I2C protocol
#include <ds3231.h>

// For testing
#define  DELAYTIME  25  // in milliseconds


#define TZ              -8       // (utc + TZ in hours)
#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_MN          60      // use 60 for summer time in some countries
#define DST_SEC         ((DST_MN)*60)
//#include <EwingsEsp8266Stack.h>
#include <EwingsEspStack.h>

#include <Timezone.h>   // https://github.com/JChristensen/Timezone
// US Pacific Time Zone (New York, Detroit)
TimeChangeRule myDST = {"PDT", Second, Sun, Mar, 2, -420};    // Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"PST", First, Sun, Nov, 2, -480};     // Standard time = UTC - 5 hours
Timezone myTZ(myDST, mySTD);
TimeChangeRule *tcr;        // pointer to the time change rule, use to get TZ abbrev

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include "clockFont.h"
#include "myFont.h"

#include <string.h>


// Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 15

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

uint16_t findCharacter(uint8_t targetCharacter, MD_MAX72XX::fontType_t font[]) {
  uint8_t fontFormatVersion;
  uint8_t fontFirstCharacter;
  uint8_t fontLastCharacter;
  uint8_t fontHeight;

  uint8_t currentCharacter; 
  uint16_t fontIndex;
  uint16_t result;

//  Serial.println("findCharacter");
  if (pgm_read_byte_near(font) == 'F') {
    fontFormatVersion = pgm_read_byte_near(font+1);
    if (fontFormatVersion == 1) {
      fontFirstCharacter = pgm_read_byte_near(font+2);
      fontLastCharacter = pgm_read_byte_near(font+3);
      fontHeight = pgm_read_byte_near(font+4);
      fontIndex = 5;
    } else {
      fontFirstCharacter = 0;
      fontLastCharacter = 255;
      fontHeight = 8;    
      fontIndex = 7;
    }
  } else {
    fontFormatVersion = 0;
    fontFirstCharacter = 0;
    fontLastCharacter = 255;
    fontHeight = 8;
    fontIndex = 0;
  }
//  Serial.println(fontFormatVersion);

  currentCharacter = fontFirstCharacter;
  result = fontIndex;

//  Serial.println(targetCharacter);
  while (currentCharacter < fontLastCharacter) {
//    Serial.println(currentCharacter);
//    Serial.println(pgm_read_byte_near(clockFont+characterPos));
    if (currentCharacter == targetCharacter) {
      result = fontIndex;
      break;
    }
    fontIndex += 1 + pgm_read_byte_near(font+fontIndex);
    currentCharacter += 1;
  }
//  Serial.println(currentCharacter);
//  Serial.println(result);

  return result;
}

void overlayCharacter(byte character, int8_t startColumn, int8_t startRow, MD_MAX72XX::fontType_t font[]) {
//  Serial.println("overlayCharacter");

  uint16_t characterStartPos = findCharacter(character, font);
  uint8_t characterWidth = pgm_read_byte_near(font+characterStartPos);
  uint16_t characterFirstColumn = characterStartPos + 1;

  uint8_t currentColumn;
  uint8_t updatedColumn;
  uint8_t shiftedCharacter;

//  Serial.println(characterWidth);
  for (int relativeColumn = 0; relativeColumn < characterWidth; relativeColumn++) {
    currentColumn = startColumn - relativeColumn;
    shiftedCharacter = pgm_read_byte_near(font+characterFirstColumn+relativeColumn);
    if (startRow > 0) {
      shiftedCharacter = shiftedCharacter << startRow;
    } else {
      shiftedCharacter = shiftedCharacter >> -startRow;
    }
    updatedColumn = mx.getColumn(currentColumn) | shiftedCharacter;

    mx.setColumn(currentColumn, updatedColumn);
  }
}

char currentChar = ' ';
unsigned long currentCharMillis=0;

void testOverlay(char *timeStr) {
//  Serial.println("testOverlay");
//  Serial.println(clockFont[0]);
//  Serial.println(sizeof(clockFont));

  if (timeStr[1] != currentChar) {
    currentChar = timeStr[1];
    currentCharMillis = millis();
  }
  uint16_t scrollPos = (((millis() - currentCharMillis) % 1000) * 16 / 1000);
  
  mx.clear();
  overlayCharacter(timeStr[0],10,0, clockFont);
  overlayCharacter(timeStr[1],4,0, clockFont);
  overlayCharacter(timeStr[0],26,0, clockFont);


  unsigned long millisSinceChange = millis() - currentCharMillis;
  if (millisSinceChange >= 150) {
    overlayCharacter(timeStr[1],20,0, _sysfontNew);    
  } else {
    char previousChar;
    if (timeStr[1] == '0') {
      previousChar = '9';    
    } else {
      previousChar = timeStr[1] - 1;
    }

    uint16_t scrollPos = (millisSinceChange * 7 / 150) + 1;

    overlayCharacter(previousChar,20,scrollPos, _sysfontNew);    
    overlayCharacter(timeStr[1],20,0-8+scrollPos, _sysfontNew);    

  }
//  mx.transform(MD_MAX72XX::TFUD);
  mx.update();
}

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

// get time from RTC and format
void rtcString(char *timeStr, 
               size_t maxsize, 
               bool showTime,
               bool showDate) {
  static ts t; // time struct
  static float treg;
  DS3231_get(&t);
  treg = DS3231_get_treg();


  if (showTime) {
    sprintf(timeStr,"%d:%d:%d", t.hour,t.min,t.sec);
  } else if (showDate) {
    sprintf(timeStr,"%d/%d/%d", t.mon,t.mday,t.year);    
  } else {
    sprintf(timeStr,"%f", treg);    
  }
  
  return;
}


// get current time in a format based on the parameters
void timeString(char *timeStr, 
                size_t maxsize,
                bool showLocalTime, 
                bool show24Hour, 
                bool showTimeZone, 
                bool showSeconds,
                bool military,
                bool flashColons) {
  time_t utcTime;
  time_t localTime;
  TimeChangeRule *tcr;        // pointer to the time change rule, use to get TZ abbrev
  struct tm *timeStruct;
  char timeZoneString[6];
  uint8_t currentSecond;
  unsigned long currentMilliSeconds;

  utcTime = __nw_time_service.get_ntp_time();
  
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
  char timeFormat[20] = "";

  
  char colonChar[2] = "";
  if(!military) {
    if (flashColons && (currentMilliSeconds < 500)) {
      strcat(colonChar," ");
    } else {
      strcat(colonChar,":");
    }
  }


  if (show24Hour) {
    strcat(timeFormat,"%H");
  } else {
    strcat(timeFormat,"%l");    
  }

  strcat(timeFormat,colonChar);
  strcat(timeFormat,"%M");

  if (showSeconds) {
    strcat(timeFormat,colonChar);
    strcat(timeFormat,"%S");
  }

// Print the time string
  strftime(timeStr, maxsize, timeFormat, timeStruct); 

// replace a leading space with our special mono-spaced space
  if(timeStr[0] == ' ') {
    timeStr[0] = 150;
  }

// append the timezone
  if (showTimeZone) {
    strcat(timeStr, " ");
    strcat(timeStr, timeZoneString);
  }

  
}

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

void dhtTemperatureString(char *str) {
  sprintf(str,"%c%.0f%cC", (char)150, dhtTemperature, (char)144);
}

void dhtTemperatureFString(char *str) {
  if (dhtTemperatureF < 100.0) {
    sprintf(str,"%c%.0f%cF", (char)150, dhtTemperatureF, (char)144);
  } else {
    sprintf(str,"%.0f%cF", dhtTemperatureF, (char)144);      
  }
}

void dhtHumidityString(char *str) {
  sprintf(str,"%.1f%%", dhtHumidity);
}


// end of DHT Sensor

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
}

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
#define timeFormatLocal12 0
#define timeFormatLocal24 1
#define timeFormatUTC 2
#define timeFormatRTC 3
#define timeFormatRTCdate 4
#define timeFormatRTCtemp 5
#define timeFormatCount 6

void timeFormatIncrement() {
  timeFormat = (timeFormat + 1) % timeFormatCount;
}

void getTimeString(char *str, size_t maxsize) {
  switch (timeFormat) {
    case timeFormatLocal12:
      timeString(str, maxsize, true, false, false, true, false, true);
//                bool showLocalTime, 
//                bool show24Hour, 
//                bool showTimeZone, 
//                bool showSeconds,
//                bool military,
//                bool flashColons)      
      break;
    case timeFormatLocal24:
      timeString(str, maxsize, true, true, false, true, false, true);
      break;
    case timeFormatUTC:
      timeString(str, maxsize, false, true, false, true, true, true);
      break;
    case timeFormatRTC:
      rtcString(str, maxsize, true, false);
      break;
    case timeFormatRTCdate:
      rtcString(str, maxsize, false, true);
      break;
    case timeFormatRTCtemp:
      rtcString(str, maxsize, false, false);
      break;
  }  
}

//void rtcString(char *timeStr, 
//               size_t maxsize, 
//               bool showTime,
//               bool showDate) {

// Display duration for temp and humidity in milliseconds
#define displayTempDuration 6000
void getDHTString(char *str, size_t maxsize) {
  static bool active = false;
  static unsigned long startMillis = 0;

  dhtRead();

  if (!active) {
    active = true;
    startMillis = millis();
  }

  switch ((millis() - startMillis) / (displayTempDuration/2)) {
    case 0:
      dhtTemperatureFString(str);
      break;
    case 1:
      dhtHumidityString(str);
      break;
    case 2:
      active = false;
      menuState = menuStateNormal;
      break;
  }  
}

void displayLoop() {
  char displayStr[20];
  strcpy(displayStr,"");
  switch (menuState) {
    case menuStateNormal:
      getTimeString(displayStr, sizeof displayStr);
      break;
    case menuStateDHT:
      getDHTString(displayStr, sizeof displayStr);
      break;
    case menuStateSelect:
      getTimeString(displayStr, sizeof displayStr);
      break;
  }
  myDisplay.print(displayStr);
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


void setup() {
  Serial.begin(115200);

  EwStack.initialize();
  __nw_time_service.init_ntp_time();

  Wire.begin(); // starting I2C for RTC
  DS3231_init(DS3231_INTCN); //register the ds3231 at the default address

  mx.begin();
//  matrixTest();

   // Intialize the object:
  myDisplay.begin();
//  myDisplay.setFont(clockFont);
  myDisplay.setFont(fourWide);
//  myDisplay.setFont(threeBySeven);
  
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(0);
  // Clear the display:
  myDisplay.displayClear();
  myDisplay.setTextAlignment(PA_LEFT);

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
    if (millis() > millisLastDisplay+ 100) {
      millisLastDisplay = millis();
      displayLoop();
    }
  } else {
    matrixTest();
  }
}
