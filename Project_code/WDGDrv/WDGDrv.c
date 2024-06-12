/**
 * WDGDRV.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */

#include <stdint.h>
#include "NVIC.h"

// Memory map addresses for RCC and WWDG peripherals
#define RCC_BASE_ADDR 0x40023800
#define WWDG_BASE_ADDR 0x40002C00

// RCC peripheral registers
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE_ADDR + 0x40))

// WWDG peripheral registers
#define WWDG_CR (*(volatile uint32_t *)(WWDG_BASE_ADDR + 0x00))
#define WWDG_CFR (*(volatile uint32_t *)(WWDG_BASE_ADDR + 0x04))
#define WWDG_SR (*(volatile uint32_t *)(WWDG_BASE_ADDR + 0x08))

// WWDG bit definitions
#define WWDG_CR_WDGA (1 << 7)
#define WWDG_CR_T (0x7F)

#define WWDG_CFR_W (0x7F)
#define WWDG_CFR_WDGTB (3 << 7)
#define WWDG_CFR_EWI (1 << 9)

// Interrupt handler for WWDG
void WWDG_IRQHandler(void)
{
    // Check for early wakeup interrupt
    if (WWDG_SR & WWDG_CFR_EWI)
    {
        // Clear the early wakeup interrupt flag
        WWDG_SR &= ~(WWDG_CFR_EWI);

        // Reload the WWDG counter
        WWDG_CR = WWDG_CR_WDGA | WWDG_CR_T;
    }
}

// Initialize the Window Watchdog (WWDG)
void WDGDrv_Init(void)
{
    // Enable clock for WWDG
    RCC_APB1ENR |= (1 << 11); // Set bit 11

    // Configure WWDG
    // Set the prescaler to divide by 8
    WWDG_CFR |= (2 << 7); // Set bits 8 and 7

    // Set the window value to maximum (0x7F)
    WWDG_CFR |= WWDG_CFR_W;

    // Enable Early Wakeup Interrupt
    WWDG_CFR |= WWDG_CFR_EWI;

    // Enable WWDG and set the counter value
    WWDG_CR = WWDG_CR_WDGA | WWDG_CR_T;

    // Enable WWDG interrupt in NVIC
    Nvic_EnableInterrupt(0);
    // (You may need to implement this depending on your platform)
}

// Definition of the function
void WDGDrv_IsrNotification(void)
{
    // Condition 1: WDGM_MainFunction is not stuck
    // (You need to implement this condition based on your application logic)
    // Example: Check if some periodic task or heartbeat signal is being received regularly

    // Condition 2: The WDGM State set by the WDGM_MainFunction is OK
    // (You need to implement this condition based on your application logic)
    // Example: Check if some system state variable indicates that everything is operating normally

    // If both conditions are satisfied, refresh the watchdog timer
    if (1 /* Condition 1 */ && 1 /* Condition 2 */)
    {
        // Reload the WWDG counter
        WWDG_CR = WWDG_CR_WDGA | WWDG_CR_T;
    }
}
