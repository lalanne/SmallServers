
#include "helpers.hpp"

#include "Response.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace std;


TEST(ResponseTests, simple_constructor) {
    const string EXPECTED_UNDEFINED_STRING = "undefined";

    Response res(EXPECTED_UNDEFINED_STRING);

    EXPECT_STREQ(res.raw().c_str(), EXPECTED_UNDEFINED_STRING.c_str());
}

TEST(ResponseTests, complete_constructor) {
    const string EXPECTED_MSISDN = "123456789";
    const string EXPECTED_RESULT = "4";

    Response res(EXPECTED_MSISDN, EXPECTED_RESULT);

    EXPECT_STREQ(res.raw().c_str(), build_response_message(EXPECTED_MSISDN, EXPECTED_RESULT).c_str());
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



