package functions

import (
	"bytes"
	"encoding/xml"
	"fmt"
	"golang.org/x/net/html/charset"
)

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

	var payload string = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" +
		"<msg>" +
		"<header action=\"1\" id=\"1111\"/>" +
		"<resp>" +
		"<op>rslt_comp_promo</op>" +
		"<msisdn>" + msisdn + "</msisdn>" +
		"<result>" + result + "</result>" +
		"<strresult>OK</strresult>" +
		"</resp>" +
		"</msg>"

	return payload
}

func BuildResponse(msisdn string) string {
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

func ParseMsisdn(buf []byte) string {
	var message Msg
	reader := bytes.NewReader(buf)
	decoder := xml.NewDecoder(reader)
	decoder.CharsetReader = charset.NewReaderLabel
	decoder.Decode(&message)

	//fmt.Printf("msisdn:[%s]\n", message.Request.Msisdn)

	return message.Request.Msisdn
}
