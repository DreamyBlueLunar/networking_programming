#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string.h>

#define BUFFER_LEN 1024
#define CONN_LEN   1024
#define EVENTS_LEN 1024
#define ADD        0
#define MOD        1

namespace moony {

class echo_server;

struct conn_item {
    int fd_;

    char r_buffer_[BUFFER_LEN];
    int r_len_;
    char w_buffer_[BUFFER_LEN];
    int w_len_;

    union {
        const int (*accept_callback_)(echo_server&, const int&);
        const int (*recv_callback_)(echo_server&, const int&);
    } recv_t_;
    const int (*send_callback_)(echo_server&, const int&);
};

class echo_server {
public:
    static echo_server& get_echo_server(void);
    const int run(const unsigned short& port, const int& cnt);

private:
    echo_server();
    ~echo_server();

    echo_server(const echo_server& obj) = delete;
    const echo_server& operator=(echo_server& obj) = delete;

    const int init_server(const unsigned short& port);
    const int set_event(const int& fd, const int& op, const int& event);
    friend const int accept_cb(echo_server& server, const int& fd);
    friend const int send_cb(echo_server& server, const int& fd);
    friend const int recv_cb(echo_server& server, const int& fd);

public:
    std::vector<conn_item> conn_list_;
    int epfd_;
};

const int accept_cb(echo_server& server, const int& fd);
const int send_cb(echo_server& server, const int& fd);
const int recv_cb(echo_server& server, const int& fd);
}