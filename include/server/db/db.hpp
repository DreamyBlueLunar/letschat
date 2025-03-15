#pragma once

#include <mysql/mysql.h>
#include <string>
#include <muduo/base/Logging.h>

class MySQL {
public:
    /* 初始化与数据库连接的资源 */
    MySQL();

    /* 销毁与数据库连接的资源 */
    ~MySQL();

    /* 连接数据库 */
    bool connect();

    /* 更新数据库 */
    bool update(std::string sql);
    
    /* 查询数据库 */
    MYSQL_RES* query(std::string sql);

private:
    MYSQL* conn_;
};