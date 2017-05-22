#!/usr/bin/expect -f

set timeout 30

spawn ssh -t -p 22 root@172.16.24.186
expect {
	"(yes/no)?"  { send "yes\r"    }
	"*password:" { send "123456\r" }
}
#interact #take over the control by user
expect "*]#" { send "ifconfig\r" }
expect "*]#" { send "exit\r"     }
expect eof

