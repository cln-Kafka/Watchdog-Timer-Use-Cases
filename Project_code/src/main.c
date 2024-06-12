/**
 * main.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include "LEDM.h"
#include "WDGDrv.h"
#include "WDGM.h"
#include "GPIO.h"

/*Standard Types*/
typedef unsigned long uint32;

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
        GPIO_Write(4, 0);
        delay(4000000);
        GPIO_Write(4, 1);
        delay(4000000);
        // LEDM_Manage();
        // delay(10000);
        // WDGM_MainFunction();
        // delay(10000);
    }

    return 0;
}
