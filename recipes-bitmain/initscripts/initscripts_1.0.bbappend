FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-1.0:"

PRINC := "${@int(PRINC) + 1}"

do_install_append() {
	install -m 0755 ${WORKDIR}/mountdevtmpfs.sh ${D}${sysconfdir}/init.d
	update-rc.d -r ${D} mountdevtmpfs.sh start 02 S .
        if [ x"C5" == x"${CTRL_BD}" ]; then
	    install -m 0755 ${WORKDIR}/network.sh ${D}${sysconfdir}/init.d
	    update-rc.d -r ${D} network.sh start 38 S .
            install -m 0755 ${WORKDIR}/bmminer.sh ${D}${sysconfdir}/init.d
	    update-rc.d -r ${D} bmminer.sh start 70 S .
        fi
        if [ x"XILINX" == x"${CTRL_BD}" ]; then
            install -m 0755 ${WORKDIR}/network_xilinx.sh ${D}${sysconfdir}/init.d/network.sh
            update-rc.d -r ${D} network.sh start 38 S .
            install -m 0755 ${WORKDIR}/bmminer_xilinx.sh ${D}${sysconfdir}/init.d/bmminer.sh
	    update-rc.d -r ${D} bmminer.sh start 70 S .
        fi
	install -m 0755 ${WORKDIR}/bitmainer_setup.sh ${D}${sysconfdir}/init.d
	update-rc.d -r ${D} bitmainer_setup.sh start 37 S .

	install -m 0755 ${WORKDIR}/ntpdate.sh ${D}${sysconfdir}/init.d
	update-rc.d -r ${D} ntpdate.sh start 39 S .

	install -m 0755 ${WORKDIR}/pgnand.sh ${D}${sysconfdir}/init.d
	
	cd ${D}${sysconfdir}/rcS.d
	ln -s ../init.d/ntpd S40ntpd

	install -m 0400 ${WORKDIR}/shadow.factory ${D}${sysconfdir}/shadow.factory

	install -m 0400 ${WORKDIR}/network.conf.factory ${D}${sysconfdir}/network.conf.factory
	install -m 0400 ${WORKDIR}/bmminer.conf.factory ${D}${sysconfdir}/bmminer.conf.factory

	install -m 0400 ${WORKDIR}/usr_defined_lcd.factory ${D}${sysconfdir}/usr_defined_lcd.factory
	install -m 0400 ${WORKDIR}/user_setting.factory ${D}${sysconfdir}/user_setting.factory

	install -d ${D}${base_sbindir}
	install -m 0755 ${WORKDIR}/monitorcg ${D}${base_sbindir}/
	install -m 0755 ${WORKDIR}/miner_lcd.sh ${D}${base_sbindir}/minerlcd
	install -d ${D}${bindir}
	rm -rf ${D}${bindir}/compile_time
	date >> ${D}${bindir}/compile_time

	echo "AntMiner ${Miner_TYPE}" >> ${D}${bindir}/compile_time
        echo "${CTRL_BD}" > ${D}${bindir}/ctrl_bd

	install -d ${D}${base_sbindir}
	install -m 0755 ${WORKDIR}/check_phy.sh ${D}${base_sbindir}/
	install -d ${D}${base_sbindir}
	install -m 0755 ${WORKDIR}/reset.sh ${D}${base_sbindir}/
}
SRC_URI_append = " file://user_setting.factory"
SRC_URI_append = " file://mountdevtmpfs.sh"
SRC_URI_append = " file://network.sh"
SRC_URI_append = " file://network_xilinx.sh"
SRC_URI_append = " file://network.conf.factory"
SRC_URI_append = " file://bmminer.sh"
SRC_URI_append = " file://bmminer_xilinx.sh"
SRC_URI_append = " file://bmminer.conf.factory"
#SRC_URI_append = " file://asic-freq.config"
#SRC_URI_append = " file://s3-asic-freq.config"
SRC_URI_append = " file://usr_defined_lcd.factory"
SRC_URI_append = " file://ntpdate.sh"
SRC_URI_append = " file://shadow.factory"
SRC_URI_append = " file://bitmainer_setup.sh"
SRC_URI_append = " file://monitorcg"
SRC_URI_append = " file://miner_lcd.sh"
SRC_URI_append = " file://pgnand.sh"
SRC_URI_append = " file://d-ddos-m.sh"
SRC_URI_append = " file://miner-m.sh"
SRC_URI_append = " file://dataformatconfig"
SRC_URI_append = " file://minermonitor.conf"
SRC_URI_append = " file://minermonitor"
SRC_URI_append = " file://check_phy.sh"
SRC_URI_append = " file://reset.sh"
