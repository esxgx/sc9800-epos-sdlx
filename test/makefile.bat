	@ECHO OFF
	goto start
****************************************************************************************
*
****************************************************************************************
:error
	@echo Please input arg for chip select!
	pause
	goto exit

:start
	@echo =======================
	@echo ex_lemon build Start!
	@echo =======================

	if exist tmplib.a del tmplib.a
	
	if "%1"=="/b" goto build
	call D:\Winners\ePDK\softwares\MakeTool\setpath
	call setchip
:build
	call via D:\Winners\ePDK\test

	if exist tmplib.o del tmplib.o
	if exist __image.axf del __image.axf

	
	call cc magic
	call cc main

	
::	call as res

	@echo LK Linking......
	armlink --noremove --entry 0 --via=%lvia% tmplib.o %libspath%\lemon.sym %libspath%\sdlx.a --verbose --errors err.txt
	@if errorlevel 2 goto ERROR
	@if errorlevel 1 goto ERROR
	
	fromelf --via=%fvia% __image.axf   
	@if errorlevel 2 goto ERROR
	@if errorlevel 1 goto ERROR

	if exist tmplib.o del tmplib.o
	if exist tmplib.a del tmplib.a
	::if exist __image.axf del __image.axf

	@echo Finished!
	if "%1"=="" pause

