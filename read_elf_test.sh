#!/bin/bash

./read $1 -h > myreadelf.txt
readelf -h $1 > readelf.txt

diff -w myreadelf.txt readelf.txt

./read $1 -S > myreadelf.txt
readelf -S $1 > readelf.txt

diff -w myreadelf.txt readelf.txt

./read $1 -s > myreadelf.txt
readelf -s $1 > readelf.txt

diff -w myreadelf.txt readelf.txt