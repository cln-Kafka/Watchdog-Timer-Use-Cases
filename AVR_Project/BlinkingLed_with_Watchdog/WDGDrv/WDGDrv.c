#include "WDGDrv.h"
#include "WDGM.h"
#include <avr/interrupt.h>
#include <avr/wdt.h>
/*Standard Types*/
typedef unsigned long uint32;

/*Watchdog Registers*/
/*
#define SREG (*(uint32 *)(0x5F))
#define WDTCSR (*(uint32 *)(0x60))
#define MCUSR (*(uint32 *)(0x55))
*/
/*Timer Registers*/
/*
#define TCCR1A (*(uint32 *)(0x80))
#define TCCR1B (*(uint32 *)(0x81))
#define OCR1A (*(uint32 *)(0x89))
#define TIMSK1 (*(uint32 *)(0x6F))
*/
/*Watchdog Bit Positions*/
#define PIN_I 7
#define WDCE 4
#define WDE 3
#define WDIE 6
#define WDP1 1
#define WDP0 0
#define WDRF 3

/*Timer1 Bit Positions*/
#define WGM12 3
#define CS11 1
#define CS10 0
#define OCIE1A 1

extern char stuck_flag;
 void WDGDrv_Init(void){
	 /*Disable global interrupts*/
	 SREG &= ~(1<<PIN_I);
	 /*reset the timer*/
	 wdt_reset();
	 // Clear the watchdog reset flag
	 MCUSR &= (~(1<< WDRF));
	 /*set the watchdog change enable and system reset enable to 1 in the same instruction before making any changes, page 44*/
	 WDTCSR |= (1<<WDCE)|(1<<WDE);
	 /*enable system reset mode
	  * Set maximum time-out value = 8K cycles (~64 ms) by seting the watchdog timer prescale pins to 0010
	  */
	 WDTCSR = (1<<WDE)| (1<<WDP1);
	 /*Normal port operation, OC1A/OC1B disconnected
	  * CTC mode*/
	 TCCR1A = 0;
	 /*CTC mode
	  * 64ms prescale*/
	 TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);
	 /* Set the compare value which achieves 50 ms timer
	  * compare value (no of pulses needed to reach the timeout) = desired time/ time of one pulse
	  * time of one pulse= prescale/ freq of the microcontroller clock
	  * */
	 OCR1A = 780;
	 // Enable timer1 output compare A match interrupt
	 TIMSK1 = (1 << OCIE1A);
	 /*enable global interrupts by setting pinI in the AVR status register to 1*/
     SREG |= (1<<PIN_I);

 }

 ISR(TIMER1_COMPA_vect){
	 WDGDrv_IsrNotification();

 }

 void WDGDrv_IsrNotification(void){
	 WDGM_StatusType wdgmStatus = WDGM_PovideSuppervisionStatus();
	 // Check if the WDGM status is OK
	 if (wdgmStatus == OK && (stuck_flag != 1))
	  {
		 //restart the timer
		   wdt_reset();
	    }
 }
