@echo on
echo **************************************
echo Removing from PATH Variables
setx /M PATH "%PATH:%cd%\bin;=%"
echo Removed from PATH Variables. Close this terminal to see effect.
echo ***************************************
