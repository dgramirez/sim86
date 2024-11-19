@echo off
setlocal

set ROOT=
for %%i in ( "%~dp0.." ) do set "ROOT=%%~fi"

set CONFIG=%~1
set X_COMPILER=%~2
set SIM86_MODE=%~3
set SIM86_FILEPATH=%~4
if ["%~1"] == ["c"]     ( goto :cleanup )
if ["%~1"] == ["clean"] ( goto :cleanup )
if ["%~1"] == ["xp"]    ( goto :xp )
if ["%~1"] == ["a"]     ( if ["%~2"] == [""] ( goto :build_all ) )
if ["%~1"] == ["all"]     ( if ["%~2"] == [""] ( goto :build_all ) )
call :call_validate_args %~1 %~2 %~3

set OUT=
set SRC=
set FAILURE=
set BUILD=
set RUN=
set TEST=
call "%~dp0\build-config.bat" "%CONFIG%" "%X_COMPILER%"

:: Note - Reiterated this from build-config since this files uses it too.
set DEBREL=1
set DEBUG=2
set RELEASE=4
set ALL=7

if defined FAILURE goto :eof
if defined BUILD   goto :build
if defined RUN     goto :run
if defined TEST    goto :test
goto :eof

:build
	if ["%BUILD%"] == ["%DEBREL%"]  goto :debrel
	if ["%BUILD%"] == ["%DEBUG%"]   goto :debug
	if ["%BUILD%"] == ["%RELEASE%"] goto :release

	:debrel
	setlocal
		if not defined OUT ( set "OUT=%ROOT%\out\%X_COMPILER%\debrel" )
		if not exist "%OUT%" ( mkdir "%OUT%" )

		pushd "%SRC%"
			echo Compiling Sim86 [Debug-Release]
			echo.

			if defined USE_MSVC (
				cl %CL_FLAGS% /Zi /O2 /D "NDEBUG" %CC_OBJ% ^
				   /link %LK_FLAGS% /DEBUG /OUT:%OUT%\sim86.exe
			)
			if defined USE_ZIGCC (
				zig cc %CC_FLAGS% /DEBUG:FULL /RELEASE -g -O3 ^
					   %CC_OBJ% -o "%OUT%\sim86.exe"
			)
		popd

		if defined RUN  ( goto :run_sim86 )
		if defined TEST ( goto :test_sim86 )
	endlocal
	if ["%BUILD%"] neq ["%ALL%"] goto :build_end

	:debug
	setlocal
		if not defined OUT ( set "OUT=%ROOT%\out\%X_COMPILER%\debug" )
		if not exist "%OUT%" ( mkdir "%OUT%" )

		pushd "%SRC%"
			echo Compiling Sim86 [Debug]
			echo.

			if defined USE_MSVC (
				cl %CL_FLAGS% /Zi /Od /D "_DEBUG" %CC_OBJ% ^
				   /link %LK_FLAGS% /DEBUG /OUT:%OUT%\sim86.exe
			)
			if defined USE_ZIGCC (
				zig cc %CC_FLAGS% /DEBUG:FULL -g -O0 -fdebug-macro ^
					   -fstandalone-debug -fdebug-info-for-profiling ^
					   -fno-eliminate-unused-debug-types ^
					   %CC_OBJ% -o "%OUT%\sim86.exe"
			)
		popd

		if defined RUN  ( goto :run_sim86  )
		if defined TEST ( goto :test_sim86 )
	endlocal
	if ["%BUILD%"] neq ["%ALL%"] goto :build_end

	:release
	setlocal
		if not defined OUT ( set "OUT=%ROOT%\out\%X_COMPILER%\release" )
		if not exist "%OUT%" ( mkdir "%OUT%" )

		pushd "%SRC%"
			echo Compiling Sim86 [Release]
			echo.

			if defined USE_MSVC (
				cl %CL_FLAGS% /O2 /D "NDEBUG" %CC_OBJ% ^
				   /link %LK_FLAGS% /RELEASE /OUT:%OUT%\sim86.exe
			)
			if defined USE_ZIGCC (
				zig cc %CC_FLAGS% /DEBUG:NONE /RELEASE -O3 ^
					   %CC_OBJ% -o "%OUT%\sim86.exe"
			)

		popd

		if defined RUN  ( goto :run_sim86  )
		if defined TEST ( goto :test_sim86 )
		if defined BUILD_XP ( endlocal && goto :eof )
	:run_end
	endlocal

