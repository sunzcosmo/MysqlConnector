#include "CResultSet.h"

CResultSet::CResultSet(MYSQL_STMT *stmt) 
{
  if(stmt == nullptr)
  {
    //log
    exit(0);
  }
  mysql_stmt_ = stmt;
  MYSQL_RESULT* metadata = mysql_stmt_result_metadata(mysql_stmt_);
  result_size_ = mysql_num_fields(metadata);
  result_binds_ = new (MYSQL_BIND)[result_size_];
  result_array_ = new (unsigned char*)[result_size_];
  MYSQL_FIELD* fields = mysql_fetch_fields(metadata);
  for(uint32_t i=0; i<result_size_; ++i)
  {
    result_binds_[i].buffer_type = fields[i].type;
    uint32_t buffer_size = fields[i].size;
    result_binds_[i[.buffer_length = buffer_size;
    result_array_[i] = new (unsigned char)[buffer_size];
    result_binds_[i].buffer = result_array_[i];
    fields_map_.push_back(make_pair<string, uint32_t>(string(fields[i].name), i));
  }
  mysql_stmt_bind_result(mysql_stmt_, result_binds_);
}

CResultSet::~CResultSet()
{
  if(result_array_)
  {
    for(int i=0; i<result_size_; ++i)
    {
      delete [] result_size_[i];
    }
    delete [] result_size;
  }
  if(mysql_binds_)
  {
    delete [] mysql_binds_;
  }
  fields_map_.clear();

}

bool CResultSet::Next()
{
  return mysql_stmt_fetch(mysql_stmt_) == 0;
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

string CResultset::GetString(const string& name)
{
  int index = _GetIndex(name);
  if(index < 0)
  {
    //log
    exit(0);
  }
  return string(result_array_[index]);
}

int CResultSet::_GetIndex(string name)
{
  map<string, uint32_t>::iterator = fields_map_.find(name);
  if(iterator == fields_map_.end()) return -1;
  else  return (int)iterator->second;
}

