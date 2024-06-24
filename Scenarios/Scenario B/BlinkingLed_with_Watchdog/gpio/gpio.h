#ifndef GPIO_H
#define GPIO_H

// Define test pins
#define TEST_PIN_MCU_Reset PB1 // Pin 1 in port B
#define TEST_PIN_WDCounter_Reset PB2 // Pin 2 in port B
#define TEST_PIN_LEDM PB3 // Pin 3 in port B
#define TEST_PIN_WDGM PB4 // Pin 4 in port B

void GPIO_Init(void);
void GPIO_Write(unsigned char PinId, unsigned char PinData);
#endif
