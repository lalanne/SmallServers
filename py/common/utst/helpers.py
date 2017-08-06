
def build_request_message(msisdn):
    return '<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n' + \
        '<msg>\n\t<header action=\"1\" id=\"1111\"  />\n\t' + \
        '<req>\n\t\t' + \
        '<op>rslt_comp_promo</op>\n\t\t' + \
        '<msisdn>' + msisdn + '</msisdn>\n\t\t' + \
        '<strresult>OK</strresult>\n\t' + \
        '</req>\n' + \
        '</msg>\n'


def build_response_message(msisdn, result):
    return '<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n' + \
        '<msg>\n\t<header action=\"1\" id=\"1111\"  />\n\t' + \
        '<resp>\n\t\t' + \
        '<op>rslt_comp_promo</op>\n\t\t' + \
        '<msisdn>' + msisdn + '</msisdn>\n\t\t' + \
        '<result>' + result + '</result>\n\t\t' + \
        '<strresult>OK</strresult>\n\t' + \
        '</resp>\n' + \
        '</msg>\n'
