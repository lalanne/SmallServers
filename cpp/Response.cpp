
#include "Response.hpp"

#include <sstream>

using namespace std;

Response::Response(const string& msisdn, const string& result) {
	stringstream response;
    response << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n <msg>\n\t" <<
            "<header action=\"1\" id=\"1111\"  />\n\t" <<
            "<resp>\n\t\t" << 
            "<op>rslt_comp_promo</op>\n\t\t" << 
            "<msisdn>" + msisdn + "</msisdn>\n\t\t" <<
            "<result>" + result + "</result>\n\t\t" <<
            "<strresult>OK</strresult>\n\t" <<
            "</resp>\n" <<
            "</msg>\n";

    representation_ = response.str();
}

Response::Response(const string& msg) {
    representation_ = msg;
}

string Response::raw() {
    return representation_;
}
