/**
 * WDGM.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr 
 */

#include <avr/io.h>
#include "WDGM.h"

/*Standard Types*/
typedef unsigned long uint8;
typedef unsigned long uint32;

/*Global Variables*/
extern char stuck_flag;                         // The flag that indicates whether the WDGM_MainFunction is stuck
static uint32 elapsedTime = 0;                  // Time elapsed since the last WDGM_MainFunction Call
static WDGM_StatusType wdgmStatus = OK;         // The status of the Watchdog Manager
static unsigned int ledM_Manage_CallCount = 0;  // The number of times the LEDM_Manage function was called

/*Test Pin of the call of WDGM_MainFunction*/
#define WDGM_MAINFUNCTION_TEST_PIN 4

void WDGM_Init(void)
{
    // Initialize internal variables
    elapsedTime = 0;
    ledM_Manage_CallCount = 0;
    wdgmStatus = OK;
    // Add a toggling pin to indicate the call of WDGM_MainFunction
    DDRB |= (1 << WDGM_MAINFUNCTION_TEST_PIN);
}

void WDGM_MainFunction(void)
{
    // Toggle the test pin to indicate the call of WDGM_MainFunction
    PINB |= (1 << WDGM_MAINFUNCTION_TEST_PIN);

    // Increment elapsed time by 10ms
    elapsedTime += 20;

    // Check if 100ms has passed
    if (elapsedTime >= 100)
    {   
        // Check if the LEDM_Manage function was called 8 to 12 times
        // Mathematically, the function should be called 10 times (100ms / 10ms(delay) = 10 times)
        if (ledM_Manage_CallCount >= 8 && ledM_Manage_CallCount <= 12)
        {
            wdgmStatus = OK;
        }
        else
        {
            wdgmStatus = NOK;
        }

        // Reset the elapsed time counter
        elapsedTime = 0;

        // Reset for next period
        ledM_Manage_CallCount = 0;
    }

    // Reset the stuck flag
    stuck_flag = 0;
}

WDGM_StatusType WDGM_PovideSuppervisionStatus(void)
{   
    // Return the status of the Watchdog Manager
    return wdgmStatus;
}

void WDGM_AlivenessIndication(void)
{   
    // Increment the LEDM_Manage call count
    ledM_Manage_CallCount++;
}
