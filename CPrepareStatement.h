
#ifndef MYSQLCLIENT_CSTMTSTATEMENT_H_
#define MYSQLCLIENT_CSTMTSTATEMENT_H_
#include <string>

#include "CResultSet.h"
#include "mysql.h"

class CPrepareStatement {
public:
  CPrepareStatement();
  CPrepareStatement(const CPrepareStatement &) = delete;
  virtual ~CPrepareStatement();

  bool Init(MYSQL* mysql_conn, const string& sql);
  bool ExecuteUpdate();
  CResultSet* ExecuteQuery();

  void SetParam(uint32_t& value, uint32_t index);
  void SetParam(const string& value, uint32_t index);
  void SetParam(int& value, uint32_t index);

  uint32_t GetInsertId();  
private:
  MYSQL_STMT* mysql_stmt_;
  MYSQL_BIND* param_binds_;
  uint32_t param_size_;

};

#endif //MYSQLCLIENT_CSTMTSTATEMENT_H_
