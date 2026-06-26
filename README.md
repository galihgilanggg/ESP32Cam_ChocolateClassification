# ESP32-CAM Chocolate Object Detection (Kitkat vs Cadbury)

This repository contains the source code for an Object Detection project that identifies two types of chocolate, **Kitkat** and **Cadbury**, using the **ESP32-CAM** module. The machine learning model was trained using Edge Impulse and runs in real-time directly on the edge device (Edge AI).

## 📌 Key Features
1. **Real-Time Object Detection:** The OV2640 camera continuously captures and scans objects in its field of view.
2. **Serial Monitor Output:** When a chocolate is detected (with a confidence score above 0.5), the ESP32 prints the label ("kitkat" or "cadbury") along with its exact confidence value to the Serial Monitor.
3. **Visual Indicators (LEDs):**
   - Detects **Kitkat** ➡️ **Red LED** turns on.
   - Detects **Cadbury** ➡️ **Yellow LED** turns on.

## 🛠️ Hardware Setup

### Required Components
* 1x ESP32-CAM (AI-Thinker) + OV2640 Camera Module
* 1x FTDI Programmer (USB-to-TTL) for uploading the code
* 1x Red LED (Kitkat indicator)
* 1x Yellow LED (Cadbury indicator)
* 2x Resistors (220 ohm or 330 ohm) for the LEDs
* Jumper wires

### Pin Configuration (Wiring)
Connect the external components (LEDs) to the following ESP32-CAM pins:

| Component | ESP32-CAM Pin | Description |
| :--- | :--- | :--- |
| **Red LED** (Positive/Anode) | `GPIO 14` | Kitkat Indicator |
| **Yellow LED** (Positive/Anode) | `GPIO 15` | Cadbury Indicator |
| LED GND (Negative/Cathode) | `GND` | *Always use a resistor in series with the LEDs* |

*Note: Make sure to connect `GPIO 0` to `GND` on the ESP32-CAM when you are about to upload/flash the code via the FTDI programmer.*

## 💻 Software Setup

1. **Install Arduino IDE:** Ensure you are using the latest version.
2. **Install the ESP32 Board:** Add the Espressif board manager URL to your IDE preferences and install the ESP32 package.
3. **Install the Machine Learning Library:** 
   This project uses an exported library from Edge Impulse. You need to add the `.zip` library file (e.g., `ei-galihgilanggg-project-1-arduino-1.0.3.zip`) into your Arduino IDE.
   - Go to Arduino IDE > `Sketch` > `Include Library` > `Add .ZIP Library...`
   - Select your Edge Impulse `.zip` file.

## 🚀 How to Run

1. Clone or download this repository to your local machine.
2. Open the `esp32camera_chocolateclassification.ino` file in the Arduino IDE.
3. Connect the ESP32-CAM to your computer using the FTDI programmer (Flash Mode: connect `GPIO 0` to `GND`).
4. Select the **AI Thinker ESP32-CAM** board from `Tools` > `Board`.
5. Click **Upload**.
6. Once the upload is complete ("Done uploading"), **disconnect the jumper wire between `GPIO 0` and `GND`**.
7. Open the **Serial Monitor** in the Arduino IDE and set the Baud Rate to `115200`.
8. Press the **Reset (RST)** button on the ESP32-CAM board.
9. Point the camera at a Kitkat or Cadbury wrapper. Watch the Serial Monitor print the results and see the LEDs light up accordingly!
