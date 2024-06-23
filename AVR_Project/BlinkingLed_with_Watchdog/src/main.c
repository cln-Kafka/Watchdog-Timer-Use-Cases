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

volatile  unsigned long time = 0; // `volatile` to ensure the variable is updated properly in the ISR
char stuck_flag = 0;
char called = 1;

void Timer0_Init(void)
{
    // Set Timer0 to CTC mode (WGM01 = 1, WGM00 = 0)
    TCCR0A = (1 << WGM01);

    // Set compare value for 1ms interrupt
    // Assuming 16 MHz clock with prescaler 64: (16*10^6 / (64 * (249 + 1))) = 1 kHz (1ms)
    OCR0A = 15;

    // Enable Timer0 Compare Match A interrupt
    TIMSK0 = (1 << OCIE0A);

    // Set prescaler to 64 and start Timer0 (CS01 and CS00 bits set)
    TCCR0B = (1 << CS01) | (1 << CS00);
}

// ISR for Timer0 Compare Match A
ISR(TIMER0_COMPA_vect)
{
    time++; // Increment the time variable every 1ms
}


int main()
{
    // Initialize peripherals
    LEDM_Init();
    WDGDrv_Init();
    WDGM_Init();

    // Initialize Timer0
    Timer0_Init();

    // Enable global interrupts by setting the I-bit in SREG
    SREG |= (1 << 7);

    unsigned long lastTime = 0;

    while (1)
    {
        // Check if 10ms have elapsed
        if ((time - lastTime) >= 10)
        {
            lastTime = time;

            LEDM_Manage();

            if (called == 1)
            {
                called = 0;
                continue;
            }
            else
            {
                called = 1;
                stuck_flag = 1;
                WDGM_MainFunction();
            }
        }
    }

    return 0;
}
