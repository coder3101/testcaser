#!/bin/bash   
set -e

platform='unknown'
unamestr="$(uname)"

if [[ "$unamestr" == 'Linux' ]]; then
    platform='Linux'
    echo -e "Using Linux Un-Installer Script."
elif [[ "$unamestr" == 'Darwin' ]]; then
    echo -e "Using MacOS Un-Installer Scripts."
    platform='MacOS'
else
    echo -e "Sorry, this OS is not supported yet."
    exit
fi

echo -e "\n***************STARTING THE UNINSTALLATION*****************"
echo -e "\nScript Running Directory is : "$PWD
if [[ $platform == 'Linux' ]]; then
    echo -e "\n1. Removing the symlink of testcaser from /usr/include/"
    rm /usr/include/testcaser
else
    echo -e "\n1. Removing the symlink of testcaser from /usr/local/include/"
    rm /usr/local/include/testcaser
fi
echo -e "2. Success Uninstall testcaser\n"
echo "*************************************************************"
