#!/bin/bash

export DEBIAN_FRONTEND=noninteractive

# Update packages list
apt-get update

# Install nginx server
apt-get install -y nginx

# Disable default server
rm -f /etc/nginx/sites-enabled/default

# Start up at boot time
update-rc.d nginx defaults

# Restart server
service nginx restart
