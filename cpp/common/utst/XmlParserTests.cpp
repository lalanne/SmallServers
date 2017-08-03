
#include "helpers.hpp"

#include "XmlParser.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace std;


TEST(XmlParserTests, constructor) {
    const string EXPECTED_MSISDN = "123456789";

    XmlParser parser(build_request_message(EXPECTED_MSISDN));

    EXPECT_STREQ(EXPECTED_MSISDN.c_str(), parser.msisdn().c_str());
}




