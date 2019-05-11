MEMORY {
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x1000 /* 4k */
	RAM (rwx) :  ORIGIN = 0x10000000, LENGTH = 0x0400 /* 1k */
}
__top_ram = 0x10000000 + 0x0400;
SECTIONS {
	.text : ALIGN(4) {
		_text = .;
		KEEP(*(.isr_vector))
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(SIZEOF(.data));
		KEEP(*(.after_vectors))
		*(.text*)
		*(.rodata*)
		. = ALIGN(4);
		_etext = .;
	} > FLASH
	.data : ALIGN(4) {
		_data = .;
		*(vtable)
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} > RAM AT>FLASH
	.bss : ALIGN(4) {
		_bss = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	} > RAM
	PROVIDE(_vStackTop = __top_ram);
/*	PROVIDE(_vStackTop = __top_RamLoc - 32); */ /* offset 32 for iap command set */
}
