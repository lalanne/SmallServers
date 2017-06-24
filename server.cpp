#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
    cout << "starting server" << endl; 

    try{
        boost::asio::io_service io_service;
        //port 4040 tcp version 4
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 4040));

        for(;;) {
            tcp::socket socket(io_service);
            boost::system::error_code error;
            boost::array<char, 128> buf;

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

    return 0;
}


