/**
 * Gpio.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include "LEDM.h"
#include "GPIO.h"

/*Standard Types*/
typedef unsigned char uint8;
typedef unsigned long uint32;

/*PinNum*/
#define PinNum 4

#define LED_ON 1
#define LED_OFF 0

// Time elapsed since the last state change, Maximum value is 500
static uint32 elapsedTime = 0;
static uint8 ledState = LED_OFF; // Initially the LED is off

void LEDM_Init(void)
{
    GPIO_Init();
    GPIO_Write(PinNum, ledState);
}

void LEDM_Manage(void)
{
    // Increment elapsed time by 10ms
    elapsedTime += 10;

    // Check if 500ms has passed
    if (elapsedTime >= 500)
    {
        // Toggle LED state
        ledState = (ledState == LED_ON) ? LED_OFF : LED_ON;
        GPIO_Write(PinNum, ledState);

        // Reset the elapsed time counter
        elapsedTime = 0;
    }

    // Indicate aliveness to the watchdog manager
    WDGM_AlivenessIndication();
}
