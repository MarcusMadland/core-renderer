@echo off

pushd ..\
call vendor\bin\premake\premake5 vs2019
popd
PAUSE