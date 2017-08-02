
#include "ResponseBuilder.hpp"

#include <iostream>

using namespace std;


ResponseBuilder::ResponseBuilder(const string& msisdn) : msisdn_(msisdn) {}

Response ResponseBuilder::build() const {
    Response response("no response");

    if(msisdn_ == "56999694443") {
        response = Response(msisdn_, RSLT_ERR_PROMO_INEXISTENTE);
    }
    else if(msisdn_ == "56999694444") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694448") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694449") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694450") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694451") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694452") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694453") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694454") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694455") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694456") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694457") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694458") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else if(msisdn_ == "56999694459") {
        response = Response(msisdn_, RSLT_EXITO);
    }
    else {
        const string epilogue = msisdn_.substr(msisdn_.length() - 2);

        if(epilogue == "14") {
            response = Response(msisdn_, RSLT_ERR_SIN_SALDO_PP);
        }
        else if(epilogue == "10") {
            response = Response(msisdn_, RSLT_ERR_TIPO_CLIENTE_DST);
        }
        else if(epilogue == "25") {
            response = Response("no response");
        }
        else {
            cout << "[ERROR] recognized msisdn NOT [" <<  msisdn_ << "]" << endl;
        }
    }

    return response;
}
