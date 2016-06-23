#include <cstring>
#include "CPrepareStatement.h"

CPrepareStatement:: CPrepareStatement()
{
  mysql_stmt_ = nullptr;
  param_binds_ = nullptr;
  param_size_ = 0;
}

CPrepareStatement::~CPrepareStatement()
{
  if(mysql_stmt_)
  {
    mysql_stmt_close(mysql_stmt_);
    mysql_stmt_ = nullptr;
  }
  if(param_binds_)
  { 
    delete [] param_binds_;
    param_binds_ = nullptr;
  }
}

bool CPrepareStatement::Init(MYSQL* mysql_conn, const string& sql)
{
  mysql_ping(mysql_conn);
  mysql_stmt_ = mysql_stmt_init(mysql_conn);
  if(!mysql_stmt_) 
  {
    //log
    return false;
  }
  if(mysql_stmt_prepare(mysql_stmt_, sql.c_str(), sql.size()))
  {
    //log
    return false;
  }
  param_size_ = mysql_stmt_param_count(mysql_stmt_);
  if(param_size_ > 0)
  {
    param_binds_ = new MYSQL_BIND[param_size_];
    if(!param_binds_)
    {
      //log
      return false;
    }
    memset(param_binds_, 0, sizeof(MYSQL_BIND)*param_size_);
  }
  return true;
}

CResultSet* CPrepareStatement::ExecuteQuery()
{
  CResultSet* reset = new CResultSet(mysql_stmt_);
  if(mysql_stmt_execute(mysql_stmt_))
  {
    //log
    exit(0);
  }
  return reset;
}

bool CPrepareStatement::ExecuteUpdate()
{
  if( !mysql_stmt_ ||
      mysql_stmt_bind_param(mysql_stmt_, param_binds_) ||
      mysql_stmt_execute(mysql_stmt_) ||
      mysql_stmt_affected_rows(mysql_stmt_) == 0 )
  {
    //log(mysql_stmt_error(mysql_stmt));
    return false;
  }
	return true;
}

void CPrepareStatement::SetParam(const string& value, uint32_t index)
{
  if(index > param_size_) 
  {
    //log
    return;
  }
  param_binds_[index].buffer_type = MYSQL_TYPE_STRING;
  param_binds_[index].buffer = (char*)value.c_str();
  param_binds_[index].buffer_length = value.size();
}

void CPrepareStatement::SetParam(int value, uint32_t index)
{
  if(index > param_size_)
  {
    //log
    return;
  }
  param_binds_[index].buffer_type = MYSQL_TYPE_LONG;
  param_binds_[index].buffer = &value;
}

uint32_t CPrepareStatement::GetInsertId()
{
  return mysql_stmt_insert_id(mysql_stmt_);
}
