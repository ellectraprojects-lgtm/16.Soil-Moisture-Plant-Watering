# 🌱 Soil Moisture Plant Watering — Wiring Guide

## 1. ⚡ System Wiring Overview

```text
        2×18650 Battery Pack
                 │
                 ▼
          5V Buck Converter
                 │
          ┌──────┴──────┐
          │             │
        +5V            GND
          │             │
          │             ├───────────────┐
          │             │               │
          ▼             ▼               ▼
   Soil Sensor       Relay GND      Control GND
          │
          │ Sensor Output
          ▼
     Control Circuit
          │
          ▼
       BC547
          │
          ▼
      Relay Module
          │
          ▼
      5V Water Pump
```

---

# 2. 🔋 Battery Connection

If the 2-cell holder is connected in **series**:

```text
Battery 1 (+) ─── Battery 2 (-)

Battery Pack:
+ ≈ 7.4V
- = GND
```

Connect the battery pack to a suitable **5V buck converter**.

```text
Battery +  ─────> Buck IN+
Battery -  ─────> Buck IN-

Buck OUT+ ──────> +5V
Buck OUT- ──────> GND
```

### ⚠️ Important

Measure the buck converter output using a multimeter.

Set:

```text
OUT+ to OUT- ≈ 5.0V
```

Do this **before connecting the pump**.

---

# 3. 🌱 Soil Moisture Sensor

For a common soil-moisture module:

| Sensor Pin | Connection |
|---|---|
| VCC | +5V |
| GND | GND |
| AO | Control circuit sensor input |
| DO | Optional threshold output |

If your sensor only has **VCC, GND and signal**, connect the signal according to the sensor module's output type.

```text
Soil Sensor
┌──────────────┐
│ VCC ─────────┼── +5V
│ GND ─────────┼── GND
│ AO  ─────────┼── Sensor signal
└──────────────┘
```

---

# 4. 🎛️ 10K Potentiometer

Use the potentiometer as an adjustable reference.

```text
        +5V
         │
      ┌──┴──┐
      │ 10K │
      │ POT │
      └──┬──┘
         │
         ├──── Reference / Control
         │
        GND
```

### Potentiometer pins

For a typical 3-pin potentiometer:

```text
Pin 1 → +5V
Pin 2 → Control/reference
Pin 3 → GND
```

If clockwise operation is opposite to what you expect, swap Pin 1 and Pin 3.

---

# 5. 🔴 Red LED

The LED should have a **current-limiting resistor**.

```text
Control / Relay indication
          │
       Resistor
          │
       LED Anode
          │
       LED Cathode
          │
         GND
```

### LED polarity

```text
Long leg  → Anode (+)
Short leg → Cathode (-)
```

⚠️ A **10K resistor is unusually high for a normal 5mm LED indicator**, so verify the intended resistor value before final assembly.

---

# 6. 🔧 BC547 Transistor

The BC547 is used as a switching transistor for the relay control.

Typical low-side arrangement:

```text
                 +5V
                  │
                  │
             Relay Coil
                  │
                  │
                  C
                BC547
                  E
                  │
                 GND
```

The control signal goes to the transistor base through an appropriate resistor.

```text
Control Signal
      │
    Resistor
      │
      B
    BC547
```

### BC547 terminals

Do **not** assume the pin order from the transistor's flat side without checking the exact BC547 package/datasheet.

Verify:

```text
Collector
Base
Emitter
```

before inserting the transistor into the breadboard.

---

# 7. 🔌 5V Relay Module

For a standard 5V relay module:

| Relay Pin | Connection |
|---|---|
| VCC | +5V |
| GND | GND |
| IN | BC547/control circuit output |

Typical arrangement:

```text
+5V ───────── Relay VCC
GND ───────── Relay GND
Control ───── Relay IN
```

⚠️ Some relay modules are **active LOW**, while others are **active HIGH**. Test the module before finalizing the logic.

---

# 8. 💧 Water Pump Wiring

Use the relay's **COM** and **NO** terminals.

```text
+5V
 │
 │
 COM
 ┌───────┐
 │ RELAY │
 └───────┘
 NO
 │
 │
 Pump +
 
Pump -
 │
 └────────── GND
```

### Relay terminals

```text
COM → +5V supply
NO  → Pump positive
Pump negative → GND
```

The pump will remain OFF until the relay activates.

---

# 9. 🔗 Complete Wiring

```text
             2×18650 BATTERY
                    │
                    ▼
             5V BUCK CONVERTER
                    │
          ┌─────────┴─────────┐
          │                   │
         +5V                 GND
          │                   │
    ┌─────┼────────┐     ┌────┼───────────┐
    │     │        │     │    │           │
    ▼     ▼        ▼     ▼    ▼           ▼
 Sensor  POT     Relay  Sensor BC547     Pump -
 VCC     +5V      VCC    GND     E
    │     │        │             │
    │     │        │             │
    ▼     ▼        │             │
 Sensor  Reference │             │
 Signal    │       │             │
    │      │       ▼             │
    └──────┴──► Control ──► B    │
                              C ─┘
                              │
                         Relay Coil
                              │
                             +5V


PUMP POWER:

+5V ───── COM [RELAY] NO ───── Pump +
GND ────────────────────────── Pump -
```

---

# 10. 🔍 Recommended Testing Order

Do not connect everything at once.

### Step 1 — Power

```text
Battery → Buck Converter
```

Check for approximately **5V**.

### Step 2 — Sensor

```text
Sensor → +5V / GND
```

Verify the sensor output changes between dry and wet soil.

### Step 3 — Potentiometer

Adjust the threshold and verify the control signal.

### Step 4 — BC547

Check that the transistor switches correctly.

### Step 5 — Relay

Confirm that the relay clicks/switches when the control circuit activates.

### Step 6 — Pump

Finally connect:

```text
+5V → Relay COM
Relay NO → Pump+
Pump− → GND
```

---

# 11. ⚠️ Important Checks

Before powering the complete circuit:

- [ ] Battery polarity checked
- [ ] Battery holder configuration checked
- [ ] Buck converter output checked
- [ ] 5V output confirmed
- [ ] Sensor VCC/GND checked
- [ ] Potentiometer wiring checked
- [ ] BC547 pinout verified
- [ ] Relay VCC/GND checked
- [ ] Relay NO/COM identified
- [ ] Pump polarity checked
- [ ] Common GND confirmed
- [ ] Water kept away from electronics

## ✅ Final Operation

```text
DRY SOIL
   ↓
Sensor detects dry condition
   ↓
Control circuit activates
   ↓
BC547 switches
   ↓
Relay ON
   ↓
Pump ON
   ↓
Water supplied
   ↓
SOIL BECOMES WET
   ↓
Relay OFF
   ↓
Pump OFF
```

**Note:** The exact sensor output polarity and relay trigger polarity depend on the modules used. Verify these two points before permanently assembling the circuit.
