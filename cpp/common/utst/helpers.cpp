
#include "helpers.hpp"

using namespace std;

string build_response_message(const string& msisdn, const string& result) {
    return "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><msg><header action=\"1\" id=\"1111\"/>"
        "<resp>"
        "<op>rslt_comp_promo</op>"
        "<msisdn>" + msisdn + "</msisdn>"
        "<result>" + result + "</result>"
        "<strresult>OK</strresult>"
        "</resp>"
        "</msg>";
}

string build_request_message(const string& msisdn) {
    const string result = "-1";

    return "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><msg><header action=\"1\" id=\"1111\"/>"
        "<req>"
        "<op>rslt_comp_promo</op>"
        "<msisdn>" + msisdn + "</msisdn>"
        "<result>" + result + "</result>"
        "<strresult>OK</strresult>"
        "</req>"
        "</msg>";
}

