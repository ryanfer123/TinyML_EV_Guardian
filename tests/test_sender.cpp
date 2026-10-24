#include <cassert>
#include <iostream>
#include "../ESP32_1_Sender_Simulator/ESP32_1_Sender_Simulator.ino"
SerialStub Serial;
int main() {
    setup();
    vehicle.throttle_var=17;
    vehicle.brake_intensity=12;
    vehicle.energy_consumption=0.145;
    transmitData();
    assert(sent.size()==12);
    assert(sent[9].id==0x300 && sent[9].first==17 && sent[9].second==12);
    assert(sent[10].id==0x301 && std::abs(sent[10].first-145)<0.001);
    assert(sent[10].second>=0 && sent[10].second<=1);
    assert(sent[11].id==0x302 && sent[11].second==0);
    std::cout << "Sender wire contract passed\n";
}
