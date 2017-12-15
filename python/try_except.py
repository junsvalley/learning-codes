#!/usr/bin/python
# Filename: try_except.py
import sys
try:
	s = raw_input('Enter something --> ')
except EOFError:
	#CTRL+D
	print '\nWhy did you do an EOF on me?'
	sys.exit() # exit the program
except:
	#CTRL+C
	print '\nSome error/exception occurred.'
	# here, we are not exiting the program
print 'Done'
