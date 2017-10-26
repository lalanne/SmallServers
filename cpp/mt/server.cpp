
#include "ResponseBuilder.hpp"
#include "Response.hpp"
#include "XmlParser.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <future>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

using namespace std;

const int BUFF_LENGTH                       = 1024;
const int SUCCESS                           = 0;
const int FAIL                              = 1;
const int IP_POSITION                       = 1;
const int PORT_POSITION                     = 2;
const int LOG_OPTION_POSITION               = 3;
const int NUMBER_OF_ARGUMENTS_LOG_OPTION    = 4;
const int NUMBER_OF_ARGUMENTS_NO_LOG_OPTION = 3;
const string LOG_ON                         = "on";
const string LOG_OFF                        = "off";

void handle_connection(tcp::socket& socket, 
                    boost::array<char, BUFF_LENGTH>& buf,
                    const int len) {
    string data;
    copy(buf.begin(), buf.begin()+len, std::back_inserter(data));
    string msisdn = XmlParser(data).msisdn();
    Response response = ResponseBuilder(msisdn).build();

    if(response != Response("no response")) {
        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(response.raw()), ignored_error);
    }
}

int main(int argc, char* argv[]) {
    if(argc < NUMBER_OF_ARGUMENTS_NO_LOG_OPTION &&
            argc > NUMBER_OF_ARGUMENTS_LOG_OPTION) {
        cout << "ERROR: wrong number of parameters [" << argc << "]" << endl;
        return FAIL;
    }
    cout << "ip[" << argv[IP_POSITION]
        << "] port[" << argv[PORT_POSITION]
        << "]" << endl;
    int port = stoi(argv[PORT_POSITION]);
    string ip = argv[IP_POSITION];
    bool logs = false;

    if(argc == NUMBER_OF_ARGUMENTS_LOG_OPTION) {
        if(string(argv[LOG_OPTION_POSITION]) == LOG_ON) {
            logs = true;
        }
        else if(string(argv[LOG_OPTION_POSITION]) == LOG_OFF) {
            logs = false;
        }
        else {
            cout << "ERROR: wrong number of parameters [" << argc << "]" <<endl;
            return FAIL;
        }
    }

    try{
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

        for(;;) {
            tcp::socket socket(io_service);
            boost::system::error_code error;
            boost::array<char, BUFF_LENGTH> buf;

            acceptor.accept(socket);

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            string data;
            copy(buf.begin(), buf.begin()+len, std::back_inserter(data));

            if(logs) cout << data;

            async(launch::async, handle_connection, std::ref(socket), std::ref(buf), len);
        }
    }
    catch(exception& e) {
        cerr << e.what() << endl;
    }

    return SUCCESS;
}


