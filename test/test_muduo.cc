#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

#include <boost/bind/bind.hpp>
#include <string>

using namespace muduo;
using namespace muduo::net;
using namespace boost;

class echo_server {
 public:
  echo_server(EventLoop* loop, const InetAddress& addr, const std::string& name)
      : server_(loop, addr, name), loop_(loop) {
    // set callbacks
    server_.setConnectionCallback(
        bind(&echo_server::on_connection, this, boost::placeholders::_1));
    server_.setMessageCallback(
        bind(&echo_server::on_message, this, boost::placeholders::_1,
             boost::placeholders::_2, boost::placeholders::_3));
    // set thread nums
    server_.setThreadNum(4);
  }

  void start() { server_.start(); }

  ~echo_server() {}

 private:
  void on_connection(const TcpConnectionPtr& conn) {
    if (conn->connected()) {
      LOG_INFO << "Connection UP: " << conn->peerAddress().toIpPort().c_str();
    } else {
      LOG_INFO << "Connection DOWN: " << conn->peerAddress().toIpPort().c_str();
    }
  }

  void on_message(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time) {
    std::string msg = buf->retrieveAllAsString();
    conn->send(msg);
    // conn->shutdown(); // 关闭写端 EPOLLHUP close_call_back_
    // 服务器主动关闭连接
  }

  EventLoop* loop_;
  TcpServer server_;
};

int main(void) {
  EventLoop loop;
  InetAddress addr(8000, "0.0.0.0");

  echo_server server(&loop, addr, "echo_server_01");

  server.start();
  loop.loop();

  return 0;
}