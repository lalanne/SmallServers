
#include "XmlParser.hpp"

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

#include <sstream>

using boost::property_tree::ptree;
using namespace std;

XmlParser::XmlParser(const std::string& message) : msg_(message) {}

string XmlParser::msisdn() const{
    istringstream is(msg_);
    string msisdn;
    ptree pt;

    read_xml(is, pt);
    BOOST_FOREACH( ptree::value_type const& v, pt.get_child("msg") ) {
         if( v.first == "req" ) {
            msisdn = v.second.get<string>("msisdn");
         }
    }

    return msisdn;
}
