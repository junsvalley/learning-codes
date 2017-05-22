#!/bin/bash

DEFAULTS="cmlgen mstpd nsm imi cmlsh"
MYMODULE=$1
ALLTARGETS=$DEFAULTS

if [ -z "$MYMODULE" ];then
  ALLTARGETS=$DEFAULTS
else
  ALLTARGETS="$DEFAULTS $MYMODULE"
fi

if [ -n "$MYMODULE" ];then
  echo "Running cmlgen for my module $MYMODULE"
  #`eval ./cmlgen.sh ../.. '$MYMODULE' 1 1 0 0 1`
  #./cmlgen.sh ../.. 'pal lib layer2 nsm bgpd isisd ospfd cmld ntpd smtpd oamd ospf6d mribd l2mribd ribd pimd ripd ldpd ripngd rsvpd vrrpd mpls mplsonm mstpd lagd udld onmd rmond imi imish cmlsh vlogd hal' 1 1 0 0 1
  #./cmlgen.sh ../.. 'pal lib layer2 nsm cmld smtpd imi cmlsh' 1 1 0 0 1
fi

for TARGET in $ALLTARGETS;do
  echo "********************************************************************"
  echo "*"
  echo "* ------------------------------------->compilation for $TARGET"
  echo "*"
  echo "********************************************************************"
  make $TARGET
done

