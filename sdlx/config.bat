@echo off
goto START

:ERROR
    pause
    goto EXIT

:START
    @echo *******************************************
    @echo *   请选择主机                            *
    @echo *******************************************
    @echo 0: V6000HDV
    @echo 1: V8000HDV
    
    @echo *********************************************
    set /p SEL=Please Select:
    if %SEL%==0     goto x_V6000HDV
    if %SEL%==1     goto x_V8000HDV
    @echo Error: please input( 0 ~ 1)!
    goto Start

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:x_V6000HDV
    copy video\awucg\v6000hdv\SDL_awucg_keymap.h video\awucg\SDL_awucg_keymap.h
    goto conti
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:x_V8000HDV
    copy video\awucg\v8000hdv\SDL_awucg_keymap.h video\awucg\SDL_awucg_keymap.h

    goto conti

::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:conti
    @echo 配置成功
    @echo *********************************************
    pause



