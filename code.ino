// =============================================================================
// Automatic Soil Moisture Plant Watering System
// =============================================================================
// Hardware:
//   - Arduino Uno
//   - Soil Moisture Sensor (Analog Output → A0)
//   - 10K Potentiometer (Threshold Adjustment → A1)
//   - 5V Relay Module (IN → D7)
//   - Red 5mm LED (→ D8)
//   - 5V Water Pump (switched by relay, powered from separate supply)
//   - 2×18650 battery pack with regulated 5V output
//
// Wiring Notes:
//   - The relay module switches the pump's separate 5V supply.
//   - The Arduino GPIO pin does NOT directly power the pump.
//   - If your relay module requires a transistor driver (BC547),
//     connect D7 → 10K resistor → BC547 Base, Collector → Relay coil.
//
// Author  : Plant Watering System Example
// Version : 1.0
// =============================================================================

// -----------------------------------------------------------------------------
// RELAY LOGIC CONFIGURATION
// -----------------------------------------------------------------------------
// Set to 'true'  if your relay module is ACTIVE LOW  (signal LOW  = relay ON)
// Set to 'false' if your relay module is ACTIVE HIGH (signal HIGH = relay ON)
// Most common 5V relay modules from Arduino kits are ACTIVE LOW.
// -----------------------------------------------------------------------------
#define RELAY_ACTIVE_LOW true

// -----------------------------------------------------------------------------
// PIN DEFINITIONS
// -----------------------------------------------------------------------------
const int PIN_MOISTURE_SENSOR = A0;  // Soil moisture sensor analog output
const int PIN_POTENTIOMETER   = A1;  // 10K potentiometer for threshold setting
const int PIN_RELAY           = 7;   // Relay module control pin (Digital)
const int PIN_LED             = 8;   // Red status LED (Digital)

// -----------------------------------------------------------------------------
// ADJUSTABLE SYSTEM PARAMETERS
// -----------------------------------------------------------------------------

// How often the sensor is read (milliseconds).
// 2000 ms = read every 2 seconds. Increase for slower response.
const unsigned long SAMPLE_INTERVAL_MS = 2000;

// Hysteresis band (in raw ADC units, 0–1023).
// Prevents rapid ON/OFF relay switching near the threshold.
// Example: if threshold = 600 and HYSTERESIS = 30
//   → Pump turns ON  when soil reading RISES ABOVE (threshold + HYSTERESIS) = 630
//   → Pump turns OFF when soil reading FALLS BELOW (threshold - HYSTERESIS) = 570
// Increase this value if the relay chatters. Decrease for finer control.
const int HYSTERESIS = 30;

// Sensor validation limits.
// Raw ADC values outside this range are treated as sensor errors.
// Valid range for most capacitive/resistive sensors: 0–1023.
const int SENSOR_MIN_VALID = 10;    // Below this → sensor likely disconnected
const int SENSOR_MAX_VALID = 1013;  // Above this → sensor likely short-circuited

// Serial baud rate
const long SERIAL_BAUD_RATE = 9600;

// -----------------------------------------------------------------------------
// GLOBAL VARIABLES
// -----------------------------------------------------------------------------
bool     pumpRunning      = false;  // Tracks current pump state
unsigned long lastSampleTime = 0;   // Timestamp of last sensor reading (millis)

// =============================================================================
// HELPER FUNCTIONS
// =============================================================================

// -----------------------------------------------------------------------------
// setRelay()
// Controls the relay output pin, accounting for active-LOW or active-HIGH logic.
//
// Parameters:
//   turnOn (bool) → true  = turn relay ON  (energise coil, close pump circuit)
//                   false = turn relay OFF (de-energise coil, open pump circuit)
// -----------------------------------------------------------------------------
void setRelay(bool turnOn) {
  if (RELAY_ACTIVE_LOW) {
    // Active-LOW relay: LOW signal energises the coil
    digitalWrite(PIN_RELAY, turnOn ? LOW : HIGH);
  } else {
    // Active-HIGH relay: HIGH signal energises the coil
    digitalWrite(PIN_RELAY, turnOn ? HIGH : LOW);
  }
}

// -----------------------------------------------------------------------------
// setLED()
// Controls the status LED.
//
// Parameters:
//   turnOn (bool) → true = LED ON, false = LED OFF
// -----------------------------------------------------------------------------
void setLED(bool turnOn) {
  digitalWrite(PIN_LED, turnOn ? HIGH : LOW);
}

// -----------------------------------------------------------------------------
// printStatus()
// Prints a formatted status line to the Serial Monitor.
//
// Parameters:
//   soilValue  (int)  → Raw ADC reading from moisture sensor (0–1023)
//   threshold  (int)  → Calculated threshold from potentiometer
//   isDry      (bool) → true = soil is dry, false = soil is wet
//   pumpOn     (bool) → true = pump is running, false = pump is stopped
// -----------------------------------------------------------------------------
void printStatus(int soilValue, int threshold, bool isDry, bool pumpOn) {
  Serial.print("Soil: ");
  Serial.print(soilValue);

  Serial.print(" | Threshold: ");
  Serial.print(threshold);

  Serial.print(" | Status: ");
  Serial.print(isDry ? "DRY" : "WET");

  Serial.print(" | Pump: ");
  Serial.println(pumpOn ? "ON" : "OFF");
}

