#include "CResultSet.h"

#ifndef MYSQLCLIENT_CSTMTSTATEMENT_H_
#define MYSQLCLIENT_CSTMTSTATEMENT_H_

class CPrepareStatement {
public:
  CPrepareStatement();
  virtual ~CPrepareStatemnt();

  CResultSet* ExecuteQuery();
  bool Init(MYSQL* mysql_conn, const string& sql);
  void ExecuteUpdate();
  CResultSet* ExecuteQuery();
  void setParam(const string& value, uint32_t index);
  void setParam(int value, uint32_t index);
  uint32_t GetInsertId();  
private:
  MYSQL_STMT* mysql_stmt_;
  MYSQL_BIND* param_binds_;
  uint32_t param_size_;

};

#endif //MYSQLCLIENT_CSTMTSTATEMENT_H_
