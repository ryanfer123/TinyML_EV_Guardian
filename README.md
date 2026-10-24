# TinyML EV Guardian

An educational EV telemetry simulator and ESP32 inference prototype. One board
sends synthetic battery and driver signals over CAN; another runs three exported
Random Forest classifiers for safety labels, battery health, and driving style.

The training CSVs are synthetic and their generator introduces overlapping classes
and label noise. Model predictions are not evidence of real battery fault detection.
The current repository does not include a verified ESP32 build-size report,
hardware timing measurements, real vehicle evaluation, or protection circuitry.

## Hardware and layout

- Two ESP32 boards with MCP2515 modules, matching 500 kbit/s CAN configuration
  and 8 MHz oscillator settings; CAN High/Low connected with suitable termination.
- `ESP32_1_Sender_Simulator/`: sender sketch, 100 ms update interval, six modes.
- `ESP32_2_Receiver_TinyML_Guardian/`: receiver, feature extraction, exported models.
- `ML_Training/`: synthetic generators, training scripts, CSVs, and model conversion.

Open each sketch in Arduino IDE, install the `mcp_can` library and ESP32 board
support, check CS/INT pins against your wiring, and upload to the corresponding
board. Serial uses 115200 baud. Sender commands `1` through `6` select idle, city,
highway, emergency, thermal-fault, and electrical-fault scenarios.

## Driver wire contract

Each standard CAN data frame contains two 32-bit floats in the native ESP32 byte
order. This protocol assumes matching float representation and endianness.

| CAN ID | First float | Second float |
| --- | --- | --- |
| `0x300` | Throttle spike/variation | Mechanical brake usage (%) |
| `0x301` | Energy consumption (Wh/km) | Regenerative efficiency (0..1) |
| `0x302` | Jerk (m/s³) | Zero padding |

The simulator converts its kWh/km energy value to Wh/km before transmission.
Regen efficiency and jerk are explicit synthetic scenario values. The receiver
extracts exactly five driver features in the CSV column order. Failed and short
CAN reads are rejected before copying floats.

## Reproduce the native checks

A C++11 compiler is sufficient; no Python environment or boards are needed.

```sh
sh tests/run.sh
```

The tests capture frames from the actual sender sketch, verify feature positions
and energy units, check extraction-array boundaries, and parse the actual receiver
and generated headers with lightweight Arduino/CAN doubles. GitHub Actions runs
the same checks. These checks do not compile with the ESP32 toolchain or validate
SPI, CAN delivery, electrical wiring, flash capacity, or inference accuracy.

## Train and export

Use a separate Python environment and install `ML_Training/requirements.txt`.
Run scripts from `ML_Training` because their paths currently depend on that working
directory. Training and conversion overwrite checked-in model artifacts.

```sh
cd ML_Training
python generate_data.py
python train_all_models.py
python convert_to_tinyml.py
```

Only load trusted pickle model files. Existing models were retained in the protocol
fix; they were not retrained or flashed as part of the native checks.

## Remaining engineering work

- Gate each classifier on a complete, fresh set of received sensor frames.
- Align all derived safety features with their training definitions; the current
  thermal-gradient and power-limit heuristics differ from the generator.
- Add grouped/scenario holdouts, per-class metrics, and a recorded model manifest.
- Measure exported model size and inference latency using the real ESP32 toolchain.

Contributions should state the failure being fixed, include a reproducible test,
and distinguish simulated results from device measurements.

## License

The existing project README identifies the project as MIT licensed. A standalone
license file and third-party artifact license inventory remain to be added.
