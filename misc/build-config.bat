@echo off

:: Note - No global setlocal, variables should persist in the build scripts
:: Also useful info: https://www.dostips.com/DtTipsStringManipulation.php
if not defined ROOT ( for %%i in ( "%~dp0.." ) do set "ROOT=%%~fi" )
set SRC=%ROOT%\src\c
set OUT=

set DEBREL=1
set DEBUG=2
set RELEASE=4
set ALL=7

set CONFIG=%~1
if ["%CONFIG%"] == [""] ( set "CONFIG=x" )

set X_COMPILER=%~2
if ["%X_COMPILER%"] == [""] ( call :get_default_compiler )
if ["%FAILURE%"] == ["1"] goto :eof

set X_ARCH=%~3
if ["%X_ARCH%"] == [""] ( set "X_ARCH=X64" )

call :get_configs "%CONFIG%" "%X_COMPILER%"
if ["%FAILURE%"] == ["1"] goto :eof
if not defined BUILD goto :validate_arg1

set TEMP=%X_COMPILER%
if ["%TEMP:~-4%"] == ["msvc"]  goto :config_msvc
if ["%TEMP:~-5%"] == ["zigcc"] goto :config_zigcc
goto :bad_arg1

:config_msvc
	if not defined LIB ( 
		if defined BUILD_XP (
			call "%~dp0\setup_cl.bat" %X_ARCH% -vcvars_ver=14.16
		) else (
			call "%~dp0\setup_cl.bat" %X_ARCH%
		)
	)
	if not defined LIB (
		echo Unable to find vcvarsall! Please install Microsoft Visual
		echo Studio with the Desktop Environment with C++ module to compile
		echo this project.
		echo.
		echo If this is due to the xp parameter, please additionally install
		echo the Windows XP Component and v141 Build Tools from the
		echo installer.
		echo.
		echo Tested: Visual Studio 2022 Build Tools

		set FAILURE=1
		goto :eof
	)

	set USE_MSVC=1
	set CL_FLAGS=/EHa- /fp:except- /fp:fast /GL- /Gm- /GR- /GS- /W4 /WX ^
	             /Gs2147483647 /nologo /wd4201

	:: Note - Keep Subsystem as last parameter for Windows XP
	set LK_FLAGS=/WX /STACK:0x200000,0x200000 /INCREMENTAL:NO ^
	             /MACHINE:%X_ARCH% /SUBSYSTEM:CONSOLE

	if ["%X_COMPILER%"] == ["win32-msvc"]  ( goto :config_win32_msvc )
	if ["%X_COMPILER%"] == ["std-msvc"]    ( goto :config_std_msvc )
	goto :bad_arg1

	:config_win32_msvc
		set CC_OBJ=win32_entry.c Kernel32.lib User32.Lib Shell32.lib
		set LK_FLAGS=/NODEFAULTLIB /ENTRY:_start %LK_FLAGS%
		if defined BUILD_XP ( goto :xp_get_subsystem_version )
	goto :eof

	:config_std_msvc
		set CC_OBJ=std_entry.c
		set CL_FLAGS=%CL_FLAGS% /D_CRT_SECURE_NO_WARNINGS
		if defined BUILD_XP ( goto :xp_get_subsystem_version )
goto :eof

:config_zigcc
	where zig >nul 2>nul
	if ["%ERRORLEVEL%"] neq ["0"] (
		echo Unable to find zig! Please download and install the latest
		echo Zig binary to compile this project.
		echo.
		echo Tested: Zig 0.13.0

		set FAILURE=1
		goto :eof
	)

	set USE_ZIGCC=1
	set CC_FLAGS=-target x86_64-windows-gnu -std=c99 ^
	             -Wall -Werror -fno-rtti -fno-builtin -fno-exceptions ^
	             -fno-asynchronous-unwind-tables -I "%ROOT%/include" ^
	             -mno-stack-arg-probe -z stack-size=0x200000 ^
	             -fno-signed-zeros -ffinite-math-only -ffast-math ^
	             -Wno-unused-function

	if ["%X_COMPILER%"] == ["win32-zigcc"] goto config_win32_zigcc
	if ["%X_COMPILER%"] == ["std-zigcc"] goto config_std_zigcc
	goto :bad_arg1

	:config_std_zigcc
		set CC_OBJ=std_entry.c
	goto :eof

	:config_win32_zigcc
		set TEMP=
		for /F %%i in ('where zig') do set "TEMP=%%~dpi"
		set TEMP="%TEMP%\lib\libc\include\any-windows-any"

		set CC_OBJ=win32_entry.c -lkernel32 -luser32 -lshell32
		set CC_FLAGS=%CC_FLAGS% -nostdlib -D_ZIG -isystem %TEMP% ^
		             -Xclang -sys-header-deps /SUBSYSTEM:WINDOWS ^
					 /ENTRY:"_start" -e "_start"
