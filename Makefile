#!/bin/sh
#======================================
DIR_PRJ = $(shell pwd)
#--------------------------------------
help:
	@echo 'make sort #compile sort subdir'
	@echo 'make conv #compile conv subdir'

default:
	./cmake.sh
sort:
	mkdir -p ./lib/sort
	gsed -i "s/set(SUBDIR [a-z]\+)/set(SUBDIR sort)/g" CMakeLists.txt
	make default

conv:
	mkdir -p ./lib/conv
	gsed -i "s/set(SUBDIR [a-z]\+)/set(SUBDIR conv)/g" CMakeLists.txt
	make default

clean:
	rm -rf lib
	rm -rf build

.PHONY : help sort conv clean default
