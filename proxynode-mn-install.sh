#/bin/bash

cd ~
echo "****************************************************************************"
echo "* Ubuntu 16.04 is the recommended operating system for this install.       *"
echo "*                                                                          *"
echo "* This script will install and configure your Proxynode   masternodes.     *"
echo "*                                                                          *"
echo "*        IPv6 will be used if available                                    *"
echo "*                                                                          *"
echo "****************************************************************************"
echo && echo && echo
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo "!                                                 !"
echo "! Make sure you double check before hitting enter !"
echo "!                                                 !"
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
echo && echo && echo

echo "Do you want to install all needed dependencies (no if you did it before)? [y/n]"
read DOSETUP

if [ $DOSETUP = "y" ]
then
  sudo apt-get update
  sudo apt-get -y upgrade
  sudo apt-get -y dist-upgrade
  sudo apt-get update
  sudo apt-get install -y zip unzip

  cd /var
  sudo touch swap.img
  sudo chmod 600 swap.img
  sudo dd if=/dev/zero of=/var/swap.img bs=1024k count=2000
  sudo mkswap /var/swap.img
  sudo swapon /var/swap.img
  sudo free
  sudo echo "/var/swap.img none swap sw 0 0" >> /etc/fstab
  cd

  wget https://github.com/proxynode/proxynode/releases/download/v1.0.0/Linux.zip
  unzip Linux.zip
  chmod +x Linux/bin/*
  sudo mv  Linux/bin/* /usr/local/bin
  rm -rf Linux.zip Windows Linux Mac

  sudo apt-get install -y ufw
  sudo ufw allow ssh/tcp
  sudo ufw limit ssh/tcp
  sudo ufw logging on
  echo "y" | sudo ufw enable
  sudo ufw status

  mkdir -p ~/bin
  echo 'export PATH=~/bin:$PATH' > ~/.bash_aliases
  source ~/.bashrc
fi

 ## Setup conf
 IP=$(curl -k https://ident.me)
 mkdir -p ~/bin
 echo ""
 echo "Configure your masternodes now!"
 echo "Detecting IP address:$IP"

  echo ""
  echo "Enter alias for new node"
  read ALIAS

  echo ""
  echo "Enter port for node $ALIAS"
  echo "Just press enter"
  DEFAULTPORT=12195
  PORT=12195
  
  echo ""
  echo "Enter masternode private key for node $ALIAS"
  read PRIVKEY

  RPCPORT=12196
  echo "The RPC port is $RPCPORT"

  ALIAS=${ALIAS}
  CONF_DIR=~/.prx_$ALIAS

  # Create scripts
  echo '#!/bin/bash' > ~/bin/prxd_$ALIAS.sh
  echo "prxd -daemon -conf=$CONF_DIR/prx.conf -datadir=$CONF_DIR "'$*' >> ~/bin/prxd_$ALIAS.sh
  echo '#!/bin/bash' > ~/bin/prx-cli_$ALIAS.sh
  echo "prx-cli -conf=$CONF_DIR/prx.conf -datadir=$CONF_DIR "'$*' >> ~/bin/prx-cli_$ALIAS.sh
  echo '#!/bin/bash' > ~/bin/prx-tx_$ALIAS.sh
  echo "prx-tx -conf=$CONF_DIR/prx.conf -datadir=$CONF_DIR "'$*' >> ~/bin/prx-tx_$ALIAS.sh
  chmod 755 ~/bin/prx*.sh

  mkdir -p $CONF_DIR
  echo "rpcuser=user"`shuf -i 100000-10000000 -n 1` >> prx.conf_TEMP
  echo "rpcpassword=pass"`shuf -i 100000-10000000 -n 1` >> prx.conf_TEMP
  echo "rpcallowip=127.0.0.1" >> prx.conf_TEMP
  echo "rpcport=$RPCPORT" >> prx.conf_TEMP
  echo "listen=1" >> prx.conf_TEMP
  echo "server=1" >> prx.conf_TEMP
  echo "daemon=1" >> prx.conf_TEMP
  echo "logtimestamps=1" >> prx.conf_TEMP
  echo "maxconnections=256" >> prx.conf_TEMP
  echo "masternode=1" >> prx.conf_TEMP
  echo "port=$PORT" >> prx.conf_TEMP
  echo "masternodeaddr="[$IP]":$PORT" >> prx.conf_TEMP
  echo "masternodeprivkey=$PRIVKEY" >> prx.conf_TEMP
  curl https://raw.githubusercontent.com/ProxyNode/proxynode/master/addnodes.txt >> prx.conf_TEMP
  sudo ufw allow $PORT/tcp

  mv prx.conf_TEMP $CONF_DIR/prx.conf

  sh ~/bin/prxd_$ALIAS.sh
  
  
 echo
 echo -e "================================================================================================================================"
 echo -e "Proxynode coin Masternode is up and running and it is listening on port $PORT."
 echo -e "Please make sure the you use the [] when using IPv6 in the masternode config of local wallet" [$IP]:$PORT
 echo -e "MASTERNODE PRIVATEKEY is: $PRIVKEY"
 echo -e "================================================================================================================================"  
    

