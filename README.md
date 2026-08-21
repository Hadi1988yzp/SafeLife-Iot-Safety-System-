# SafeLife-Iot-Safety-System-
Smart safety monitoring system for real-time environmental sensing, motion detection, and GSM-based alerts.
# SafeLife – Smart Safety Monitoring System

**SafeLife** is a prototype safety monitoring system developed using **Arduino Uno**. The system monitors environmental conditions and detects human movement, providing local and remote alerts when an abnormal condition is detected.

The project was developed as an embedded systems and IoT prototype with a focus on low-cost safety monitoring and real-time response.

## Features

* 🌡️ Temperature and humidity monitoring
* 🚶 Human motion detection
* 🔊 Local audible warning
* 📱 GSM-based remote notification
* ⚡ Relay control for external devices
* 🔄 Real-time sensor monitoring
* 🔧 Modular and expandable design

## Hardware

* **Arduino Uno** – Main controller
* **DHT11** – Temperature and humidity sensor
* **PIR Motion Sensor** – Human movement detection
* **SIM800L** – GSM communication
* **Buzzer** – Local alarm
* **Relay Module** – External device control

## System Architecture

```text
             ┌──────────────┐
             │    DHT11     │
             │ Temperature  │
             │  & Humidity  │
             └──────┬───────┘
                    │
                    │
             ┌──────▼───────┐
             │              │
             │  Arduino Uno │
             │              │
             └───┬────┬─────┘
                 │    │
          ┌──────┘    └─────────┐
          ▼                      ▼
      ┌────────┐            ┌─────────┐
      │ Buzzer │            │ SIM800L │
      │  Alarm │            │   GSM   │
      └────────┘            └────┬────┘
                                 │
                                 ▼
                           Remote Alert

             ┌──────────────┐
             │ PIR Sensor   │
             │ Motion       │
             └──────┬───────┘
                    │
                    ▼
               Arduino Uno
                    │
                    ▼
                 Decision
```

## How It Works

1. The **DHT11 sensor** measures temperature and humidity.
2. The **PIR sensor** detects human movement.
3. The **Arduino Uno** processes the sensor data.
4. When a predefined abnormal condition is detected, the system activates the **buzzer**.
5. The **SIM800L GSM module** can send a remote notification.
6. The **relay module** can be used to control an external electrical device.

## Software

The system is programmed using **Arduino C/C++** and developed in the Arduino IDE.

## Technologies

* Arduino Uno
* Arduino C/C++
* Embedded Systems
* IoT
* GSM Communication
* Sensor Integration
* Automation
* Real-Time Monitoring

## Project Structure

```text
SafeLife-IoT-Safety-System/
│
├── README.md
│
├── src/
│   └── SafeLife.ino
│
├── hardware/
│   ├── circuit-diagram.png
│   └── wiring.png
│
├── images/
│   └── prototype.jpg
│
└── docs/
    └── system-architecture.png
```

## Future Development

Future versions of SafeLife can include:

* ESP32-based wireless communication
* Mobile application
* Cloud monitoring
* GPS location tracking
* Battery monitoring
* Additional environmental sensors
* Advanced anomaly detection
* Improved emergency notification system

## Project Status

**Prototype – Completed / Further Development Possible**

The current prototype demonstrates the integration of environmental sensing, motion detection, local alarm, GSM communication, and external device control.

## Author

**Hadi Yazdan**

Mechanical Engineer | Embedded Systems & Robotics

---

⭐ SafeLife is part of my embedded systems and robotics project portfolio.

