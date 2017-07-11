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

		go handleRequest(conn, buf)
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

const (
	RSLT_EXITO                 = "0"
	RSLT_ERR_PROMO_INEXISTENTE = "4"
	RSLT_ERR_SIN_SALDO_PP      = "14"
	RSLT_ERR_TIPO_CLIENTE_DST  = "18"
)

func buildResponseBase(msisdn string, result string) string {
	//fmt.Printf("[buildResponse] msisdn[%s] reuslt[%s]\n", msisdn, result)

	var payload string = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n" +
		"<msg>\n\t" +
		"<header action=\"1\" id=\"1111\"  />\n\t" +
		"<resp>\n\t\t" +
		"<op>rslt_comp_promo</op>\n\t\t" +
		"<msisdn>" + msisdn + "</msisdn>\n\t\t" +
		"<result>" + result + "</result>\n\t\t" +
		"<strresult>OK</strresult>\n\t" +
		"</resp>\n" +
		"</msg>\n"

	return payload
}

func buildResponse(msisdn string) string {
	//fmt.Printf("[buildResponse] msisdn[%s]\n", msisdn)

	var payload string = "no response"

	switch msisdn {
	case "56999694443":
		payload = buildResponseBase(msisdn, RSLT_ERR_PROMO_INEXISTENTE)
	case "56999694444":
		fallthrough
	case "56999694448":
		fallthrough
	case "56999694449":
		fallthrough
	case "56999694450":
		fallthrough
	case "56999694451":
		fallthrough
	case "56999694452":
		fallthrough
	case "56999694453":
		fallthrough
	case "56999694454":
		fallthrough
	case "56999694455":
		fallthrough
	case "56999694456":
		fallthrough
	case "56999694457":
		fallthrough
	case "56999694458":
		fallthrough
	case "56999694459":
		payload = buildResponseBase(msisdn, RSLT_EXITO)
	default:
		var epilogue string = msisdn[len(msisdn)-2:]
		fmt.Printf("[buildResponse] epilogue[%s]", epilogue)

		switch epilogue {
		case "14":
			payload = buildResponseBase(msisdn, RSLT_ERR_SIN_SALDO_PP)
		case "10":
			payload = buildResponseBase(msisdn, RSLT_ERR_TIPO_CLIENTE_DST)
		case "25":
			payload = "no response"
		default:
			fmt.Printf("[buildResponse] not recognized msisdn[%s]", msisdn)

		}
	}

	return payload
}

func parseMsisdn(buf []byte) string {
	var message Msg
	reader := bytes.NewReader(buf)
	decoder := xml.NewDecoder(reader)
	decoder.CharsetReader = charset.NewReaderLabel
	decoder.Decode(&message)

	//fmt.Printf("msisdn:[%s]\n", message.Request.Msisdn)

	return message.Request.Msisdn
}

func handleRequest(connection net.Conn, message []byte) {

	var response string = buildResponse(parseMsisdn(message))

	if response != "no response" {
		connection.Write([]byte(response))
		connection.Close()
	}
}
