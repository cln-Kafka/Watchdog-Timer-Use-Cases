/**
 * Gpio.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include "GPIO.h"
#include "Rcc.h"
#include "Utils.h"
#include "Std_Types.h"

/*PortName*/
#define GPIO_A 'A'

/*PinNum*/
#define PinNum 4

/*PinMode*/
#define GPIO_OUTPUT 0x01

/*DefaultState*/
#define GPIO_PUSH_PULL 0x00

/*Data*/
#define LOW 0x00
#define HIGH 0x01

/*GPIO Registers*/
#define GPIOA_BASE_ADDR 0x40020000
#define GPIOA_MODER REG32(GPIOA_BASE_ADDR, 0x00)
#define GPIOA_OTYPER REG32(GPIOA_BASE_ADDR, 0x04)
#define GPIOA_OSPEEDR REG32(GPIOA_BASE_ADDR, 0x08)
#define GPIOA_PUPDR REG32(GPIOA_BASE_ADDR, 0x0C)
#define GPIOA_ODR REG32(GPIOA_BASE_ADDR, 0x14)
#define GPIOA_BSRR REG32(GPIOA_BASE_ADDR, 0x18)

void GPIO_Init(void)
{
    // Enable the clock for Port A
    RCC_init();
    Rcc_Enable(RCC_GPIOA);

    // Set the mode to output (01)
    GPIOA_MODER &= ~(0x03 << (PinNum * 2));
    GPIOA_MODER |= (GPIO_OUTPUT << (PinNum * 2));

    // Set the output type to push-pull (0)
    GPIOA_OTYPER &= ~(0x01 << PinNum);
    GPIOA_OTYPER |= (GPIO_PUSH_PULL << PinNum);

    // Set the output speed to low (00)
    GPIOA_OSPEEDR &= ~(0x03 << (PinNum * 2));

    // Set no pull-up, no pull-down (00)
    GPIOA_PUPDR &= ~(0x03 << (PinNum * 2));
}

void GPIO_Write(unsigned char PinId, unsigned char PinData)
{
    // Extract the mode of the pin
    uint8 Check_PinMode = (GPIOA_MODER & (0x3 << (2 * PinId))) >> (2 * PinId);
    // Check if the PinMode is Output (However, we already know because it is globally defined)
    if (Check_PinMode == 0x01)
    {
        if (PinData)
        {
            GPIOA_ODR |= (PinData << PinId); // Set bit
        }
        else
        {
            GPIOA_ODR &= ~(PinData << PinId); // Reset bit
        }
    }
}

// void GPIO_Write(unsigned char PinId, unsigned char PinData)
// {
//     if (PinData)
//     {
//         GPIOA_BSRR = (1 << PinId); // Set bit
//     }
//     else
//     {
//         GPIOA_BSRR = (1 << (PinId + 16)); // Reset bit
//     }
// }