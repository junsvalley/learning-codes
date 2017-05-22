#!/bin/bash

EXP_PATH=/root/myscripts/myenvexp.txt

echo "ls -l $EXP_PATH"

RSTS=`eval ls -l $EXP_PATH`

echo "$RSTS"

source myenvexp.txt

echo "$ZEBM_DB_CONF_DIR"
echo "$ZEBM_BIN_DIR"
