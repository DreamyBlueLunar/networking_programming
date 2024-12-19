#include "epoll_poller.h"
#include "../../base/logger/logger.h"

#include <errno.h>
#include <unistd.h>

namespace {
    const int k_new = 1;
    const int k_add = 2;
    const int k_del = -1;
}

lee::epoll_poller::epoll_poller(event_loop* loop): 
         poller(loop),
         epoll_fd_(::epoll_create(1)),
         events_(k_init_event_list_size) {
    if (epoll_fd_ < 0) {
        LOG_FATAL << "epoll_create error: " << errno << ENDL;
    }
}

lee::epoll_poller::~epoll_poller() {
    ::close(epoll_fd_);
}