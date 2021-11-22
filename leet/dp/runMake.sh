#!/bin/bash
if [ ! -n "$1" ] ;then
  echo "usage: ./runMake.sh test.cpp"
	exit
fi

cppfile=$1
g++  -lgtest -lpthread -lgtest_main \
	  -o  $cppfile.bin -std=c++14\
		$cppfile
