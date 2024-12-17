#include "echo_server.h"

int main(void) {
  LOG_INFO << "pid = " << getpid();
  muduo::net::EventLoop loop;
  muduo::net::InetAddress listenAddr(8888);
  echo_server server(&loop, listenAddr);
  server.start();
  loop.loop();
}
