# HelloVST2

## Development environment

### Mac

Install [Xcode](https://developer.apple.com/xcode/).

### Windows

Install [MSYS2](http://www.msys2.org/).
With the MinGW 64-bit shell (not the default MSYS shell), install dependencies.

	pacman -S make mingw-w64-x86_64-gcc

Or with the MinGW 32-bit shell

	pacman -S make mingw-w64-i386-gcc


## Building

Download the [VST3 SDK](https://www.steinberg.net/en/company/developers.html), and move the `VST2_SDK` folder to this directory.

Run `make`.
