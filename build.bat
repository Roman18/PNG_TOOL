@echo off

rem List of sources
set SRC=main.c rw.c


rem Compilation flags
set CFLAGS=-Wall -Wextra

gcc.exe -o png.exe %SRC% %CFLAGS%