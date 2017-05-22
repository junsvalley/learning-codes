#!/usr/bin/bash

IDX=0
MODULENAME=$1
ATTRNAME=
ATTRTYPE=
TEMPFILE=tmpxml
CREATEDATE=`date +%Y-%m-%d`
OBLISTFLAG=no
CONTAINERFLAG=no

ALLATTRS="template string CML_STRING_T authentication int CML_PPPOE_AUTHENTICATION_TYPE_T checkMagicNumber int CML_PPPOE_ENABLE_STATE_T keepaliveTime u_int32_t CML_UINT32_T keepaliveCount u_int32_t CML_UINT32_T mru u_int32_t CML_UINT32_T acName string CML_STRING_T defaultDomain string CML_STRING_T checkAcCookie int CML_PPPOE_ENABLE_STATE_T serviceNameOmit int CML_PPPOE_ENABLE_STATE_T accessMaxSession u_int32_t CML_UINT32_T accessDelayTime u_int32_t CML_UINT32_T accessDelayMacType int CML_ACCESS_DELAY_MAC_TYPE_T"

BUILD_HEADER()
{
echo "<?xml version=\"1.0\" encoding=\"utf-8\"?>                           " >  $TEMPFILE
echo " <cml:CMLDataModel                                                   " >> $TEMPFILE
echo "     xmlns:cml=\"http://www.ipinfusion.com/CMLSchema\"               " >> $TEMPFILE
echo "     xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"         " >> $TEMPFILE
echo "     cml:noNamespaceSchemaLocation=\"cml_data_model.xsd\">           " >> $TEMPFILE
echo "  <managedObjectClass name=\"$MODULENAME\" desc=\"$MODULENAME data module\"> " >> $TEMPFILE
echo "    <!--belongs-to>ZebOS</belongs-to-->                              " >> $TEMPFILE
echo "    <import>cml_data_types</import>                                  " >> $TEMPFILE
echo "    <revision>$CREATEDATE</revision>                                 " >> $TEMPFILE
echo "    <category>CML_CONFIG</category>                                  " >> $TEMPFILE
}

BUILD_TAILER()
{
echo "  </managedObjectClass>" >> $TEMPFILE
echo "</cml:CMLDataModel>" >> $TEMPFILE
}

BUILD_OBLIST()
{
OBLISTFLAG=yes
echo "    <objectlist name=\"$MODULENAME\">                                " >> $TEMPFILE
echo "      <cli>                                                          " >> $TEMPFILE
echo "        <cli-mode-prompt>(config-$MODULENAME)</cli-mode-prompt>      " >> $TEMPFILE
echo "      </cli>                                                         " >> $TEMPFILE
}

OBLIST_END()
{
echo "    </objectlist>                                                    " >> $TEMPFILE
OBLISTFLAG=no
}

BUILD_CONTAINER()
{
CONTAINERFLAG=yes
echo "    <container name=\"$MODULENAME\" desc=\"container\">              " >> $TEMPFILE
echo "      <cli>                                                          " >> $TEMPFILE
echo "        <!--cliFlag>drop-element-name</cliFlag-->                    " >> $TEMPFILE
echo "      </cli>                                                         " >> $TEMPFILE
}

CONTAINER_END()
{
echo "    </container>                                                     " >> $TEMPFILE
CONTAINERFLAG=no
}

CLIPREPENDSTR_DEF()
{
echo "    <cli>                                                            " >> $TEMPFILE
echo "      <cliprependstr str='example' desc='example description' value='example' />" >> $TEMPFILE
echo "    </cli>                                                           " >> $TEMPFILE
}

