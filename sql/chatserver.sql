DROP DATABASE IF EXISTS chat;
CREATE DATABASE chat;
USE chat;
DROP TABLE IF EXISTS User;
CREATE TABLE User (                                     -- 用户表
    id INT PRIMARY KEY AUTO_INCREMENT,                  -- 用户id（主键）
    name VARCHAR(50) NOT NULL UNIQUE,                   -- 用户名
    password VARCHAR(50) NOT NULL,                      -- 用户密码
    state ENUM('online', 'offline') DEFAULT 'online'    -- 用户状态，在线/离线
);

DROP TABLE IF EXISTS Friend;
CREATE TABLE Friend (               -- 记录好友关系
    userid INT NOT NULL,            -- 用户id
    friendid INT NOT NULL,          -- 好友id
    PRIMARY KEY(userid, friendid)   -- 显然每一条记录都由<userid, 
                                    -- friendid>唯一标识，所以设置一个联合主键
);

DROP TABLE IF EXISTS AllGroup;
CREATE TABLE AllGroup (                 -- 记录所有的群
    id INT PRIMARY KEY AUTO_INCREMENT,  -- 群id（主键）
    groupname VARCHAR(50) NOT NULL,     -- 群名
    groupdesc VARCHAR(200) DEFAULT ''   -- 群描述
);

DROP TABLE IF EXISTS GroupUser;
CREATE TABLE GroupUser (                                    -- 记录群成员
    groupid INT PRIMARY KEY,                                -- 群id（主键）
    userid INT NOT NULL,                                    -- 成员id
    grouprole ENUM('creator', 'normal') DEFAULT 'normal'    -- 成员角色（默认普通）
);

DROP TABLE IF EXISTS OfflineMessage;
CREATE TABLE OfflineMessage (       -- 记录离线消息
    userid INT PRIMARY KEY,         -- 用户id（主键）
    message VARCHAR(500) NOT NULL   -- 用户的离线消息
);
