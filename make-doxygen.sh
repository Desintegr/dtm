#!/bin/sh

# script pour générer la documentation Doxygen

rm -rf doxygen/html
doxygen doxygen/doxygen.conf
