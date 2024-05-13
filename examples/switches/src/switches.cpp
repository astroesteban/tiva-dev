/**
 * @file switches.cpp
 * @author Esteban Duran (@astroesteban)
 * @brief This example uses a combination of the onboard switches and LEDs.
 * Both switches SW1 and SW2 are pressed  --  The LED should be blue
 * Just SW1 switch is pressed  --  The LED should be red
 * Just SW2 switch is pressed  --  The LED should be green
 * Neither SW1 or SW2 is pressed  --  The LED should be off
 * @version 0.1
 * @date 2024-05-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <cstdint>

#include "lm4f120h5qr.h"

// The onboard LED colors
static constexpr uint32_t LED_OFF = 0;
static constexpr uint32_t LED_RED = 0x02;
static constexpr uint32_t LED_BLUE = 0x04;
static constexpr uint32_t LED_PINK = 0x06;
static constexpr uint32_t LED_GREEN = 0x08;
static constexpr uint32_t LED_YELLOW = 0x0A;
static constexpr uint32_t LED_SKY_BLUE = 0x0C;
static constexpr uint32_t LED_WHITE = 0x0E;

/**
 * @brief Initializes GPIO Port F
 * 
 */
static inline void init_port_f() {
    // 1. Enable the clock for the GPIO F register (5th bit)
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;

    // 1a. Unlock Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // 2) unlock Port F

    // 1b. Allow changes to PF4-PF0
    GPIO_PORTF_CR_R |= 0x1F;

    // 2. Set the direction of the GPIO port pins
    GPIO_PORTF_DIR_R |= 0b00001110; // C++14 binary literals

    // 3. Set the GPIOAFSEL register to program each bit as GPIO or alternate
    GPIO_PORTF_AFSEL_R = 0x00;

    // 4. Program each pad in the port to have either pull-up, pull-down, or open drain
    GPIO_PORTF_PUR_R |= 0b00010001;

    // 5. To enable GPIO pins as digital I/Os, set the appropriate DEN bit
    GPIO_PORTF_DEN_R |= 0b00011111;
}

#include <array>

int main() {
    init_port_f();

    std::array<std::uint8_t, 100> buffer{};

    GPIO_PORTF_DATA_R = LED_OFF;

    while (true) {
        volatile std::uint32_t switch1 = GPIO_PORTF_DATA_R & 0x10;
        volatile std::uint32_t switch2 = GPIO_PORTF_DATA_R & 0x01;

        // switches are negative logic
        if (switch1 && switch2) {           // no switch pressed
            GPIO_PORTF_DATA_R = LED_OFF;
        }
        else if (!switch1 && switch2) {     // only switch1 pressed
            GPIO_PORTF_DATA_R = LED_RED;
        }
        else if (switch1 && !switch2) {      // only switch2 pressed
            GPIO_PORTF_DATA_R = LED_GREEN;
        }
        else {                              // both switches are pressed
            GPIO_PORTF_DATA_R = LED_BLUE;
        }
    }
}
