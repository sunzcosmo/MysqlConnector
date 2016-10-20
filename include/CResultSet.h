#ifndef SUN_MYSQL_CONNECTOR_CRESULTSET_H_
#define SUN_MYSQL_CONNECTOR_CRESULTSET_H_

#include <map>
#include <memory>
#include "Utils.h"
#include "mysql.h"

using namespace std;

class CResultSet {
public:
  CResultSet(const CResultSet&) = delete;
  CResultSet& operator=(const CResultSet&) = delete;
  explicit CResultSet(MYSQL_STMT *mysql_stmt);
  virtual  ~CResultSet();

  bool Next();
  int GetInt(const string& key);
  string GetString(const string& key);
private:
  uint32_t result_size_;
  MYSQL_STMT * mysql_stmt_;
  MYSQL_BIND* result_binds_;  //result bind; delete
  BYTE** result_array_; //the list of result data, stored by char value; delete
  map<string, int> fields_map_;
  int _GetIndex(const string& key);
  void _Bind();
 
};

#endif  //SUN_MYSQL_CONNECTOR_CRESULTSET_H_    