:build_end
endlocal
goto :eof

:call_validate_args
if ["%~2"] == ["decode"] (
	set CONFIG=%~1
	set X_COMPILER=
	set SIM86_MODE=%~2
	set SIM86_FILEPATH=%~3
)

if ["%~1"] == ["std-msvc"]    ( set "X_COMPILER=%~1" && set "CONFIG=%~2")
if ["%~1"] == ["std-zigcc"]   ( set "X_COMPILER=%~1" && set "CONFIG=%~2")
if ["%~1"] == ["win32-msvc"]  ( set "X_COMPILER=%~1" && set "CONFIG=%~2")
if ["%~1"] == ["win32-zigcc"] ( set "X_COMPILER=%~1" && set "CONFIG=%~2")
goto :eof

:run
	if exist "%OUT%\sim86.exe" ( goto :just_run_sim86 )

	if ["%RUN%"] == ["%DEBREL%"]  (
		call "%~dp0\build-config.bat" x %X_COMPILER%
		goto :debrel
	)
	if ["%RUN%"] == ["%DEBUG%"] (
		call "%~dp0\build-config.bat" d %X_COMPILER%
		goto :debug
	)
	if ["%RUN%"] == ["%RELEASE%"] (
		call "%~dp0\build-config.bat" r %X_COMPILER%
		goto :release
	)

	:run_sim86
	"%OUT%\sim86.exe" "%SIM86_MODE%" "%SIM86_FILEPATH%"
	goto :run_end

	:just_run_sim86
	"%OUT%\sim86.exe" "%SIM86_MODE%" "%SIM86_FILEPATH%"
goto :build_end

:test
	where nasm >nul 2>nul
	if ["%ERRORLEVEL%"] neq ["0"] (
		echo Nasm cannot be found. . .
		goto :build_end
	)

	if exist "%OUT%\sim86.exe" ( goto :test_sim86 )

	if ["%TEST%"] == ["%DEBREL%"]  (
		call "%~dp0\build-config.bat" x %X_COMPILER%
		goto :debrel
	)
	if ["%TEST%"] == ["%DEBUG%"] (
		call "%~dp0\build-config.bat" d %X_COMPILER%
		goto :debug
	)
	if ["%TEST%"] == ["%RELEASE%"] (
		call "%~dp0\build-config.bat" r %X_COMPILER%
		goto :release
	)

	:test_sim86
	if ["%SIM86_MODE%"] == ["decode"] goto :test_decode
	echo Bad mode for sim86 [not decode]

	:test_decode
	"%OUT%\sim86.exe" "%SIM86_MODE%" "%SIM86_FILEPATH%" > _test.asm
	if ["%ERRORLEVEL%"] neq ["0"] ( goto :sim86_fail )

	nasm _test.asm >nul 2>nul
	if ["%ERRORLEVEL%"] neq ["0"] ( goto :nasm_fail )

	fc /B "%SIM86_FILEPATH%" _test >nul 2>nul
	if ["%ERRORLEVEL%"] neq ["0"] ( goto :fc_fail )

	echo NASM Test was successful!
	goto :test_done

	:sim86_fail
		echo FAILURE during sim86 stage. . .
		echo Exit Code: %ERRORLEVEL%
	goto :test_done

	:nasm_fail
		echo FAILURE during nasm stage. . .
		echo Exit Code: %ERRORLEVEL%
	goto :test_done

	:fc_fail
		echo Two files are different. . .
		echo Exit Code: %ERRORLEVEL%
	:test_done
	del /s /f /q _test.asm >nul 2>nul
	del /s /f /q _test >nul 2>nul
	if defined BUILD ( goto :run_end )
