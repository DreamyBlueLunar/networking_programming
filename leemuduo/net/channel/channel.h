#pragma once

#include "../../base/noncopyable.h"
#include "../../base/time_stamp/time_stamp.h"

#include <functional>
#include <memory>

namespace lee {
class event_loop;

/**
 * channel 理解成通道，其中封装了 sockfd 和其感兴趣的事件，如EPOLLIN、EPOLLOUT
 * 还封装了一个 poller 用于监听 fd 上发生的事件
 */
class channel : lee::noncopyable {
public:
    using event_callback = std::function<void()>;
    using read_event_callback = std::function<void(time_stamp)>;

    channel(event_loop* loop, int fd);
    ~channel();

    void handle_event(time_stamp receive_time);

private:
    static const int k_none_event_;
    static const int k_read_event_;
    static const int k_write_event_;

    event_loop *loop_;
    const int fd_; // poller 监听的对象
    int events_;   // 注册fd感兴趣的事件
    int revents_;  // 返回具体发生的事件
    int idx_;

    std::weak_ptr<void> tie_; // 防止手动调用remove之后还在使用这个channel，多线程显然需要考虑这一点
    bool tied_;

    // 因为channel通道里可以获知revents，所以它调用事件的回调函数
    read_event_callback read_callback_;
    event_callback write_callback_;
    event_callback close_callback_;
    event_callback error_callback_;
};
}