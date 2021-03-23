/*======================================================================*/
/* Proxy kernel linker script                                           */
/*======================================================================*/
/* This is the linker script used when building the proxy kernel. */

/*----------------------------------------------------------------------*/
/* Setup                                                                */
/*----------------------------------------------------------------------*/

/* The OUTPUT_ARCH command specifies the machine architecture where the
   argument is one of the names used in the BFD library. More
   specifically one of the entires in bfd/cpu-mips.c */

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

/*----------------------------------------------------------------------*/
/* Sections                                                             */
/*----------------------------------------------------------------------*/

SECTIONS
{
  /* text: test code section */
  PROVIDE(__boot_addr = ROM_BASE);
  . = __boot_addr;
  .text.init : { *(.text.init) }
  .text : { *(.text*) }
  . = ALIGN(0x4);
  __text_end$ = .;

  . = ITIM_BASE; /* ITIM */
  /*
  .text.itim : AT (__text_end$ + __data_size + __sdata_size) {
    __itim_text_lma = LOADADDR(.text.itim);
    __itim_text_vma = .;
    *(.itim.text);
  }
  . = ALIGN(0x4);
  __itim_text_size = . - __itim_text_vma;
  */

  . = RAM_BASE;
  __stack_pointer$ = . + RAM_SIZE;

  . = ALIGN(0x1000);
  .tohost : { *(.tohost) }

  /* data segment */
  . = ALIGN(0x4);
  .data : AT ( __text_end$ ) {
    __data_lma = LOADADDR(.data);
    __data_vma = .;
    *(.data .data* .rodata*);
  }
  . = ALIGN(0x4);
  __data_size = . - __data_vma;
  .sdata : AT ( __text_end$ + __data_size ) {
    __sdata_lma = LOADADDR(.sdata);
    __sdata_vma = .;
    __global_pointer$ = . + 0x800;
    *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata*)
    *(.sdata .sdata* .gnu.linkonce.s.*)
  }
  . = ALIGN(0x4);
  __sdata_size = . - __sdata_vma;

  /*
  .text.sram : AT (__text_end$ + __data_size + __sdata_size) {
    __sram_text_lma = LOADADDR(.text.sram);
    __sram_text_vma = .;
    *(.sram.text);
  }
  . = ALIGN(0x4);
  __sram_text_size = . - __sram_text_vma;
  */

  /* bss segment */
  .sbss : {
    __sbss_vma = .;
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
  }
  __sbss_size = . - __sbss_vma;
  .bss : {
    __bss_vma = .;
    *(.bss)
  }
  __bss_size = . - __bss_vma;

  /* thread-local data segment */
  /*
  .tdata :
  {
    _tls_data = .;
    *(.tdata.begin)
    *(.tdata)
    *(.tdata.end)
  }
  .tbss :
  {
    *(.tbss)
    *(.tbss.end)
  }
  */

  /* End of uninitalized data segement */
  _end = .;
  . = ALIGN(4);
  __malloc_start = .;
}

