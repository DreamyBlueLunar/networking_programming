#include "echo_server.h"

echo_server::echo_server(muduo::net::EventLoop *loop,
        const muduo::net::InetAddress &listenAddr,
        const std::string &nameArg):
            server_(loop, listenAddr, nameArg), loop_(loop) {
    // 设置用户连接事件的回调
    server_.setConnectionCallback(std::bind(&echo_server::on_connection, 
                                            this, 
                                            std::placeholders::_1));
    // 设置用户读写事件的回调
    server_.setMessageCallback(std::bind(&echo_server::on_message, 
                                        this, 
                                        std::placeholders::_1, 
                                        std::placeholders::_2, 
                                        std::placeholders::_3));
    // 设置线程池中线程的数量
    // 1 * I/O线程 + 3 * 工作线程
    server_.setThreadNum(4);
}

echo_server::~echo_server() {}

void echo_server::on_connection(const muduo::net::TcpConnectionPtr& conn) {
    if (conn->connected()) {
        LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is UP";
    } else {
        LOG_INFO << "EchoServer - " << conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is DOWN";
        conn->shutdown();
    }
}

void echo_server::on_message(const muduo::net::TcpConnectionPtr& conn,
                             muduo::net::Buffer* buf,
                             muduo::Timestamp time) {
    // 接收到所有的消息，然后回显
    muduo::string msg(buf->retrieveAllAsString());
    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
             << "data received at " << time.toString();
    conn->send(msg);
}