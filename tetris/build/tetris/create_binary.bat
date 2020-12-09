@echo off

cd ../../TDM-GCC-64/bin
set FOLDER_PATH=%cd%

if exist ../../build/source/binary.exe (
    echo binary.exe already exists.
) else (
    set PATH="%PATH%;%FOLDER_PATH%"
    gcc ../../build/source/client.c -o ../../build/source/binary.exe -lws2_32
)

start ../../build/source/binary.exe