#ifndef SUN_MYSQL_CONNECTOR_CRESULTSET_H_
#define SUN_MYSQL_CONNECTOR_CRESULTSET_H_

#include <map>
#include "mysql.h"

#define BYTE unsigned char

using namespace std;

class CResultSet {
public:
  CResultSet() {}
  CResultSet(const CResultSet&) = delete;
  CResultSet& operator=(const CResultSet&) = delete;
  CResultSet(MYSQL_STMT *mysql_stmt);
  virtual  ~CResultSet();

  bool Next();
  int GetInt(const string& key);
  string GetString(const string& key);

private:
  MYSQL_STMT* mysql_stmt_;  //mysql_stmt
  MYSQL_RES* metadata_;
  int result_size_;  //field num
  MYSQL_BIND* result_binds_;  //result bind; delete
  BYTE** result_array_; //the list of result data, stored by char value; delete

  //list<string> field_name_list_;  //the list of field name; delete
  map<string, int> fields_map_;
  
  int _GetIndex(const string& key);
};

#endif  //SUN_MYSQL_CONNECTOR_CRESULTSET_H_    

