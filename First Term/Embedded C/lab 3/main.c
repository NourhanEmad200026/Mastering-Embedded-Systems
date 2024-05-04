typedef unsigned volatile int vuint32_t;
#include <stdint.h>

//register addresses

#define RCC_BASE   0x40021000
#define GPIOA_BASE 0x40010800
#define RCC_APB *((vuint32_t *)(RCC_BASE + 0x18))
#define GPIOA_CRH *((vuint32_t *)(GPIOA_BASE + 0x04))

// bit fields
#define RCC_IOPAEN (1<<2)

typedef union{
	vuint32_t all_Fields;
	struct{
		vuint32_t reserved:13;
		vuint32_t Pin_13:1;
	}Pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE + 0x0C) ;

int main(void)
{
	RCC_APB |= RCC_IOPAEN;
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	while(1)
	{
		R_ODR->Pin.Pin_13 = 1;
		for(int i = 0; i<5000;i++);
		R_ODR->Pin.Pin_13 = 0;
		for(int i = 0; i<5000;i++);
	}
}