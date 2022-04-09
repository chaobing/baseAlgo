#!/bin/bash
if [ ! -n "$1" ] ;then
  echo "usage: ./runMake.sh test.cpp"
	exit
fi

cppfile=$1
g++  -std=c++11 -lgtest -lpthread -lgtest_main \
	  -o  $cppfile.bin \
		$cppfile
