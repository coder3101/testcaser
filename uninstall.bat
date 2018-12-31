@echo off
echo **************************************
echo Removing from PATH Variables
setlocal enableextensions enabledelayedexpansion
setx /M PATH "%PATH:"%cd%\bin";=%"
set PATH=%PATH%
echo Removed from PATH Variables. 
echo ***************************************
