/*
 * STM32F103x8.h
 *
 *  Created on: May 28, 2024
 *      Author: nemad
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_
//-------------------------------------------------------------------
//Includes
//-------------------------------------------------------------------
#include "stdlib.h"
#include <stdint.h>

//-------------------------------------------------------------------
//Base Address for memories
//-------------------------------------------------------------------
#define FLASH_Memory_BASE                         0x08000000UL
#define System_Memory_BASE                        0x1FFFF000UL
#define SRAM_Memory_BASE                          0x20000000UL
#define Peripherals_BASE                          0x40000000UL
#define Cortex_M3_Internal_Peripherals_BASE       0xE0000000UL

//NVIC Register Map
#define NVIC_BASE                                 0xE000E100UL
#define NVIC_ISER0                                *(volatile uint32_t *)(NVIC_BASE + 0x00)
#define NVIC_ISER1                                *(volatile uint32_t *)(NVIC_BASE + 0x04)
#define NVIC_ISER2                                *(volatile uint32_t *)(NVIC_BASE + 0x08)
#define NVIC_ICER0                                *(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1                                *(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2                                *(volatile uint32_t *)(NVIC_BASE + 0x88)

//...............................
//Base Address AHB for memories
//...............................
#define RCC_BASE                                 0x40021000UL


//...............................
//Base Address for APB2 bus peripherals
//...............................

//GPIO
//A,B fully included in LQFP48
#define GPIOA_BASE                                0x40010800UL
#define GPIOB_BASE                                0x40010C00UL

//C,D partially included in LQFP48
#define GPIOC_BASE                                0x40011000UL
#define GPIOD_BASE                                0x40011400UL

//E not included in LQFP48
#define GPIOE_BASE                                0x40011800UL

//EXTI
#define EXTI_BASE                                 0x40010400UL

//AFIO
#define AFIO_BASE                                 0x40010000UL

//...............................
//Base Address for APB1 bus peripherals
//...............................

//-------------------------------------------------------------------
//Peripheral Register:
//-------------------------------------------------------------------

//...............................
//Peripheral Register:GPIO
//...............................
typedef struct{
	volatile uint32_t CRL  ;
	volatile uint32_t CRH  ;
	volatile uint32_t IDR  ;
	volatile uint32_t ODR  ;
	volatile uint32_t BSRR ;
	volatile uint32_t BRR  ;
	volatile uint32_t LCKR ;
}GPIO_TypeDef;

//...............................
//Peripheral Register:RCC
//...............................
typedef struct{
	volatile uint32_t CR       ;
	volatile uint32_t CFGR     ;
	volatile uint32_t CIR      ;
	volatile uint32_t APB2RSTR ;
	volatile uint32_t APB1RSTR ;
	volatile uint32_t AHBENR   ;
	volatile uint32_t APB2ENR  ;
	volatile uint32_t APB1ENR  ;
	volatile uint32_t BDCR     ;
	volatile uint32_t CSR      ;
}RCC_TypeDef;

//...............................
//Peripheral Register:EXTI
//...............................
typedef struct{
	volatile uint32_t IMR   ;
	volatile uint32_t EMR   ;
	volatile uint32_t RTSR  ;
	volatile uint32_t FTSR  ;
	volatile uint32_t SWIER ;
	volatile uint32_t PR    ;
}EXTI_TypeDef;

//...............................
//Peripheral Register:AFIO
//...............................
typedef struct{
	volatile uint32_t EVCR         ;
	volatile uint32_t MAPR         ;
	volatile uint32_t EXTICR[4]    ;
	uint32_t          RESERVED0    ;
	volatile uint32_t AFIO_MAPR2   ;
}AFIO_TypeDef;

//-------------------------------------------------------------------
//Peripheral Instants:
//-------------------------------------------------------------------

#define GPIOA         ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB         ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC         ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD         ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE         ((GPIO_TypeDef *)GPIOE_BASE)


#define RCC           ((RCC_TypeDef *)RCC_BASE)

#define EXTI          ((EXTI_TypeDef *)EXTI_BASE)

#define AFIO          ((AFIO_TypeDef *)AFIO_BASE)

//-------------------------------------------------------------------
//Clock Enable Macros
//-------------------------------------------------------------------

#define RCC_GPIOA_CLKEN()     (RCC->APB2ENR |= (1 << 2))
#define RCC_GPIOB_CLKEN()     (RCC->APB2ENR |= (1 << 3))
#define RCC_GPIOC_CLKEN()     (RCC->APB2ENR |= (1 << 4))
#define RCC_GPIOD_CLKEN()     (RCC->APB2ENR |= (1 << 5))
#define RCC_GPIOE_CLKEN()     (RCC->APB2ENR |= (1 << 6))


#define AFIO_GPIOE_CLKEN()     (RCC->APB2ENR |= (1 << 0))

//-------------------------------------------------------------------
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//NVIC MACROS Enable/Disable
//-------------------------------------------------------------------
//Enable
#define NVIC_IRQ6_EXTI0_Enable       (NVIC_ISER0 |= 1 << 6)
#define NVIC_IRQ7_EXTI1_Enable       (NVIC_ISER0 |= 1 << 7)
#define NVIC_IRQ8_EXTI2_Enable       (NVIC_ISER0 |= 1 << 8)
#define NVIC_IRQ9_EXTI3_Enable       (NVIC_ISER0 |= 1 << 9)
#define NVIC_IRQ10_EXTI4_Enable      (NVIC_ISER0 |= 1 << 10)
#define NVIC_IRQ23_EXTI5_9_Enable    (NVIC_ISER0 |= 1 << 23)
#define NVIC_IRQ40_EXTI10_15_Enable  (NVIC_ISER1 |= 1 << 8)
//Disable
#define NVIC_IRQ6_EXTI0_Disable       (NVIC_ICER0 |= 1 << 6)
#define NVIC_IRQ7_EXTI1_Disable       (NVIC_ICER0 |= 1 << 7)
#define NVIC_IRQ8_EXTI2_Disable       (NVIC_ICER0 |= 1 << 8)
#define NVIC_IRQ9_EXTI3_Disable       (NVIC_ICER0 |= 1 << 9)
#define NVIC_IRQ10_EXTI4_Disable      (NVIC_ICER0 |= 1 << 10)
#define NVIC_IRQ23_EXTI5_9_Disable    (NVIC_ICER0 |= 1 << 23)
#define NVIC_IRQ40_EXTI10_15_Disable  (NVIC_ICER1 |= 1 << 8)

//-------------------------------------------------------------------
//-------------------------------------------------------------------

//==================================================================
//Interrupt Vector Table
//==================================================================
#define EXTI0_IRQ               6
#define EXTI1_IRQ               7
#define EXTI2_IRQ               8
#define EXTI3_IRQ               9
#define EXTI4_IRQ               10
#define EXTI5_IRQ               23
#define EXTI6_IRQ               23
#define EXTI7_IRQ               23
#define EXTI8_IRQ               23
#define EXTI9_IRQ               23
#define EXTI10_IRQ              40
#define EXTI11_IRQ              40
#define EXTI12_IRQ              40
#define EXTI13_IRQ              40
#define EXTI14_IRQ              40
#define EXTI15_IRQ              40
//-------------------------------------------------------------------
//-------------------------------------------------------------------

#endif /* INC_STM32F103X6_H_ */
