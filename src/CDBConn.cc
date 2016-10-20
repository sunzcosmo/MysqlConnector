#include "mysql.h"

#include "CDBConn.h"

CDBConn::CDBConn(): mysql_conn_(nullptr)
{
}

CDBConn::~CDBConn()
{
  if(mysql_conn_) mysql_close(mysql_conn_);
  mysql_conn_ = nullptr;
}

bool CDBConn::Init(
    const string& db_host, 
    const string& username, 
    const string& passwd,
    const string& db_name, 
    uint32_t db_port)
{
  db_host_ = db_host;
  username_ = username;
  passwd_ = passwd;
  db_name_ = db_name;
  db_port_ = db_port;
  mysql_conn_ = mysql_init(nullptr);
  //assert(mysql_conn_ != nullptr);
  //mybool reconnect = true;
  //mysql_options(mysql_conn_, MYSQL_OPT_RECONNECT, &reconnect);
	mysql_options(mysql_conn_, MYSQL_SET_CHARSET_NAME, "utf8mb4");
  return mysql_real_connect(
      mysql_conn_, 
      db_host_.c_str(), 
      username_.c_str(), 
      passwd_.c_str(), 
      db_name_.c_str(), 
      db_port_, 
      nullptr, 
      0);
}

MYSQL* CDBConn::GetConn()
{
  //assert(mysql_conn_ != nullptr);
  return mysql_conn_;
}

