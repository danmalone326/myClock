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


#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Hardware SPI:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 15

// Create a new instance of the MD_Parola class with hardware SPI connection:
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

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

   // Intialize the object:
  myDisplay.begin();
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(0);
  // Clear the display:
  myDisplay.displayClear();
  myDisplay.setTextAlignment(PA_LEFT);
}

unsigned long myTime = 0;
unsigned long lastTime = 0;

void loop() {
  // Handle OTA updates
  ArduinoOTA.handle();

  // Framework loop
  EwStack.serve();

  // custom code starts here
  char timeStr[20];
  time_t t = __nw_time_service.get_ntp_time();
  time_t local = myTZ.toLocal(t, &tcr);
  struct tm *lt = gmtime(&local);
  strftime(timeStr, sizeof timeStr, "%H:%M", lt); 

  myTime = millis() / 1000;
  if (myTime > lastTime) { 
    lastTime = myTime;
    myDisplay.print(timeStr);
  }
}
