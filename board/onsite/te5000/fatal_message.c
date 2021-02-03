#include <fatal_message.h>
#include <common.h>
#include <clcd.h>

#define U_BOOT_BOOT_ERROR_ID 2

#define ret_on_err(stmt)                        \
    ({                                          \
        int ret = stmt;                         \
        if (ret < 0)                            \
            return ret;                         \
    })

int fatal_message(unsigned int op, unsigned int err)
{
    char buf[CLCD_COLS + 1];

    sprintf(buf, " %04x%04x %08x  ", U_BOOT_BOOT_ERROR_ID, op, err);

	ret_on_err(clcd_write_string_at(0, 0, "     BOOT ERROR     "));
	ret_on_err(clcd_write_string_at(1, 0, buf));
	ret_on_err(clcd_write_string_at(2, 0, "    Call OnSite     "));
	return     clcd_write_string_at(3, 0, "   (949) 409-4031   ");
}
