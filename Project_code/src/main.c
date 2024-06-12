/**
 * main.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include "LEDM.h"
#include "WDGDrv.h"
#include "WDGM.h"
#include "Std_Types.h"

void delay(uint32 time)
{
    volatile uint32 i;
    for (i = 0; i < time; i++)
    {
    }
}

int main()
{
    LEDM_Init();
    WDGDrv_Init();
    WDGM_Init();

    while (1)
    {
        delay(10000);
        LEDM_Manage();
        // WDGM_MainFunction();
    }

    return 0;
}