DESCRIPTION = "DEVMEM2"
LICENSE = "CLOSED"

SRC_URI = "file://devmem2/* \
	"

S = "${WORKDIR}/${PN}"
PACKAGES = "${PN}"

do_compile() {
	make
}

do_install_append() {
	install -d ${D}${bindir}
	install -m 0755 ${S}/devmem2 ${D}${bindir}/devmem2
}


