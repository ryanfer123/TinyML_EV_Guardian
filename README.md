# TinyML EV Guardian: Edge AI Battery Diagnostics ⚡🔋

This project implements a **Real-Time Battery Diagnostic System** using **TinyML** for Electric Vehicles (EVs). It uses a dual-ESP32 architecture: one to simulate realistic vehicle sensor data via CAN bus, and another to run parallel ML models on the edge to detect safety, health, and driving profiles.

---

## 📂 Project Structure

### 1. `ESP32_1_Sender_Simulator/` (Vehicle Simulator)
*   **Role:** Simulates the EV sensors (BMS, Motor Controller, etc.) and transmits data via CAN bus.
*   **Hardware:** ESP32 + MCP2515 CAN Module.
*   **Features:**
    *   Simulates realistic physics (Voltage sag, Temp rise, Regenerative Braking).
    *   6 Modes: Idle, City, Highway, Emergency, Thermal Fault, Electrical Fault.
    *   Control via Serial Monitor (Type `1`-`6`).

### 2. `ESP32_2_Receiver_TinyML_Guardian/` (The AI Brain)
*   **Role:** Receives CAN data, parses it, and runs 3 Random Forest models in real-time.
*   **Hardware:** ESP32 + MCP2515 CAN Module.
*   **Models:**
    *   **Safety Monitor:** Detects thermal runaway/faults.
    *   **Health Estimator:** Estimates SOH (Good/Bad).
    *   **Driver Profiling:** Classifies driving context (City/Highway/Panic).

### 3. `ML_Training/` (Python Workflow)
*   **Role:** Contains all scripts to generate data, train models, and convert them to C++.
    *   `generate_data.py`: Creates synthetic training datasets.
    *   `train_all_models.py`: Trains Scikit-Learn Random Forest models.
    *   `convert_to_tinyml.py`: Converts .pkl models to .h C++ headers for the ESP32.

---

## 🚀 How to Run

### Step 1: Hardware Setup
1.  Connect two ESP32s with MCP2515 CAN modules.
2.  Connect CAN High to CAN High, CAN Low to CAN Low.
3.  Ensure 120-ohm termination resistors are enabled on the modules.

### Step 2: Flash the Sender (Simulator)
1.  Open `ESP32_1_Sender_Simulator/ESP32_1_Sender_Simulator.ino`.
2.  Upload to **ESP32 #1**.
3.  Open Serial Monitor (115200 baud).

### Step 3: Flash the Receiver (TinyML Guardian)
1.  Open `ESP32_2_Receiver_TinyML_Guardian/ESP32_2_Receiver_TinyML_Guardian.ino`.
2.  Upload to **ESP32 #2**.
3.  Open Serial Monitor (115200 baud).

### Step 4: Test
1.  On the **Sender** Serial Monitor, type `2` to start City Driving simulation.
2.  On the **Receiver** Serial Monitor, watch the AI classify the incoming data in real-time!

---

## 🛠️ Requirements
*   **Hardware:** 2x ESP32 Dev Boards, 2x MCP2515 CAN Modules.
*   **Software:** Arduino IDE or PlatformIO.
*   **Libraries:** `mcp_can`, `SPI`.

## 📜 License
MIT License.
