INCLUDE ./AgRV2K_mem.ld

PROVIDE(__boot_addr = SRAM_BASE);
ASSERT(__boot_addr >= SRAM_BASE && __boot_addr < SRAM_BASE + SRAM_SIZE, "Wrong ram boot address");

REGION_ALIAS("REGION_TEXT", SRAM);
REGION_ALIAS("REGION_EXEC", SRAM);
REGION_ALIAS("REGION_DATA", SRAM);

INCLUDE ../mem.ld
