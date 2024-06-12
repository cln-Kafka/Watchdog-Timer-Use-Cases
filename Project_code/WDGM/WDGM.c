/**
 * WDGM.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include "WDGM.h"

/*How many times the LEDM_Manage was called*/
static unsigned int ledM_Manage_CallCount = 0;

//
static WDGM_StatusType wdgmStatus = NOK;

void WDGM_Init(void)
{
    // Initialize internal variables
    ledM_Manage_CallCount = 0;
    wdgmStatus = NOK;
}

void WDGM_MainFunction(void)
{
    if (ledM_Manage_CallCount >= 8 && ledM_Manage_CallCount <= 12)
    {
        wdgmStatus = OK;
    }
    else
    {
        wdgmStatus = NOK;
    }

    // Reset for next period
    ledM_Manage_CallCount = 0;
}

WDGM_StatusType WDGM_PovideSuppervisionStatus(void)
{
    return wdgmStatus;
}

void WDGM_AlivenessIndication(void)
{
    ledM_Manage_CallCount++;
}
