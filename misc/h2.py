#!/usr/bin/python
import urllib
import webbrowser as web

f = open("bbbbbb", "r")
result = list()  
index = 0
for url in open("bbbbbb", "r"):  
  url = f.readline()  
  print url
  result.append(url)
  content = urllib.urlopen(url).read()
  sf = "file%d" % (index)
  index = index + 1
  open(sf, "w").write(content)
  #web.open_new_tab('jeapedu.html')
print result  
f.close() 

