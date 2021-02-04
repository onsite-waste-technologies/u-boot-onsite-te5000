# Generate boot.scr:
# ./tools/mkimage -c none -A arm -T script -d netboot.cmd netboot.scr
#
# It requires a list of environment variables to be defined before load:
# boot_ip - TFTP and NFS server IP
# nfsmount - path to rootfs export on NFS server
#
# To invoke:
# setenv loadbootscr 'setenv autoload no; dhcp; tftp ${bootscraddr} ${boot_ip}:netboot.scr'
clcd 1 13 .

setenv kernaddr   23000000
setenv zimagepath zImage
setenv dtbpath    at91-onsite_te5000.dtb
setenv initrdpath initrd.img-onsite-te5000.cpio.gz
setenv staticargs console=ttyS0,115200 earlyprintk rw rootwait atmel.pm_modes=standby,ulp1

tftp ${kernaddr} ${boot_ip}:${zimagepath} || fatal 10 $? && exit
setexpr dtbaddr ${kernaddr} + ${filesize}

tftp ${dtbaddr} ${boot_ip}:${dtbpath} || fatal 11 $? && exit
setexpr initrdaddr ${dtbaddr} + ${filesize}

tftp ${initrdaddr} ${boot_ip}:${initrdpath} || fatal 12 $? && exit
setenv initrdsz ${filesize}

setenv bootargs root=/dev/nfs ip=dhcp nfsroot=${boot_ip}:${nfsmount},vers=3 ${staticargs} ${extraargs}

clcd 1 14 .
bootz ${kernaddr} ${initrdaddr}:${initrdsz} ${dtbaddr} || fatal 13 $? && exit
