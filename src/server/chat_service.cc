#include "../../include/server/chat_service.hpp"

#include <muduo/base/Logging.h>

#include <functional>

#include "../../include/public.hpp"

// 单例模式
chat_service* chat_service::instance() {
  static chat_service service;
  return &service;
}

chat_service::chat_service() {
  msg_handler_map_.insert(
      {SIGN_IN_MSG,
       std::bind(&chat_service::sign_in, this, std::placeholders::_1,
                 std::placeholders::_2, std::placeholders::_3)});
  msg_handler_map_.insert(
      {SIGN_UP_MSG,
       std::bind(&chat_service::sign_up, this, std::placeholders::_1,
                 std::placeholders::_2, std::placeholders::_3)});
}

msg_handler chat_service::get_handler(int msg_id) {
  auto it = msg_handler_map_.find(msg_id);
  if (it == msg_handler_map_.end()) {
    return [=](const muduo::net::TcpConnectionPtr&, json&,
               muduo::Timestamp) -> void {
      LOG_ERROR << "message id: " << msg_id << " cannot find handler";
    };
  } else {
    return msg_handler_map_[msg_id];
  }
}

// 登录处理函数
void chat_service::sign_in(const muduo::net::TcpConnectionPtr& conn, json& js,
                           muduo::Timestamp time) {
  LOG_INFO << "sign in";
}
// 注册处理函数
void chat_service::sign_up(const muduo::net::TcpConnectionPtr& conn, json& js,
                           muduo::Timestamp time) {
  LOG_INFO << "sign up";
}
