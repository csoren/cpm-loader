# CPM+.SYS in .prg format
This project embeds CPM+.SYS for the Commodore 128 in a .prg file. This is useful for booting CP/M off a flash cart, such as the [Kerberos](http://www.frank-buss.de/kerberos/index.html). Booting CP/M this way will shave off at least 15 seconds of boot time, plus you don't need CPM+.SYS on your boot disk, leaving 24+ KiB of free space to use.

[Download the .prg](cpm+.prg) - This version contains CPM+.SYS from [this repository](https://github.com/csoren/c128cpm)

## Building

To build your own .prg, replace CPM+.SYS with the version you want and run

        $ ./build.sh
