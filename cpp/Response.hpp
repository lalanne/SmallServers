#ifndef RESPONSE_HFOILFKEFKHEFKJH
#define RESPONSE_HFOILFKEFKHEFKJH

#include <string>

class Response {
    public:
        Response(const std::string& msisdn, const std::string& result);
        Response(const std::string& msg);

        std::string raw() const;

    private:
        std::string representation_;

};

#endif //RESPONSE_HFOILFKEFKHEFKJH
