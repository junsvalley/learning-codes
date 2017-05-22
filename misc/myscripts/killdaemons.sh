#!/bin/bash

ADDS=$1

DEFAULTS="mstpd ospf nsm imi cmld netconfd"
ALLS="$DEFAULTS $ADDS"

for module in $ALLS;do
  KID=`eval ps aux | grep $module | egrep -v grep | awk '{print \$2}'`
  echo "$module $KID"
  if [ -n "$KID" ];then
    kill -9 $KID
  fi
done
