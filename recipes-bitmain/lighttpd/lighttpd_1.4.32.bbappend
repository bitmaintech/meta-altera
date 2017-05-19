FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-1.0:"

PRINC := "${@int(PRINC) + 1}"

RDEPENDS_${PN} += " \
               lighttpd-module-auth \
               lighttpd-module-cgi \
               lighttpd-module-expire \
"

do_install_append() {
    update-rc.d -r ${D} lighttpd start 60 S .
    install -m 0755 ${WORKDIR}/lighttpd.conf ${D}${sysconfdir}
    install -m 0755 ${WORKDIR}/lighttpd-htdigest.user ${D}${sysconfdir}
    if [ x"XILINX" == x"${CTRL_BD}" ]; then
    	cp -pr ${WORKDIR}/www_c5/* ${D}/www/pages
    fi
    if [ x"XILINX" == x"${CTRL_BD}" ]; then
	cp -pr ${WORKDIR}/www_xilinx/* ${D}/www/pages
    fi
}

SRC_URI_append = " file://lighttpd.conf"
SRC_URI_append = " file://lighttpd-htdigest.user"
SRC_URI_append = " file://www_c5"
SRC_URI_append = " file://www_xilinx"


