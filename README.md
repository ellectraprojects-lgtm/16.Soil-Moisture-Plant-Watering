# 🌱 Soil Moisture Plant Watering System

## 📌 Project Overview

The **Soil Moisture Plant Watering System** is an automatic plant-watering project that detects when the soil becomes dry and activates a **5V water pump** to supply water to the plant.

The soil moisture sensor detects the moisture condition, while the control circuit uses a **10K potentiometer, BC547 transistor, and 5V relay module** to control the pump. An LED can be used as a watering/status indicator.

This project is suitable for beginner electronics, school/college projects, and small indoor plant automation.

## 🎯 Objectives

- Detect soil moisture automatically.
- Turn the water pump ON when the soil is dry.
- Turn the pump OFF when the soil has sufficient moisture.
- Adjust the moisture trigger level using a 10K potentiometer.
- Provide an LED indication when watering is active.
- Operate from rechargeable 18650 batteries.

## 🧩 Components Required

| Component | Qty |
|---|---:|
| Soil Moisture Sensor | 1 |
| Connecting Wires | 1 set |
| 2×18650 Battery Holder | 1 |
| 18650 3.7V Battery | 2 |
| 5V Water Pump | 1 |
| Red LED 5mm | 1 |
| 10K Potentiometer | 1 |
| 10K Resistor | 2 |
| 5V Relay Module | 1 |
| BC547 Transistor | 1 |
| Breadboard | 1 |
| Jumper Wires | 1 set |

## ⚙️ Working Principle

The soil moisture sensor continuously monitors the condition of the soil.

### When the soil is dry

1. The sensor detects low moisture.
2. The control circuit compares the sensor signal with the preset threshold.
3. The BC547 transistor drives the relay.
4. The relay switches ON the water pump.
5. Water is supplied to the plant.
6. The red LED indicates that watering is active.

### When the soil becomes wet

1. The sensor detects sufficient moisture.
2. The control circuit switches the relay OFF.
3. The water pump stops.
4. The LED turns OFF.

This closed-loop approach is commonly used in automatic irrigation projects, where a moisture reading is compared against a threshold to control a relay-driven pump.

## 🔋 Power Supply

The project uses two rechargeable **3.7V 18650 batteries**.

**Important:** Check the battery-holder configuration before connecting the pump.

- If the holder connects the batteries **in series**, the pack is approximately **7.4V nominal** and must **not be connected directly to a 5V pump**.
- A suitable **5V buck converter/regulator** is required to safely power the 5V pump.
- If the batteries are connected in parallel, the voltage remains approximately **3.7V**, which may also be insufficient for a 5V pump.

A 5V pump should therefore have a properly regulated 5V supply.

## 💧 Pump Control

The relay acts as an electrically controlled switch.

Typical pump-side connection:

```text
5V Supply (+)
     │
     │
    COM
   Relay
    NO
     │
     │
  Pump (+)

Pump (-)
     │
5V Supply (-)
```

The **NO (Normally Open)** contact keeps the pump OFF until the relay is activated.

## 🎛️ Moisture Adjustment

The **10K potentiometer** can be used to adjust the moisture threshold.

Calibration procedure:

1. Place the soil sensor in dry soil.
2. Observe the sensor output.
3. Place the sensor in properly wet soil.
4. Adjust the potentiometer until the desired switching point is reached.
5. Test the pump several times.
6. Fine-tune the threshold if necessary.

The exact sensor values depend on the sensor type and soil conditions, so calibration is recommended rather than relying on a fixed threshold.

## 🔴 LED Indicator

The red LED can indicate the watering state.

```text
Pump OFF → LED OFF
Pump ON  → LED ON
```

Use a current-limiting resistor with the LED. A **10K resistor is much higher than normally required for a 5mm LED**, so verify the intended LED-resistor circuit before assembling it.

## 🧠 Role of Main Components

| Component | Function |
|---|---|
| Soil Moisture Sensor | Detects soil moisture |
| 10K Potentiometer | Sets moisture threshold |
| BC547 | Transistor switching/driver |
| 5V Relay | Switches the pump |
| 5V Pump | Supplies water |
| Red LED | Watering/status indication |
| 10K Resistors | Bias/control components |
| 18650 Batteries | Portable power source |
| Breadboard | Circuit prototyping |

## ⚠️ Important Safety Notes

- Do **not** connect a 5V pump directly to a 7.4V battery pack.
- Use a suitable 5V regulator/buck converter when required.
- Keep water away from the breadboard, batteries, relay module, and other electronics.
- Do not short-circuit 18650 batteries.
- Use protected, properly rated rechargeable cells and a suitable charger.
- Confirm the relay module's operating voltage before connecting it.
- Test the control circuit before connecting the pump.

## 🚀 Possible Improvements

- Add an Arduino/ESP32 for digital control.
- Display moisture percentage on an LCD/OLED.
- Add a water-level sensor to the reservoir.
- Add a manual ON/OFF button.
- Add a buzzer for low-water alerts.
- Add Wi-Fi monitoring using ESP32.
- Use a capacitive soil-moisture sensor for better long-term durability.

## 📚 Project Applications

- Indoor plant watering
- Home gardening
- Small greenhouse systems
- Smart agriculture demonstrations
- Electronics educational projects
- Automatic irrigation prototypes

## ✅ Expected Result

The completed system should automatically:

**Dry Soil → Relay ON → Pump ON → Plant Watered → Soil Wet → Relay OFF → Pump OFF**

The system should be calibrated for the actual soil and sensor being used before normal operation.
