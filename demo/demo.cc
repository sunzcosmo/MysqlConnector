#include <iostream>

#include "CDBConn.h"
#include "CPrepareStatement.h"
#include "CResultSet.h"

#include "pri.h"  //local password

using std::string;

int main()
{
  CDBConn mysql_conn;
  if(!mysql_conn.Init("127.0.0.1", "root", pwd, "test", 3306) )
  {
    std::cout<<"can not make access to db"<<std::endl;
  }
  string strsql("SELECT * FROM TEST_TABLE");
  CPrepareStatement pstmt;
  pstmt.Init(mysql_conn.GetConn(), strsql);
  CResultSet *ret = pstmt.ExecuteQuery();
  if(ret)
  {
    while(ret->Next())
    {
      std::cout<<ret->GetString("name");
    }
    delete ret;
  }
  return 0;
}
