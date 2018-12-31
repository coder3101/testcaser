@echo off
echo *******************************************
echo 1. Begining the VirtualJudge Installtion.
echo 2. Taking BACKUP of current PATH.
echo %PATH% > old_path.txt
echo 3. Backup Done, You can use this to restore your path incase of failures.
echo 4. Backup was saved as old_path.txt in current directory.
echo 5. Setting new PATH Variable for current Session.
set PATH=%PATH%;%cd%\bin\
echo 6. Setting new PATH Variable for other Session.
setx /M PATH "%PATH%"
echo NOTE : Installation Completed. Please Note if you see a warning 
echo PATH WAS TRUNCATED TO 1024, It means your environment variables are 
echo Corrupted. Please Restore your old PATH from backup and manually
echo add %cd%\bin to your PATH Variables. 
echo *******************************************