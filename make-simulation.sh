#!/bin/sh

# script pour compiler et installer les modules

PWD1=$PWD;
mkdir build;
cd build;
cmake -DCMAKE_VERBOSE_MAKEFILE=1 -DBUILD_MODULES=1 -DCMAKE_INSTALL_PREFIX:PATH=$PWD1 $PWD1;
make install;
cd $PWD1;
