/**
 * @file test_tm4c_blinky.cpp
 * @author Esteban Duran (@astroesteban)
 * @brief A simple test program that blinks the TM4C's onboard LED without
 *        using TivaWare.
 * 
 * @version 0.1
 * @date 2022-01-16
 */
#include <cstdint>

#define GPIO_PORTF_DATA_R (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R (*((volatile unsigned long *)0x400FE108))

// The onboard LED colors
#define LED_OFF 0
#define LED_RED 0x02
#define LED_BLUE 0x04
#define LED_PINK 0x06
#define LED_GREEN 0x08
#define LED_YELLOW 0x0A
#define LED_SKY_BLUE 0x0C
#define LED_WHITE 0x0E

/**
 * @brief Initializes Port F
 * 
 */
void portFInit() {
    volatile uint32_t delay; // Give clock enough time to stabilize
    SYSCTL_RCGC2_R |= 0x00000020; // 1) F clock
    delay = SYSCTL_RCGC2_R; // delay
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // 2) unlock PortF PF0
    GPIO_PORTF_CR_R = 0x1F; // allow changes to PF4-0
    GPIO_PORTF_AMSEL_R = 0x00; // 3) disable analog function
    GPIO_PORTF_PCTL_R = 0x00000000; // 4) GPIO clear bit PCTL
    GPIO_PORTF_DIR_R = 0x0E; // 5) PF4,PF0 input, PF3,PF2,PF1 output
    GPIO_PORTF_AFSEL_R = 0x00; // 6) no alternate function
    GPIO_PORTF_PUR_R = 0x11; // enable pullup resistors on PF4,PF0
    GPIO_PORTF_DEN_R = 0x1F; // 7) enable digital pins PF4-PF0
}


/**
 * @brief Software delay to wait for 0.1 seconds
 * 
 */
void delay() {
    // 0.1sec
    volatile uint32_t time = (727240 * 200) / 91;

    while (time > 0) {
        time--;
    }
}


/**
 * @brief Blink the TM4C's onboard LED
 * 
 * @return int 
 */
int main() {
    // Call initialization of port PF4 PF2
    portFInit();

    while (true) {
        GPIO_PORTF_DATA_R = LED_RED;
        delay();
        GPIO_PORTF_DATA_R = LED_WHITE;
        delay();
        GPIO_PORTF_DATA_R = LED_BLUE;
        delay();
    }
}
