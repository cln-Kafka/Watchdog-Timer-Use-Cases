/**
 * WDGM.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include "WDGM.h"

/*Standard Types*/
typedef unsigned long uint32;

/*How many times the LEDM_Manage was called*/
static unsigned int ledM_Manage_CallCount = 0;

static WDGM_StatusType wdgmStatus = NOK;

// Time elapsed since the last MainFunction Call
static uint32 elapsedTime = 0;

void WDGM_Init(void)
{
    // Initialize internal variables
    ledM_Manage_CallCount = 0;
    wdgmStatus = NOK;
}

void WDGM_MainFunction(void)
{
    // Increment elapsed time by 10ms
    elapsedTime += 10;

    // Check if 500ms has passed
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
}

WDGM_StatusType WDGM_PovideSuppervisionStatus(void)
{
    return wdgmStatus;
}

void WDGM_AlivenessIndication(void)
{
    ledM_Manage_CallCount++;
}
