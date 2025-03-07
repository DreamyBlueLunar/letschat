#include "db.h"

static std::string host = "127.0.0.1";
static short port = 3306;
static std::string user = "root";
static std::string passwd = "123456";
static std::string db_name = "chat";

/* 初始化与数据库连接的资源 */
MySQL::MySQL() {
    conn_ = mysql_init(nullptr);
}

/* 销毁与数据库连接的资源 */
MySQL::~MySQL() {
    if (nullptr != conn_) {
        mysql_close(conn_);
    }
}

/* 连接数据库 */
bool MySQL::connect() {
    MYSQL* p = mysql_real_connect(conn_, host.c_str(), user.c_str(), passwd.c_str(), db_name.c_str(), port, nullptr, 0);
    if (nullptr != p) {
        /* C/C++字符默认是ASCII码，数据库中的中文读取到代码中会出现编码错误 */
        mysql_query(conn_, "set names gbk");
    }
    return p;
}

/* 更新数据库 */
bool MySQL::update(std::string sql) {
    if (mysql_query(conn_, sql.c_str())) {
        LOG_INFO << __FILE__ << ": " << __LINE__ << ": " << sql << " 更新失败";
        return false;
    }

    return true;
}

/* 查询数据库 */
MYSQL_RES* MySQL::query(std::string sql) {
    if (mysql_query(conn_, sql.c_str())) {
        LOG_INFO << __FILE__ << ": " << __LINE__ << ": " << sql << " 查询失败";
        return nullptr;
    }

    return mysql_use_result(conn_);
}
