#include <iostream>
#include <gpiod.hpp> // Include the C++ header
#include <chrono>
#include <thread>
#include <stdexcept>

#ifndef CONSUMER
#define CONSUMER "my-led-blinker" // Name for the consumer
#endif

int main() {
    const std::string chip_path = "gpiochip1"; // Or the name, e.g., "gpiochip0"
    const int gpio_write_pin = 12;             // Example pin offset

    try {
        // 1. Open the GPIO chip
        gpiod::chip chip(chip_path);

        // 2. Define line settings
        gpiod::line_settings settings;
        settings.set_direction(gpiod::line::direction::OUTPUT);
        settings.set_output_value(gpiod::line::value::ACTIVE); // Start with active state (on)

        // 3. Prepare a request
        auto request = chip.prepare_request()
                           .set_consumer(CONSUMER)
                           .add_line_settings(gpio_write_pin, settings)
                           .do_request();

        std::cout << "LED on GPIO " << gpio_write_pin << " blinking..." << std::endl;

        for (int i = 0; i < 5; ++i) {
            // Set value to 0 (inactive/off)
            request.set_value(gpio_write_pin, gpiod::line::value::INACTIVE);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            // Set value to 1 (active/on)
            request.set_value(gpio_write_pin, gpiod::line::value::ACTIVE);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        std::cout << "Done." << std::endl;

        // The 'request' and 'chip' objects automatically clean up resources when they go out of scope.

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}