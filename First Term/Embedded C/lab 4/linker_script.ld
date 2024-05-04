MEMORY
{
	Flash(RX) : ORIGIN = 0x00000000, LENGTH = 128K
	SRAM(RWX) : ORIGIN  =0x20000000, LENGTH = 20K
}

SECTIONS
{
	.text : {
		*(.vectors*)
		*(.text*)
		*(.rodata)
		E_text = .;
	}>Flash

	.data : {
		S_DATA = .;
		*(.data)
		. = ALIGN(4);
		E_DATA = . ,
	}>SRAM AT> Flash

	.bss : {
		_S_bss = .;
		*(.bss*)
		_E_bss = .;
	}>SRAM
}