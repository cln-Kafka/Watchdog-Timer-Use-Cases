///**
// * NVIC.c
// *
// *  Created on  :   Sun 09 JUN 2024
// *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
// */
//
//#include "Nvic.h"
//#include <stdint.h>
//
//#define NVIC_ISER_BASE (0xE000E100)
//#define NVIC_ICER_BASE (0xE000E180)
//
//// Number of NVIC registers
//#define NVIC_REG_COUNT 8
//
//// initializing 'NVIC_ISER' as an array of pointers pointing to the memory addresses starting from 'NVIC_ISER_BASE'
//#define NVIC_ISER ((volatile uint32 *)(NVIC_ISER_BASE))
//// initializing 'NVIC_ICER' as an array of pointers pointing to the memory addresses starting from 'NVIC_ICER_BASE'
//#define NVIC_ICER ((volatile uint32 *)(NVIC_ICER_BASE))
//
//void Nvic_EnableInterrupt(uint8_t IRQn)
//{
//  uint8_t regIndex = IRQn / 32;    // determine which ISER will be used
//  uint8_t bitPosition = IRQn % 32; // determine the bit to set
////  SET_BIT(*(NVIC_ISER + regIndex), bitPosition);
//}
//
//void Nvic_DisableInterrupt(uint8_t IRQn)
//{
//  uint8_t regIndex = IRQn / 32;    // determine which ISER will be used
//  uint8_t bitPosition = IRQn % 32; // determine the bit to clear
//  SET_BIT(*(NVIC_ICER + regIndex), bitPosition);
//}
