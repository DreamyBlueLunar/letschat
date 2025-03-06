#include "../../include/server/chat_server.hpp"

#include <muduo/base/Logging.h>

#include <functional>

#include "../../include/server/chat_service.hpp"

chat_server::chat_server(muduo::net::EventLoop *loop,
                         const muduo::net::InetAddress &addr,
                         const std::string &name)
    : loop_(loop), server_(loop, addr, name) {
  server_.setConnectionCallback(
      std::bind(&chat_server::on_connection, this, std::placeholders::_1));
  server_.setMessageCallback(
      std::bind(&chat_server::on_message, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));
  server_.setThreadNum(4);
}

void chat_server::start() { server_.start(); }

void chat_server::on_connection(const muduo::net::TcpConnectionPtr &conn) {
  if (!conn->connected()) {
    // 如果客户端断开连接，服务器也断开连接
    conn->shutdown();
  }
}

void chat_server::on_message(const muduo::net::TcpConnectionPtr &conn,
                             muduo::net::Buffer *buf, muduo::Timestamp time) {
  // 从buf中拿出所有的字符串
  std::string buffer = buf->retrieveAllAsString();
  // json反序列化：std::string -> json
  json js = json::parse(buffer);

  // 根据js["msgid"]获取对应的事件处理器并执行
  msg_handler message_handler =
      chat_service::instance()->get_handler(js["msgid"].get<int>());
  message_handler(conn, js, time);
}