/**
 * @file startup.c
 * @author Esteban Duran (@astroesteban)
 * @brief The startup file containing the vector table for the Texas
 *        Instruments TM4C.
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Apache License
 * 
 */
// +--------------------------------------------------------------------------+
// +			        Type Definitions and Macros                           +
// +--------------------------------------------------------------------------+

/*
 * Defines a macro DEFAULT that aliases the function prototype
 * to Default_Handler if the function is not defined
*/
#define DEFAULT __attribute__((weak, alias("Default_Handler")))

/* Defines a type for the ISR's in the vector table */
typedef void (*element_t)(void);

/* Defines a type for the vector table */
typedef union {
    element_t isr;   //all ISRs use this type
    void *stack_top; //pointer to top of the stack
} vector_table_t;


// +--------------------------------------------------------------------------+
// +			        Prototypes of Basic Exception Handlers                +
// +--------------------------------------------------------------------------+

//Default Handler,does nothing
void Default_Handler(void);

//System Exception Handlers
void Reset_Handler(void);
void NMI_Handler(void);
DEFAULT void SVC_Handler(void);
DEFAULT void DebugMonitor_Handler(void);
DEFAULT void PendSV_Handler(void);
DEFAULT void SysTick_Handler(void);

//Fault Handlers
void HardFault_Handler(void);
DEFAULT void MemManageFault_Handler(void);
DEFAULT void BusFault_Handler(void);
DEFAULT void UsageFault_Handler(void);

// +--------------------------------------------------------------------------+
// +                Prototypes of Interrupt Service Routines                  +
// +--------------------------------------------------------------------------+
DEFAULT void GPIOPortA_ISR(void);
DEFAULT void GPIOPortB_ISR(void);
DEFAULT void GPIOPortC_ISR(void);
DEFAULT void GPIOPortD_ISR(void);
DEFAULT void GPIOPortE_ISR(void);
DEFAULT void UART0_ISR(void);
DEFAULT void UART1_ISR(void);
DEFAULT void SPI0_ISR(void);
DEFAULT void I2C0_ISR(void);
DEFAULT void PWM0Fault_ISR(void);
DEFAULT void PWM0Generator0_ISR(void);
DEFAULT void PWM0Generator1_ISR(void);
DEFAULT void PWM0Generator2_ISR(void);
DEFAULT void QEI0_ISR(void);
DEFAULT void ADC0Sequence0_ISR(void);
DEFAULT void ADC0Sequence1_ISR(void);
DEFAULT void ADC0Sequence2_ISR(void);
DEFAULT void ADC0Sequence3_ISR(void);
DEFAULT void WatchDogTimer_ISR(void);
DEFAULT void Timer0A_ISR(void);
DEFAULT void Timer0B_ISR(void);
DEFAULT void Timer1A_ISR(void);
DEFAULT void Timer1B_ISR(void);
DEFAULT void Timer2A_ISR(void);
DEFAULT void Timer2B_ISR(void);
DEFAULT void AnalogComparator0_ISR(void);
DEFAULT void AnalogComparator1_ISR(void);
DEFAULT void SystemCtrl_ISR(void);
DEFAULT void FlashCtrl_ISR(void);
DEFAULT void GPIOPortF_ISR(void);
DEFAULT void UART2_ISR(void);
DEFAULT void SPI1_ISR(void);
DEFAULT void Timer3A_ISR(void);
DEFAULT void Timer3B_ISR(void);
DEFAULT void I2C1_ISR(void);
DEFAULT void QEI1_ISR(void);
DEFAULT void CAN0_ISR(void);
DEFAULT void CAN1_ISR(void);
DEFAULT void Hibernation_ISR(void);
DEFAULT void USB0_ISR(void);
DEFAULT void PWM0Generator3_ISR(void);
DEFAULT void UDMASoftware_ISR(void);
DEFAULT void UDMAError_ISR(void);
DEFAULT void ADC1Sequence0_ISR(void);
DEFAULT void ADC1Sequence1_ISR(void);
DEFAULT void ADC1Sequence2_ISR(void);
DEFAULT void ADC1Sequence3_ISR(void);
DEFAULT void SPI2_ISR(void);
DEFAULT void SPI3_ISR(void);
DEFAULT void UART3_ISR(void);
DEFAULT void UART4_ISR(void);
DEFAULT void UART5_ISR(void);
DEFAULT void UART6_ISR(void);
DEFAULT void UART7_ISR(void);
DEFAULT void I2C2_ISR(void);
DEFAULT void I2C3_ISR(void);
DEFAULT void Timer4A_ISR(void);
DEFAULT void Timer4B_ISR(void);
DEFAULT void Timer5A_ISR(void);
DEFAULT void Timer5B_ISR(void);
DEFAULT void WideTimer0A_ISR(void);
DEFAULT void WideTimer0B_ISR(void);
DEFAULT void WideTimer1A_ISR(void);
DEFAULT void WideTimer1B_ISR(void);
DEFAULT void WideTimer2A_ISR(void);
DEFAULT void WideTimer2B_ISR(void);
DEFAULT void WideTimer3A_ISR(void);
DEFAULT void WideTimer3B_ISR(void);
DEFAULT void WideTimer4A_ISR(void);
DEFAULT void WideTimer4B_ISR(void);
DEFAULT void WideTimer5A_ISR(void);
DEFAULT void WideTimer5B_ISR(void);
DEFAULT void SystemException_ISR(void);
DEFAULT void PWM1Generator0_ISR(void);
DEFAULT void PWM1Generator1_ISR(void);
DEFAULT void PWM1Generator2_ISR(void);
DEFAULT void PWM1Generator3_ISR(void);
DEFAULT void PWM1Fault_ISR(void);

