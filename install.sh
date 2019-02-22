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

platform='unknown'
unamestr="$(uname)"
unameplatform="$(uname -m)"

if [[ "$unameplatform" != 'x86_64' ]]; then
    # We have ARM if its not x86
    echo -e "Detected ARM. Installing ARM Binary";
    mv $CWD/bin/virtualjudge $CWD/bin/virtualjudge-x86_64
    mv $CWD/bin/virtualjudge-arm $CWD/bin/virtualjudge
fi

if [[ "$unamestr" == 'Linux' ]]; then
    platform='Linux'
    echo -e "Using Linux Installer Script."
elif [[ "$unamestr" == 'Darwin' ]]; then
    platform='MacOS'
    echo -e "Using MacOS Installer Script."
else
    echo -e "Sorry, this OS is not supported yet."
    exit
fi

echo -e "\n***************STARTING THE INSTALLATION*****************\n"
echo "Script Running Directory is : "$CWD
chmod +x $CWD/bin/virtualjudge
if contains $CWD "testcaser" 
    then
    echo -e "\n1. Starting Installation..."
    if [[ $platform == 'Linux' ]]; then
        echo "2. Creating a symlink of testcaser to /usr/include/"
        ln -s "$CWD/testcaser" /usr/include/
        echo "3. Symlink created to /usr/include/"

    else
        echo "2. Creating a symlink of testcaser to /usr/local/include/"
        ln -s "$CWD/testcaser" /usr/local/include/
        echo "3. Symlink created to /usr/local/include/"
    fi
    echo "4. Successfully Installed testcaser."
    echo "5. Do you wish to install virtual judge binary in (/usr/local/bin/)?"
    if [ ! -v TRAVIS ]; then
        select yn in "Yes" "No"; do
            case $yn in
                Yes ) sudo cp "$CWD/bin/virtualjudge" /usr/local/bin/ ; break;;
                No ) break;;
            esac
        done
    else 
    echo ">> Found TRAVIS, Skipping Prompt for binary install"
    sudo cp "$CWD/bin/virtualjudge" /usr/local/bin/
    fi
    echo -e "\n*********************** NOTE ****************************"
    echo "Do not Remove testcaser from :  $CWD"
    echo "or else it won't compile. To uninstall run uninstall.sh"
    echo "*********************************************************"

else
    echo "Aborting Installation. You are not executing the script from withing the testcaser directory."
fi
