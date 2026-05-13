/************************************************************
   ESP32 Battery Monitor + OLED + Blynk IoT
 ************************************************************/

#define BLYNK_TEMPLATE_ID "TMPL3EmB2ZwQO"
#define BLYNK_TEMPLATE_NAME "Battery Monitor"
#define BLYNK_AUTH_TOKEN "Zi9CGWzXSXVMGDepdobMPLQVoz1p1JiY"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- WiFi Credentials ----------------
char ssid[] = "Oneplus Nord CE4 5G";
char pass[] = "9gpjhvji";

// ---------------- OLED Config ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------- Pin Definitions ----------------
#define ADC_PIN      34
#define GREEN_LED    26
#define RED_LED      27

// ---------------- ADC Config ----------------
#define DIVIDER_RATIO  2.0f
#define ADC_REF_V      3.3f
#define ADC_RESOLUTION 4095.0f

// ---------------- Battery Table ----------------
const float voltageTable[] = {
  3.00, 3.20, 3.40, 3.60, 3.70,
  3.80, 3.90, 4.00, 4.10, 4.20
};

const float socTable[] = {
  0, 5, 10, 25, 40,
  55, 70, 82, 92, 100
};

const int TABLE_SIZE = 10;

// ---------------- Threshold ----------------
#define LOW_BATTERY_SOC 20
#define SAMPLE_COUNT 10

BlynkTimer timer;

// =====================================================
// Read Battery Voltage
// =====================================================

float readBatteryVoltage() {

  long sum = 0;

  for (int i = 0; i < SAMPLE_COUNT; i++) {
    sum += analogRead(ADC_PIN);
    delay(5);
  }

  float avgADC = sum / (float)SAMPLE_COUNT;

  float adcVoltage =
    (avgADC / ADC_RESOLUTION) * ADC_REF_V;

  return adcVoltage * DIVIDER_RATIO;
}

// =====================================================
// Voltage to SOC Conversion
// =====================================================

float voltageToSOC(float voltage) {

  if (voltage <= voltageTable[0])
    return socTable[0];

  if (voltage >= voltageTable[TABLE_SIZE - 1])
    return socTable[TABLE_SIZE - 1];

  for (int i = 0; i < TABLE_SIZE - 1; i++) {

    if (voltage >= voltageTable[i] &&
        voltage <= voltageTable[i + 1]) {

      float ratio =
        (voltage - voltageTable[i]) /
        (voltageTable[i + 1] - voltageTable[i]);

      return socTable[i] +
             ratio * (socTable[i + 1] - socTable[i]);
    }
  }

  return 0;
}

// =====================================================
// Battery Icon
// =====================================================

void drawBatteryIcon(int x, int y, int soc) {

  display.drawRect(x, y, 28, 14, WHITE);

  display.fillRect(x + 28, y + 4, 3, 6, WHITE);

  int fillWidth = (int)(24 * soc / 100.0f);

  if (fillWidth > 0) {
    display.fillRect(x + 2, y + 2,
                     fillWidth, 10, WHITE);
  }

  if (soc <= LOW_BATTERY_SOC) {
    display.setCursor(x + 10, y + 3);
    display.print("!");
  }
}

// =====================================================
// Update OLED
// =====================================================

void updateDisplay(float voltage, int soc) {

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("Battery Monitor");

  display.drawLine(0, 10, 128, 10, WHITE);

  drawBatteryIcon(48, 14, soc);

  display.setTextSize(2);

  String socStr = String(soc) + "%";

  int textWidth = socStr.length() * 12;

  display.setCursor(
    (SCREEN_WIDTH - textWidth) / 2,
    32
  );

  display.print(socStr);

  display.setTextSize(1);

  display.setCursor(0, 52);

  display.print("Volt: ");
  display.print(voltage, 2);
  display.print("V");

  display.display();
}

// =====================================================
// LEDs
// =====================================================

void updateLEDs(int soc) {

  if (soc <= LOW_BATTERY_SOC) {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

  } else {

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
}

// =====================================================
// Send Data to Blynk
// =====================================================

void sendData() {

  float voltage = readBatteryVoltage();

  int soc = (int)voltageToSOC(voltage);

  soc = constrain(soc, 0, 100);

  // OLED Update
  updateDisplay(voltage, soc);

  // LED Update
  updateLEDs(soc);

  // Serial Monitor
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V | SOC: ");
  Serial.print(soc);
  Serial.println("%");

  // ---------------- Blynk ----------------

  Blynk.virtualWrite(V0, voltage);

  Blynk.virtualWrite(V1, soc);

  if (soc <= LOW_BATTERY_SOC) {
    Blynk.virtualWrite(V2, "LOW BATTERY");
  }
  else if (soc > 80) {
    Blynk.virtualWrite(V2, "FULL");
  }
  else {
    Blynk.virtualWrite(V2, "GOOD");
  }
}

// =====================================================
// Setup
// =====================================================

void setup() {

  Serial.begin(115200);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // OLED Start
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS)) {

    Serial.println("OLED failed");

    while (1);
  }

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(10, 20);

  display.print("Connecting WiFi");

  display.display();

  // WiFi + Blynk Connection
  Blynk.begin(
    BLYNK_AUTH_TOKEN,
    ssid,
    pass
  );

  // Timer every 2 sec
  timer.setInterval(2000L, sendData);

  // Startup Screen
  display.clearDisplay();

  display.setCursor(10, 20);
  display.print("Blynk Connected");

  display.display();

  delay(2000);

  Serial.println("Battery Monitor Started");
}

// =====================================================
// Main Loop
// =====================================================

void loop() {

  Blynk.run();

  timer.run();
}
