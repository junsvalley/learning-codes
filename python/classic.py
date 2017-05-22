#!/usr/bin/python

import types

class Fountain:
	aList = None
	bDictionary = None
	cTuple = None

f = Fountain()
f.aList = ['abc', ['def','ghi'],'jkl','mno']
f.bDictionary = {'abc':123, 'def':[456,789], 'ghi':100}
f.cTuple = (6, 5, (4, 3), 2, 1)

def printValues(values):
	if type(values) is types.ListType:
		for ai in values:
			print '-%s' %(ai)
	else:
		print values

print f.aList
for a in f.aList:
	printValues(a)
#	if type(a) is types.StringType:
#		print a
#	else:
#		for ai in a:
#			print '-' + ai

print

print f.bDictionary
for b in f.bDictionary.keys():
	print b
	printValues(f.bDictionary[b])
#	if type(f.bDictionary[b]) is types.ListType:
#		for bi in f.bDictionary[b]:
#			print bi
#	else:
#		print f.bDictionary[b]

print

print f.cTuple
for c in f.cTuple:
	print c

print f.cTuple[2:4]

ff = open("a.cc", "w")
content = """#include <stdlib.h>
#include <stdio.h>

int main()
{
  printf("Hello World!!!\\n");
}
"""

ff.write(content)











