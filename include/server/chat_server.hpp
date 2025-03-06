#pragma once

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

class chat_server {
 public:
  chat_server(muduo::net::EventLoop *loop, const muduo::net::InetAddress &addr,
              const std::string &name);
  void start();

 private:
  void on_connection(const muduo::net::TcpConnectionPtr &conn);

  void on_message(const muduo::net::TcpConnectionPtr &conn,
                  muduo::net::Buffer *buf, muduo::Timestamp time);

  muduo::net::TcpServer server_;
  muduo::net::EventLoop *loop_;
};