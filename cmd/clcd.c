// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2021
 * Dennis Lambe Jr., Professional Firmware Services, dennis@profirmserv.com
 */

#include <common.h>
#include <command.h>
#include <clcd.h>

static int do_clcd(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;
	int row = 0, col = 0;

	if (argc < 4)
		return CMD_RET_USAGE;

	row = simple_strtoul(argv[1], NULL, 10);
	col = simple_strtoul(argv[2], NULL, 10);

	if (row >= CLCD_ROWS || col >= CLCD_COLS)
		return CMD_RET_USAGE;

    clcd_goto(row, col);

	for (i = 3; i < argc; i++) {
		if (i > 3)
			clcd_write_string(" ");

		clcd_write_string(argv[i]);
	}

	return 0;
}

U_BOOT_CMD(
	clcd,	CONFIG_SYS_MAXARGS,	1,	do_clcd,
	"Write strings to a character LCD",
	"<row> <col> [args..]\n"
	"    - Write args to lcd starting at coordinates (row,col)"
);
