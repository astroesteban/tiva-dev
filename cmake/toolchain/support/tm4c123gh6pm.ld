/*
 * File:        tm4c123gh6pm.ld
 * Author:      Esteban Duran (@astroesteban)
 * Version:     1.0.0
 * Description: Linker file for the Texas Instruments TM4C Launchpad
 * Useful Link: https://blog.thea.codes/the-most-thoroughly-commented-linker-script/
*/


/*
   OUTPUT_FORMAT configures the linker to use a platform-specific BFD
   backend to generate ELF files. BFD backends instruct the linker on
   how to properly create the ELF sections for a given platform.

   The first is the default BFD. The second and third arguments are used
   when big (-EB) or little (-EL) endian is requested.

   Since the SAM D series are configured with only little endian support,
   "elf32-littlearm" is used across the board. This option seems to be
   included by Atmel/Microchip out of an abundance of caution, as
   arm-none-eabi-ld will do the right thing and use "elf32-littlearm" by
   default.

   The list of acceptable values can be obtained using `objdump -i`.

   https://sourceware.org/binutils/docs/ld/Format-Commands.html#Format-Commands
   https://sourceware.org/binutils/docs/ld/BFD.html

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
*/


/*
    These variables are used by the following "MEMORY" command to define the 
    various memory spaces.
*/
FLASH_SIZE = 0x40000;      /* 256kB */
SRAM_SIZE  = 0x8000;       /*  32kB */


/*
    This section declares blocks of memories for specific purposes. Since an
    ARM's adress space is generally split between flash, SRAM, peripherals, and
    other regions, it's necessary to tell the linker what sections go where.
    The MEMORY block is used in the SECTIONS block below.

    We start with the flash memory region. On the TM4C flash starts at address
    0x00000000 and is contiguous right up to the size of the flash. Flash is 
    marked a rx so that the linker knows that this space is read-only (r) 
    and executable (x).

    The SRAM block is mapped to the CPU's SRAM and it's where the stack, heap, 
    and all variables will go. For the TM4C the SRAM starts at address
    0x20000000 and is contiguous for the size of the SRAM. We also mark this
    section as rwx so that the linker knows that this space has read-write
    capabilities and executable.

    https://sourceware.org/binutils/docs/ld/MEMORY.html#MEMORY
*/
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = FLASH_SIZE
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = SRAM_SIZE
}


/*
    The sections command tells the linker how to combine the input files into 
    an output ELF and where segments belong in memory. The linker takes a set 
    of input files containing the "input sections" and uses this to map them to
    "output sections" which are placed in the output ELF file.

    The bss section reserves RAM space for declared but uninitialized variables.

    https://sourceware.org/binutils/docs/ld/SECTIONS.html#SECTIONS
    http://www.sco.com/developers/gabi/latest/ch4.sheader.html#special_sections
*/
SECTIONS
{
    /* 
     * Initial stack pointer pointing to top of stack,starts from higher 
     * addresses i.e ORIGIN(SRAM) + LENGTH(SRAM)-1 in this case 0x20007FFF to 
     * lower addesses i.e those lesser than 0x20007FFF to 0x2000000,which is 
     * the origina address of SRAM, until it comes in contact with .bss or 
     * .data in which case a buffer overflow occurs
    */
    PROVIDE( _stack_ptr = ORIGIN(SRAM) + LENGTH(SRAM));

    /* The text segment contains program code and read-only data. */
    .text :
    {
        _text = .;                              /* beginning of .text segment,also called code memory */
        KEEP(*(.vector_table))                  /* vector table defined in tm4c_startup.c to be included */
        *(.text*)                               /* other code */
        *(.rodata*)                             /* constants go here */
        _etext = .;                             /* end of .text segment */
    } > FLASH                                   /* starts at the FLASH segment */

    /* data, initialized variables, to be copied to RAM upon <RESET> by tm4c_startup.c */
    .data :
    {
        _data = .;                              /* beginning of .data segment */
        *(.data*)                               /* data goes here */
        _edata = .;                             /* end of .data segment */
    } > SRAM AT >FLASH                          /* .data segment starts directly after the .text section in FLASH */

    /* uninitialized data which is initialized to 0 upon <RESET> by tm4c_startup.c */
    .bss :
    {
        _bss = .;                               /* beginning of .bss segment */
        *(.bss*)                                /* .bss content goes here */
        *(COMMON)
        _ebss = .;                              /* end of .bss segment */
    } > SRAM
}