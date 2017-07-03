#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

const int PORT = 4040;
const int BUFF_LENGTH = 512;
const int SUCCESS = 0;

int main() {
    cout << "starting server" << endl; 

    try{
        boost::asio::io_service io_service;
        //port 4040 tcp version 4
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), PORT));

        for(;;) {
            tcp::socket socket(io_service);
            boost::system::error_code error;
            boost::array<char, BUFF_LENGTH> buf;

            cout << "Waiting for connection..." << endl;
            acceptor.accept(socket);

            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            cout << "len[" << len << "]" << endl;
            for(int i=0; i<len; ++i) {
                cout << buf[i];
            }

            string message = "answer ijdowjedoijwodjwoeij";

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
        
    }
    catch(exception& e) {
        cerr << e.what() << endl;
    }

    return SUCCESS;
}


