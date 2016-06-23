#include <iostream>
#include <string>
#include "mysql.h"

#include "CDBConn.h"
#include "CPrepareStatement.h"
#include "CResultSet.h"

using namespace std;

int main()
{
  string db_host = "127.0.0.1";
  uint32_t db_port = 3306;
  string username = "root";
  string passwd = "passw0rd";
  string db_name = "test";
  CDBConn* db_conn = new CDBConn();
  db_conn->Init(db_host, username, passwd, db_name, db_port);
  CPrepareStatement* pstmt = new CPrepareStatement();
  string str_sql = "select * from products;";
  pstmt->Init(db_conn->GetConn(), str_sql);
  CResultSet* reset = pstmt->ExecuteQuery();
  while(reset->Next())
  {
    cout<<reset->GetString("version_id")<<endl;
  }
  delete reset;
  delete pstmt;
  delete db_conn;
  return 0;
}
