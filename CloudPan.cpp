#include "CloudPan.hpp"
#include "iostream"
#include <mysql/mysql.h>
using namespace std;

int main(int argc,char * argv[])
{
    MYSQL mysql;

    if(mysql_library_init(0,NULL,NULL))
    {
        cout<<"could not initialize MySQL Library\n";
        return 1;
    }
    mysql_init(&mysql);

    if(mysql_real_connect(&mysql,"127.0.0.1","root","20020508","test",3306,NULL,0)==NULL)
    {
        cout<<"Could not connect MySQL\n";
        return 2;
    }
    
    if(mysql_query(&mysql,"show databases"))
    {
        cout<<"error";
        return 3;
    }
    cout<<"succed\n";
    MYSQL_RES *res;
    MYSQL_ROW row;
    res=mysql_use_result(&mysql);

    while(row=mysql_fetch_row(res))
    {
        cout<<row[0]<<'\n';
    }

    mysql_free_result(res);
    mysql_close(&mysql);
    return 0;
}
