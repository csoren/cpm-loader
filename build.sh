#!/bin/sh
cd asmotor/build/scons
scons
cd ../../..

asm6502=asmotor/build/scons/build_6502/motor6502
asmz80=asmotor/build/scons/build_gameboy/motorgb
link=asmotor/build/scons/build_xlink/xlink

$asm6502 -fx -omain.o main.asm
$link -tc128 -oloader.prg main.o
