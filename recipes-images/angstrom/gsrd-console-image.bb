require recipes-images/angstrom/console-image.bb

DEPENDS += "bash perl gcc i2c-tools\
"

IMAGE_INSTALL += "bash perl gcc i2c-tools altera-gsrd-apps altera-gsrd-pio-interrupt altera-gsrd-initscripts lighttpd altera-gsrd-webcontent lighttpd-module-cgi altera-lighttpd-conf\
"

export IMAGE_BASENAME = "gsrd-console-image"

