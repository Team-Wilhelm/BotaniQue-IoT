// Load Wi-Fi library
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ST7789.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "plant_image.h"


#define SEALEVELPRESSURE_HPA (1013.25)
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

#define OLED_DC 16
#define OLED_CS 4
#define OLED_RESET 17

#define PLANT_MOOD_TOPIC "plant/mood"
#define PLANT_DATA_TOPIC "plant/data"

Adafruit_BME280 bme;                                                  // I2C
Adafruit_ST7789 tft = Adafruit_ST7789(OLED_CS, OLED_DC, OLED_RESET);  // SPI
WiFiClient espClient;
PubSubClient client(espClient);

// WiFi and Flespi credentials
const char* ssid = "";      
const char* password = "";
const char* mqttServer = "mqtt.flespi.io";
const int mqttPort = 1883;
const char* mqttToken = "";

// Base values measured by the sensor
const int airMoisture = 3550;
const int waterMoisture = 1620;

const int soilSensor = 36;

// Data
float temperature;
int pressure;
int humidity;
int soilMoisturePercentage;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  bool status;

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1)
      ;
  }

  tft.init(240, 240, SPI_MODE2);  // Init ST7789 display 240x240 pixel
  tft.setRotation(3);
  tft.drawRGBBitmap(0, 0, plant_bitmap, 240, 240);

  connectToWifi();
  connectToFlespi();

  // TODO: intergrate with WS backend
  // client.subscribe();
  // client.setCallback();
}

void loop() {
  temperature = bme.readTemperature();
  pressure = bme.readPressure();
  humidity = bme.readHumidity();
  soilMoisturePercentage = map(analogRead(soilSensor), airMoisture, waterMoisture, 0, 100);

  // Create a JSON document
  StaticJsonDocument<200> doc;
  doc["temperature"] = temperature;
  doc["pressure"] = pressure;
  doc["humidity"] = humidity;
  doc["soilMoisturePercentage"] = soilMoisturePercentage;

  // Serialize JSON to a buffer
  char buffer[256];
  size_t len = serializeJson(doc, buffer);

  client.publish(PLANT_DATA_TOPIC, buffer, len);
  delay(10000);
}

void connectToWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to the WiFi network");
}

void connectToFlespi() {
  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP32Client", mqttToken, NULL, NULL, 1, false, NULL)) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
