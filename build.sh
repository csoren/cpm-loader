#!/bin/sh
cd asmotor/build/scons
scons
cd ../../..

asm6502=asmotor/build/scons/build_6502/motor6502
asmz80=asmotor/build/scons/build_gameboy/motorgb

$asm6502 -fb -oloader.prg main.asm
