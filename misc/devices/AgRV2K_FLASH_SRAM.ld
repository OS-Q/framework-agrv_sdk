INCLUDE ./AgRV2K_mem.ld

PROVIDE(__boot_addr = FLASH_BASE);
ASSERT(__boot_addr >= FLASH_BASE && __boot_addr < FLASH_BASE + FLASH_SIZE, "Wrong flash ram boot address");

REGION_ALIAS("REGION_TEXT", FLASH);
REGION_ALIAS("REGION_EXEC", SRAM);
REGION_ALIAS("REGION_DATA", SRAM);

INCLUDE ../mem.ld
