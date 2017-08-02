
#include "response_factory.hpp"

#include <iostream>

using namespace std;


Response response_factory(string& msisdn) {
    Response response("no response");

    if(msisdn == "56999694443") {
        response = Response(msisdn, RSLT_ERR_PROMO_INEXISTENTE);
    }
    else if(msisdn == "56999694444") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694448") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694449") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694450") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694451") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694452") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694453") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694454") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694455") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694456") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694457") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694458") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else if(msisdn == "56999694459") {
        response = Response(msisdn, RSLT_EXITO);
    }
    else {
        const string epilogue = msisdn.substr(msisdn.length() - 2);

        if(epilogue == "14") {
            response = Response(msisdn, RSLT_ERR_SIN_SALDO_PP);
        }
        else if(epilogue == "10") {
            response = Response(msisdn, RSLT_ERR_TIPO_CLIENTE_DST);
        }
        else if(epilogue == "25") {
            response = Response("no response");
        }
        else {
            cout << "[ERROR] recognized msisdn NOT [" <<  msisdn << "]" << endl;
        }
    }

    return response;
}
