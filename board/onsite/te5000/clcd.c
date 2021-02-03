#include <common.h>
#include <clcd.h>
#include <i2c.h>
#include <dm.h>

#define CLCD_ADDR 0x3c

static int clcd_write(unsigned char offset, uint8_t *data, unsigned int len)
{
    struct udevice *bus, *dev;
    struct dm_i2c_chip *chip;
    struct i2c_msg msg[2];
    int ret;

    ret = uclass_get_device_by_seq(UCLASS_I2C, 0, &bus);
    if (ret < 0)
        return ret;

    ret = dm_i2c_probe(bus, CLCD_ADDR, 0, &dev);
    if (ret < 0)
        return ret;

    chip = dev_get_parent_platdata(dev);

    /* This exploits a bug in the at91 i2c driver which special-cases
     * a 2-element message list and copies the first message's paylaod
     * into the offset register rather than transmitting a separate
     * packet. */
    msg[0].addr = msg[1].addr = chip->chip_addr;
    msg[0].flags = msg[1].flags = chip->flags;
    msg[0].buf = &offset;
    msg[0].len = 1;

    msg[1].buf = data;
    msg[1].len = len;

    return dm_i2c_xfer(dev, msg, 2);
}

static int clcd_write_cmd(uint8_t cmd)
{
    return clcd_write(0x80, &cmd, 1);
}

int clcd_write_string(char *data)
{
    return clcd_write(0x40, (uint8_t *)data, strlen(data));
}

int clcd_goto(unsigned char row, unsigned char col)
{
    static const unsigned char
        ddram_row_addrs[] = {0x00, 0x20, 0x40, 0x60};
    unsigned char ddram_addr = ddram_row_addrs[row] + col;
    return clcd_write_cmd(0x80 | ddram_addr);
}

int clcd_write_string_at(unsigned char row, unsigned char col, char *data)
{
    int ret;

    ret = clcd_goto(row, col);
    if (ret < 0)
        return ret;
    return clcd_write_string(data);
}
