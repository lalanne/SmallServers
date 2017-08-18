
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

const int BUFF_LENGTH                   = 256;
const int SUCCESS                       = 0;
const int CORRECT_NUMBERS_OF_ARGUMENTS  = 3;


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
    if(argc != CORRECT_NUMBERS_OF_ARGUMENTS) {
        cout << "ERROR: wrong number of parameters [" << argc << "]" <<endl;
        return SUCCESS;
    }
    cout << "ip[" << argv[1] << "] port[" << argv[2] << "]";
    int port = stoi(argv[2]);
    string ip = argv[1];

    try{
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

        for(;;) {
            tcp::socket socket(io_service);
            boost::system::error_code error;
            boost::array<char, BUFF_LENGTH> buf;

            acceptor.accept(socket);

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            async(launch::async, handle_connection, std::ref(socket), std::ref(buf), len);
        }
    }
    catch(exception& e) {
        cerr << e.what() << endl;
    }

    return SUCCESS;
}


