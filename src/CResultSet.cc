#include <iostream>
#include <map>
#include <memory>
#include <cstring>
#include <cstdlib>

#include "CResultSet.h"

CResultSet::CResultSet(MYSQL_STMT* mysql_stmt):mysql_stmt_(mysql_stmt)
{
  _Bind();
}

CResultSet::~CResultSet()
{
  if(result_array_)
  {
    for(int i=0; i<result_size_; ++i)
    {
      free(result_array_);
    }
    free(result_array_);
  }
  if(result_binds_)
  {
    free(result_binds_);
  }
}

bool CResultSet::Next()
{
  return (mysql_stmt_fetch(mysql_stmt_) == 0);
}

int CResultSet::GetInt(const string& name)
{
  int index = _GetIndex(name);
  if(index < 0) 
  {
    //log
    exit(0);
  }
  return *reinterpret_cast<int*>(result_array_[index]);
}

string CResultSet::GetString(const string& name)
{
  int index = _GetIndex(name);
  if(index < 0)
  {
    //log
    exit(0);
  }
  return string(reinterpret_cast<char *>(result_array_[index]));
}

int CResultSet::_GetIndex(const string& name)
{
  map<string, int>::iterator it = fields_map_.find(name);
  if(it == fields_map_.end()) return -1;
  else  return (int)it->second;
}

void CResultSet::_Bind()
{
  if(mysql_stmt_ == nullptr)
  {
    exit(0);
  }
  MYSQL_RES *metadata =
    mysql_stmt_result_metadata(mysql_stmt_);
  int result_size = mysql_num_fields(metadata);
  result_size_ = result_size;
  result_binds_ = 
    (MYSQL_BIND*)calloc(result_size, sizeof(MYSQL_BIND));
  result_array_ = 
    (BYTE**)calloc(result_size, sizeof(BYTE*));
  MYSQL_FIELD* fields = mysql_fetch_fields(metadata);
  for(int i=0; i<result_size; ++i)
  {
    result_binds_[i].buffer_type = fields[i].type;
    uint32_t buffer_length = fields[i].length;
    result_binds_[i].buffer_length = buffer_length;
    result_array_[i] = 
      (BYTE*)calloc(buffer_length, sizeof(BYTE));
    result_binds_[i].buffer = result_array_[i];
    fields_map_.insert(
        std::make_pair(string(fields[i].name), i));
  }
  mysql_stmt_bind_result(mysql_stmt_, result_binds_);
  mysql_free_result(metadata);
}
