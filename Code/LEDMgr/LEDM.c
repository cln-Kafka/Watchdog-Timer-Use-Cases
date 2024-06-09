/**
 * Gpio.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include "LEDM.h"
#include "GPIO.h"
#include "Std_Types.h"

/*LED is initially turned OFF*/
static int led_state = 0;

/*PinNum*/
#define PinNum 4

void delay(uint32 time)
{
    volatile uint32 i;
    for (i = 0; i < time; i++)
    {
    }
}

void LEDM_Init(void)
{
    GPIO_init();
    led_state = 0;
}

void LEDM_Manage(void)
{
    GPIO_Write(PinNum, led_state);
    led_state = !led_state;

    delay(500000); // Make a delay for 500ms

    GPIO_Write(PinNum, led_state);
    led_state = !led_state;

    delay(500000); // Make a delay for 500ms
}