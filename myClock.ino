// for OTA updates
#include <ArduinoOTA.h>

/* stack initialize the services in setup and
 * should serve in loop continueously
 */
#define TZ              -8       // (utc + TZ in hours)
#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_MN          60      // use 60 for summer time in some countries
#define DST_SEC         ((DST_MN)*60)
#include <EwingsEsp8266Stack.h>

#include <Timezone.h>   // https://github.com/JChristensen/Timezone
// US Pacific Time Zone (New York, Detroit)
TimeChangeRule myDST = {"PDT", Second, Sun, Mar, 2, -420};    // Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"PST", First, Sun, Nov, 2, -480};     // Standard time = UTC - 5 hours
Timezone myTZ(myDST, mySTD);
TimeChangeRule *tcr;        // pointer to the time change rule, use to get TZ abbrev

#define  DELAYTIME  25  // in milliseconds

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include "clockFont.h"
#include "myFont.h"


// Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 15

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

byte smallDigit[20][4] = 
{
  {0x36,0x41,0x41,0x36},
  {0x00,0x00,0x00,0x36},
  {0x30,0x49,0x49,0x06},
  {0x00,0x49,0x49,0x36},
  {0x06,0x08,0x08,0x36},
  {0x06,0x49,0x49,0x30},
  {0x36,0x49,0x49,0x30},
  {0x00,0x01,0x01,0x36},
  {0x36,0x49,0x49,0x36},
  {0x06,0x49,0x49,0x36},
  {0x36,0x09,0x09,0x36},
  {0x36,0x48,0x48,0x30},
  {0x36,0x41,0x41,0x00},
  {0x30,0x48,0x48,0x36},
  {0x36,0x49,0x49,0x00},
  {0x36,0x09,0x09,0x00}
};

void displaySmallDigit(uint8_t digit, uint8_t startColumn) {
  uint8_t column = startColumn;
  for(int column = startColumn; ((column>=0) && (column>(startColumn-4))); column--) {
    mx.setColumn(column,smallDigit[digit][startColumn-column]);  
  }
}

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

void bounce()
// Animation of a bouncing ball
{
  const int minC = 0;
  const int maxC = mx.getColumnCount()-1;
  const int minR = 0;
  const int maxR = ROW_SIZE-1;

  int  nCounter = 0;

  int  r = 0, c = 2;
  int8_t dR = 1, dC = 1;  // delta row and column

  mx.clear();

  while (nCounter++ < 100)
  {
    mx.setPoint(r, c, false);
    r += dR;
    c += dC;
    mx.setPoint(r, c, true);
    delay(DELAYTIME/2);

    if ((r == minR) || (r == maxR))
      dR = -dR;
    if ((c == minC) || (c == maxC))
      dC = -dC;
  }
}

void matrixTest() {
  uint16_t rows;
  uint16_t columns;

  rows = 8;
  columns = mx.getColumnCount();

  mx.update(MD_MAX72XX::OFF);
  for (int i = 0; i < rows; i++) {
    mx.clear();
    mx.setRow(i,0xff);
    mx.transform(MD_MAX72XX::TFUD);
    mx.update();
    delay(1000/rows);
  }
  for (int i = 0; i < columns; i++) {
    mx.clear();
    mx.setRow(i/(columns/rows),0xff);
    mx.setColumn(i,0xff);
    mx.update();
    delay(1000/columns);
  }
  mx.clear();
}

void binaryTick(unsigned long mil) {
  union mt
  {
     unsigned long value;
     uint8_t bytes[4];
  };

  mt myT;

  myT.value=mil;
  
  int  nCounter = 0;
  
  mx.clear();

  while (nCounter < 4)
  {
    mx.setColumn(nCounter,myT.bytes[nCounter]); 
    nCounter++;
  }
}

void timeMilitaryZone(struct tm *timeStruct, unsigned long currentMilliSeconds, char timeZoneString[]) {
  char timeStr[20];

  strftime(timeStr, sizeof timeStr, "%H%M ", timeStruct); 
  strcat(timeStr, timeZoneString);

  myDisplay.print(timeStr);
  mx.update();
}

void time24Hour(struct tm *timeStruct, unsigned long currentMilliSeconds, char timeZoneString[]) {
  char timeStr[20];

  if (currentMilliSeconds < 500) {
    strftime(timeStr, sizeof timeStr, "%H:%M", timeStruct); 
  } else {
    strftime(timeStr, sizeof timeStr, "%H %M", timeStruct); 
  }

  myDisplay.print(timeStr);
  mx.update();
}

