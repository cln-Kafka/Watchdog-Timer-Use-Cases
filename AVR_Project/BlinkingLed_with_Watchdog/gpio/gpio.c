#include <avr/io.h>
#include "gpio.h"

#define LED_PIN PB0

void GPIO_Init(void)
{
    // Initialise pin 4 in port B as output
    DDRB |= (1 << LED_PIN);
}

void GPIO_Write(unsigned char PinId, unsigned char PinData)
{
    if (PinData == 1)
    {
        PORTB |= (1 << PinId); // Set the pin high
    }
    else
    {
        PORTB &= ~(1 << PinId); // Set the pin low
    }
}
