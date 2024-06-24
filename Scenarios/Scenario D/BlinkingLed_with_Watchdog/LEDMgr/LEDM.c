/**
 * LEDM.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include <avr/io.h>
#include "LEDM.h"
#include "gpio.h"
#include "WDGM.h"

/*LED Pin number*/
#define LED_PIN PB0

/*LED States*/
#define LED_ON 1
#define LED_OFF 0

/*Global Variables*/
static uint8_t ledState = LED_ON;               // Initial LED State
static uint32_t elapsedTime = 0;                // Time elapsed since the last LEDM_Manage Call

void LEDM_Init(void)
{
    // Initialise GPIO for LED
    GPIO_Init();
    // Set the initial state of the LED to "ON"
    GPIO_Write(LED_PIN, ledState);

}

void LEDM_Manage(void)
{
    // toggle ledmanage
    PORTB ^= (1 << TEST_PIN_LEDM);

    // Increment elapsed time by 10ms
    elapsedTime += 10;

    // Check if 500ms has passed
    if (elapsedTime >= 500)
    {
        // Toggle LED state
        ledState = (ledState == LED_ON) ? LED_OFF : LED_ON;

        // Write the new state to the LED
        GPIO_Write(LED_PIN, ledState);

        // Reset elapsed time
        elapsedTime = 0;
    }

    // Call WDGM Aliveness Indication to indicate that the LEDM_Manage function is running
    // This counts the number of times the LEDM_Manage function is called
     WDGM_AlivenessIndication();
}
