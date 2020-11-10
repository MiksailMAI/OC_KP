#include <iostream>
#include <zmq.hpp>

int main() {
    zmq::context_t context(1);
    zmq::socket_t toC(context, ZMQ_REQ);
    toC.connect("tcp://localhost:8080");
    zmq::socket_t toB(context, ZMQ_PUSH);
    toB.connect("tcp://localhost:8081");


    std::string message = "";
    while(message != "stop") {
        std::getline(std::cin, message);
        zmq::message_t msg(message.c_str(), message.size());
        toC.send(msg);

        zmq::message_t resp;
        toC.recv(&resp);

        std::string reqSizeToB = "A:" + std::to_string(message.size());
        zmq::message_t reqSize(reqSizeToB.c_str(), reqSizeToB.size());
        toB.send(reqSize);
    }
}