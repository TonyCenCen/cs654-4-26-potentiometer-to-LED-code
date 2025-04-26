/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include <xc.h>       // Required for __delay_ms()

#define NUM_LEDS 8
#define _XTAL_FREQ 200000000UL // Replace with your actual system clock 
// frequency (e.g., 200 MHz for PIC32MZ EF)

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

// Simple delay function based on CPU cycles
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < (_XTAL_FREQ / 10000); j++) {
            asm("nop");
        }
    }
}

// a function to update LEDs based on potentiometer value
void Update_LEDs(unsigned int potValue) {
    // calculate how many LEDs should be turned on based on the pot value
    // ADC is 12-bit (0-4095), so we divide this range into steps for 
    // each LED
    
    // range of potValue is also 0-4095
    // range of ledsToLight [0,8]]
    unsigned int ledsToLight = (potValue * NUM_LEDS) / 4096;
    
    // safety, start with all LEDs off
    LED3_Clear();
    LED4_Clear();
    LED5_Clear();
    LED6_Clear();
    LED7_Clear();
    LED8_Clear();
    LED9_Clear();
    LED10_Clear();
    
    // now turn on the appropriate number of LEDs based on potentiometer posn
    if (ledsToLight >= 1) LED10_Set();
    if (ledsToLight >= 2) LED9_Set();
    if (ledsToLight >= 3) LED8_Set();
    if (ledsToLight >= 4) LED7_Set();
    if (ledsToLight >= 5) LED6_Set();
    if (ledsToLight >= 6) LED5_Set();
    if (ledsToLight >= 7) LED4_Set();
    if (ledsToLight >= 8) LED3_Set();
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    // local var
//    unsigned int potValue;
    
    // Enable the ADC module
    ADCHS_ModulesEnable(ADCHS_MODULE0_MASK);
    
    // Set up output pins for LEDs, just for safety, if not set to output yet
    LED3_OutputEnable();
    LED4_OutputEnable();
    LED5_OutputEnable();
    LED6_OutputEnable();
    LED7_OutputEnable();
    LED8_OutputEnable();
    LED9_OutputEnable();
    LED10_OutputEnable();

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        LED3_Toggle();
        LED4_Toggle();
        LED5_Toggle();
        LED6_Toggle();
        LED7_Toggle();
        LED8_Toggle();
        LED9_Toggle();
        LED10_Toggle();
        delay_ms(500);
        
//        // Start conversion on the potentiometer channel (ADC Channel 45)
//        ADCHS_ChannelConversionStart(CHANNEL_0);
//        
//        // Wait for conversion to complete
//        while(!ADCHS_ChannelResultIsReady(ADCHS_CH45));
//        
//        // Get the result
//        potValue = ADCHS_ChannelResultGet(ADCHS_CH45);
//        
//        // Update LED status based on the potentiometer value
//        Update_LEDs(potValue);
//        
//        // Small delay to prevent too frequent updates and potential flickering
//        delay_ms(50);
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

