#include <iostream>
#include <zmq.hpp>

int main() {
    zmq::context_t context(1);
    zmq::socket_t fromA(context, ZMQ_REP);
    fromA.bind("tcp://*:8080");
    zmq::socket_t toB(context, ZMQ_PUSH);
    toB.connect("tcp://localhost:8081");


    std::string message = "";
    while(message != "stop") {
        zmq::message_t req;
        fromA.recv(&req);
        std::string result(static_cast<char*>(req.data()), req.size());
        std::cout << "C:" << result << "\n";

        zmq::message_t resp("OK", 2);
        fromA.send(&resp, resp.size());

        std::string reqSizeToB = "C:" + std::to_string(req.size());
        zmq::message_t reqSize(reqSizeToB.c_str(),reqSizeToB.size());
        toB.send(reqSize);
    }
}