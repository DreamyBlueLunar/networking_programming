#include "reactor.hpp"

moony::echo_server::echo_server() {
    conn_list_.resize(CONN_LEN);
    epfd_ = epoll_create(1);
}

moony::echo_server::~echo_server() {
    for (int i = 0; i < conn_list_.size(); i ++) {
        if (conn_list_[i].fd_ > 2) {
            close(conn_list_[i].fd_);
        }
    }
    close(epfd_);
}

const int moony::echo_server::init_server(const unsigned short& port) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        return -1;
    }

    conn_list_[listen_fd].fd_ = listen_fd;
    memset(conn_list_[listen_fd].r_buffer_, '\0', BUFFER_LEN);
    conn_list_[listen_fd].r_len_ = 0;
    memset(conn_list_[listen_fd].w_buffer_, '\0', BUFFER_LEN);
    conn_list_[listen_fd].w_len_ = 0;
    conn_list_[listen_fd].recv_t_.accept_callback_ = accept_cb;

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(sockaddr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    int ret = bind(listen_fd, (const sockaddr*)&server_addr, sizeof(sockaddr));
    if (ret < 0) {
        return -1;
    }

    listen(listen_fd, 5);

    return listen_fd;
}

const int moony::echo_server::set_event(const int& fd, const int& op, const int& event) {
    epoll_event ev;
    memset(&ev, 0, sizeof(epoll_event));
    ev.data.fd = fd;
    ev.events = event;
        
    if (op == ADD) {
        int ret = epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev);    
        if (ret < 0) {
            return -1;
        }
    } else if (op == MOD) {
        int ret = epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &ev);    
        if (ret < 0) {
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

const int moony::accept_cb(echo_server& server, const int& fd) {
    sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(sockaddr));
    socklen_t len = sizeof(sockaddr);
    int conn_fd = accept(fd, (sockaddr*)&client_addr, &len);
    if (conn_fd < 0) {
        return -1;
    }

    server.conn_list_[conn_fd].fd_ = conn_fd;
    memset(server.conn_list_[conn_fd].r_buffer_, '\0', BUFFER_LEN);
    server.conn_list_[conn_fd].r_len_ = 0;
    memset(server.conn_list_[conn_fd].w_buffer_, '\0', BUFFER_LEN);
    server.conn_list_[conn_fd].w_len_ = 0;
    server.conn_list_[conn_fd].recv_t_.recv_callback_ = recv_cb;
    server.conn_list_[conn_fd].send_callback_ = send_cb;

    int ret = server.set_event(conn_fd, ADD, EPOLLIN);
    if (-1 == ret) {
        return -1;
    }

    return conn_fd;
}

const int moony::send_cb(echo_server& server, const int& fd) {
    char* buffer = server.conn_list_[fd].w_buffer_;
    int len = server.conn_list_[fd].w_len_;

    int cnt = send(fd, buffer, len, 0);
    if (cnt < 0) {
        return -1;
    }
    
    int ret = server.set_event(fd, MOD, EPOLLIN);
    if (ret < 0) {
        return -1;
    }

    return cnt;
}

const int moony::recv_cb(echo_server& server, const int& fd) {
    char* buffer = server.conn_list_[fd].r_buffer_;
    memset(buffer, 0, sizeof(buffer));
    server.conn_list_[fd].r_len_ = 0;
    int cnt = read(fd, buffer, BUFFER_LEN);
    if (cnt < 0) {
        if (errno != EAGAIN || errno != EWOULDBLOCK) {
            return -1;
        }
    } else if (cnt == 0) {
        int ret = epoll_ctl(server.epfd_, EPOLL_CTL_DEL, fd, nullptr);
        if (ret < 0) {
            return -1;
        }
        close(fd);
    }

    memset(server.conn_list_[fd].w_buffer_, '\0', BUFFER_LEN); // 这里就是reactor模型中工作线程的业务逻辑
                                                               // 不过显然这个demo里面没有用到线程
    memcpy(server.conn_list_[fd].w_buffer_, server.conn_list_[fd].r_buffer_, cnt);
    server.conn_list_[fd].r_len_ = cnt;
    server.conn_list_[fd].w_len_ = cnt;

    int ret = server.set_event(fd, MOD, EPOLLOUT);
    if (ret < 0) {
        return -1;
    }

    return cnt;
}

const int moony::echo_server::run(const unsigned short& port, const int& cnt) {
    for (int i = 0; i < cnt; i ++) {
        int listen_fd = init_server(port + i);
        if (-1 == listen_fd) {
            return -1;
        }
        int ret = set_event(listen_fd, ADD, EPOLLIN);
        if (ret < 0) {
            return -1;
        }
        std::cout << "port: " << port + i << std::endl;
    }

    epoll_event events[EVENTS_LEN];
    memset(&events, 0, EVENTS_LEN * sizeof(epoll_event));
    while (true) {
        int nready = epoll_wait(epfd_, events, EVENTS_LEN, -1);
        for (int i = 0; i < nready; i ++) {
            int conn_fd = events[i].data.fd;

            if (events[i].events & EPOLLIN) {
                int cnt = conn_list_[conn_fd].recv_t_.recv_callback_(*this, conn_fd);
                std::cout << "recv <-- " << conn_list_[conn_fd].r_buffer_ << std::endl;
            } else if (events[i].events & EPOLLOUT) {
                std::cout << "send --> " << conn_list_[conn_fd].w_buffer_ << std::endl;
                int cnt = conn_list_[conn_fd].send_callback_(*this, conn_fd);
            }
        }
    }
}