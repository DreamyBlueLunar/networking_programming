#include "reactor.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "usage: ./" << argv[0] << " $port $port_cnt" << std::endl;
        return -1;
    }

    unsigned short port = atoi(argv[1]);
    int port_cnt = atoi(argv[2]);
    
    moony::echo_server echo;
    echo.run(port, port_cnt);

    return 0;
}