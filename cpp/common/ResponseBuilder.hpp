
#ifndef RESPONSEBUILDER_IUHIUHFIDHFIDHF
#define RESPONSEBUILDER_IUHIUHFIDHFIDHF

#include "Response.hpp"

#include <string>


const std::string RSLT_EXITO                    = "0";
const std::string RSLT_ERR_PROMO_INEXISTENTE    = "4";
const std::string RSLT_ERR_SIN_SALDO_PP         = "14";
const std::string RSLT_ERR_TIPO_CLIENTE_DST     = "18";


class ResponseBuilder {
    public:
        explicit ResponseBuilder(const std::string& msisdn);

        Response build() const;

    private:
        const std::string& msisdn_;
};

#endif //RESPONSEBUILDER_IUHIUHFIDHFIDHF
