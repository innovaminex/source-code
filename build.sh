#!/bin/bash

set -e

date

#################################################################
# Update Ubuntu and install prerequisites for running innovaminex   #
#################################################################
sudo apt-get update
#################################################################
# Build innovaminex from source                                     #
#################################################################
NPROC=$(nproc)
echo "nproc: $NPROC"
#################################################################
# Install all necessary packages for building innovaminex           #
#################################################################
sudo apt-get install -y qt4-qmake libqt4-dev libminiupnpc-dev libdb++-dev libdb-dev libcrypto++-dev libqrencode-dev libboost-all-dev build-essential libboost-system-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libssl-dev libdb++-dev libssl-dev ufw git
sudo add-apt-repository -y ppa:bitcoin/bitcoin
sudo apt-get update
sudo apt-get install -y libdb4.8-dev libdb4.8++-dev

# By default, assume running within repo
repo=$(pwd)
file=$repo/src/innovaminexd
if [ ! -e "$file" ]; then
	# Now assume running outside and repo has been downloaded and named innovaminex
	if [ ! -e "$repo/innovaminex/build.sh" ]; then
		# if not, download the repo and name it innovaminex
		git clone https://github.com/innovaminexd/source innovaminex
	fi
	repo=$repo/innovaminex
	file=$repo/src/innovaminexd
	cd $repo/src/
fi
make -j$NPROC -f makefile.unix

cp $repo/src/innovaminexd /usr/bin/innovaminexd

################################################################
# Configure to auto start at boot                                      #
################################################################
file=$HOME/.innovaminex
if [ ! -e "$file" ]
then
        mkdir $HOME/.innovaminex
fi
printf '%s\n%s\n%s\n%s\n' 'daemon=1' 'server=1' 'rpcuser=u' 'rpcpassword=p' | tee $HOME/.innovaminex/innovaminex.conf
file=/etc/init.d/innovaminex
if [ ! -e "$file" ]
then
        printf '%s\n%s\n' '#!/bin/sh' 'sudo innovaminexd' | sudo tee /etc/init.d/innovaminex
        sudo chmod +x /etc/init.d/innovaminex
        sudo update-rc.d innovaminex defaults
fi

/usr/bin/innovaminexd
echo "innovaminex has been setup successfully and is running..."

