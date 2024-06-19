#include "WDGDrv.h"
#include "WDGM.h"
#define WDR()  __asm__ __volatile__ ("wdr");
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr/wdt.h"
/*Standard Types*/
typedef unsigned long uint32;

/*Registers*/
/*
#define SREG (*(uint32 *)(0x5F))
#define WDTCSR (*(uint32 *)(0x60))
#define MCUSR (*(uint32 *)(0x55))
*/
/*Bit Positions*/
#define PIN_I 7
#define WDCE 4
#define WDE 3
#define WDIE 6
#define WDP1 1
#define WDP0 0
#define WDRF 3

extern char stuck_flag;
 void WDGDrv_Init(void){
//	 /*Disable global interrupts*/
//	 SREG &= ~(1<<PIN_I); //we can also use the macro "cli()" provided in the AVR header library
//	 /*reset the timer*/
//	 WDR(); //we can also use the wdt_reset() function provided in the AVR header library
//	 // Clear the watchdog reset flag
//	 MCUSR &= (~(1<< WDRF));
//	 /*set the watchdog change enable and system reset enable to 1 in the same instruction before making any changes, page 44*/
//	 WDTCSR |= (1<<WDCE)|(1<<WDE);
//	 /*enable watchdog interrupt mode and system reset mode
//	  * Set maximum time-out value = 8K cycles (~64 ms) by seting the watchdog timer prescale pins to 0010
//	  */
//	 WDTCSR = (1<<WDIE)| (1<<WDE)| (1<<WDP1);
//	 /*enable global interrupts by setting pinI in the AVR status register to 1*/
//     SREG |= (1<<PIN_I); //we can also use the macro "sei()" provided in the AVR header library
	 wdt_reset();
	 wdt_enable(WDTO_60MS);
	 sei();
	 WDTCSR |= (1<<WDIE);

 }
//
// ISR(WDT_vect) {
//	 WDGM_StatusType wdgmStatus = WDGM_PovideSuppervisionStatus();
//	// Check if the WDGM status is OK
//	if (wdgmStatus == OK)
//    {	   //restart the timer without resetting the program
//		WDGDrv_Init();
//	}
// }
// ISR(WDT_vect){
//	 WDGDrv_IsrNotification();
//
// }

 void WDGDrv_IsrNotification(void){
	 WDGM_StatusType wdgmStatus = WDGM_PovideSuppervisionStatus();
	 // Check if the WDGM status is OK
	 if (wdgmStatus == OK && (stuck_flag != 1))
	  {
		 //restart the timer without resetting the program
		   WDGDrv_Init();
	    }
 }
 ISR(WDT_vect, ISR_ALIASOF(WDGDrv_IsrNotification));
