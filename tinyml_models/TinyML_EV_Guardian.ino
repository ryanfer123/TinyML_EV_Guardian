#include <Arduino.h>
#include "model_a_safety.h"
#include "model_b_health.h"
#include "model_c_driver.h"
#include "model_utils.h"

/*
 * TinyML EV Guardian - ESP32 Firmware
 * -----------------------------------
 * Runs 3 machine learning models in parallel on the edge:
 * 1. Safety Monitor: Detects thermal runaway/faults
 * 2. Battery Health: Estimates SOH (Good/Bad)
 * 3. Driver Profile: Classifies driving context (City/Highway/Panic)
 *
 * Optimizations:
 * - Namespace isolation for model classes
 * - Feature extraction helper utilities
 * - Non-blocking loop structure
 */

// Model Instances
SafetyModel::Eloquent::ML::Port::RandomForest safety_classifier;
HealthModel::Eloquent::ML::Port::RandomForest health_classifier;
DriverModel::Eloquent::ML::Port::RandomForest driver_classifier;

// Simulation Variables
unsigned long last_inference_time = 0;
const unsigned long INFERENCE_INTERVAL = 2000; // Run every 2 seconds

void setup() {
  Serial.begin(115200);
  while(!Serial) delay(10);

  Serial.println("
========================================");
  Serial.println("  TinyML EV Guardian System Booting...  ");
  Serial.println("========================================");
  
  // Initialize sensors here...
  // CAN.begin(...)
  // TempSensors.begin(...)
  
  Serial.println("Models Loaded Successfully.");
  Serial.println("System Ready.
");
}

void loop() {
  if (millis() - last_inference_time > INFERENCE_INTERVAL) {
    last_inference_time = millis();
    
    Serial.println("
--- [Running Diagnostics] ---");

    // ==========================================
    // 1. SAFETY CHECK (High Priority)
    // ==========================================
    // Simulate real-time sensor data
    SafetySensors safety_in = {
      .pack_voltage = 350.5,
      .pack_current = 60.2,
      .cell_max_v = 4.15,
      .cell_min_v = 4.10,
      .pack_temp = 35.0,
      .inverter_temp = 40.0,
      .ambient_temp = 25.0,
      .coolant_flow = 8.0,
      .iso_resistance = 450.0,
      .gas_ppm = 0.0
    };
    
    float safety_features[13];
    extract_safety_features(safety_in, safety_features);
    
    int safety_result = safety_classifier.predict(safety_features);
    
    Serial.print("SAFETY STATUS:   ");
    Serial.println(get_safety_label(safety_result));
    
    if (safety_result == 2) {
      Serial.println("!!! CRITICAL ALERT: INITIATING SHUTDOWN !!!");
      // Trigger relay / contactor open
    }

    // ==========================================
    // 2. HEALTH CHECK (Low Priority)
    // ==========================================
    HealthSensors health_in = {
      .soc = 80.0,
      .internal_res = 65.0,
      .cycle_count = 450.0,
      .dod = 60.0,
      .cell_imbalance = 0.05,
      .coulombic_eff = 98.5,
      .pol_voltage = 0.05,
      .stress_index = 1.2
    };

    float health_features[8];
    extract_health_features(health_in, health_features);
    
    int health_result = health_classifier.predict(health_features);
    Serial.print("BATTERY HEALTH:  ");
    Serial.println(get_health_label(health_result));

    // ==========================================
    // 3. DRIVER CONTEXT (Medium Priority)
    // ==========================================
    DriverSensors driver_in = {
      .speed_avg = 25.0,
      .brake_freq = 15.0,
      .brake_intensity = 30.0,
      .throttle_var = 20.0,
      .energy_consumption = 0.15,
      .range_est = 130.0
    };

    float driver_features[6];
    extract_driver_features(driver_in, driver_features);
    
    int driver_result = driver_classifier.predict(driver_features);
    Serial.print("DRIVING MODE:    ");
    Serial.println(get_driver_label(driver_result));
    
    Serial.println("-----------------------------");
  }
}
