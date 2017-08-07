package main

import (
	"common"
	"fmt"
	"net"
	"os"
)

const (
	CONN_HOST = "localhost"
	CONN_PORT = "4040"
	CONN_TYPE = "tcp"
)

func handleRequest(connection net.Conn, message []byte) {

	var response string = functions.BuildResponse(functions.ParseMsisdn(message))

	if response != "no response" {
		connection.Write([]byte(response))
		connection.Close()
	}
}

func main() {
	l, err := net.Listen(CONN_TYPE, CONN_HOST+":"+CONN_PORT)

	if err != nil {
		fmt.Println("Error listening:", err.Error())
		os.Exit(1)
	}

	defer l.Close()

	fmt.Println("Listening on " + CONN_HOST + ":" + CONN_PORT)

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

		//fmt.Printf("incoming buffer: [%s]\n", buf)

		handleRequest(conn, buf)
	}
}
