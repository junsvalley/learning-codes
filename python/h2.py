import urllib
import webbrowser as web
url = "http://www.163.com"
content = urllib.urlopen(url).read()
open("jeapedu.html", "w").write(content)
web.open_new_tab('jeapedu.html')
