#!/bin/bash
#set -x

DEFAULTS="pppoe"
MYMODULE=$1
MYMODULED=

if [ -n "$MYMODULE" ];then
  MYMODULED=$MYMODULE"d"
else
  MYMODULE=$DEFAULTS
  MYMODULED=$DEFAULTS"d"
fi


KIDSTR="ps aux | grep $MYMODULE | egrep -v '(grep|mymodule)' | awk '{print \$2}'"
KID=`eval $KIDSTR`
#echo "$KIDSTR $KID"
if [ -n "$KID" ];then
  echo "$MYMODULED daemon(pid=$KID) exists"
  kill -9 $KID
fi

echo "$ZEBM_BIN_DIR/$MYMODULED"
$ZEBM_BIN_DIR/$MYMODULED
