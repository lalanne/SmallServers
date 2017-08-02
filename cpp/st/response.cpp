
#include "response.hpp"

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <sstream>

using namespace std;
using boost::property_tree::ptree;

string extract_msisdn(const string& message) {
    istringstream is(message);
    string msisdn;
    ptree pt;

    read_xml(is, pt);
    BOOST_FOREACH( ptree::value_type const& v, pt.get_child("msg") ) {
         if( v.first == "req" ) {
            msisdn = v.second.get<string>("msisdn");
         }
    }

    //cout << "[extract_msisdn] msisdn[" << msisdn  << "]" << endl;
    return msisdn;
}

string build_response(const string& msisdn, const string& result) {
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

    return response.str();
}

string select_message(string& msisdn) {
    string response = "no response";

    if(msisdn == "56999694443") {
        response = build_response(msisdn, RSLT_ERR_PROMO_INEXISTENTE);
    }
    else if(msisdn == "56999694444") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694448") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694449") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694450") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694451") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694452") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694453") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694454") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694455") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694456") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694457") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694458") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694459") {
        response = build_response(msisdn, RSLT_EXITO);
    }
    else {
        const string epilogue = msisdn.substr(msisdn.length() - 2);

        if(epilogue == "14") {
            response = build_response(msisdn, RSLT_ERR_SIN_SALDO_PP);
        }
        else if(epilogue == "10") {
            response = build_response(msisdn, RSLT_ERR_TIPO_CLIENTE_DST);
        }
        else if(epilogue == "25") {
            response = "no response";
        }
        else {
            cout << "[ERROR] recognized msisdn NOT [" <<  msisdn << "]" << endl;
        }
    }

    return response;
}
