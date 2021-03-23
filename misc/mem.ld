OUTPUT_ARCH( "riscv" )
ENTRY(_start)

SECTIONS
{
  PROVIDE(__stack_pointer$ = SRAM_BASE + SRAM_SIZE);
  . = __boot_addr;

  .text.init __boot_addr : ALIGN(4) {
    *(.text.entry)
    *(.text.init)
    *(.text.init.*)
    . = ALIGN(4);
  } >REGION_TEXT

  .text.itim : ALIGN(4) {
    *(.text.itim);
    *(.text.itim.*);
    . = ALIGN(4);
  } >ITIM AT >REGION_TEXT
  __itim_text_lma  = LOADADDR(.text.itim);
  __itim_text_vma  = ADDR(.text.itim);
  __itim_text_size = __itim_text_lma == __itim_text_vma  ? 0 : SIZEOF(.text.itim);

  .text.sram : ALIGN(4) {
    *(.text.sram);
    *(.text.sram.*);
    . = ALIGN(4);
  } >SRAM AT >REGION_TEXT
  __sram_text_lma  = LOADADDR(.text.sram);
  __sram_text_vma  = ADDR(.text.sram);
  __sram_text_size = __sram_text_lma == __sram_text_vma  ? 0 : SIZEOF(.text.sram);

  .flash : ALIGN(4) {
    *(.flash);
    *(.flash.*);
    . = ALIGN(4);
  } >FLASH

  .text : ALIGN(4) {
    *(.text*)
    . = ALIGN(4);
  } >REGION_EXEC AT >REGION_TEXT
  __exec_text_lma  = LOADADDR(.text);
  __exec_text_vma  = ADDR(.text);
  __exec_text_size = __exec_text_lma == __exec_text_vma ? 0 : SIZEOF(.text);

  .data : ALIGN(4) {
    *(.data* .rodata*);
    *(.got*);
    . = ALIGN(4);
  } >REGION_DATA AT >REGION_TEXT
  __data_lma  = LOADADDR(.data);
  __data_vma  = ADDR(.data);
  __data_size = __data_lma == __data_vma  ? 0 : SIZEOF(.data);

  .sdata : ALIGN(4) {
    __global_pointer$ = . + 0x800;
    *(.sdata* .srodata*)
    . = ALIGN(4);
  } >REGION_DATA AT >REGION_TEXT
  __sdata_lma  = LOADADDR(.sdata);
  __sdata_vma  = ADDR(.sdata);
  __sdata_size = __sdata_lma == __sdata_vma  ? 0 : SIZEOF(.sdata);

  /* bss segment */
  .bss : ALIGN(4) {
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
  } >REGION_DATA
  __bss_vma  = ADDR(.bss);
  __bss_size = SIZEOF(.bss);

  .sbss : ALIGN(4) {
    *(.sbss*)
    . = ALIGN(4);
  } >REGION_DATA
  __sbss_vma = ADDR(.sbss);
  __sbss_size = SIZEOF(.sbss);

  /* For uninitalized data in sram, use NOLOAD to reduce .bin size and avoid putting them in bss, which saves init time */
  .noinit (NOLOAD) : ALIGN(4) {
    *(.noinit*)
    . = ALIGN(4);
  } >REGION_DATA

  /* thread-local data segment */
  .tdata : ALIGN(4) {
    _tls_data = .;
    *(.tdata*)
    . = ALIGN(4);
  } >REGION_DATA AT >REGION_TEXT
  .tbss : ALIGN(4) {
    *(.tbss*)
    . = ALIGN(4);
  } >REGION_DATA

  /* End of uninitalized data segement */
  . = ALIGN(4);
  end = .;
  __malloc_start = .;

  PROVIDE(__stack_size = 0x1000);
  .stack : {
    ASSERT((__malloc_start + __stack_size < SRAM_BASE + SRAM_SIZE), "Error: Not enough SRAM for stack");
  }
}
