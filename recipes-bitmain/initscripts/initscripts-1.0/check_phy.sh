#!/bin/sh
while :
do
    newret=`ifconfig eth0 | grep RUNNING | wc -l`
    if [ $newret -eq 1 ]; then
        ifconfig eth0 down && ifconfig eth0 up
        /etc/init.d/ntpd stop
        /etc/init.d/network.sh
        ntpdate pool.ntp.org && sleep 1
        /etc/init.d/ntpd start
        return
    fi           
    sleep 1      
done
