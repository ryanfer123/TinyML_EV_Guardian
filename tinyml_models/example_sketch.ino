#include "model_a_safety.h"
#include "model_b_health.h"
#include "model_c_driver.h"

// Instantiate the classifiers
// Note: Each model is wrapped in its own namespace to prevent conflicts
SafetyModel::Eloquent::ML::Port::RandomForest safety_model;
HealthModel::Eloquent::ML::Port::RandomForest health_model;
DriverModel::Eloquent::ML::Port::RandomForest driver_model;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("ESP32 Battery Diagnostic System Initialized");
}

void loop() {
  // ==========================================
  // 1. SAFETY PREDICTION
  // ==========================================
  // Features: [Pack_Voltage, Pack_Current, Instant_Power, Cell_Max, Cell_Min, 
  //            Pack_Temp, Thermal_Grad, Inverter_Temp, Ambient_Temp, Coolant_Flow, 
  //            Iso_Resistance, Gas_PPM, SoP]
  float safety_input[] = {
      350.5, 60.2, 21.1, 4.15, 4.10, 
      35.0, 0.05, 40.0, 25.0, 8.0, 
      450.0, 0.0, 150.0
  };
  
  int safety_class = safety_model.predict(safety_input);
  const char* safety_label = "";
  switch(safety_class) {
    case 0: safety_label = "Normal"; break;
    case 1: safety_label = "Warning"; break;
    case 2: safety_label = "Critical"; break;
  }
  
  Serial.print("Safety Status: ");
  Serial.println(safety_label);

  // ==========================================
  // 2. HEALTH PREDICTION
  // ==========================================
  // Features: [SoC, Internal_Res, Cycle_Count, DoD, Cell_Imbalance, 
  //            Coulombic_Eff, Pol_Voltage, Stress_Index]
  float health_input[] = {
      80.0, 65.0, 450.0, 60.0, 0.05, 
      98.5, 0.05, 1.2
  };
  
  int health_class = health_model.predict(health_input);
  Serial.print("Battery Health: ");
  Serial.println(health_class == 0 ? "Good" : "Bad");

  // ==========================================
  // 3. DRIVER PREDICTION
  // ==========================================
  // Features: [Speed_Avg, Brake_Frequency, Brake_Intensity, Throttle_Variance, 
  //            Energy_Consumption, Range_Est]
  float driver_input[] = {
      25.0, 15.0, 30.0, 20.0, 0.15, 130.0
  };
  
  int driver_class = driver_model.predict(driver_input);
  const char* driver_label = "";
  switch(driver_class) {
    case 0: driver_label = "City"; break;
    case 1: driver_label = "Highway"; break;
    case 2: driver_label = "Emergency"; break;
  }
  
  Serial.print("Driving Profile: ");
  Serial.println(driver_label);

  Serial.println("-----------------------------------");
  delay(5000);
}
