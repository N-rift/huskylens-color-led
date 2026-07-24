# HuskyLens Color-Triggered LED Indicator

An Arduino project that uses a HuskyLens AI camera in **Color Recognition**
mode to detect one of three trained colors and light a matching LED —
green, red, or yellow — depending on which color is currently in view.

## Overview

The HuskyLens is trained to recognize three colors, saved internally as
IDs `1`, `2`, and `3`. The Arduino continuously polls the HuskyLens over
a serial connection; whichever trained color it sees, the corresponding
LED lights up. If no trained color is visible, all LEDs turn off.

## Hardware Used

* Arduino (Uno or compatible)
* HuskyLens AI camera
* 3x LEDs (green, red, yellow)
* 3x current-limiting resistors (~220Ω) for the LEDs
* Jumper wires + breadboard

## Wiring

| HuskyLens / LED | Arduino Pin |
|---|---|
| HuskyLens TX | Pin 10 (Arduino RX, via SoftwareSerial) |
| HuskyLens RX | Pin 11 (Arduino TX, via SoftwareSerial) |
| HuskyLens VCC | 5V |
| HuskyLens GND | GND |
| Green LED (+) | Pin 5 |
| Red LED (+) | Pin 4 |
| Yellow LED (+) | Pin 3 |
| All LEDs (−) | GND (through a resistor) |

> **Note:** HuskyLens is wired to pins 10/11 via `SoftwareSerial`
> specifically to avoid pins 0/1, which are the Arduino's hardware
> serial (used for USB/Serial Monitor) — using those instead would
> conflict with uploading code and debugging output.

## HuskyLens Setup (do this before running the code)

1. Power on the HuskyLens and swipe to select the **Color Recognition**
   algorithm from the on-device menu.
2. Set the HuskyLens to **UART/Serial protocol mode** (not I2C) in its
   General Settings, since this project communicates over `SoftwareSerial`.
3. Point the camera at your first color, center it in the frame, and
   long-press the learn button to save it — it becomes **ID 1**.
4. Repeat for a second color (**ID 2**) and a third color (**ID 3**).
5. The order you learn the colors in determines their ID number, which
   determines which LED lights up (see the code's `switch` statement).

## Libraries Required

Install via the Arduino IDE Library Manager:
* `HUSKYLENS` (by HuskyLens/DFRobot)
* `SoftwareSerial` (built into the Arduino IDE by default)

## How It Works

1. `huskylens.request()` asks the HuskyLens for its current result over
   serial.
2. If nothing is detected, `huskylens.available()` returns false and all
   LEDs are turned off.
3. If a trained color is detected, `huskylens.read()` returns a result
   with an `ID` matching whichever color it recognized.
4. A `switch` statement maps that ID to the correct LED:
   - ID 1 → Green LED
   - ID 2 → Red LED
   - ID 3 → Yellow LED
5. The loop reruns every ~50ms, so the LED updates in near real-time as
   different colors are shown to the camera.

## Running It

1. Wire everything per the table above.
2. Complete the HuskyLens setup steps (train the 3 colors) first —
   the LEDs won't map correctly otherwise.
3. Open `huskylens_led.ino` in the Arduino IDE, select your board and
   port, and upload.
4. Open the Serial Monitor at **115200 baud** to see live detection IDs
   printed as you show different colors to the camera.

## Troubleshooting

- **"HuskyLens not connected!" printed repeatedly** → check the
  HuskyLens is in UART mode (not I2C), and that TX/RX aren't swapped
  (HuskyLens TX → Arduino pin 10, HuskyLens RX → Arduino pin 11).
- **Wrong LED lights up for a color** → the IDs are assigned in the
  order you trained them, not by color name. Retrain in Color
  Recognition mode if the order doesn't match `case 1/2/3` in the code.
- **LED flickers between correct and off** → normal at the edges of the
  camera's view; move the color more fully into frame.
- **Nothing lights up ever** → confirm all three IDs were actually
  saved on the HuskyLens (check its on-device menu), and that
  `Serial.println(result.ID)` in the Serial Monitor shows a number
  other than 0 when a trained color is shown.

## Author

**V**
