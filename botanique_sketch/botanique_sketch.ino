// Load Wi-Fi library
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ST7789.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <BotaniqueSecrets.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240

#define OLED_DC 16
#define OLED_CS 15
#define OLED_RESET 17
#define BUTTON 12
#define LIGHT 34

#define PLANT_MOOD_TOPIC "plant/mood"
#define PLANT_DATA_TOPIC "plant/data"

Adafruit_BME280 bme;                                                  // I2C
Adafruit_ST7789 tft = Adafruit_ST7789(OLED_CS, OLED_DC, OLED_RESET);  // SPI
WiFiClient espClient;
PubSubClient client(espClient);

// Base values measured by the sensor
const int airMoisture = 3550;
const int waterMoisture = 1620;
const int soilSensor = 36;

// Mood values
int currentMood = 2;
String currentMoodString = "neutral";
String moods[] = { "dead", "unhappy", "neutral", "content", "thriving" };

// Data
float temperature;
int pressure;
int humidity;
int soilMoisturePercentage;
int lightLevel;

int loopCounter = 0;

void setup() {
  pinMode(BUTTON, INPUT_PULLDOWN);
  Serial.begin(115200);
  while (!Serial) {}
  bool status;

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1)
      ;
  }

  connectToWifi();
  connectToFlespi();

  client.subscribe(PLANT_MOOD_TOPIC);
  client.setCallback(displayPlantMood);

  tft.init(240, 240, SPI_MODE2);  // Init ST7789 display 240x240 pixel
  tft.setRotation(1);
  displayMoodEmoji(currentMood);
}

void loop() {
  client.loop();
  loopCounter++;

  temperature = bme.readTemperature();
  pressure = bme.readPressure();
  humidity = bme.readHumidity();
  soilMoisturePercentage = map(analogRead(soilSensor), airMoisture, waterMoisture, 0, 100);
  lightLevel = analogRead(LIGHT);

  if (digitalRead(BUTTON) == HIGH) {
    drawStatsScreen();
  }

  if (loopCounter > 10) {
    loopCounter = 0;
    // Create a JSON document
    StaticJsonDocument<200> doc;
    doc["temperature"] = temperature;
    doc["pressure"] = pressure;
    doc["humidity"] = humidity;
    doc["soilMoisturePercentage"] = soilMoisturePercentage;
    doc["lightLevel"] = lightLevel;

    // Serialize JSON to a buffer
    char buffer[256];
    size_t len = serializeJson(doc, buffer);

    client.publish(PLANT_DATA_TOPIC, buffer, len);
  }

  delay(1000);
}

void displayPlantMood(const char* topic, byte* payload, unsigned int length) {
  // Create a buffer to hold the payload as a string
  char payloadStr[length + 1];
  memcpy(payloadStr, payload, length);
  payloadStr[length] = '\0';  // Null-terminate the string

  // Parse the JSON payload
  DynamicJsonDocument doc(1024);  // Adjust the size based on payload
  DeserializationError error = deserializeJson(doc, payloadStr);

  // Extract information from the JSON document
  const int mood = doc["mood"];
  if (mood != currentMood) {
    currentMood = mood;
    currentMoodString = moods[mood];
    displayMoodEmoji(currentMood);
  }

  // Check for parsing errors
  if (error) {
    Serial.print("JSON parsing error: ");
    Serial.println(error.c_str());
    return;
  }
}
