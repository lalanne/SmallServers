
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <boost/foreach.hpp>

#include <boost/asio.hpp>

#include <iostream>
#include <string>
#include <sstream>

using boost::asio::ip::tcp;
using boost::property_tree::ptree;

using namespace std;

const int PORT = 4040;
const int BUFF_LENGTH = 256;
const int SUCCESS = 0;

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

    cout << "[extract_msisdn] msisdn[" << msisdn  << "]" << endl;
    return msisdn;
}

string build_response(string& msisdn, string& result) {
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

}

int main() {
    cout << "starting server" << endl; 

    try{
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), PORT));

        for(;;) {
            tcp::socket socket(io_service);
            boost::system::error_code error;
            boost::array<char, BUFF_LENGTH> buf;

            cout << "Waiting for connection..." << endl;
            acceptor.accept(socket);

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            for(int i=0; i<len; ++i) {
                cout << buf[i];
            }

            string data;
            copy(buf.begin(), buf.begin()+len, std::back_inserter(data));
            string msisdn = extract_msisdn(data);
            select_message(msisdn);

            string message = "answer ijdowjedoijwodjwoeij";

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch(exception& e) {
        cerr << e.what() << endl;
    }

    return SUCCESS;
}


