/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// RCC
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *((volatile uint32_t *)(RCC_BASE + 0x18))

// GPIOA
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *((volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_CRH *((volatile uint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_IDR *((volatile uint32_t *)(GPIOA_BASE + 0x08))
#define GPIOA_ODR *((volatile uint32_t *)(GPIOA_BASE + 0x0C))

// GPIOB
#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL *((volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_CRH *((volatile uint32_t *)(GPIOB_BASE + 0x04))
#define GPIOB_IDR *((volatile uint32_t *)(GPIOB_BASE + 0x08))
#define GPIOB_ODR *((volatile uint32_t *)(GPIOB_BASE + 0x0C))

void clock_init()
{
	// Enable GPIOA and GPIOB clocks
	RCC_APB2ENR |= (1 << 2); // Enable GPIOA clock
	RCC_APB2ENR |= (1 << 3); // Enable GPIOB clock
}

void GPIO_init()
{
	// PA1 input floating
	GPIOA_CRL &= ~(0xF << 4);  // Clear CNF1[1:0] and MODE1[1:0] (bits 7:4)
	GPIOA_CRL |= (0b0100 << 4); // Set CNF1[1:0] to 01 (floating input)

	// PA13 input floating
	GPIOA_CRH &= ~(0xF << 20);  // Clear CNF13[1:0] and MODE13[1:0] (bits 23:20)
	GPIOA_CRH |= (0b0100 << 20); // Set CNF13[1:0] to 01 (floating input)

	// PB1 push-pull output
	GPIOB_CRL &= ~(0xF << 4);   // Clear CNF1[1:0] and MODE1[1:0] (bits 7:4)
	GPIOB_CRL |= (0b0001 << 4); // Set CNF1[1:0] to 00 (push-pull), MODE1[1:0] to 10 (output mode, max speed 2 MHz)

	// PB13 push-pull output
	GPIOB_CRH &= ~(0xF << 20);  // Clear CNF13[1:0] and MODE13[1:0] (bits 23:20)
	GPIOB_CRH |= (0b0001 << 20); // Set CNF13[1:0] to 00 (push-pull), MODE13[1:0] to 10 (output mode, max speed 2 MHz)
}

int main(void)
{
	clock_init();
	GPIO_init();

	while(1)
	{
		if(((GPIOA_IDR & (1 << 1)) >> 1) == 0) // Check if PA1 is low
		{
			GPIOB_ODR ^= (1 << 1); // Toggle PB1
			while(((GPIOA_IDR & (1 << 1)) >> 1) == 0); // Wait until PA1 is high
		}
		if(((GPIOA_IDR & (1 << 13)) >> 13) == 1) // Check if PA13 is high
		{
			GPIOB_ODR ^= (1 << 13); // Toggle PB13
		}

		for(int i = 0; i < 5000; i++); // Simple delay
	}

}
