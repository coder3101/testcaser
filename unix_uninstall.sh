#!/bin/bash   
set -e
echo -e "\n***************STARTING THE UNINSTALLATION*****************"
echo -e "\nScript Running Director is : "$PWD
echo -e "\n1. Removing the symlink of testcaser from /usr/include/"
rm /usr/include/testcaser
echo -e "2. Uninstall Success\n"
echo "*************************************************************"
