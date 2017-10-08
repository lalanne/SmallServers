package main

import (
	"common"
	"fmt"
	"net"
	"os"
	"strconv"
)

const (
	CONN_TYPE = "tcp"
	SUCCESS   = 0
)

func handleRequest(connection net.Conn, message []byte) {

	var response string = functions.BuildResponse(functions.ParseMsisdn(message))

	if response != "no response" {
		connection.Write([]byte(response))
		connection.Close()
	}
}

func main() {
	fmt.Println("Number of arguments: [" + strconv.Itoa(len(os.Args)) + "]")
	if len(os.Args) != 3 {
		fmt.Println("Error: Wrong number of command line arguments!!!")
		os.Exit(SUCCESS)
	}

	ip := os.Args[1]
	port := os.Args[2]

	l, err := net.Listen(CONN_TYPE, ip+":"+port)

	if err != nil {
		fmt.Println("Error listening:", err.Error())
		os.Exit(1)
	}

	defer l.Close()

	fmt.Println("Listening on " + ip + ":" + port)

	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Println("Error accepting: ", err.Error())
			os.Exit(1)
		}
		buf := make([]byte, 1024)
		reqLen, err := conn.Read(buf)
		if err != nil || reqLen <= 0 {
			fmt.Println("Error reading:", err.Error())
		}

		fmt.Printf("incoming buffer: [%s]\n", buf)

		go handleRequest(conn, buf)
	}
}
