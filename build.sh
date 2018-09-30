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
$asm6502 -fx -oprgmain.o prgmain.65
$asmz80 -mcz -fx -oprgloader.o prgloader.z80
$link -tc128 -ocpm+.prg prgmain.o prgloader.o

$asm6502 -fx -oromheader.o romheader.65
$asmz80 -mcz -fx -oromloader.o romloader.z80
$link -tc128f -ocpm+.rom romheader.o prgmain.o romloader.o

