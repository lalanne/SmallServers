
from Parser import Parser
from helpers import build_request_message


class TestParser(object):
    def test_msisdn(self):
        expected_msisdn = '123456789'
        msg = build_request_message(expected_msisdn)

        assert expected_msisdn == Parser(msg).msisdn().text

    def test_very_short_msisdn(self):
        expected_msisdn = '7'
        msg = build_request_message(expected_msisdn)

        assert expected_msisdn == Parser(msg).msisdn().text
