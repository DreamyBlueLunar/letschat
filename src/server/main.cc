#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include "chat_server.hpp"

int main(void) {
  muduo::net::EventLoop loop;
  muduo::net::InetAddress addr("0.0.0.0", 8000);

  chat_server server(&loop, addr, "chat_server");
  server.start();
  loop.loop();

  return 0;
}