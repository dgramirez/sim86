## 8086 Decoder ##
(Under Development)

In the current state of this repository, this is an i8086 decoder that only
decodes mov. I will be following the [Computer Enhance] [1] class, which
has the students do a simple 8086 /8088 simulator. This repository will be
updated for each homework that I've completed, and perhaps more.

Latest Update: 2. Decoding Multiple Instructions and Suffixes

## Build ##
Currently, Windows is the only platform with a build script. You can double
click on build.bat inside the misc directory to get a debug-release build
right away (sim86/out/win32-xxxxx/debrel).

For further builds, go into the misc directory and use the command prompt:
> build [configuration] [platform-compiler]
> <br />  
> [Configuration]  
> **x, debrel** - Debug-Release (Default)  
> **d, debug** - Debug  
> **r, release** - Release  
> <br />
> [Platform-Compiler]  
> **std-msvc** - Standard Library using vcvarsall.bat  
> **std-zigcc** - Standard Library using zig cc  
> **win32-msvc** - Win32 API using vcvarsall.bat  
> **win32-zigcc** - Win32 API using zig cc

## sim86 Command Line ##
`sim86 decode [i8086 binary filepath]`

This will decode the binary and print it onto the screen.

## Compatibility ##
### Compilers ###
* MSVC - **Works (Tested: VS Build Tools 2022)**
  * STD: **MS CRT**
  * Windows: **Win32 API (MSVC)**
* Zig CC - **Works (Tested: 0.13.0)**
  * STD: **Mingw (Zig-Windows)** *\[Untested: Musl (Unix / Linux)\]*
  * Windows: **Win32 API (Zig-Windows)**
* GCC - *Untested: No build script*
* clang - *Untested: No build script*
* TCC - *Untested: No build script*
* cproc/qbe - *Untested: No build script*

### Windows ###
* Windows 11 (x64) - **Works (Tested)**
* Windows 10 (x64) - **Works (Tested)**
* Windows 7  (x86, x64) - *Untested: Potentially Binary Compatible (Windows 7.1A SDK)*
* Windows Vista (x86, x64) - *Untested: Potentially Binary Compatible (Windows 7.1A SDK)*
* Windows XP (x64, x64) **Binary Compatible (Tested: VS Build Tools 2022 w/ Windows 7.1A SDK)**

### Unix &amp; Linux ###
* [All]: *Untested: No Build Scripts*
* Note - I am banking that the standard library version covers libc and musl. Unfortunately: *Untested*.

[1]: https://www.computerenhance.com "Computer Enhance"

