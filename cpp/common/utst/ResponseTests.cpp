
#include "Response.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace std;


string build_message(const string& msisdn, const string& result) {
    return "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n <msg>\n\t<header action=\"1\" id=\"1111\"  />\n\t"
        "<resp>\n\t\t"
        "<op>rslt_comp_promo</op>\n\t\t"
        "<msisdn>" + msisdn + "</msisdn>\n\t\t"
        "<result>" + result + "</result>\n\t\t"
        "<strresult>OK</strresult>\n\t"
        "</resp>\n"
        "</msg>\n";
}

TEST(ResponseTests, simple_constructor) {
    const string EXPECTED_UNDEFINED_STRING = "undefined";

    Response res(EXPECTED_UNDEFINED_STRING);

    EXPECT_STREQ(res.raw().c_str(), EXPECTED_UNDEFINED_STRING.c_str());
}

TEST(ResponseTests, complete_constructor) {
    const string EXPECTED_MSISDN = "123456789";
    const string EXPECTED_RESULT = "4";

    Response res(EXPECTED_MSISDN, EXPECTED_RESULT);

    EXPECT_STREQ(res.raw().c_str(), build_message(EXPECTED_MSISDN, EXPECTED_RESULT).c_str());
}

TEST(ResponseTests, equality) {
    const string EXPECTED_MSISDN = "123456789";
    const string EXPECTED_RESULT = "4";

    Response res(EXPECTED_MSISDN, EXPECTED_RESULT);
    Response res1(EXPECTED_MSISDN, EXPECTED_RESULT);

    EXPECT_TRUE(res == res1);
}

TEST(ResponseTests, not_equality) {
    const string EXPECTED_MSISDN = "123456789";
    const string EXPECTED_RESULT = "4";
    const string EXPECTED_RESULT_1 = "10";

    Response res(EXPECTED_MSISDN, EXPECTED_RESULT);
    Response res1(EXPECTED_MSISDN, EXPECTED_RESULT_1);

    EXPECT_TRUE(res != res1);
}



