# IoT-Based Smart Battery Monitoring System using ESP32, OLED & Blynk Cloud

![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)
![GitHub issues](https://img.shields.io/github/issues/username/repo.svg)
![GitHub forks](https://img.shields.io/github/forks/username/repo.svg)

---

## 📌 Project Overview

This is a real-time **IoT-based battery monitoring system** using an ESP32 microcontroller, an SSD1306 OLED display, and the Blynk IoT cloud platform.  

The system continuously monitors a lithium-ion battery voltage, estimates its **State of Charge (SoC)**, and displays the information **locally on the OLED** and **remotely on the Blynk mobile dashboard**.

**Key Concepts Demonstrated:**
- Embedded Systems
- Internet of Things (IoT)
- Cloud Connectivity
- Battery Analytics
- Wireless Monitoring

**Applications include:**
- Electric Vehicle (EV) battery systems
- Solar energy storage
- UPS monitoring systems
- Smart energy management
- Embedded IoT research projects

---

## 🚀 Features

✅ Real-time battery voltage monitoring  
✅ Battery percentage (SoC) estimation  
✅ OLED local display visualization  
✅ Remote cloud monitoring using Blynk IoT  
✅ WiFi connectivity using ESP32  
✅ Low battery LED indication  
✅ Serial monitor debugging output  
✅ Lightweight embedded implementation  

---

## 🧰 Components Used

| Component             | Quantity | Purpose                        |
|----------------------|----------|--------------------------------|
| ESP32 Development Board | 1      | Main controller                |
| SSD1306 OLED Display    | 1      | Display battery information    |
| Li-ion Battery         | 1      | Power source                   |
| LEDs (Green & Red)     | 2      | Status indication              |
| Resistors (220Ω)       | 2      | Voltage divider                |
| Breadboard             | 1      | Prototyping                    |
| Jumper Wires           | Multiple| Connections                    |

---

## 🖼️ Project Images

Hardware Setup:  
![Hardware Setup](images/hardware_setup.jpg)

OLED Display Output:  
![OLED Output](images/oled_output.jpg)

Blynk IoT Dashboard:  
![Blynk Dashboard](images/blynk_dashboard.jpg)

Circuit Diagram:  
![Circuit Diagram](images/circuit_diagram.png)

System Architecture:  
![System Architecture](images/system_architecture.png)

---

## 🔋 Working Principle

1. Battery voltage is measured using the ESP32 ADC pin through a voltage divider.  
2. ESP32 converts ADC values into real battery voltage.  
3. A **lookup-table-based SoC algorithm** estimates battery percentage.  
4. Data is:
   - Displayed on OLED
   - Sent wirelessly over WiFi
   - Uploaded to Blynk Cloud  

**LED Indications:**
- 🟢 Green → Battery healthy  
- 🔴 Red → Low battery  

---

## ☁️ Blynk IoT Integration

| Datastream         | Virtual Pin | Type    |
|-------------------|-------------|--------|
| Battery Voltage    | V0          | Double |
| Battery Percentage | V1          | Integer|
| Battery Status     | V2          | String |

---

## 📟 OLED Display Information

- Battery percentage  
- Battery voltage  
- Battery icon visualization  
- Battery status  

---

## 🔌 Pin Connections

**OLED Connections**

| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3.3V      |
| GND      | GND       |
| SDA      | GPIO21    |
| SCL      | GPIO22    |

**LED Connections**

| LED         | ESP32 Pin |
|------------|-----------|
| Green LED  | GPIO26    |
| Red LED    | GPIO27    |

**Battery Divider**

| Component       | ESP32 Pin |
|----------------|-----------|
| Divider Output | GPIO34    |

---

## 💻 Software & Libraries

- **IDE:** Arduino IDE  
- **Libraries:** 
  - Blynk
  - Adafruit SSD1306
  - Adafruit GFX
  - WiFi  

**Arduino IDE Download:** [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

---

## 🧠 State of Charge (SoC) Calculation

| Voltage (V) | Estimated SoC (%) |
|------------|------------------|
| 4.20       | 100              |
| 4.10       | 92               |
| 4.00       | 82               |
| 3.90       | 70               |
| 3.80       | 55               |
| 3.70       | 40               |
| 3.60       | 25               |
| 3.40       | 10               |
| 3.20       | 5                |
| 3.00       | 0                |

---

## 📱 Mobile Dashboard

The Blynk dashboard provides:
- Live voltage visualization  
- Battery percentage monitoring  
- Battery status monitoring  
- Cloud-based remote access  

---

## 🖥️ Serial Monitor Output
