// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2021
 * Dennis Lambe Jr., Professional Firmware Services, dennis@profirmserv.com
 */

#include <common.h>
#include <command.h>
#include <fatal_message.h>

static int do_fatal(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned int op = 0, err = 0;

	if (argc != 3)
		return CMD_RET_USAGE;

	op = simple_strtoul(argv[1], NULL, 10);
	err = simple_strtoul(argv[2], NULL, 10);

    fatal_message(op, err);

    return 0;
}

U_BOOT_CMD(
	fatal,	3,	1,	do_fatal,
	"Write a fatal error code to the character LCD",
	"<op_code> <err_code>"
);