goto :build_end

:xp
	:: Note - This is an "AIO" for packaging up XP executables.
	set BUILD_XP=1
	if not exist "C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A" (
		echo Unable to find Windows 7.1A SDK. Please install the deprecated
		echo Windows XP component from your visual studio installer.
		goto :run_end
	)

	set X_COMPILER=win32-msvc
	set X_ARCH=X86
	call :compile_xp

	set X_ARCH=X64
	call :compile_xp

	set X_COMPILER=std-msvc
	set X_ARCH=X86
	call :compile_xp

	set X_ARCH=X64
	call :compile_xp
goto :run_end

:compile_xp
	setlocal
		call "%~dp0\build-config.bat" "all" "%X_COMPILER%" "%X_ARCH%"
		if defined FAILURE goto :xp_finish
		set CL_FLAGS=%CL_FLAGS% /D "_USING_V110_SDK71_"

		if ["%ARCH%"] == ["X86"] ( call xp_env_32 )
		if ["%ARCH%"] == ["X64"] ( call xp_env_64 )

		:: TODO - These are independent because win32-config handled the
		::        OUT var for run & test (As of Oct. 28th 2024, It doesn't
		::        know which version of the executable to execute.
		set STATIC_OUT=%ROOT%\out\%X_COMPILER%-xp-%X_ARCH%

		set BUILD=%DEBREL%
		set OUT=%STATIC_OUT%\debrel
		call :debrel

		set BUILD=%DEBUG%
		set OUT=%STATIC_OUT%\debug
		call :debug

		set BUILD=%RELEASE%
		set OUT=%STATIC_OUT%\release
		call :release
	:xp_finish
	endlocal
goto :eof

:xp_env_32
	:: Note - Not messing with these environment variables with spacing.
	::        One of the few times line count will not matter!
	set PATH=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Bin;%PATH%
	set INCLUDE=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include;%INCLUDE%
	set LIB=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib;%LIB%
	set LIBPATH=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib;%LIBPATH%

	set CL_FLAGS=%CL_FLAGS% /D"WINVER=0x0501" /D"_WIN32_WINNT=0x0501" ^
				 /D"NTDDI_VERSION=0x05010300"
goto :eof

:xp_env_64
	:: Note - Not messing with these environment variables with spacing.
	::        One of the few times line count will not matter!
	set PATH=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Bin\x64;%PATH%
	set INCLUDE=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include;%INCLUDE%
	set LIB=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib\x64;%LIB%
	set LIBPATH=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib\x64;%LIBPATH%

	set CL_FLAGS=%CL_FLAGS% /D"WINVER=0x0502" /D"_WIN32_WINNT=0x0502" ^
				 /D"NTDDI_VERSION=0x05020200"
goto :eof

:build_all
	echo ===================
	echo = Zig Compilation =
	echo ===================
	echo.
	call :recurse_build a win32-zigcc
	call :recurse_build a std-zigcc
	call :recurse_build a win32-msvc
	call :recurse_build a std-msvc
	call :recurse_build xp
goto :eof

:recurse_build
	call "%ROOT%\misc\build.bat" %1 %2
goto :eof

:cleanup
	:: Note - Cleanup happens before configuration, so OUT and SRC are not
	::        set at this time.
	rmdir /s /q "%ROOT%\out" >nul 2>nul
	pushd "%ROOT%\src\c"
		for /f "delims=" %%F in ('dir /b /a-d ^| findstr /vile ".c .h"') do del "%%F"
	popd
	echo Cleaned up the project.
goto :build_end

