#!/bin/bash   
set -e 
contains() {
    string="$1"
    substring="$2"
    if test "${string#*$substring}" != "$string"
    then
        return 0    # $substring is in $string
    else
        return 1    # $substring is not in $string
    fi
}

CWD=$(pwd)

echo -e "\n***************STARTING THE INSTALLATION*****************\n"
echo "Script Running Director is : "$CWD
if contains $CWD "testcaser" 
    then
    echo -e "\n1. Starting Installation..."
    echo "2. Creating a symlink of testcaser to /usr/include/"
    ln -s "$CWD/testcaser" /usr/include/
    echo "3. Symlink created to /usr/include/"
    echo "4. Successfully Installed testcaser."
    echo -e "\n*********************** NOTE ****************************"
    echo "Do not Remove testcaser from :  $CWD"
    echo "or else it won't compile. To uninstall run uninstall.sh"
    echo "*********************************************************"

else
    echo "Aborting Installation. You are not executing the script from withing the testcaser directoy."
fi