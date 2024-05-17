

typedef volatile unsigned long vuint32_t;

#define SYSCTL_RCGC2_R    *((vuint32_t*)(0x400FE108))
#define GPIO_PORTF_DATA_R *((vuint32_t*)(0x400253FC))
#define GPIO_PORTF_DIR_R  *((vuint32_t*)(0x40025400))
#define GPIO_PORTF_DEN_R  *((vuint32_t*)(0x4002551C))

int main(void)
{
	vuint32_t delay_count;
	SYSCTL_RCGC2_R = 0x00000020;
	for(delay_count = 0; delay_count< 200;delay_count++);
	GPIO_PORTF_DIR_R |= 1<< 3;
	GPIO_PORTF_DEN_R |= 1<< 3;
	while(1)
	{
		GPIO_PORTF_DATA_R |= 1<<3;
		for(delay_count = 0; delay_count< 200;delay_count++);
		GPIO_PORTF_DATA_R &=~ (1<<3);
		for(delay_count = 0; delay_count< 200;delay_count++);
	}
	return 0;
}