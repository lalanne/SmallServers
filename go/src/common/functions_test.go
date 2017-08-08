package functions

import (
	"testing"
)

func buildMessage(msisdn string) string {
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

func TestParseMsisdn(t *testing.T) {
	const expected_msisdn = "56999694444"
	buf := make([]byte, 1024)
	buf = []byte(buildMessage(expected_msisdn))
	var actual_msisdn string = ParseMsisdn(buf)

	if expected_msisdn != actual_msisdn {
		t.Errorf("expected msisdn, got: [%s], want: [%s].", expected_msisdn, actual_msisdn)
	}
}
