
def build_request_message(msisdn):
    return '<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>' + \
        '<msg><header action=\"1\" id=\"1111\"/>' + \
        '<req>' + \
        '<op>rslt_comp_promo</op>' + \
        '<msisdn>' + msisdn + '</msisdn>' + \
        '<strresult>OK</strresult>' + \
        '</req>' + \
        '</msg>'


def build_response_message(msisdn, result):
    return '<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>' + \
        '<msg><header action=\"1\" id=\"1111\"/>' + \
        '<resp>' + \
        '<op>rslt_comp_promo</op>' + \
        '<msisdn>' + msisdn + '</msisdn>' + \
        '<result>' + result + '</result>' + \
        '<strresult>OK</strresult>' + \
        '</resp>' + \
        '</msg>'
