#!/bin/sh

echo "starting recovery factoary"
/etc/init.d/dropbear stop
/etc/init.d/bmminer.sh stop

cd /config
rm_files=`ls /config/ | grep -v mac`
rm -rf $rm_files

sync

echo "recovery factory complete, rebooting"

reboot -f
