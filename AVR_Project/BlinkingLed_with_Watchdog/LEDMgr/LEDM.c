/**
 * Gpio.c
 *
 *  Created on  :   Tuesday 18 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include <avr/io.h>
#include "LEDM.h"
#include "gpio.h"

/*LED Pin number*/
#define LED_PIN PB0

#define LED_ON 1
#define LED_OFF 0

static uint32_t elapsedTime = 0;
static uint8_t ledState = LED_OFF;

void LEDM_Init(void)
{
    GPIO_Init(); // Initialise GPIO for LED
    GPIO_Write(LED_PIN, ledState);
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
        GPIO_Write(LED_PIN, ledState);

        // Reset elapsed time
        elapsedTime = 0;
    }

    // Indicate aliveness to the watchdog manager (stub function for now)
    // Replace with appropriate watchdog management code if needed
    WDGM_AlivenessIndication();
}
