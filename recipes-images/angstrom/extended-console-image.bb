require recipes-images/angstrom/console-image.bb

DEPENDS += "bash perl gcc i2c-tools \
"

IMAGE_INSTALL += "bash perl gcc i2c-tools \
"

export IMAGE_BASENAME = "extended-console-image"

