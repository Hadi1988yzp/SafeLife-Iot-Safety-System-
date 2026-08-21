# SafeLife-Iot-Safety-System-
Smart safety monitoring system for real-time environmental sensing, motion detection, and GSM-based alerts.
# SafeLife – Smart Safety Monitoring System

SafeLife is an IoT-based safety monitoring prototype designed to detect abnormal environmental conditions and human movement and provide immediate alerts.

## Features

* 🌡️ Temperature and humidity monitoring
* 🚶 Motion detection
* 🔊 Audible alarm
* 📱 GSM-based alert system
* ⚡ Relay control
* 🔧 Modular and expandable design

## Hardware

* Arduino
* DHT11 Temperature & Humidity Sensor
* PIR Motion Sensor
* SIM800L GSM Module
* Buzzer
* Relay Module

## How It Works

The system continuously monitors environmental conditions and detects human movement.

The Arduino processes the sensor data and activates the appropriate response when an abnormal condition is detected.

The buzzer provides a local warning, while the SIM800L module can be used to send remote alerts.

## System Architecture

```text
DHT11 ──────┐
            │
PIR ────────┼──> Arduino ───> Buzzer
            │
            └───────────────> SIM800L ───> Remote Alert

Arduino ─────────────────────> Relay
```

## Technologies

* Arduino
* C/C++
* Embedded Systems
* IoT
* GSM Communication
* Sensor Integration
* Automation

## Project Status

**Prototype – In Development**

The current version demonstrates the core sensing, processing, alarm, and communication concepts.

## Future Development

Future versions may include:

* ESP32-based wireless connectivity
* Mobile application
* Cloud monitoring
* GPS tracking
* Battery monitoring
* Additional environmental sensors
* Automatic emergency response
* Advanced anomaly detection

## Author

**Hadi Yazdan**

Mechanical Engineer | Embedded Systems & Robotics

---

⭐ This project is part of my embedded systems and robotics portfolio.
