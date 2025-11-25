#!/bin/bash

# install default version
./install.sh

# install build-essential
sudo apt install -y build-essential make

# make c++ build
make -j3
