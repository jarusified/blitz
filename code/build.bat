:: @ is to ensure that echo off doesnt run 
@echo off 
mkdir .\..\build
pushd .\..\build
cl -Zi ..\code\win32.cpp user32.lib gdi32.lib
popd

