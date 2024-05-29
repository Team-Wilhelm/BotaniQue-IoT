# BotaniQue Smart Plant Pot

Created as an IoT exam project by Júlia Ilášová & Maria Ruth Nielsen

## Overview

BotaniQue aims to simplify plant care by providing real-time monitoring of plant conditions via a Smart Plant Pot. The pot tracks soil moisture, air humidity, temperature, and light levels using various sensors, and displays the plant's status on an OLED screen. The system uses MQTT for data communication between the sensors and a backend server, which calculates and returns the plant's mood.

## Key Features

- **Real-time Monitoring**: Check your plant's status and stats through an OLED screen or the BotaniQue mobile app.
- **Smart Sensors**: Soil moisture, air humidity, temperature, and light levels are tracked.
- **MQTT Communication**: Sensors send data to an MQTT broker, which forwards it to a backend server for processing.

![image](https://github.com/Team-Wilhelm/BotaniQue-IoT/assets/113031776/f7eddca3-441e-4cf8-b9bc-b6b716a55707)

## Technical Setup

- **Hardware**: ESP32 with BME280 sensor, soil moisture sensor, photoresistor, and OLED screen.
- **Software**: Arduino C++ for sensor communication; PubSub library for MQTT.
- **Backend**: .NET server using WebSockets for real-time updates.
- **Frontend**: Flutter-based app for user interaction.

![image](https://github.com/Team-Wilhelm/BotaniQue-IoT/assets/113031776/1a8b7486-1a79-43f8-93b9-c4e834dff3e0)
