
#ifndef XMLPARSER_UIHSIFHSFIHSF
#define XMLPARSER_UIHSIFHSFIHSF

#include <string>

class XmlParser {
    public:
        explicit XmlParser(const std::string& message);

        std::string msisdn() const;

    private:
        const std::string& msg_;
};

#endif //XMLPARSER_UIHSIFHSFIHSF
