#pragma once

/*
 * server 和 client 共有的头文件
 */

enum msg_type {
  SIGN_IN_MSG = 1,  // 登录消息
  SIGN_UP_MSG       // 注册消息
};
