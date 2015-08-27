#!/bin/bash
set -o posix

##############################################################################
# These are needed for the C++ Project Template
sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test # g++-4.9
sudo add-apt-repository --yes ppa:kubuntu-ppa/backports   # cmake over 2.8.7
##############################################################################

##############################################################################
# Add your projects necessary "before_install" commands here
sudo apt-add-repository --yes ppa:zoogie/sdl2-snapshots		  # sdl2
sudo apt-add-repository --yes ppa:libreoffice/libreoffice-4-2 # doxygen 1.8
##############################################################################

##############################################################################
# This is needed for the C++ Project Template
sudo apt-get update -qq
##############################################################################
