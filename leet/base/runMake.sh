#!/bin/bash
if [ ! -n "$1" ] ;then
  echo "usage: ./runMake.sh test.cpp"
	exit
fi

cppfile=$1
g++  -g -std=c++11 -lgtest -lpthread -lgtest_main -I /usr/local/include/ -L /usr/local/lib/ \
	  -o  $cppfile.bin \
		$cppfile
