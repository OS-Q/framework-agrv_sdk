INCLUDE ./AgRV2K_mem.ld

PROVIDE(__boot_addr = ROM_BASE);
ASSERT(__boot_addr >= ROM_BASE && __boot_addr < ROM_BASE + ROM_SIZE, "Wrong ROM boot address");

REGION_ALIAS("REGION_TEXT", ROM);
REGION_ALIAS("REGION_EXEC", ROM);
REGION_ALIAS("REGION_DATA", SRAM);

INCLUDE ../mem.ld
