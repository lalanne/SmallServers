
def build_base_message(msisdn, result):
    message = '<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>' + \
        '<msg>' + \
        '<header action=\"1\" id=\"1111\"/>' + \
        '<resp>' + \
        '<op>rslt_comp_promo</op>' + \
        '<msisdn>' + str(msisdn) + '</msisdn>' + \
        '<result>' + str(result) + '</result>' + \
        '<strresult>OK</strresult>' + \
        '</resp>' + \
        '</msg>'
    return message


class Response:
    def __init__(self, msisdn):
        self.msisdn = int(msisdn)
        self.RSLT_EXITO = 0
        self.RSLT_ERR_PROMO_INEXISTENTE = 4
        self.RSLT_ERR_SIN_SALDO_PP = 14
        self.RSLT_ERR_TIPO_CLIENTE_DST = 18

    def build(self):
        # print '[build] msisdn[' + str(self.msisdn) + ']'

        response = 'no response'
        if self.msisdn == 56999694443:
            response = build_base_message(self.msisdn,
                                          self.RSLT_ERR_PROMO_INEXISTENTE)
        elif self.msisdn == 56999694444:
            response = build_base_message(self.msisdn,
                                          self.RSLT_EXITO)
        elif self.msisdn >= 56999694448 and self.msisdn <= 56999694459:
            response = build_base_message(self.msisdn,
                                          self.RSLT_EXITO)
        else:
            epilogue = str(self.msisdn)[-2:]
            print 'epilogue[' + epilogue + ']'

            if epilogue == '14':
                response = build_base_message(self.msisdn,
                                              self.RSLT_ERR_SIN_SALDO_PP)
            elif epilogue == '10':
                response = build_base_message(self.msisdn,
                                              self.RSLT_ERR_TIPO_CLIENTE_DST)
            elif epilogue == '25':
                response = 'no response'
            else:
                print '[ERROR] not recognized msisdn[' + str(self.msisdn) + ']'

        return response
