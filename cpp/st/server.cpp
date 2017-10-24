
#include "ResponseBuilder.hpp"
#include "Response.hpp"
#include "XmlParser.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <iostream>
#include <string>

using boost::asio::ip::tcp;

using namespace std;

const int BUFF_LENGTH                   = 1024;
const int SUCCESS                       = 0;
const int FAIL                          = 1;

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
    if(argc < 3 && argc > 4) {
        cout << "ERROR: wrong number of parameters [" << argc << "]" << endl;
        return FAIL;
    }
    cout << "ip[" << argv[1] << "] port[" << argv[2] << "]" << endl;
    int port = stoi(argv[2]);
    string ip = argv[1];
    bool logs = false;

    if(argc == 4) {
        if(string(argv[3]) == "on") {
            logs = true;
        }
        else if(string(argv[3]) == "off") {
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

            //cout << "Waiting for connection..." << endl;
            acceptor.accept(socket);

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            string data;
            copy(buf.begin(), buf.begin()+len, std::back_inserter(data));

            if(logs) cout << data;

            handle_connection(socket, 
                            buf,
                            len);
        }
    }
    catch(exception& e) {
        cerr << e.what() << endl;
    }

    return SUCCESS;
}


