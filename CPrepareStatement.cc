#include "CPrepareStatement.h"
#include "CResultset.h"
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
    param_binds = nullptr;
  }
}

bool CPrepareStatement::Init(MYSQL* mysql_conn, const string& sql)
{
  mysql_ping(mysql);
  mysql_stmt_ = mysql_stmt_init(mysql_conn);
  if(!mysql_stmt) 
  {
    //log
    return false;
  }
  if(mysqLstmt_prepare(mysql_stmt, sql.c_str(), sql.size()))
  {
    //log
    return false;
  }
  param_size_ = mysql_stmt_param_count(mysql_stmt);
  if(param_size_ > 0)
  {
    param_binds = new MYSQL_BIND[param_size_];
    if(!param_binds)
    {
      //log
      return false;
    }
    memset(param_binds, 0, sizeof(MYSQL_BIND)*param_size_);
  }
  return true;
}

CResultSet* CPrepareStatement::ExecuteQuery()
{
  if(mysql_stmt_execute(mysql_stmt)
  {
    //log
    exit(0);
  }
  return new CResultSet(mysql_stmt);
}

void CPrepareStatement::ExexuteUpdate()
{
 if( !mysql_stmt ||
      mysql_stmt_bind_param(mysql_stmt, mysql_param_binds) ||
      mysql_stmt_execute(mysql_stmt_) ||
      mysql_stmt_affected_rows(mysql_stmt) == 0 )
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
  param_binds[index].buffer_type = MYSQL_TYPE_STRING;
  param_binds[index].buffer = (char*)value.c_str();
  param_binds[index].buffer_length = value.size();
}

void CPrepareStatement::SetParam(int value, uint32_t index)
{
  if(index > param_size_)
  {
    //log
    return;
  }
  param_binds[index].buffer_type = MYSQL_TYPE_LONG;
  param_binds[index].buffer = &value;
}

uint32_t CPrepareStatement::GetInsertId()
{
  return mysql_stmt_insert_id(mysql_stmt);
}
