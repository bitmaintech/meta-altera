DESCRIPTION = "Cgminer bitcoin miner SW"
LICENSE = "CLOSED"
DEPENDS = "ncurses curl"
SRCREV = "4.10.0"
PR = "r1"

SRC_URI = "file://cgminer-1.0/*"

S = "${WORKDIR}/cgminer"
CFLAGS_prepend = "-I ${S}/compat/jansson-2.9/src"

EXTRA_OECONF = "\
    --enable-bitmain_soc \
    --disable-adl \
    --disable-opencl \
    --disable-libcurl \ 
    --enable-bitmain_${MINER_TYPE}"
		 
do_configure_prepend() {
        autoreconf -fiv
}

do_compile_append() {
    make api-example
}

do_install_append() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/api-example ${D}${bindir}/cgminer-api
}
 
inherit autotools pkgconfig
