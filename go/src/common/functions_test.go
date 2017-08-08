package functions

import (
	"testing"
)

func buildRequestMessage(msisdn string) string {
	var message string = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" +
		"<msg>" +
		"<header action=\"1\" id=\"1111\"  />" +
		"<req>" +
		"<op>rslt_comp_promo</op>" +
		"<msisdn>56999694444</msisdn>" +
		"<result>0</result>" +
		"<strresult>OK</strresult>" +
		"</req>" +
		"</msg>"

	return message
}

func buildResponseMessage(msisdn string, result string) string {

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

func TestParseMsisdn(t *testing.T) {
	const expected_msisdn = "56999694444"
	buf := make([]byte, 1024)
	buf = []byte(buildRequestMessage(expected_msisdn))

	var actual_msisdn string = ParseMsisdn(buf)

	if expected_msisdn != actual_msisdn {
		t.Errorf("expected msisdn, got: [%s], want: [%s].", expected_msisdn, actual_msisdn)
	}
}

func TestBuildResponseBase(t *testing.T) {
	const msisdn = "56999694444"
	const result = "0"

	var expected_response string = buildResponseMessage(msisdn, result)
	var actual_response string = buildResponseBase(msisdn, result)

	if expected_response != actual_response {
		t.Errorf("expected response, got: [%s], want: [%s].", expected_response, actual_response)
	}
}

func TestBuildResponsePromoInexistente(t *testing.T) {
	var expected_response = buildResponseMessage("56999694443", RSLT_ERR_PROMO_INEXISTENTE)
	var actual_response = BuildResponse("56999694443")

	if expected_response != actual_response {
		t.Errorf("expected response, got: [%s], want: [%s].", expected_response, actual_response)
	}
}

func TestBuildResponseExito(t *testing.T) {
	var expected_response = buildResponseMessage("56999694457", RSLT_EXITO)
	var actual_response = BuildResponse("56999694457")

	if expected_response != actual_response {
		t.Errorf("expected response, got: [%s], want: [%s].", expected_response, actual_response)
	}
}

func TestBuildResponseSinSaldoPP(t *testing.T) {
	var expected_response = buildResponseMessage("56999694414", RSLT_ERR_SIN_SALDO_PP)
	var actual_response = BuildResponse("56999694414")

	if expected_response != actual_response {
		t.Errorf("expected response, got: [%s], want: [%s].", expected_response, actual_response)
	}
}

func TestBuildResponseTipoClienteDst(t *testing.T) {
	var expected_response = buildResponseMessage("56999694410", RSLT_ERR_TIPO_CLIENTE_DST)
	var actual_response = BuildResponse("56999694410")

	if expected_response != actual_response {
		t.Errorf("expected response, got: [%s], want: [%s].", expected_response, actual_response)
	}
}

func TestBuildResponseNoResponse(t *testing.T) {
	var expected_response = "no response"
	var actual_response = BuildResponse("56999694425")

	if expected_response != actual_response {
		t.Errorf("expected response, got: [%s], want: [%s].", expected_response, actual_response)
	}
}
