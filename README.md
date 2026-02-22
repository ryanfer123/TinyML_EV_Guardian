# TinyML EV Guardian

An embedded project that leverages Tiny Machine Learning (TinyML) for smart monitoring and protection of Electric Vehicles (EV). The aim is to demonstrate how ML models can run efficiently on tiny, power-constrained microcontrollers to monitor, predict, and react to EV state or environment events in real-time.

## Features

- **Real-time anomaly detection** (e.g., battery, motion, temperature)
- **Low-power ML inference** on microcontrollers
- **Alerts & notifications** on unsafe or anomalous events
- Easy integration with standard EV hardware sensors

## Hardware Requirements

- A microcontroller (e.g., Arduino Nano 33 BLE Sense, ESP32)
- Supported sensors (accelerometer, temperature, voltage, current etc.)
- Optional: WiFi, Bluetooth module for alerts

## Software Requirements

- [TensorFlow Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers)
- Arduino IDE or PlatformIO (if applicable)
- Python (for model training, if included)
- C/C++

## Getting Started

### 1. Clone this repository
```sh
git clone https://github.com/ryanfer123/TinyML_EV_Guardian.git
cd TinyML_EV_Guardian
```

### 2. Train or Download the Model

- Train your model using the provided notebooks/scripts **OR**
- Use the provided default model ([model.tflite](model.tflite), if available)

### 3. Deploy to Hardware

- Open the source code in Arduino IDE/PlatformIO
- Upload the code and model to your board
- Connect the required sensors

### 4. Test & Monitor

- Test by simulating various vehicle states or anomalies
- Observe LED indicators, serial output, or wireless notifications

## Repository Structure

```
/src          # Main source code for embedded device
/model        # Model training scripts, datasets, pre-trained models
/notebooks    # Jupyter notebooks for model development
/README.md    # You're here!
```

## Usage Example

```cpp
// Pseudo-code snippet
if(model.predict(sensor_data) == ANOMALY) {
    alert_user();
    shutdown_sequence();
}
```

## Contributing

1. Fork this repository
2. Create a feature branch (`git checkout -b feature`)
3. Commit your changes
4. Push to the branch and open a Pull Request

## License

[MIT](LICENSE)

## Acknowledgements

- TensorFlow Lite for Microcontrollers
- [Edge Impulse](https://www.edgeimpulse.com/)
- Open source EV projects

---

*Project maintained by [ryanfer123](https://github.com/ryanfer123)*