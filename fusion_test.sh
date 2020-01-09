#!/bin/bash
arm-eabi-ld -r -o fichiers_exemples/gotenks.o -EB $1 $2
readelf -s fichiers_exemples/gotenks.o > fusion.txt

./merge_bis $1 $2 > myfusion.txt
diff -w myfusion.txt fusion.txt
