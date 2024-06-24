/**
 * gpio.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Nada Amr, Mohamed Samy, Nouran Mahmoud
 */

#include <avr/io.h>
#include "gpio.h"

/*LED Pin number*/
#define LED_PIN PB0             // Pin 0 in port B

void GPIO_Init(void)
{
    // Initialise pin 0 in port B and test pins for the oscilloscope as output 
    DDRB |= (1 << LED_PIN) | (1 << TEST_PIN_WDGM) | (1<<TEST_PIN_LEDM) | (1 << TEST_PIN_MCU_Reset)| (1 << TEST_PIN_WDCounter_Reset);
}

void GPIO_Write(unsigned char PinId, unsigned char PinData)
{   
    if (PinData == 1)
    {
        PORTB |= (1 << PinId);  // Set the pin high (Set)
    }
    else
    {
        PORTB &= ~(1 << PinId); // Set the pin low (Clear)
    }
}
