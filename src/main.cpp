#include <thread>
#include <chrono>
#include "publisher.h"
#include "gpio.h"

using namespace std::chrono_literals;

int main() {
    // std::string interface_name = "eth0";
    // GP publisher(interface_name);
    // printf("Using interface %s\n", interface_name.c_str());

    // int i = 0;
    // bool n = false;
    // while (true) {
    //     publisher.Tick();
    //     std::this_thread::sleep_for(1ms);
    //     publisher.SetValue(n, i);
    //     if (i<3) {
    //         i++;
    //     }
    //     else {
    //         i = 0;
    //     }

    //     n = !n;
    // }

    while (true) {
        GPIO::SetPin();
    };

}