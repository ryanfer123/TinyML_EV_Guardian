# TinyML EV Guardian: Edge AI Battery Diagnostics ⚡🔋

This project implements a **Real-Time Battery Diagnostic System** using **TinyML (Machine Learning on the Edge)** for Electric Vehicles (EVs). It runs three parallel machine learning models directly on an **ESP32 microcontroller** to analyze sensor data, estimate health, and detect critical safety risks without needing a cloud connection.

## 🚀 Features

### 1. **Safety Monitor (Model A)**
*   **Purpose:** Detects thermal runaway, electrical faults, and pre-failure conditions.
*   **Input Features:** Voltage, Current, Temperature (Pack/Inverter/Ambient), Coolant Flow, Isolation Resistance.
*   **Output Classes:** `Normal`, `Warning` (Thermal Risk), `Critical` (Shutdown).

### 2. **Battery Health Estimator (Model B)**
*   **Purpose:** Estimates the State of Health (SOH) of the battery pack.
*   **Input Features:** SoC, Internal Resistance, Cycle Count, DoD, Cell Imbalance.
*   **Output Classes:** `Good`, `Bad` (Replace/Service).

### 3. **Driver Profiling (Model C)**
*   **Purpose:** Classifies driving behavior tailored to **Indian Road Conditions**.
*   **Input Features:** Speed, Brake Frequency/Intensity, Throttle Variance.
*   **Output Classes:** `City` (Stop-and-Go), `Highway` (Steady), `Emergency` (Panic Braking).

---

## 🛠️ Hardware Requirements
*   **Microcontroller:** ESP32 (DevKit V1 or similar), ESP32-S3, or any Arduino-compatible board with >500KB Flash.
*   **Sensors (Simulated in Code):** BMS Voltage/Current sensors, NTC Thermistors, Hall Effect sensors.

---

## 📂 Project Structure

```bash
TinyML_EV_Guardian/
├── tinyml_models/           # C++ Code for ESP32
│   ├── TinyML_EV_Guardian.ino   # Main Arduino Sketch
│   ├── model_utils.h            # Helper functions for features/labels
│   ├── model_a_safety.h         # Safety Model (Random Forest)
│   ├── model_b_health.h         # Health Model (Random Forest)
│   └── model_c_driver.h         # Driver Model (Random Forest)
├── models/                  # Trained Python Models (.pkl)
├── generate_data.py         # Script to generate synthetic training data
├── train_all_models.py      # Script to train models using Scikit-Learn
├── convert_to_tinyml.py     # Script to convert .pkl -> .h (C++)
└── requirements.txt         # Python dependencies
```

---

## ⚡ How to Run on ESP32

### Option 1: Using Arduino IDE

1.  **Download** this repository.
2.  Navigate to the `tinyml_models` folder.
3.  **Rename** the folder `tinyml_models` to `TinyML_EV_Guardian` (Arduino IDE requires the folder name to match the `.ino` file name).
4.  Open `TinyML_EV_Guardian.ino` in the Arduino IDE.
5.  Select your board: `Tools` > `Board` > `ESP32 Dev Module`.
6.  **Upload** the code to your ESP32.
7.  Open the **Serial Monitor** (Baud Rate: 115200) to see the real-time predictions.

### Option 2: Using PlatformIO (VS Code)

1.  Create a new PlatformIO project for your board (e.g., `esp32dev`).
2.  Copy the contents of `TinyML_EV_Guardian.ino` into `src/main.cpp`.
3.  Copy all `.h` files (`model_a_safety.h`, `model_b_health.h`, etc.) into the `src/` or `include/` folder.
4.  Build and Upload.

---

## 🧠 How to Retrain the Models

If you want to modify the data or retrain the models:

1.  **Install Python Dependencies:**
    ```bash
    pip install -r requirements.txt
    ```

2.  **Generate New Data:**
    ```bash
    python generate_data.py
    ```
    *Generates 3 CSV files with synthetic data (including noise/errors).*

3.  **Train Models:**
    ```bash
    python train_all_models.py
    ```
    *Trains Random Forest classifiers and saves them as .pkl files in `models/`.*

4.  **Convert to C++ (TinyML):**
    ```bash
    python convert_to_tinyml.py
    ```
    *Converts .pkl models into .h C++ header files in `tinyml_models/`.*

---

## 📊 Model Performance (Accuracy)
*   **Safety Model:** ~85% (Realistic confusion between Warning/Normal states)
*   **Health Model:** ~86% (Realistic ambiguity in "Gray Zone" health)
*   **Driver Model:** ~90% (Distinguishes Highway vs City traffic in Indian context)

---

## 📜 License
MIT License. Free to use for educational and commercial purposes.
