
#include "helpers.hpp"

using namespace std;

string build_response_message(const string& msisdn, const string& result) {
    return "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n <msg>\n\t<header action=\"1\" id=\"1111\"  />\n\t"
        "<resp>\n\t\t"
        "<op>rslt_comp_promo</op>\n\t\t"
        "<msisdn>" + msisdn + "</msisdn>\n\t\t"
        "<result>" + result + "</result>\n\t\t"
        "<strresult>OK</strresult>\n\t"
        "</resp>\n"
        "</msg>\n";
}

string build_request_message(const string& msisdn) {
    const string result = "-1";

    return "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n <msg>\n\t<header action=\"1\" id=\"1111\"  />\n\t"
        "<req>\n\t\t"
        "<op>rslt_comp_promo</op>\n\t\t"
        "<msisdn>" + msisdn + "</msisdn>\n\t\t"
        "<result>" + result + "</result>\n\t\t"
        "<strresult>OK</strresult>\n\t"
        "</req>\n"
        "</msg>\n";
}

