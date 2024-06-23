/**
 * main.c
 *
 *  Created on  :   Tuesday 18 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "LEDM.h"
#include "WDGDrv.h"
#include "WDGM.h"
#include "GPIO.h"

/*I-bit in SREG*/
#define PIN_I 	7

/*Global Variables*/
char is_WDGM_MainFunction_called = 1;   // Flag to indicate whether the WDGM_MainFunction was called
char stuck_flag = 0;                    // Flag to indicate whether the WDGM_MainFunction is stuck
volatile unsigned long time = 0;        // Time variable to count the number of milliseconds

/*Timer0 Variables*/
#define TIMER0_OUTPUT_COMPARE_A    15          // Compare value for 1ms timer

void Timer0_Init(void)
{
    // Set Timer0 to CTC mode (WGM01 = 1, WGM00 = 0)
    TCCR0A = (1 << WGM01);

    // Set compare value for 1ms interrupt
    // the clock frequency is 1MHz, the prescaler is 64, the timer is 8-bit
    OCR0A = TIMER0_OUTPUT_COMPARE_A;

    // Enable Timer0 Compare Match A interrupt
    TIMSK0 = (1 << OCIE0A);

    // Set prescaler to 64 and start Timer0 (CS01 and CS00 bits set)
    TCCR0B = (1 << CS01) | (1 << CS00);
}

// ISR for Timer0 Compare Match A
ISR(TIMER0_COMPA_vect)
{
    // Increment the time variable every 1ms
    time++;
}

int main()
{
    // Initialize peripherals
    LEDM_Init();                // LED Manager
    WDGDrv_Init();              // Watchdog Driver
    WDGM_Init();                // Watchdog Manager
    Timer0_Init();              // Timer0

    // Enable global interrupts by setting the I-bit in SREG
    SREG |= (1 << PIN_I);

    unsigned long lastTime = 0;

    while (1)
    {
        // Check if 10ms have elapsed
        if ((time - lastTime) >= 10)
        {   
            // Update the last time to the current time
            // So that the second time, the check will be after (20ms - 10ms = 10ms)
            lastTime = time;

            // Call the LED Manager to toggle the LED state if 500ms have passed
            // Also, to track the number of calls
            LEDM_Manage();

            // Check whether to call the WDGM_MainFunction or not
            if (is_WDGM_MainFunction_called == 1)
            {   
                // If it won't be called now, reset the flag to call it the next iteration
                // That way 20ms will pass between each call
                is_WDGM_MainFunction_called = 0;

                continue;
            }
            else
            {   
                // If it will be called now, set the flag to indicate that it was called
                // So that it won't be called the next iteration
                is_WDGM_MainFunction_called = 1;
                
                // Reset the stuck flag to indicate that the WDGM_MainFunction is stuck
                // If the function is not stuck, it will be set to 0 in the WDGM_MainFunction
                stuck_flag = 1;

                // Call the WDGM_MainFunction to check the LEDM_Manage call count if 100ms have passed
                WDGM_MainFunction();
            }
        }
    }

    return 0;
}
