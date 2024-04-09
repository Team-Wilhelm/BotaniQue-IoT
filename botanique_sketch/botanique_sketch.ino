// Load Wi-Fi library
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ST7789.h>
#include "plant_image.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 16
#define OLED_CS 4
#define OLED_RESET 17

Adafruit_BME280 bme;                                                  // I2C
Adafruit_ST7789 tft = Adafruit_ST7789(OLED_CS, OLED_DC, OLED_RESET);  // SPI

// Replace with your network credentials
const char* ssid = "";      //Your network's SSID
const char* password = "";  //Your network's password

const int soilSensor = 36;

const int airMoisture = 3550;
const int waterMoisture = 1620;

float p = 3.1415926;

// Variable to store the HTTP request
String header;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  //status = bme.begin();
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1)
      ;
  }

  tft.init(240, 240, SPI_MODE2);  // Init ST7789 display 240x240 pixel
  tft.setRotation(3);
  tft.drawRGBBitmap(0, 0, plant_bitmap, 240, 240);

  // Connect to Wi-Fi network with SSID and password
  /*Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  */
}

void loop() {
  Serial.print(bme.readTemperature());
  Serial.print(" *C\n");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.print(" hPa\n");
  Serial.print(bme.readHumidity());
  Serial.print(" %\n");
  int soilmoisturepercent = map(analogRead(soilSensor), airMoisture, waterMoisture, 0, 100);
  Serial.print(soilmoisturepercent);
  Serial.print(" %\n");
  delay(1000);
}
