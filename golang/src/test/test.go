package main

import (
	"fmt"
	"net"
)

func main() {
	ipv4 := net.IPv4(255, 255, 254, 0)
	fmt.Println(ipv4)
}
