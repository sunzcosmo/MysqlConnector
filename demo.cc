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
  string username = "###";
  string passwd = "###";
  string db_name = "###";
  CDBConn* db_conn = new CDBConn();
  db_conn->Init(db_host, username, passwd, db_name, db_port);
  CPrepareStatement* pstmt = new CPrepareStatement();
  string str_sql = "select * from IMUser where nick like ?";
  pstmt->Init(db_conn->GetConn(), str_sql);
  uint32_t index = 0;
  string value = "%P%";
  pstmt->SetParam(value, index);
  CResultSet* reset = pstmt->ExecuteQuery();
  while(reset->Next())
  {
    cout<<reset->GetString("nick")<<endl;
  }
  delete reset;
  delete pstmt;
  delete db_conn;
  return 0;
}
