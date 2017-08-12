
#include "Response.hpp"

#include <sstream>

using namespace std;

Response::Response(const string& msisdn, const string& result) {
	stringstream response;
    response << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><msg>" <<
            "<header action=\"1\" id=\"1111\"/>" <<
            "<resp>" << 
            "<op>rslt_comp_promo</op>" << 
            "<msisdn>" + msisdn + "</msisdn>" <<
            "<result>" + result + "</result>" <<
            "<strresult>OK</strresult>" <<
            "</resp>" <<
            "</msg>";

    representation_ = response.str();
}

Response::Response(const string& msg) {
    representation_ = msg;
}

bool Response::operator!=(const Response& rhs) const {
    return !(*this == rhs);
}

bool Response::operator==(const Response& rhs) const {
    return this->representation_ == rhs.representation_;
}

string Response::raw() const {
    return representation_;
}
