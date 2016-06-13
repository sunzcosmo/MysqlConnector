#ifndef MYSQL_CLIENT_CRESULTSET_H_
#define MYSQL_CLIENT_CRESULTSET_H_    

#include <map>

#include "mysql.h"

using namespace std;

class CResultSet {
public:
  CResultSet(MYSQL_STMT *mysql_stmt);
  virtual  ~CResultSet();

  bool Next();
  int GetInt(const string& key);
  string GetString(const string& key);

private:
  MYSQL_STMT* mysql_stmt_;  //mysql_stmt
  int result_size_;  //field num

  //list<string> field_name_list_;  //the list of field name; delete
  map<string, uint32_t> fields_map_;
  unsigned char** result_array_; //the list of result data, stored by char value; delete
  MYSQL_BIND* mysql_binds_;  //result bind; delete
  
  int _GetIndex(const string& key);
};

#endif  //MYSQL_CLIENT_CRESULTSET_H_
