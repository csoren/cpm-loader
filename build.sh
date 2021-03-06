#!/bin/sh
cd asmotor/build/scons
scons
cd ../../..

asm6502=asmotor/build/scons/build_6502/motor6502
asmz80=asmotor/build/scons/build_gameboy/motorgb
link=asmotor/build/scons/build_xlink/xlink

gcc -oextract extract.c
rm *.bin
rm cpmsys.inc
./extract CPM+.SYS
$asm6502 -fx -omain.o main.65
$asmz80 -mcz -fx -oloader.o loader.z80
$link -tc128 -ocpm+.prg main.o loader.o

