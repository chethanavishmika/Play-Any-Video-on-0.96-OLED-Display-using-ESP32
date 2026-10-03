# How to Play Any Video on 0.96" OLED Display using ESP32

A complete step-by-step tutorial on converting, storing, and rendering video clips or custom frame animations on a 0.96-inch monochrome SSD1306 I2C OLED display using an **ESP32 Development Board**.

This project walks through extracting video frames, converting them into 1-bit monochrome byte arrays, storing frame data in ESP32 flash memory (`PROGMEM`), and displaying them smoothly using the `Adafruit_SSD1306` and `Adafruit_GFX` libraries.

---

## 📸 Features

* **Custom Frame Animation Playback:** Play high-FPS video animations directly on a 128x64 / 128x32 OLED module.
* **Minimal Hardware Setup:** Requires only an ESP32 board and a 4-pin I2C OLED display—no SD card module needed for short clips.
* **Efficient Memory Usage:** Efficient storing of byte arrays utilizing ESP32 internal flash memory (`PROGMEM`).

---

## 🛠 Hardware Required

| Component | Quantity | Description |
| :--- | :--- | :--- |
| **ESP32 Development Board** | 1 | ESP32-WROOM-32 / ESP32 Dev |
| **0.96" I2C OLED Display** | 1 | Monochrome SSD1306 128x64 Screen |
| **Breadboard & Wires** | - | Jumper cables for I2C wiring |

---

## 🔌 Wiring & Pin Mapping

Connect the 0.96" I2C OLED display to the default ESP32 I2C pins:

| OLED Display Pin | ESP32 Board Pin | Function |
| :--- | :--- | :--- |
| **GND** | **GND** | Ground Rail |
| **VCC** | **3.3V / 5V** | Power Supply |
| **SCL / SCK** | **GPIO 22** | I2C Clock Line |
| **SDA** | **GPIO 21** | I2C Data Line |

---

## 📚 Required Libraries

Install these libraries via the **Arduino IDE Library Manager** (*Sketch > Include Library > Manage Libraries*):

1. **`Adafruit SSD1306`** by Adafruit
2. **`Adafruit GFX Library`** by Adafruit

For computer:

1. **`Pillow`** : Run cmd "py -m pip install pillow"
2. **`Numpy`** : Run cmd "py -m pip install numpy"

---

## 🚀 How to Run

1. **Prepare Frames:** Extract video frames using tools like `ffmpeg` or Python, scale them to **128x64**, and convert them into C byte arrays using tools like `image2cpp`.
2. **Wire Circuit:** Connect your ESP32 to the OLED display as described in the pinout section above.
3. **Upload Sketch:** Open Arduino IDE, select your ESP32 board, paste the bitmap arrays into the sketch, and upload.
4. **Playback:** The video frames will loop automatically on the display!

---

## 📜 License
This project is open-source under the **MIT License**.
