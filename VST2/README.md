# HelloVST2

## Development environment

### Mac

Install [Xcode](https://developer.apple.com/xcode/).

### Windows

Install [MSYS2](http://www.msys2.org/).
With the MinGW 64-bit shell (not the default MSYS shell), install dependencies.

	pacman -S make mingw-w64-x86_64-gcc

Or with the MinGW 32-bit shell if you wish to build 32-bit VST plugins.

	pacman -S make mingw-w64-i386-gcc


## Building

Copy the `VST2_SDK` folder from the Steinberg VST2 SDK to this directory.
Unfortunately, if you have not signed the Steinberg VST2 SDK license agreement by October 2018, you can not legally obtain the VST2 SDK.

Run `make`.
