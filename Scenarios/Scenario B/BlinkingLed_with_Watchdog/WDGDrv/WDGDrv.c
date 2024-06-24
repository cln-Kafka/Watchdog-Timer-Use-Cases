/**
 * WDGDrv.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Nada Amr, Kareem Salah, Mohamed Samy, Nouran Mahmoud
 */

#include "WDGDrv.h"
#include "WDGM.h"
#include "gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

/*Standard Types*/
typedef unsigned long uint32;

/*Watchdog Bit Positions*/
#define PIN_I 	7
#define WDCE 	4					// Watchdog Change Enable
#define WDE 	3					// Watchdog Enable
#define WDIE 	6					// Watchdog Interrupt Enable
#define WDP1 	1					// Watchdog Prescaler 1
#define WDP0 	0					// Watchdog Prescaler 0
#define WDRF 	3					// Watchdog Reset Flag

/*Timer1 Bit Positions*/
#define WGM12 	3					// Waveform Generation Mode
#define CS11 	1					// Clock Select
#define CS10 	0					// Clock Select
#define OCIE1A 	1					// Output Compare A Match Interrupt Enable

/*Timer1 Variables*/
#define TIMER1_OUTPUT_COMPARE_A	815		// Compare value for 50ms timer

/*Global Variables*/
extern char stuck_flag;				// The flag that indicates whether the WDGM_MainFunction is stuck

void WDGDrv_Init(void)
{
	// Disable global interrupts
	SREG &= ~(1 << PIN_I);

	// Reset the timer
	wdt_reset();

	// Clear the watchdog reset flag
	MCUSR &= (~(1 << WDRF));

	// Set the watchdog change enable and system reset enable to 1 in the same instruction before making any changes, page 44
	WDTCSR |= (1 << WDCE) | (1 << WDE);

	// Enable system reset mode
	// Set maximum time-out value = 8K cycles (~64ms) by seting the watchdog timer prescale pins to 0010
	WDTCSR = (1 << WDE) | (1 << WDP1);

	// Normal port operation, OC1A/OC1B disconnected
	// CTC mode
	TCCR1A = 0;

	// CTC mode, prescaler 64
	TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);

	// Set the compare value which achieves 50ms timer
	// the clock frequency is 1MHz, the prescaler is 64, the timer is 16-bit
	// sCompare value (no of pulses needed to reach the timeout) = [(clock frequency) / (prescaler*(1/desired time))]-1
	OCR1A = TIMER1_OUTPUT_COMPARE_A;

	// Enable Timer1 output compare A match interrupt
	TIMSK1 = (1 << OCIE1A);

	// Enable global interrupts by setting PIN_I in the AVR status register to 1
	SREG |= (1 << PIN_I);
}

ISR(TIMER1_COMPA_vect)
{	
	// Call the WDGDrv_IsrNotification function at the timeout (50ms)
	WDGDrv_IsrNotification();
}

void WDGDrv_IsrNotification(void)
{	
	// Get the WDGM status from the WDGM component
	WDGM_StatusType wdgmStatus = WDGM_PovideSuppervisionStatus();

	// Check if the WDGM status is OK and whether the WDGM_MainFunction is stuck
	if (((wdgmStatus == OK) && (stuck_flag != 1)))
	{
		// toggle WDT Counter reset 
		PORTB ^= (1 << TEST_PIN_WDCounter_Reset);
		// If so, refresh the watchdog
		wdt_reset();
	}
}
