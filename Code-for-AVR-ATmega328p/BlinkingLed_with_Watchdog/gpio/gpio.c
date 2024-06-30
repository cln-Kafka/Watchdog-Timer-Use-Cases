/**
 * gpio.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Nada Amr, Mohamed Samy 
 */

#include <avr/io.h>
#include "gpio.h"

/*LED Pin number*/
#define LED_PIN PB0             // Pin 0 in port B

void GPIO_Init(void)
{
    // Initialise pin 0 in port B as output
    DDRB |= (1 << LED_PIN);
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
