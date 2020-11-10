#include <iostream>
#include <zmq.hpp>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PULL);
    socket.bind("tcp://*:8081");


    std::string message = "";
    while(message != "stop") {
        zmq::message_t msg;
        socket.recv(&msg);
        std::string result(static_cast<char*>(msg.data()), msg.size());
        std::cout << "B:" << result << "\n";
    }
}