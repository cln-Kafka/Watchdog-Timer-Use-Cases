/**
 * WDGM.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include "WDGM.h"

/*Standard Types*/
typedef unsigned long uint8;
typedef unsigned long uint32;

/*How many times the LEDM_Manage was called*/
static unsigned int ledM_Manage_CallCount = 0;

static WDGM_StatusType wdgmStatus = OK;

// Time elapsed since the last MainFunction Call
static uint32 elapsedTime = 0;
extern char stuck_flag;

void WDGM_Init(void)
{
    // Initialize internal variables
    ledM_Manage_CallCount = 0;
    wdgmStatus = OK;
}

void WDGM_MainFunction(void)
{
    // Increment elapsed time by 10ms
    elapsedTime += 20;

    // Check if 100ms has passed
    if (elapsedTime >= 100)
    {
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
    stuck_flag=0;
}

WDGM_StatusType WDGM_PovideSuppervisionStatus(void)
{
    return wdgmStatus;
}

void WDGM_AlivenessIndication(void)
{
    ledM_Manage_CallCount++;
}

