#pragma once

#include <muduo/net/TcpConnection.h>

#include <functional>
#include <unordered_map>

#include "../thrid_party/json.hpp"

using json = nlohmann::json;

// 消息处理器
using msg_handler = std::function<void(const muduo::net::TcpConnectionPtr&,
                                       json&, muduo::Timestamp)>;

class chat_service {
 public:
  // 单例模式
  static chat_service* instance();
  // 登录处理函数
  void sign_in(const muduo::net::TcpConnectionPtr& conn, json& js,
               muduo::Timestamp time);
  // 注册处理函数
  void sign_up(const muduo::net::TcpConnectionPtr& conn, json& js,
               muduo::Timestamp time);

  msg_handler get_handler(int msg_id);

 private:
  chat_service();
  ~chat_service();

  chat_service(const chat_service& other) = delete;
  chat_service(chat_service&& other) = delete;
  chat_service& operator=(const chat_service& other) = delete;
  chat_service& operator=(chat_service&& other) = delete;

  // 一个消息类型和消息处理器的映射表
  std::unordered_map<int, msg_handler> msg_handler_map_;
};