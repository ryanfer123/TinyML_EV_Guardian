#include <cassert>
#include <iostream>
#include "../ESP32_2_Receiver_TinyML_Guardian/model_utils.h"
int main() {
    SafetySensors safety{350,60,4.2,4.1,50,55,25,8,500,10};
    float s[13];
    extract_safety_features(safety,s);
    assert(s[0]==350 && s[1]==60 && s[2]==21);
    assert(std::abs(s[6]-0.5)<0.00001 && s[12]==140);
    HealthSensors health{80,60,400,60,0.05,99,0.05,1};
    float h[8]; extract_health_features(health,h);
    assert(h[0]==80 && h[2]==400 && h[7]==1);
    DriverSensors driver{17,12,145,0.25,0.5};
    float d[6]={0,0,0,0,0,987};
    extract_driver_features(driver,d);
    assert(d[0]==17 && d[1]==12 && d[2]==145 && d[3]==0.25 && d[4]==0.5);
    assert(d[5]==987); // Five features only; no write past the array.
    assert(std::strcmp(get_safety_label(99),"UNKNOWN")==0);
    std::cout << "Feature extraction contract passed\n";
}