goto :eof

:get_default_compiler
	if not defined LIB ( call "%ROOT%\misc\setup_cl.bat" x64 )
	if defined LIB ( set "X_COMPILER=win32-msvc" && goto :eof )

	where zig >nul 2>nul
	if ["%ERRORLEVEL%"] == ["0"] ( set "X_COMPILER=win32-zigcc" && goto :eof )

	echo Unable to find vcvarsall and zig. Please install either Microsoft
	echo Visual Studio with the Desktop Environment with C++ module or
	echo the latest stable version of Zig to compile this project.
	echo.
	echo Tested with:
	echo     - Visual Studio 2022 Build Tools
	echo     - Zig 0.13.0

	set FAILURE=1
goto :eof

:xp_get_subsystem_version
	if ["%X_ARCH%"] == ["X86"] ( set LK_FLAGS=%LK_FLAGS%",5.01" )
	if ["%X_ARCH%"] == ["X64"] ( set LK_FLAGS=%LK_FLAGS%",5.02" )
goto :eof

:get_configs
	set BUILD=
	if ["%~1"] == ["x"]      ( set "BUILD=%DEBREL%" && goto config_x )
	if ["%~1"] == ["debrel"] ( set "BUILD=%DEBREL%" && goto config_x )

	if ["%~1"] == ["d"]     ( set "BUILD=%DEBUG%" && goto config_d )
	if ["%~1"] == ["debug"] ( set "BUILD=%DEBUG%" && goto config_d )

	if ["%~1"] == ["r"]       ( set "BUILD=%RELEASE%" && goto config_r )
	if ["%~1"] == ["release"] ( set "BUILD=%RELEASE%" && goto config_r )

	if ["%~1"] == ["a"]   ( set "BUILD=%ALL%" )
	if ["%~1"] == ["all"] ( set "BUILD=%ALL%" )

	set RUN=
	if ["%~1"] == ["run"]  ( set "RUN=%DEBREL%"  && goto config_x )
	if ["%~1"] == ["runx"] ( set "RUN=%DEBREL%"  && goto config_x )
	if ["%~1"] == ["rund"] ( set "RUN=%DEBUG%"   && goto config_d )
	if ["%~1"] == ["runr"] ( set "RUN=%RELEASE%" && goto config_r )

	set TEST=
	if ["%~1"] == ["test"]  ( set "TEST=%DEBREL%"  && goto config_x )
	if ["%~1"] == ["testx"] ( set "TEST=%DEBREL%"  && goto config_x )
	if ["%~1"] == ["testd"] ( set "TEST=%DEBUG%"   && goto config_d )
	if ["%~1"] == ["testr"] ( set "TEST=%RELEASE%" && goto config_r )

	if defined BUILD goto :eof

	echo ERROR: Bad Argument 1. It should be one of the following:
	echo.
	echo To Compile:
	echo     * Debug-Release    - [x] [debrel]
	echo     * Debug            - [d] [debug]
	echo     * Release          - [r] [release]
	echo.
	echo To Run Sim86:
	echo      * Debug-Release    - [run] [runx]
	echo      * Debug            - [rund]
	echo      * Release          - [runr]
	echo.
	echo To Test Sim86:
	echo      * Debug-Release    - [test] [testx]
	echo      * Debug            - [testd]
	echo      * Release          - [testr]

	set FAILURE=1
	goto :eof

	:config_x
		set OUT=%ROOT%\out\%~2\debrel
	goto :eof

	:config_d
		set OUT=%ROOT%\out\%~2\debug
	goto :eof

	:config_r
		set OUT=%ROOT%\out\%~2\release
	goto :eof
goto :eof

:validate_arg1
	if ["%X_COMPILER%"] == ["win32-msvc"]  ( goto :eof )
	if ["%X_COMPILER%"] == ["std-msvc"]    ( goto :eof )
	if ["%X_COMPILER%"] == ["win32-zigcc"] ( goto :eof )
	if ["%X_COMPILER%"] == ["std-zigcc"]   ( goto :eof )
:bad_arg1
	echo INTERNAL ERROR: Bad Argument 1. It should be one of the following:
	echo     * win32-msvc
	echo     * win32-zigcc
	echo     * std-msvc
	echo     * std-zigcc

	set FAILURE=1

