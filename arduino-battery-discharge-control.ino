#define POWER_RELAY_PIN 2
#define VOLTAGE_IN_PIN A0
#define VOLTAGE_MIN_RAW 818


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
    Serial.println(F("Discharging started"));
}

void loop() {
    int current_voltage = getVoltageRaw();

    Serial.print(current_voltage);
    Serial.println(" raw V");

    if (current_voltage <= VOLTAGE_MIN_RAW) {
        switchRelay(false);
        Serial.println(F("Minimal charge reached, relay off"));
        while (true) {}
    }

    delay(10000);
}