void time12Hour(struct tm *timeStruct, unsigned long currentMilliSeconds, char timeZoneString[])  {
  char timeStr[20];

  if (currentMilliSeconds < 500) {
    strftime(timeStr, sizeof timeStr, "%l:%M", timeStruct); 
  } else {
    strftime(timeStr, sizeof timeStr, "%l %M", timeStruct); 
  }

  if(timeStr[0] == ' ') {
    timeStr[0] = 150;
  }

  myDisplay.print(timeStr);
  mx.update();
}

uint8_t lastSecond = 60;
unsigned long millisLastSecondChange = 0;
bool displayLocalTime = false;

void timeLoop() {
  time_t utcTime;
  time_t localTime;
  TimeChangeRule *tcr;        // pointer to the time change rule, use to get TZ abbrev
  struct tm *timeStruct;
  char timeZoneString[6];
  uint8_t currentSecond;
  unsigned long currentMilliSeconds;

  utcTime = __nw_time_service.get_ntp_time();
  currentSecond = second(utcTime);
  if (currentSecond != lastSecond) {
    millisLastSecondChange = millis();
    lastSecond = currentSecond;
  }
  currentMilliSeconds = millis() - millisLastSecondChange;

  // Another way until later...
  displayLocalTime = (currentSecond < 30);

  if (displayLocalTime) {
    localTime = myTZ.toLocal(utcTime, &tcr);
    timeStruct = gmtime(&localTime);
    strncpy(timeZoneString, tcr -> abbrev, sizeof(timeZoneString)-1 );
  } else {
    timeStruct = gmtime(&utcTime);
    strncpy(timeZoneString, "UTC", sizeof(timeZoneString)-1 );
  }

  switch (int(floor((currentSecond%30)/10))) {
    case 0: 
      timeMilitaryZone(timeStruct, currentMilliSeconds, timeZoneString);
      break;
    case 1:
      time24Hour(timeStruct, currentMilliSeconds, timeZoneString);
      break;
    case 2:
      time12Hour(timeStruct, currentMilliSeconds, timeZoneString);
      break;
  }
}

void timeLoopOrig() {
  time_t utcTime;
  time_t localTime;
  struct tm *lt;
  char timeStr[20];
  uint8_t currentSecond;
  unsigned long currentMilliSeconds;

  utcTime = __nw_time_service.get_ntp_time();
  currentSecond = second(utcTime);
  if (currentSecond != lastSecond) {
    millisLastSecondChange = millis();
    lastSecond = currentSecond;
  }
  currentMilliSeconds = millis() - millisLastSecondChange;

  // Now decide which time format to display
  localTime = myTZ.toLocal(utcTime, &tcr);
  lt = gmtime(&localTime);
  if (currentMilliSeconds < 500) {
    strftime(timeStr, sizeof timeStr, "%H:%M", lt); 
  } else {
    strftime(timeStr, sizeof timeStr, "%H %M", lt); 
  }

  myDisplay.print(timeStr);
  mx.update();
}


void setup() {
  Serial.begin(115200);

  EwStack.initialize();
  __nw_time_service.init_ntp_time();

// OTA Setup
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
// End OTA Setup

  mx.begin();
  matrixTest();

   // Intialize the object:
  myDisplay.begin();
  myDisplay.setFont(clockFont);
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(0);
  // Clear the display:
  myDisplay.displayClear();
  myDisplay.setTextAlignment(PA_LEFT);
}



void loop() {

  // Handle OTA updates
  ArduinoOTA.handle();

  // Framework loop
  EwStack.serve();

  // custom code starts here
  timeLoop();
//  char timeStr[20];
//  time_t t;
//  time_t local;
//  struct tm *lt;
//  time_t t = __nw_time_service.get_ntp_time();
//  time_t local = myTZ.toLocal(t, &tcr);
//  struct tm *lt = gmtime(&local);
//  strftime(timeStr, sizeof timeStr, "%H:%M", lt); 
//
//  showColon = ((millis() / 500) % 2) == 0;
//  if (true) { 
//    t = __nw_time_service.get_ntp_time();
//    local = myTZ.toLocal(t, &tcr);
//    lt = gmtime(&local);
//    if (showColon) {
//      strftime(timeStr, sizeof timeStr, "%H:%M", lt); 
//    } else {
//      strftime(timeStr, sizeof timeStr, "%H %M", lt);      
//    }
//    strftime(timeStr, sizeof timeStr, "%S", lt);      
//    testOverlay(timeStr);
//    
//    myDisplay.print(timeStr);
//    displaySmallDigit((millis()/1000)%16,4);
//    mx.update();
//    binaryTick(millis());
//    lastColon = showColon;
//  }
}
