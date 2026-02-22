#ifndef MODEL_UTILS_H
#define MODEL_UTILS_H

#include <Arduino.h>

// ==========================================
// DATA STRUCTURES (RAW SENSOR INPUTS)
// ==========================================

struct SafetySensors {
    float pack_voltage;      // V
    float pack_current;      // A
    float cell_max_v;        // V
    float cell_min_v;        // V
    float pack_temp;         // C
    float inverter_temp;     // C
    float ambient_temp;      // C
    float coolant_flow;      // L/min
    float iso_resistance;    // kOhm
    float gas_ppm;           // ppm
};

struct HealthSensors {
    float soc;               // %
    float internal_res;      // mOhm
    float cycle_count;       // count
    float dod;               // % (Depth of Discharge)
    float cell_imbalance;    // V (delta)
    float coulombic_eff;     // %
    float pol_voltage;       // V
    float stress_index;      // 0-10 scale
};

struct DriverSensors {
    float throttle_spike;    // variance/magnitude
    float brake_usage;       // mechanical braking %
    float energy_cons;       // Wh/km
    float regen_eff;         // % (0.0 - 1.0)
    float jerk;              // m/s^3
};

// ==========================================
// FEATURE EXTRACTION HELPERS
// ==========================================

/**
 * Calculates derived features for the Safety Model
 * Input: Raw sensor struct
 * Output: Feature array [13] expected by the model
 */
void extract_safety_features(SafetySensors data, float* features) {
    features[0] = data.pack_voltage;
    features[1] = data.pack_current;
    features[2] = (data.pack_voltage * data.pack_current) / 1000.0; // Instant Power
    features[3] = data.cell_max_v;
    features[4] = data.cell_min_v;
    features[5] = data.pack_temp;
    features[6] = (data.cell_max_v - data.cell_min_v) * 5.0; // Thermal Grad Est
    features[7] = data.inverter_temp;
    features[8] = data.ambient_temp;
    features[9] = data.coolant_flow;
    features[10] = data.iso_resistance;
    features[11] = data.gas_ppm;
    
    // SoP Heuristic
    float temp_derating = max(0.0, (double)(data.pack_temp - 45.0) * 2.0);
    features[12] = max(0.0, 150.0 - temp_derating); 
}

/**
 * Prepares features for the Health Model
 * Input: Raw sensor struct
 * Output: Feature array [8]
 */
void extract_health_features(HealthSensors data, float* features) {
    features[0] = data.soc;
    features[1] = data.internal_res;
    features[2] = data.cycle_count;
    features[3] = data.dod;
    features[4] = data.cell_imbalance;
    features[5] = data.coulombic_eff;
    features[6] = data.pol_voltage;
    features[7] = data.stress_index;
}

/**
 * Prepares features for the Driver Model
 * Input: Raw sensor struct
 * Output: Feature array [5]
 */
void extract_driver_features(DriverSensors data, float* features) {
    features[0] = data.throttle_spike;
    features[1] = data.brake_usage;
    features[2] = data.energy_cons;
    features[3] = data.regen_eff;
    features[4] = data.jerk;
}

// ==========================================
// PREDICTION INTERPRETERS
// ==========================================

const char* get_safety_label(int class_idx) {
    switch(class_idx) {
        case 0: return "Safe (Normal Operation)";
        case 1: return "Warning (Check Systems)";
        case 2: return "DANGER (Thermal Runaway)";
        default: return "UNKNOWN";
    }
}

const char* get_health_label(int class_idx) {
    return (class_idx == 0) ? "Optimal (Healthy)" : "Degraded (Service Req)";
}

const char* get_driver_label(int class_idx) {
    return (class_idx == 0) ? "Eco (Smooth)" : "Aggressive (Sport)";
}

#endif
