// /**
//  * main.c
//  *
//  *  Created on  :   Tuesday 18 JUN 2024
//  *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
//  */

// #include <avr/io.h>
// #include <util/delay.h>

// #include "LEDM.h"
// #include "WDGDrv.h"
// #include "WDGM.h"
// #include "GPIO.h"

// char stuck_flag = 0;
// char called = 1;

// int main()
// {
//   LEDM_Init();
//   WDGDrv_Init();
//   WDGM_Init();

//   while (1)
//   {
//     LEDM_Manage();
//     _delay_ms(10);
//     if (called == 1)
//     {
//       called = 0;
//       continue;
//     }
//     else
//     {
//       called = 1;
//       stuck_flag = 1;
//       WDGM_MainFunction();
//     }
//   }

//   return 0;
// }

/**
 * main.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */
#include <avr/io.h>
#include <avr/interrupt.h> // Include the interrupt library

#include "LEDM.h"
#include "WDGDrv.h"
#include "WDGM.h"
#include "GPIO.h"

volatile char timer_flag = 0;
char stuck_flag = 0;
char called = 1;

// Timer0 initialization function
void Timer0_Init()
{
  // Set timer to CTC mode
  TCCR0A |= (1 << WGM01);

  // Set prescaler to 64
  TCCR0B |= (1 << CS01) | (1 << CS00);

  // Set CTC compare value for 10ms at 16MHz AVR clock, with prescaler of 64
  OCR0A = 249;

  // Enable compare match interrupt
  TIMSK0 |= (1 << OCIE0A);

  // Enable global interrupts by setting the I-bit in SREG
  SREG |= (1 << 7);
}

// Timer0 compare match interrupt service routine
ISR(TIMER0_COMPA_vect)
{
  timer_flag = 1; // Set the flag when the timer interrupt occurs
}

int main()
{
  LEDM_Init();
  WDGDrv_Init();
  WDGM_Init();
  Timer0_Init(); // Initialize Timer0

  while (1)
  {
    if (timer_flag)
    {
      timer_flag = 0; // Clear the flag
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
