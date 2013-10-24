DESCRIPTION = "Linux Unit tests"
AUTHOR = "someone@altera.com"
SECTION = "Tests"
# TODO: update license
LICENSE = "GPLv2"
LIC_FILES_CHKSUM="file://driver/LICENSE;md5=a2c916c096f4cf1974df39bedd5cb1bf"
S="${WORKDIR}/linux-test"
BP="${BPN}"
DEPENDS = "virtual/kernel vlan"

# git:/git.linaro.org/git-ro/arm/ds5/gator.git;protocol=http
# This variable points to rocketboards by default. It can be overridden
# by setting it in the shell env and by adding it to BB_WHITE_ENV
LINUX_TEST_REPO=http://git.rocketboards.org/linux-test

SRC_URI = "${LINUX_TEST_REPO}"

do_compile() {

	cd ${S}
	make CROSS_COMPILE=${TARGET_PREFIX} clean
        make CROSS_COMPILE=${TARGET_PREFIX}
}

do_install() {
	
	install -d ${D}/unit-tests/
	make INSTALL_PATH=${D}/unit-tests/
}
