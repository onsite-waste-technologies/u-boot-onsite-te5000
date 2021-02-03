// SPDX-License-Identifier: GPL-2.0+

#ifndef _CLCD_H_
#define _CLCD_H_

#define CLCD_ROWS 4
#define CLCD_COLS 20

int clcd_goto(unsigned char row, unsigned char col);
int clcd_write_string(char *data);
int clcd_write_string_at(unsigned char row, unsigned char col, char *data);

#endif
