
#include "helpers.hpp"

#include "ResponseBuilder.hpp"

#include <gtest/gtest.h>

#include <string>

using namespace std;

const string MSISDN_PROMO_INEXISTENTE = "56999694443";
const string MSISDN_EXITO = "56999694448";
const string MSISDN_SIN_SALDO_PP = "56999694414";
const string MSISDN_TIPO_CLIENTE_DST = "56999694410";
const string MSISDN_NO_RESPONSE = "56999694425";


TEST(ResponseBuilderTests, promo_inexistente) {
    Response expected(MSISDN_PROMO_INEXISTENTE, RSLT_ERR_PROMO_INEXISTENTE);

    ResponseBuilder builder(MSISDN_PROMO_INEXISTENTE);
    Response actual = builder.build();

    EXPECT_EQ(actual, expected);
}

TEST(ResponseBuilderTests, promo_exito) {
    Response expected(MSISDN_EXITO, RSLT_EXITO);

    ResponseBuilder builder(MSISDN_EXITO);
    Response actual = builder.build();

    EXPECT_EQ(actual, expected);
}

TEST(ResponseBuilderTests, sin_saldo_pp) {
    Response expected(MSISDN_SIN_SALDO_PP, RSLT_ERR_SIN_SALDO_PP);

    ResponseBuilder builder(MSISDN_SIN_SALDO_PP);
    Response actual = builder.build();

    EXPECT_EQ(actual, expected);
}

TEST(ResponseBuilderTests, tipo_cliente_dst) {
    Response expected(MSISDN_TIPO_CLIENTE_DST, RSLT_ERR_TIPO_CLIENTE_DST);

    ResponseBuilder builder(MSISDN_TIPO_CLIENTE_DST);
    Response actual = builder.build();

    EXPECT_EQ(actual, expected);
}

TEST(ResponseBuilderTests, no_response) {
    const string NO_RESPONSE = "no response";
    Response expected(NO_RESPONSE);

    ResponseBuilder builder(MSISDN_NO_RESPONSE);
    Response actual = builder.build();

    EXPECT_EQ(actual, expected);
}
