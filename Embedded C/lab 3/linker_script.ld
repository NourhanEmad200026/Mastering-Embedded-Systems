/* linker script: CortexM3
Eng.Nourhan
*/

MEMORY
{
	flash(RX) : ORIGIN = 0X08000000, LENGTH = 128k
	SRAM(RWX) : ORIGIN = 0X20000000, LENGTH = 20k
}

SECTIONS
{
	.text :{
		*(.vectors*)
		*(.text*)
		*(.rodata)
		E_text = . ;
	} > flash

	.data : {
		S_DATA = . ;
		*(.data)
		E_DATA = . ;
		. = ALIGN(4) ;
	}> SRAM AT> flash

	.bss : {
		_S_bss = . ;
		*(.bss)
		_E_bss = . ;
		. = ALIGN(4) ;
		. = . + 0x1000;
		Stack_top = . ;
	} > SRAM
}