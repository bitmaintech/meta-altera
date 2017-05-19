#!/bin/sh

# gpio 23 = DHCP Static key
#ver = 1
# gpio 27 = DHCP Static key
#dhcppin=27
#echo $dhcppin > /sys/class/gpio/export
#echo in > /sys/class/gpio/gpio$dhcppin/direction


if [ ! -f /config/network.conf ] ; then
    cp /etc/network.conf.factory /config/network.conf
fi

# Read network configuration
#dhcp_key="`cat /sys/class/gpio/gpio$dhcppin/value`"

dhcp_key=0
if [ "dhcp_key" = "1" ] ; then
	dhcp=true
	hostname=antMiner
elif [ -s /config/network.conf ] ; then
    . /config/network.conf
else
    dhcp=true
    hostname=antMiner
fi

#echo $dhcppin > /sys/class/gpio/unexport

if [ -n "$hostname" ] ; then
	hostname $hostname
	echo $hostname > /etc/hostname
fi

# Setup link 
ip link set lo up
ip link set eth0 up
ip link ls eth0
ip addr flush dev eth0

#id_h=`/sbin/devmem 0xff2000f0 | awk 'NR==1 {s=and($NF,0xfeff); printf("%04X",s)}'`
#mac0=${id_h:0:2}
#mac1=${id_h:2:2}

#id_l=`/sbin/devmem 0xff2000f4 | awk 'NR==1 {s=and($NF,0x7fffffff); printf("%08X",s)}'`

#mac2=${id_l:0:2}
#mac3=${id_l:2:2}
#mac4=${id_l:4:2}
#mac5=${id_l:6:2}

if [ ! -f /config/mac ];then
    id_h=`devmem 0xff2000f0`
    id_l=`devmem 0xff2000f4`
    echo $id_h$id_l > /tmp/chip_id
    mac_string=`openssl rand -rand /tmp/chip_id -hex 6`
    mac0=`echo ${mac_string:0:2} | awk 'NR==1 {s=and($NF,0xfe); printf("%02x",s)}'`
    mac1=${mac_string:2:2}
    mac2=${mac_string:4:2}
    mac3=${mac_string:6:2}
    mac4=${mac_string:8:2}
    mac5=${mac_string:10:2}
    mac="$mac0:$mac1:$mac2:$mac3:$mac4:$mac5"
    echo $mac > /config/mac
else
    mac=`cat /config/mac`
fi

echo $mac
ifconfig eth0 down > /dev/null 2>&1
ifconfig eth0 hw ether $mac > /dev/null 2>&1
ifconfig eth0 up  > /dev/null 2>&1

killall -9 udhcpc > /dev/null 2>&1

if [ "$dhcp" = "true" ] ; then
    if [ "$QUIET" = "true" ] ; then
        udhcpc -b -t 10 -A 10 -x hostname:$hostname -i eth0 > /dev/null
    else
        udhcpc -b -t 10 -A 10 -x hostname:$hostname -i eth0
    fi
else
    # Manual setup
    ip addr add $ipaddress/$netmask dev eth0
    
    ip ro add default via $gateway

    > /etc/resolv.conf
    for ip in $dnsservers ; do
	echo nameserver $ip >> /etc/resolv.conf
    done
fi
