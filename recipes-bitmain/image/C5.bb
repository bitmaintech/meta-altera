export IMAGE_BASENAME = "C5"
IMAGE_INSTALL = " \
	busybox \
	base-files \
	initscripts \
	sysvinit \
	sysvinit-pidof \
	angstrom-version \
	shadow \
	i2c-tools \
	screen \
	dropbear \
	libcurl \
	lighttpd \
	cgminer \
	dtc \
	stunnel \
	initc-bin \
	openssl \
	mtd-utils \
	curl \
	udev \
	ntp \
	ntpdate \
	netbase \
	avahi \
	monitor-ipsig \
	monitor-recobtn \
        devmem2 \
"
#omap3-mkcard 			   
#cgminer 
#bitmain-spi-s3
#bitmain-lcd
inherit image

do_rootfs_append() {
	echo "do_build_append"
}

