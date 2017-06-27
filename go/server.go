package main

import (
	//"code.google.com/p/go-charset/charset"
	"bytes"
	"encoding/xml"
	"fmt"
	"golang.org/x/net/html/charset"
	"net"
	"os"
)

const (
	CONN_HOST = "localhost"
	CONN_PORT = "4040"
	CONN_TYPE = "tcp"
)

func main() {
	fmt.Println("server initiating.....!")

	// Listen for incoming connections.
	l, err := net.Listen(CONN_TYPE, CONN_HOST+":"+CONN_PORT)

	if err != nil {
		fmt.Println("Error listening:", err.Error())
		os.Exit(1)
	}

	// Close the listener when the application closes.
	defer l.Close()

	fmt.Println("Listening on " + CONN_HOST + ":" + CONN_PORT)

	for {
		// Listen for incoming connection
		conn, err := l.Accept()
		if err != nil {
			fmt.Println("Error accepting: ", err.Error())
			os.Exit(1)
		}

		//for multithreaded server
		//go handleRequest(conn)
		handleRequest(conn)
	}
}

type Req struct {
	Op      string `xml:"op"`
	Msisdn  string `xml:"msisdn"`
	IdPromo string `xml:"idPromo"`
}

type Head struct {
	XMLName xml.Name `xml:"header"`
}

type Msg struct {
	Request Req `xml:"req"`
}

func handleRequest(conn net.Conn) {
	// Make a buffer to hold incoming data.
	buf := make([]byte, 1024)
	// Read the incoming connection into the buffer.
	reqLen, err := conn.Read(buf)
	if err != nil {
		fmt.Println("Error reading:", err.Error())
	}
	fmt.Println("incoming len:", reqLen)
	fmt.Printf("incoming buffer: %s", buf)

	var message Msg
	//xml.Unmarshal(buf, &message)
	reader := bytes.NewReader(buf)
	decoder := xml.NewDecoder(reader)
	decoder.CharsetReader = charset.NewReaderLabel
	err = decoder.Decode(&message)
	fmt.Println("msisdn:[", message.Request.Msisdn)

	// Send a response back to person contacting us.
	conn.Write([]byte("Message received."))
	// Close the connection when you're done with it.
	conn.Close()
}
