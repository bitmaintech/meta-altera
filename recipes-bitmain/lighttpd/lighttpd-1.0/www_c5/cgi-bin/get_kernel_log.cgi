#!/bin/sh

dmesg

if [ -e /tmp/search ];then
	cat /tmp/search
fi

if [ -e /tmp/freq ];then
	cat /tmp/freq
fi

if [ -e /tmp/lasttemp ];then
	cat /tmp/lasttemp
fi
