/**
 * main.c
 *
 *  Created on  :   Tuesday 18 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LEDM.h"
#include "WDGDrv.h"
#include "WDGM.h"
#include "GPIO.h"

/* I-bit in SREG */
#define PIN_I   7

/* Global Variables */
char is_WDGM_MainFunction_called = 1;           // Flag to indicate whether the WDGM_MainFunction was called
char stuck_flag = 0;                            // Flag to indicate whether the WDGM_MainFunction is stuck
volatile unsigned long time = 0;                // Time variable to count the number of milliseconds
unsigned long LEDM_Manage_time = 10;

/* Timer0 Variables */
#define TIMER0_OUTPUT_COMPARE_A    15           // Compare value for 1ms timer

/* Define intervals for function calls in milliseconds */
#define LEDM_INTERVAL     10                    // Interval for calling LEDM_Manage
#define WDGM_INTERVAL     20                    // Interval for calling WDGM_MainFunction

unsigned long ledm_lastTime = 0;                // Time marker for the last LEDM_Manage call
unsigned long wdgm_lastTime = 0;                // Time marker for the last WDGM_MainFunction call

/* Function Prototypes */
void Timer0_Init(void);
void __vector_reset(void) __attribute__ ((signal, used, externally_visible));

/* Vector Reset Function */
void __vector_reset(void)
{
    DDRB |= (1 << TEST_PIN_MCU_Reset);  // Set as output
    PORTB ^= (1 << TEST_PIN_MCU_Reset); // Toggle
    asm("jmp 0");  // Jump to the actual reset vector
}

/* Timer0 Initialization */
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

    while (1)
    {
        _delay_ms(1);  // Short delay
        PORTB ^= (1 << TEST_PIN_MCU_Reset);  // Toggle again

        // Check if it's time to call LEDM_Manage
        if ((time - ledm_lastTime) >= LEDM_INTERVAL)
        {
            // Update the last time to the current time
            ledm_lastTime = time;

            // Call the LED Manager
            LEDM_Manage();
        }

        // Check if it's time to call WDGM_MainFunction
        if ((time - wdgm_lastTime) >= WDGM_INTERVAL)
        {
            // Update the last time to the current time
            wdgm_lastTime = time;

            // Call the WDGM_MainFunction
            stuck_flag = 1;
           // WDGM_MainFunction(); // Commented out for Scenario B
        }
    }

    return 0;
}
