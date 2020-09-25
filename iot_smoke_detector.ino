#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

//BOARD
const int BAUD_RATE = 115200;
const int SMOKE_SENSOR_PIN = A0; // smoke sensor is connected with the analog pin A0

//BLYNK
const char AUTH[] = "YOUR_BLINK_TOKEN";

// WIFI
const char SSIDD[] = "YOUR_HOME_WIFI_SSID";
const char PASS[] = "YOUR_PASSWORD";

//CONSTANTS
const long INTERVAL = 1000L; //interval in ms to send the data
const int THRESHOLD = 100;  //threshold to trigger the fire alarm

//VARS
SimpleTimer timer;
int data = 0;





void setup() {
  Serial.begin(BAUD_RATE);
  Blynk.begin(AUTH, SSIDD, PASS);
  timer.setInterval(INTERVAL, readAndSend);
}

void loop() {
  timer.run(); // init timer
  Blynk.run(); // init Blynk
}


/**
 * Send the smoke sensor data to Blynk every INTETVAL ms
 */
void readAndSend() {
  data = analogRead(SMOKE_SENSOR_PIN);
  Blynk.virtualWrite(V2, data); //write data from smoke sensor to Blynk virtual pin V2
  if (data > THRESHOLD ) {
    Blynk.notify("Smoke detected!");
  }
}
