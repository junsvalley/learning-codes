#!/bin/bash

ADDS=$1
KID=
YANGCLIRUN=no
#YANGCLIRUN=yes

source ~/myscripts/myenvexp.txt
insmod $ZEBM_BIN_DIR/layer2_module.ko 2>/dev/null
insmod $ZEBM_BIN_DIR/mpls_module.ko 2>/dev/null

KILL_EXIST_PROCESS()
{
  if [ -n "$KID" ]
  then
    kill -9 $KID
  fi
}

START_MODULE_DAEMON_PROCESS()
{
  for module in $MODULES;do
    KID=`eval ps aux | grep $module | egrep -v grep | awk '{print \$2}'`
    echo "$module $KID"
    KILL_EXIST_PROCESS
    $ZEBM_BIN_DIR/$module -d
  done
}

#DEFAULTS="mstpd nsm imi cmld"
DEFAULTS="nsm imi cmld"
ALLS="$ADDS $DEFAULTS"
MODULES=$ALLS
START_MODULE_DAEMON_PROCESS

if [ "$YANGCLIRUN" == "yes" ];then
  #cd $ZEBM_BIN_DIR
  #./install_netconf.sh

  KID=`eval ps aux | grep "netconfd --superuser=root" | egrep -v grep | awk '{print \$2}'`
  echo "netconf $KID"
  KILL_EXIST_PROCESS
  netconfd --superuser=root &

  rm -rf /tmp/ncxserver.sock

  CKSTR=`eval netstat -plnt | grep sshd | grep 830`
  if [ `expr length "$CKSTR"` == 0 ]
  then
    iptables -F
    iptables -X
    setenforce 0
    systemctl restart sshd.service
  else
    echo -e "\n$CKSTR"
  fi
fi