// =============================================================================
// SETUP — Runs once at power-on or reset
// =============================================================================
void setup() {
  // --- Serial Monitor ---
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("=========================================");
  Serial.println("  Automatic Plant Watering System");
  Serial.println("  Initialising...");
  Serial.println("=========================================");

  // --- Configure Output Pins ---
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LED,   OUTPUT);

  // --- Safe Startup: Ensure pump is OFF before any reading ---
  // This prevents the pump from accidentally running on startup.
  setRelay(false);   // Relay OFF
  setLED(false);     // LED OFF
  pumpRunning = false;

  // --- Analog pins are INPUT by default; no pinMode needed for A0/A1 ---

  // --- Print relay logic mode for confirmation ---
  Serial.print("  Relay Mode: ");
  Serial.println(RELAY_ACTIVE_LOW ? "ACTIVE LOW" : "ACTIVE HIGH");

  Serial.print("  Hysteresis Band: +/- ");
  Serial.println(HYSTERESIS);

  Serial.print("  Sample Interval: ");
  Serial.print(SAMPLE_INTERVAL_MS);
  Serial.println(" ms");

  Serial.println("=========================================");
  Serial.println("  System Ready. Monitoring soil...");
  Serial.println("=========================================");
  Serial.println();

  // Small pause so the user can see the startup messages
  delay(1000);
}

// =============================================================================
// LOOP — Runs repeatedly after setup()
// =============================================================================
void loop() {
  // --- Non-blocking timing using millis() ---
  // Only take a new reading when SAMPLE_INTERVAL_MS has elapsed.
  // This avoids blocking delays and keeps the loop responsive.
  unsigned long currentTime = millis();

  if (currentTime - lastSampleTime >= SAMPLE_INTERVAL_MS) {
    lastSampleTime = currentTime;  // Record when this sample was taken

    // -----------------------------------------------------------------
    // STEP 1: Read the Soil Moisture Sensor (A0)
    // -----------------------------------------------------------------
    // analogRead() returns 0–1023.
    // Dry soil  → higher reading (less conductivity → higher resistance)
    // Wet soil  → lower  reading (more conductivity → lower resistance)
    // Note: This is typical for resistive sensors. Capacitive sensors
    //       may behave differently — adjust threshold direction if needed.
    int soilValue = analogRead(PIN_MOISTURE_SENSOR);

    // -----------------------------------------------------------------
    // STEP 2: Validate Sensor Reading
    // -----------------------------------------------------------------
    // If the reading is outside the expected range, skip this cycle
    // and report the error. This prevents false pump activations caused
    // by a disconnected or short-circuited sensor wire.
    if (soilValue < SENSOR_MIN_VALID || soilValue > SENSOR_MAX_VALID) {
      Serial.print("WARNING: Sensor reading out of valid range (");
      Serial.print(soilValue);
      Serial.println("). Check wiring. Pump held OFF.");

      // Safety: keep pump OFF during sensor fault
      setRelay(false);
      setLED(false);
      pumpRunning = false;

      return;  // Skip the rest of this sample cycle
    }

    // -----------------------------------------------------------------
    // STEP 3: Read the Potentiometer (A1) and Map to Threshold
    // -----------------------------------------------------------------
    // The potentiometer gives 0–1023.
    // We map this to a practical threshold range of 200–900.
    // This avoids extreme thresholds that would keep the pump
    // always ON or always OFF regardless of soil condition.
    int potValue = analogRead(PIN_POTENTIOMETER);
    int threshold = map(potValue, 0, 1023, 200, 900);

    // -----------------------------------------------------------------
    // STEP 4: Apply Hysteresis to Determine Pump State
    // -----------------------------------------------------------------
    // Without hysteresis: if soil ≈ threshold, tiny sensor fluctuations
    // cause rapid relay ON/OFF switching, which damages the relay.
    //
    // With hysteresis:
    //   Pump turns ON  only when reading > (threshold + HYSTERESIS)
    //   Pump turns OFF only when reading < (threshold - HYSTERESIS)
    //   In between → keep current state (no change)
    //
    // Higher soil reading = drier soil (less resistance passes less signal
    // on many resistive modules — verify for your specific sensor).

    int upperBand = threshold + HYSTERESIS;  // Crossing UP   → turn pump ON
    int lowerBand = threshold - HYSTERESIS;  // Crossing DOWN → turn pump OFF

    if (soilValue > upperBand) {
      // Soil is DRY — reading is above the upper hysteresis band
      pumpRunning = true;

    } else if (soilValue < lowerBand) {
      // Soil is WET — reading is below the lower hysteresis band
      pumpRunning = false;

    }
    // else: soilValue is within the hysteresis band → no change to pumpRunning

    // -----------------------------------------------------------------
    // STEP 5: Apply Pump and LED State
    // -----------------------------------------------------------------
    setRelay(pumpRunning);  // Turn relay ON or OFF
    setLED(pumpRunning);    // Mirror pump state on LED

    // -----------------------------------------------------------------
    // STEP 6: Print Status to Serial Monitor
    // -----------------------------------------------------------------
    // soilValue > threshold means DRY for this sensor type
    bool isDry = (soilValue > threshold);
    printStatus(soilValue, threshold, isDry, pumpRunning);

  } // end if (time elapsed)

  // The rest of the loop() runs freely without any blocking.
  // You can add other non-blocking tasks here if needed.

} // end loop()

// =============================================================================
// END OF FILE
// =============================================================================
