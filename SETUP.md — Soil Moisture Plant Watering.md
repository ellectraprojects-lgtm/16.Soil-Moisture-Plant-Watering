# 🌱 Soil Moisture Plant Watering — Setup Guide

## 1. 📋 Requirements

### Hardware

- Soil Moisture Sensor × 1
- 10K Potentiometer × 1
- 10K Resistor × 2
- BC547 Transistor × 1
- 5V Relay Module × 1
- 5V Water Pump × 1
- Red LED 5mm × 1
- 18650 Battery Holder (2-cell) × 1
- 18650 3.7V Batteries × 2
- Breadboard × 1
- Connecting/Jumper Wires
- Suitable 5V regulator/buck converter

### Tools

- Breadboard
- Multimeter
- Screwdriver for potentiometer adjustment
- Water container
- Plant/soil for testing

---

## 2. 🔋 Power Supply Setup

Before connecting anything, identify how the **2×18650 battery holder** is wired.

### If batteries are in series

Two 3.7V cells provide approximately:

```text
3.7V + 3.7V ≈ 7.4V nominal
```

Do **not** connect this directly to the 5V water pump.

Use a suitable buck converter:

```text
2×18650 Battery Pack
        │
        ▼
   Buck Converter
        │
       5V
        │
        ├── Relay/Pump circuit
        └── Control circuit
```

Set and verify the converter output with a multimeter before connecting the pump.

---

## 3. 🌱 Soil Sensor Preparation

1. Connect the soil moisture sensor to the control circuit.
2. Insert the sensing probe into the soil.
3. Keep the probe at a consistent depth.
4. Do not place the electronic portion of the module directly in water.
5. Test the sensor in both dry and wet soil.

The sensor reading can vary depending on soil type, temperature, and probe position.

---

## 4. 🎛️ Potentiometer Calibration

The 10K potentiometer is used to set the moisture switching threshold.

### Calibration

1. Keep the soil relatively dry.
2. Power the circuit.
3. Slowly rotate the potentiometer.
4. Find the point where the relay changes state.
5. Add water to the soil.
6. Check whether the relay switches OFF.
7. Make small adjustments until the desired moisture level is obtained.

Avoid turning the potentiometer rapidly through its entire range during initial testing.

---

## 5. 🔴 LED Setup

Connect the red LED with a suitable current-limiting resistor.

Recommended basic arrangement:

```text
Control Output
     │
     R
     │
   LED
     │
    GND
```

**Important:** Verify the resistor value before powering the LED. A 10K resistor will produce a very low LED current in a typical 5V circuit.

---

## 6. 🔌 Relay and Pump Setup

The relay should be used to switch the pump supply.

Typical pump connection:

```text
5V Supply (+)
      │
     COM
    RELAY
      NO
      │
   Pump (+)

Pump (-)
   │
5V Supply (-)
```

Use **NO (Normally Open)** so the pump remains OFF when the relay is not activated.

---

## 7. 🧪 First Power-On Test

Do not connect the water pump initially.

### Test 1 — Control Circuit

1. Check all wiring.
2. Verify the battery voltage.
3. Verify the regulated 5V output.
4. Power the circuit.
5. Test the soil sensor.
6. Adjust the potentiometer.
7. Listen for the relay switching.

### Test 2 — Pump

After the relay operates correctly:

1. Switch OFF the power.
2. Connect the pump.
3. Place the pump in a water container.
4. Keep the pump outlet away from electronics.
5. Power the system.
6. Test with dry soil.
7. Confirm that the pump turns ON.
8. Wet the soil.
9. Confirm that the pump turns OFF.

---

## 8. ⚡ Multimeter Checks

Before connecting the pump, check:

| Test Point | Expected |
|---|---:|
| Single 18650 cell | ~3.0–4.2V |
| Two cells in series | ~6.0–8.4V |
| Regulated pump supply | ~5V |
| Relay VCC | According to module rating |
| Pump supply | ~5V |
| Ground continuity | Connected |

**Never assume the battery holder is series or parallel. Measure it first.**

---

## 9. 💧 Final Testing

Perform the following test sequence:

```text
Dry Soil
   ↓
Sensor detects dry condition
   ↓
Relay ON
   ↓
Pump ON
   ↓
Water reaches soil
   ↓
Soil becomes wet
   ↓
Relay OFF
   ↓
Pump OFF
```

Repeat the test several times to confirm stable operation.

---

## 10. ⚠️ Safety

- Never connect a 5V pump directly to a 7.4V nominal battery pack.
- Do not short-circuit 18650 cells.
- Use a proper charger for the batteries.
- Keep water away from the electronics.
- Do not operate the pump dry for extended periods.
- Verify relay contact ratings before using the pump.
- Disconnect the battery before changing wiring.
- Always check voltages with a multimeter before connecting components.

## ✅ Setup Complete

Once the sensor, relay, and pump respond correctly to dry and wet soil conditions, the **Soil Moisture Plant Watering System** is ready for enclosure mounting and final testing.