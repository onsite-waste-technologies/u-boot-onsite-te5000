# Generate boot.scr:
# ./tools/mkimage -c none -A arm -T script -d autoboot.cmd boot.scr
#
# It requires a list of environment variables to be defined before load:
# rootpart
#
clcd 1 13 .

setenv bootpart   1
setenv rootrwpart 4
setenv kernaddr   23000000
setenv zimagepath boot/zImage
setenv dtbpath    boot/at91-onsite_te5000.dtb
setenv initrdpath boot/initrd.img-onsite-te5000.cpio.gz
setenv staticargs console=ttyS0,115200 earlyprintk rw rootwait atmel.pm_modes=standby,ulp1

ext4load mmc 0:${rootpart} ${kernaddr} ${zimagepath} || fatal 10 $? && exit
setexpr dtbaddr ${kernaddr} + ${filesize}

ext4load mmc 0:${rootpart} ${dtbaddr} ${dtbpath} || fatal 11 $? && exit
setexpr initrdaddr ${dtbaddr} + ${filesize}

ext4load mmc 0:${rootpart} ${initrdaddr} ${initrdpath} || fatal 12 $? && exit
setenv initrdsz ${filesize}

setenv bootargs rootro=/dev/mmcblk0p${rootpart} rootrw=/dev/mmcblk0p${rootrwpart} ${staticargs} ${extraargs}

clcd 1 14 .
bootz ${kernaddr} ${initrdaddr}:${initrdsz} ${dtbaddr} || fatal 13 $? && exit
