#!/bin/sh

# No configuration, create it!
if [ ! -f /config/bmminer.conf ] ; then
    cp /config/bmminer.conf.factory /config/bmminer.conf
fi
