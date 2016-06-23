
#include "CResultSet.h"
#include <map>
#include <string.h>

CResultSet::CResultSet(MYSQL_STMT *stmt): mysql_stmt_(stmt)
{
  if(stmt == nullptr)
  {
    //log
    exit(0);
  }
  //mysql_stmt_ = stmt;
  MYSQL_RES* metadata = mysql_stmt_result_metadata(mysql_stmt_);
  result_size_ = mysql_num_fields(metadata);
  //result_binds_ = new MYSQL_BIND[result_size_];
  //memset(result_binds_, 0, result_size_);
  result_binds_ = (MYSQL_BIND*)calloc(result_size_, sizeof(MYSQL_BIND));
  //result_array_ = new unsigned char*[result_size_];
  //memset(result_array_, 0, result_size_);
  result_array_ = (unsigned char**)calloc(result_size_, sizeof(unsigned char*));
  MYSQL_FIELD* fields = mysql_fetch_fields(metadata);
  for(int i=0; i<result_size_; ++i)
  {
    result_binds_[i].buffer_type = fields[i].type;
    uint32_t buffer_size = fields[i].length;
    result_binds_[i].buffer_length = buffer_size;
    //result_array_[i] = new unsigned char[buffer_size];
    //memset(result_array_, 0, buffer_size);
    result_array_[i] = (unsigned char*)calloc(buffer_size, sizeof(unsigned char));
    result_binds_[i].buffer = result_array_[i];
    fields_map_.insert(std::make_pair(string(fields[i].name), i));
  }
  mysql_stmt_bind_result(mysql_stmt_, result_binds_);
}

CResultSet::~CResultSet()
{
  if(result_array_)
  {
    for(int i=0; i<result_size_; ++i)
    {
      delete [] result_array_[i];
    }
    delete [] result_array_;
  }
  if(result_binds_)
  {
    delete [] result_binds_;
  }
  fields_map_.clear();

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

