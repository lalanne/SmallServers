package main

import (
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

func buildResponse(msisdn string) string {
	fmt.Printf("[buildResponse] msisdn[%s]\n", msisdn)

	var ret string = "loco"
	return ret
}

func handleRequest(conn net.Conn) {
	// Make a buffer to hold incoming data.
	buf := make([]byte, 1024)
	// Read the incoming connection into the buffer.
	reqLen, err := conn.Read(buf)
	if err != nil || reqLen <= 0 {
		fmt.Println("Error reading:", err.Error())
	}

	fmt.Printf("incoming buffer: [%s]\n", buf)

	var message Msg
	reader := bytes.NewReader(buf)
	decoder := xml.NewDecoder(reader)
	decoder.CharsetReader = charset.NewReaderLabel
	err = decoder.Decode(&message)

	fmt.Printf("msisdn:[%s]\n", message.Request.Msisdn)

	var payload string = buildResponse(message.Request.Msisdn)

	// Send a response back to person contacting us.
	//conn.Write([]byte("Message received."))
	conn.Write([]byte(payload))
	// Close the connection when you're done with it.
	conn.Close()
}
