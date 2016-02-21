#!/bin/bash

# This script should be run with user privileges
################################################

export DEBIAN_FRONTEND=noninteractive

# Go to project directory
cd /vagrant

# Enable additional 512MB swap area for compilation process
#   -- assuming vagrant machine with 512MB of RAM
SWAPFILE="${HOME}/swapfile"
dd if=/dev/zero of=${SWAPFILE} bs=1M count=512
mkswap ${SWAPFILE}
sudo swapon ${SWAPFILE}

# Install project backend requirements
npm install || :

# Install project frontend requirements
bower install || :

# Disable swap area
sudo swapoff ${SWAPFILE}
rm -f ${SWAPFILE}
