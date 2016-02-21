#!/bin/bash

export DEBIAN_FRONTEND=noninteractive

# Update packages list
apt-get update

# Install Node.js and npm
apt-get install -y nodejs npm

# Add symbolic link "node" to "nodejs"
apt-get install -y nodejs-legacy

# Install bower
npm install -g bower

# Install grunt-cli
npm install -g grunt-cli

# Install gulp
npm install -g gulp