// +--------------------------------------------------------------------------+
// +					External Variables declaration					      +
// +--------------------------------------------------------------------------+

//main() of your program
extern int main(void);
//stack pointer
extern int _stack_ptr;
//.text/code,stored in Flash
extern int _etext;
//.data,copied into RAM on boot
extern int _data;
extern int _edata;
//.bss,unitialized variables
extern int _bss;
extern int _ebss;


// +--------------------------------------------------------------------------+
// +			  		         Vector Table                                 +
// +--------------------------------------------------------------------------+

// * marks this vector table as part of the .vector_table section in the ld
// * The vector table is defined in the datasheet table 2-9.
__attribute__((section(".vector_table")))
const vector_table_t vectors[] = {
    {.stack_top = &_stack_ptr}, // 0    Pointer to top of Stack
    Reset_Handler,              // 1    Reset handler is called when the <RESET> button is pressed
    NMI_Handler,                // 2    Non-Maskable Interrupt handler
    HardFault_Handler,          // 3    Hard Fault Handler
    MemManageFault_Handler,     // 4    Memory management fault Handler
    BusFault_Handler,           // 5    Bus Fault Handler
    UsageFault_Handler,         // 6    Usage Fault Handler
    0,                          // 7    Reserved
    0,                          // 8    Reserved
    0,                          // 9    Reserved
    0,                          // 10   Reserved
    SVC_Handler,                // 11   SuperVisor Call Handler
    DebugMonitor_Handler,       // 12   Debug Monitor Handler
    0,                          // 13   Reserved
    PendSV_Handler,             // 14   Pendeable interrupt driven request
    SysTick_Handler,            // 15   SysTick Timer handler
    GPIOPortA_ISR,              // 16   GPIO Port A Interrupt Service Routine
    GPIOPortB_ISR,              // 17   GPIO Port B Interrupt Service Routine
    GPIOPortC_ISR,              // 18   GPIO Port C Interrupt Service Routine
    GPIOPortD_ISR,              // 19   GPIO Port D Interrupt Service Routine
    GPIOPortE_ISR,              // 20   GPIO Port C Interrupt Service Routine
    UART0_ISR,                  // 21   UART 0
    UART1_ISR,                  // 22   UART 1
    SPI0_ISR,                   // 23   SPI 0
    I2C0_ISR,                   // 24   I2C0 Master and Slave
    PWM0Fault_ISR,              // 25   PWM Fault
    PWM0Generator0_ISR,         // 26   PWM Generator 0
    PWM0Generator1_ISR,         // 27   PWM Generator 1
    PWM0Generator2_ISR,         // 28   PWM Generator 2
    QEI0_ISR,                   // 29   Quadrature Encoder 0
    ADC0Sequence0_ISR,          // 30   ADC Sequence 0
    ADC0Sequence1_ISR,          // 31   ADC Sequence 1
    ADC0Sequence2_ISR,          // 32   ADC Sequence 2
    ADC0Sequence3_ISR,          // 33   ADC Sequence 3
    WatchDogTimer_ISR,          // 34   Watchdog timer
    Timer0A_ISR,                // 35   Timer 0 subtimer A
    Timer0B_ISR,                // 36   Timer 0 subtimer B
    Timer1A_ISR,                // 37   Timer 1 subtimer A
    Timer1B_ISR,                // 38   Timer 1 subtimer B
    Timer2A_ISR,                // 39   Timer 2 subtimer A
    Timer2B_ISR,                // 40   Timer 2 subtimer B
    AnalogComparator0_ISR,      // 41   Analog Comparator 0
    AnalogComparator1_ISR,      // 42   Analog Comparator 1s
    0,                          // 43   Reserved
    SystemCtrl_ISR,             // 44   System Control
    FlashCtrl_ISR,              // 45   Flash Memory Control and EEPROM Control
    GPIOPortF_ISR,              // 46   GPIO Port F
    0,                          // 47   Reserved
    0,                          // 48   Reserved
    UART2_ISR,                  // 49   UART2
    SPI1_ISR,                   // 50   SSI1
    Timer3A_ISR,                // 51   16/32-Bit Timer 3A
    Timer3B_ISR,                // 52   16/32-Bit Timer 3B
    I2C1_ISR,                   // 53   I2C1
    QEI1_ISR,                   // 54   QEI1
    CAN0_ISR,                   // 55   CAN0
    CAN1_ISR,                   // 56   CAN1
    0,                          // 57   Reserved
    0,                          // 58   Reserved
    Hibernation_ISR,            // 59   Hibernation Module
    USB0_ISR,                   // 60   USB
    PWM0Generator3_ISR,         // 61   PWM Generator 3
    UDMASoftware_ISR,           // 62   μDMA Software
    UDMAError_ISR,              // 63   μDMA Error
    ADC1Sequence0_ISR,          // 64   ADC1 Sequence 0
    ADC1Sequence1_ISR,          // 65   ADC1 Sequence 1
    ADC1Sequence2_ISR,          // 66   ADC1 Sequence 2
    ADC1Sequence3_ISR,          // 67   ADC1 Sequence 3
    0,                          // 68   Reserved
    0,                          // 69   Reserved
    0,                          // 70   Reserved
    0,                          // 71   Reserved
    0,                          // 72   Reserved
    SPI2_ISR,                   // 73   SSI2
    SPI3_ISR,                   // 74   SSI3
    UART3_ISR,                  // 75   UART3
    UART4_ISR,                  // 76   UART4
    UART5_ISR,                  // 77   UART5
    UART6_ISR,                  // 78   UART6
    UART7_ISR,                  // 79   UART7
    0,                          // 80   Reserved
    0,                          // 81   Reserved
    0,                          // 82   Reserved
    0,                          // 83   Reserved
    I2C2_ISR,                   // 84   I2C2
    I2C3_ISR,                   // 85   I2C3
    Timer4A_ISR,                // 86   16/32-Bit Timer 4A
    Timer4B_ISR,                // 87   16/32-Bit Timer 4B
    0,                          // 88   Reserved
    0,                          // 89   Reserved
    0,                          // 90   Reserved
    0,                          // 91   Reserved
    0,                          // 92   Reserved
    0,                          // 93   Reserved
    0,                          // 94   Reserved
    0,                          // 95   Reserved
    0,                          // 96   Reserved
    0,                          // 97   Reserved
    0,                          // 98   Reserved
    0,                          // 99   Reserved
    0,                          // 100  Reserved
    0,                          // 101  Reserved
    0,                          // 102  Reserved
    0,                          // 103  Reserved
    0,                          // 104  Reserved
    0,                          // 105  Reserved
    0,                          // 106  Reserved
    0,                          // 107  Reserved
    Timer5A_ISR,                // 108  16/32-Bit Timer 5A
    Timer5B_ISR,                // 109  16/32-Bit Timer 5B
    WideTimer0A_ISR,            // 110  32/64-Bit Timer 0A
    WideTimer0B_ISR,            // 111  32/64-Bit Timer 0B
    WideTimer1A_ISR,            // 112  32/64-Bit Timer 1A
    WideTimer1B_ISR,            // 113  32/64-Bit Timer 1B
    WideTimer2A_ISR,            // 114  32/64-Bit Timer 2A
    WideTimer2B_ISR,            // 115  32/64-Bit Timer 2B
    WideTimer3A_ISR,            // 116  32/64-Bit Timer 3A
    WideTimer3B_ISR,            // 117  32/64-Bit Timer 3B
    WideTimer4A_ISR,            // 118  32/64-Bit Timer 4A
    WideTimer4B_ISR,            // 119  32/64-Bit Timer 4B
    WideTimer5A_ISR,            // 120  32/64-Bit Timer 5A
    WideTimer5B_ISR,            // 121  32/64-Bit Timer 5B
    SystemException_ISR,        // 122  System Exception (imprecise)
    0,                          // 123  Reserved
    0,                          // 124  Reserved           
    0,                          // 125  Reserved
    0,                          // 126  Reserved
    0,                          // 127  Reserved
    0,                          // 128  Reserved
    0,                          // 129  Reserved
    0,                          // 130  Reserved
    0,                          // 131  Reserved
    0,                          // 132  Reserved
    0,                          // 133  Reserved
    0,                          // 134  Reserved
    0,                          // 135  Reserved
    0,                          // 136  Reserved
    0,                          // 137  Reserved
    0,                          // 138  Reserved
    0,                          // 139  Reserved
    0,                          // 140  Reserved
    0,                          // 141  Reserved
    0,                          // 142  Reserved
    0,                          // 143  Reserved
    0,                          // 144  Reserved
    0,                          // 145  Reserved
    0,                          // 146  Reserved
    0,                          // 147  Reserved
    0,                          // 148  Reserved
    0,                          // 149  Reserved
    PWM1Generator0_ISR,         // 150  PWM1 Generator 0
    PWM1Generator1_ISR,         // 151  PWM1 Generator 1
    PWM1Generator2_ISR,         // 152  PWM1 Generator 2
    PWM1Generator3_ISR,         // 153  PWM1 Generator 3
    PWM1Fault_ISR,              // 154  PWM1 Fault
};


// +--------------------------------------------------------------------------+
// +                Implementations of Interrupt Service Routines             +
// +--------------------------------------------------------------------------+
void Reset_Handler(void) {
    int *src, *dest;

    /* copying of the .data values into RAM */
    src = &_etext;
    for (dest = &_data; dest < &_edata;) {
        *dest++ = *src++;
    }

    /* initializing .bss values to zero*/
    for (dest = &_bss; dest < &_ebss;) {
        *dest++ = 0;
    }

    /* your program's main() called */
    main();

    // ? Do I need this? It's just habit at this point.
    while (1);
}

void Default_Handler(void) {
    while (1);
}

void NMI_Handler(void) {
    while (1);
}

void HardFault_Handler(void) {
    while (1);
}