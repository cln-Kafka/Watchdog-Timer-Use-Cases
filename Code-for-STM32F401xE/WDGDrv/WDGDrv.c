/**
 * WDGDRV.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include <stdint.h>
#include "WDGM.h"

/*Base addresses for peripherals*/
#define RCC_BASE 0x40023800  // Memory Map: page 38
#define WWDG_BASE 0x40002C00 // Memory Map: page 39

/*Register Offsets*/
#define RCC_APB1ENR *((volatile uint32_t *)(RCC_BASE + 0x40))
#define WWDG_CR *((volatile uint32_t *)(WWDG_BASE + 0x00))
#define WWDG_CFR *((volatile uint32_t *)(WWDG_BASE + 0x04))
#define WWDG_SR *((volatile uint32_t *)(WWDG_BASE + 0x08))

/*Bit Positions*/
// Control Register (CR) -> WWDG: page 431
#define WWDG_CR_WDGA 7 // for activated watchdog
#define WWDG_CR_T 0
#define WWDG_CR_T_Msk (0x7F << WWDG_CR_T)

// Configuration Register (CFR) -> WWDG: page 432
#define WWDG_CFR_EWI 9   // Early Wakeup Interrupt
#define WWDG_CFR_WDGTB 7 // Prescaler
#define WWDG_CFR_W 0     // Window value

// Status Register (SR) -> WWDG: page 432
#define WWDG_SR_EWIF 0

#define RCC_APB1ENR_WWDGEN 11 // for enabling the clock, RCC: page 138

// /*For initialization of WWDG*/
// #define PCLK1_FREQ 16000
// #define WWDG_PRESCALER 8
// #define WWDG_TIMEOUT 50

// // Calculate the counter value based on the desired timeout and prescaler
// #define WWDG_COUNTER_VALUE (uint8_t)(((PCLK1_FREQ / 4096) * WWDG_TIMEOUT) / (2 * WWDG_PRESCALER))

#define APB1CLK 16000000
#define PRESCALER 3

#define WWDG_COUNTER_VALUE (uint8_t)(((50 * APB1CLK) / (1000 * 4096 * (2 << PRESCALER))) - 1) // at 16MHZ, should be about 5

/*For enabling the interrupt (NVIC), page 203*/
#define WWDG_IRQn 0 // from the datasheet, NVIC: page 203

/*NVIC*/
#define NVIC_ISER_BASE (0xE000E100)
#define NVIC_ISER ((volatile uint32_t *)(NVIC_ISER_BASE))

void WDGDrv_Init(void)
{
    // Enable the clock for the WWDG
    RCC_APB1ENR |= (1 << RCC_APB1ENR_WWDGEN); // RCC: page 138

    // We can combine the following in one line, but I split it to be easy to understand
    WWDG_CFR |= (1 << WWDG_CFR_EWI);   // Enable "Early Wakeup Interrupt"
    WWDG_CFR |= (3 << WWDG_CFR_WDGTB); // Set prescaler to 8 (WDGTB = 3, (11) in binary)
    WWDG_CFR |= (0x7F);                // Disable window by setting it to maximum value

    // WWDG_CR = (WWDG_COUNTER_VALUE & WWDG_CR_T_Msk);
    WWDG_CR |= (WWDG_COUNTER_VALUE << WWDG_CR_T);
    // Enable/Activate the WWDG
    WWDG_CR |= (1 << WWDG_CR_WDGA);

    // Enable the Early Wakeup Interrupt in the NVIC
    // uint8_t regIndex = WWDG_IRQn / 32;    // determine which ISER will be used
    // uint8_t bitPosition = WWDG_IRQn % 32; // determine the bit to set
    // *(NVIC_ISER + regIndex) |= (1 << bitPosition);
    // Nvic_EnableInterrupt(WWDG_IRQn);
}

void WDGDrv_IsrNotification(void)
{
    WDGM_StatusType wdgmStatus = WDGM_PovideSuppervisionStatus();

    // Check if the WDGM status is OK
    if (wdgmStatus == OK && (WWDG_SR & (1 << WWDG_SR_EWIF)))
    {
        // Reload the WWDG counter
        WWDG_CR = (WWDG_COUNTER_VALUE & WWDG_CR_T_Msk) | (1 << WWDG_CR_WDGA);
    }
}

// /* WWDG interrupt handler */
// void WWDG_IRQHandler(void)
// {
//     // Check if the Early Wakeup Interrupt flag is set
//     if (WWDG_SR & (1 << WWDG_SR_EWIF))
//     {
//         // Clear the Early Wakeup Interrupt Flag
//         WWDG_SR &= ~(1 << WWDG_SR_EWIF);

//         // Call the ISR Notification to potentially refresh the watchdog
//         WDGDrv_IsrNotification();
//     }
// }