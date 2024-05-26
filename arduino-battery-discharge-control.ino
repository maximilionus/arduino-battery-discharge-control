#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define POWER_RELAY_PIN 2
#define VOLTAGE_IN_PIN A0
#define VOLTAGE_MIN 10.80
#define VOLTAGE_REF 4.9
#define DIV_R1 1975.0
#define DIV_R2 1130.0
#define DISPLAY_ADDR 0x3C


Adafruit_SSD1306 display(128, 64, &Wire, -1);


int getVoltageRaw() {
    return analogRead(VOLTAGE_IN_PIN);
}

float getVoltageVolt() {
    float raw = (float)getVoltageRaw();
    return raw * (VOLTAGE_REF / 1024.0) * ((DIV_R1 + DIV_R2) / DIV_R2);
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
    float current_voltage = getVoltageVolt();

    Serial.print(current_voltage);
    Serial.println(" Volts");

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("CUR ")); display.println(current_voltage);
    display.print(F("MIN ")); display.println(VOLTAGE_MIN);
    display.display();

    if (current_voltage <= VOLTAGE_MIN) {
        switchRelay(false);
        Serial.println(F("Minimal charge reached"));

        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(F("> DONE"));
        display.display();

        for (;;);
    }

    delay(10000);
}
