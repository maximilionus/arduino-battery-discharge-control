#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define POWER_RELAY_PIN 2
#define VOLTAGE_IN_PIN A0
#define VOLTAGE_MIN_RAW 818
#define DISPLAY_ADDR 0x3C


Adafruit_SSD1306 display(128, 64, &Wire, -1);


int getVoltageRaw() {
    return analogRead(VOLTAGE_IN_PIN);
}

void switchRelay(bool enable) {
    if (enable) {
        digitalWrite(POWER_RELAY_PIN, LOW);
    } else {
        digitalWrite(POWER_RELAY_PIN, HIGH);
    }
}


void setup() {
    Serial.begin(9600);
    pinMode(VOLTAGE_IN_PIN, INPUT);
    pinMode(POWER_RELAY_PIN, OUTPUT);

    switchRelay(true);

    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDR);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    Serial.println(F("Discharging"));
}

void loop() {
    int current_voltage = getVoltageRaw();

    Serial.print(current_voltage);
    Serial.println(" raw V");

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("CURR: ")); display.println(current_voltage);
    display.print(F("MIN: ")); display.println(VOLTAGE_MIN_RAW);
    display.display();

    if (current_voltage <= VOLTAGE_MIN_RAW) {
        switchRelay(false);
        Serial.println(F("Minimal charge reached"));

        display.invertDisplay(true);
        display.println(F("> DONE"));
        display.display();

        for (;;);
    }

    delay(10000);
}
