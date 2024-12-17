#pragma once

#include <muduo/base/Logging.h>
#include <boost/bind/bind.hpp>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <functional>
#include <iostream>

class echo_server {
public:
    echo_server(muduo::net::EventLoop *loop,
                const muduo::net::InetAddress &listenAddr,
                const std::string &nameArg = "moony");
    ~echo_server();

    void start() {
        server_.start();
    }

private:
    void on_connection(const muduo::net::TcpConnectionPtr&);
    void on_message(const muduo::net::TcpConnectionPtr&,
                            muduo::net::Buffer*,
                            muduo::Timestamp);

    muduo::net::TcpServer server_;
    muduo::net::EventLoop *loop_;
};