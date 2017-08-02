#ifndef RESPONSE_HFOILFKEFKHEFKJH
#define RESPONSE_HFOILFKEFKHEFKJH

#include <string>

class Response {
    public:
        Response(const std::string& msisdn, const std::string& result);
        explicit Response(const std::string& msg);

        bool operator!=(const Response& rhs) const;
        bool operator==(const Response& rhs) const;

        std::string raw() const;

    private:
        std::string representation_;

};

#endif //RESPONSE_HFOILFKEFKHEFKJH