DEFINE_ATTRS()
{
IDX=0
for VALUE in $ALLATTRS;do
  IDX=`expr $IDX + 1`
  CHK=`expr $IDX % 3`
  if [ $CHK == 1 ];then
    ATTRNAME=$VALUE
  elif [ $CHK == 0 ];then
    ATTRCMLTYPE=$VALUE
echo "      <attr>                                                         " >> $TEMPFILE
echo "        <name>$ATTRNAME</name>                                       " >> $TEMPFILE
echo "        <desc displayString=\"$ATTRNAME\" helpString=\"<Help string for $ATTRNAME>\"/>" >> $TEMPFILE
echo "        <type>$ATTRCMLTYPE</type>                                    " >> $TEMPFILE
  if [ $IDX == 3 ];then #first attribute
    if [ "$OBLISTFLAG" == "yes" ];then
echo "        <flag>CML_RDN</flag>                                         " >> $TEMPFILE
    fi
  fi
echo "        <!--default></default-->                                     " >> $TEMPFILE
echo "        <!--range min='0' max='100' helpString=\"Available Range to Set\"/-->" >> $TEMPFILE
echo "        <cli>                                                        " >> $TEMPFILE
echo "          <cliFlag>include-input-for-unset<cliFlag>                  " >> $TEMPFILE
echo "          <!--prependstr><prependstr-->                              " >> $TEMPFILE
echo "        </cli>                                                       " >> $TEMPFILE
echo "      </attr>                                                        " >> $TEMPFILE
  fi
done
} 

SOUTHINTERFACE()
{
IDX=0
for VALUE in $ALLATTRS;do
  IDX=`expr $IDX + 1`
  CHK=`expr $IDX % 3`
  if [ $CHK == 1 ];then
    ATTRNAME=$VALUE
  elif [ $CHK == 2 ];then
    ATTRTYPE=$VALUE
echo "    <operation name=\"objectUpdate\">                                " >> $TEMPFILE
echo "      <implicit-UnsetApi>yes</implicit-UnsetApi>                     " >> $TEMPFILE
echo "      <attr>$ATTRNAME</attr>                                         " >> $TEMPFILE
echo "      <southInterface name=\"set_$ATTRNAME\">                        " >> $TEMPFILE
echo "        <params>                                                     " >> $TEMPFILE
echo "          <param name=\"$ATTRNAME\" type=\"$ATTRTYPE\"  direction=\"in\" />" >> $TEMPFILE
echo "        </params>                                                    " >> $TEMPFILE
echo "      </southInterface>                                              " >> $TEMPFILE
#echo "      <unsetApi name=\"unset_$ATTRNAME\">                            " >> $TEMPFILE
#echo "        <params>                                                     " >> $TEMPFILE
#echo "          <param name=\"$ATTRNAME\" type=\"u_int32_t\"  direction=\"in\" />" >> $TEMPFILE
#echo "        </params>                                                    " >> $TEMPFILE
#echo "      </unsetApi>                                                    " >> $TEMPFILE
echo "    </operation>                                                     " >> $TEMPFILE
  else
    ATTRCMLTYPE=$VALUE
    printf "ATTRNAME %-20s -->ATTRTYPE %-12s -->ATTRCMLTYPE %-20s\n" "$ATTRNAME" "$ATTRTYPE" "$ATTRCMLTYPE"
  fi
done
}


SHOW_CONFIG()
{
echo "    <cli-command name=\"show $MODULENAME info\" helpString=\"'Show running system information','$MODULENAME module','$MODULENAME config info'\"> " >> $TEMPFILE
  IDX=0
  for VALUE in $ALLATTRS;do
    IDX=`expr $IDX + 1`
    CHK=`expr $IDX % 3`
    if [ $CHK == 1 ];then
      ATTRNAME=$VALUE
echo "      <attr>$ATTRNAME</attr> " >> $TEMPFILE
    fi
  done
echo "      <ShowTemplate> " >> $TEMPFILE
  IDX=0
  for VALUE in $ALLATTRS;do
    IDX=`expr $IDX + 1`
    CHK=`expr $IDX % 3`
    if [ $CHK == 1 ];then
      ATTRNAME=$VALUE
echo "        <cli-out name=\"$ATTRNAME : \$$ATTRNAME \n\"/> " >> $TEMPFILE
    fi
  done
echo "      </ShowTemplate> " >> $TEMPFILE
echo "    </cli-command> " >> $TEMPFILE
}


##
## START
##
BUILD_HEADER

#ATTRS defined in objectlist
BUILD_CONTAINER
#BUILD_OBLIST
DEFINE_ATTRS
#OBLIST_END
CONTAINER_END

CLIPREPENDSTR_DEF

#SOUTHINTERFACE generate
SOUTHINTERFACE

SHOW_CONFIG

BUILD_TAILER



