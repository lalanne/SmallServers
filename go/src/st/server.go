package main

import (
	"common"
	"fmt"
	"net"
	"os"
	"strconv"
)

const (
	IP_POSITION                       = 1
	PORT_POSITION                     = 2
	LOG_OPTION_POSITION               = 3
	CONN_TYPE                         = "tcp"
	LOG_ON                            = "on"
	LOG_OFF                           = "off"
	SUCCESS                           = 0
	FAIL                              = 1
	NUMBER_OF_ARGUMENTS_LOG_OPTION    = 4
	NUMBER_OF_ARGUMENTS_NO_LOG_OPTION = 3
	NUMBER_OF_BYTES_RECEIVED          = 1024
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
	if len(os.Args) < NUMBER_OF_ARGUMENTS_NO_LOG_OPTION &&
		len(os.Args) > NUMBER_OF_ARGUMENTS_LOG_OPTION {
		fmt.Println("Error: Wrong number of command line arguments!!!")
		os.Exit(SUCCESS)
	}

	ip := os.Args[IP_POSITION]
	port := os.Args[PORT_POSITION]
	logs := false

	if len(os.Args) == NUMBER_OF_ARGUMENTS_LOG_OPTION {
		if os.Args[LOG_OPTION_POSITION] == LOG_ON {
			logs = true
		} else if os.Args[LOG_OPTION_POSITION] == LOG_OFF {
			logs = false
		} else {
			fmt.Println("Error: wrong option for logging!!!")
			os.Exit(FAIL)
		}
	}

	l, err := net.Listen(CONN_TYPE, ip+":"+port)

	if err != nil {
		fmt.Println("Error listening:", err.Error())
		os.Exit(FAIL)
	}

	defer l.Close()

	fmt.Println("Listening on " + ip + ":" + port)

	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Println("Error accepting: ", err.Error())
			os.Exit(FAIL)
		}
		buf := make([]byte, NUMBER_OF_BYTES_RECEIVED)
		reqLen, err := conn.Read(buf)
		if err != nil || reqLen <= 0 {
			fmt.Println("Error reading:", err.Error())
		}

		if logs {
			fmt.Printf("incoming buffer: [%s]\n", buf)
		}

		handleRequest(conn, buf)
	}
}
