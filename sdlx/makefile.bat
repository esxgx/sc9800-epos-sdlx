	@ECHO OFF
	goto start
@echo off
@echo ========================================
@echo fm_radio app
@echo ========================================
goto start
****************************************************************************************
*
****************************************************************************************
:error
	@echo Please input arg for chip select!
	pause
	goto exit

:start
	if exist tmplib.a del tmplib.a
	
	if "%1"=="/b" goto build

	call tools\setpath
	call setchip
:build
	call via D:\Winners\ePDK\sdlx
	
	call  pl audio
	call  pl cdrom
	call  pl cpuinfo
	call  pl events
	call  pl file
	call  pl joystick
	call  pl loadso
	call  pl main
	call  pl stdlib
	call  pl thread
	call  pl timer

	call  pl video

	call  cl SDL
	call  cl SDL_error
	call  cl SDL_fatal
	
	armar -rs sdlx.a tmplib.a 
	
	@if errorlevel 2 goto ERROR
	@if errorlevel 1 goto ERROR
	

	@if errorlevel 2 goto ERROR
	@if errorlevel 1 goto ERROR

	if exist tmplib.a del tmplib.a
@echo Finished!
	if "%1"=="" pause



