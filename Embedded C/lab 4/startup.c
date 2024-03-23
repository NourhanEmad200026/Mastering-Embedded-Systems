#include <stdint.h>

extern int main(void);

void Reset_Handler();

void Default_Handler()
{
    Reset_Handler();
}

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void H_Fault_Handler(void) __attribute__((weak, alias("Default_Handler")));

static unsigned long Stack_top[256];

void(* const g_p_fn_Vectors[])()__attribute__((section(".vectors")))={
    (void(*)()) ((unsigned long)Stack_top + sizeof(Stack_top)),
    &Reset_Handler,
    &NMI_Handler,
    &H_Fault_Handler,
};

extern unsigned int E_text;
extern unsigned int S_DATA;
extern unsigned int E_DATA ;
extern unsigned int _S_bss;
extern unsigned int _E_bss;

void Reset_Handler(void)
{
	// copy data section from rom to ram
	unsigned int DATA_size = (unsigned char*)&E_DATA - (unsigned char*)&S_DATA;
	unsigned char* P_src =(unsigned char*)&E_text ;
	unsigned char* P_des =(unsigned char*)&S_DATA;
	
	for(int i =0; i< DATA_size;i++)
	{
		*((unsigned char*)P_des ++) = *((unsigned char*)P_src++) ;	
	}

	// init .bss section in RAM and put 0 
	unsigned int BSS_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
	P_des = (unsigned char*)&_S_bss;
	for(int i =0; i<BSS_size;i++)
	{
		*((unsigned char*)P_des ++) = (unsigned char) 0 ;	
	}

	//jump to main 
    main();
}
