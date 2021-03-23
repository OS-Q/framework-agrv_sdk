INCLUDE ./AgRV2K_mem.ld

PROVIDE(__stack_pointer$ = ITIM_BASE + ITIM_SIZE / 4 * 3);
PROVIDE(__boot_addr = ITIM_BASE);
ASSERT(__boot_addr >= ITIM_BASE && __boot_addr < ITIM_BASE + ITIM_SIZE, "Wrong ITIM boot address");

REGION_ALIAS("REGION_TEXT", ITIM);
REGION_ALIAS("REGION_EXEC", ITIM);
REGION_ALIAS("REGION_DATA", ITIM);

INCLUDE ../mem.ld
