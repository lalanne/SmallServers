
from ResponseBuilder import Response
from helpers import build_response_message


class TestResponseBuilder(object):
    RSLT_EXITO = '0'
    RSLT_ERR_PROMO_INEXISTENTE = '4'
    RSLT_ERR_SIN_SALDO_PP = '14'
    RSLT_ERR_TIPO_CLIENTE_DST = '18'
    NO_RESPONSE = 'no response'

    def test_not_known_msisdn(self):
        msisdn = '12'
        r = Response(msisdn)
        assert self.NO_RESPONSE == r.build()

    def test_no_response(self):
        msisdn = '56999694425'
        r = Response(msisdn)
        assert self.NO_RESPONSE == r.build()

    def test_promo_inexistente(self):
        msisdn = '56999694443'
        r = Response(msisdn)
        expected_response = \
            build_response_message(
                msisdn, self.RSLT_ERR_PROMO_INEXISTENTE
            )
        assert expected_response == r.build()

    def test_exito(self):
        msisdn = '56999694444'
        r = Response(msisdn)
        assert build_response_message(
                   msisdn, self.RSLT_EXITO
               ) == r.build()

    def test_sin_saldo(self):
        msisdn = '56999694414'
        r = Response(msisdn)
        assert build_response_message(
                   msisdn, self.RSLT_ERR_SIN_SALDO_PP
               ) == r.build()

    def test_tipo_cliente_dst(self):
        msisdn = '56999694410'
        r = Response(msisdn)
        assert build_response_message(
                   msisdn, self.RSLT_ERR_TIPO_CLIENTE_DST
               ) == r.build()
