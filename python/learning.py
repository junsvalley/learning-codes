#!/usr/bin/python

import MySQLdb
import os
import re

def printdb(results):
  for row in results:
    print "db vaue:", row[0], row[1]
  return

a = 10.0
b = 3.0
c = a / b
print "a / b = ", c
c = a // b #remove the digitals after decimal point
print "a // b =", c

print "identity:", id(a), id(b)

lista = [0,2,4,6,8]

a = 4
if( a in lista): #if( a not in lista):
  print "a in list"

strl = []
db = MySQLdb.connect("localhost", "root", "abcd#1234", "mydb")
cursor = db.cursor()

try:
  cursor.execute("SELECT * FROM tab1");
  results = cursor.fetchall()
  printdb(results)
  cursor.execute("DROP TABLE IF EXISTS EMPLOYEE")
  sql = """CREATE TABLE EMPLOYEE(
           FIRST_NAME CHAR(20) NOT NULL,
           LAST_NAME CHAR(20),
           AGE INT,
           SEX CHAR(1),
           INCOME FLOAT)"""
  print sql
  cursor.execute(sql)
except:
  print "error happened!!!"

db.close()

fo = open("foo.txt", "rw")
fstr = fo.read(10)
print "read str :", fstr
pos = fo.tell()
fo.seek(0, 0)
fstr = fo.read(10)
print "read str :", fstr, pos
fo.close()

print os.getcwd()

raw_input("Press the enter key to exit...")
