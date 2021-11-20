#include "CloudPan.hpp"
#include "iostream"
#include <mysql/mysql.h>
using namespace std;

int main(int argc,char * argv[])
{
    MYSQL mysql;
    MYSQL *connect;
    if(mysql_library_init(0,NULL,NULL))
    {
        cout<<"could not initialize MySQL Library\n";
        return 1;
    }
    mysql_init(&mysql);
    //connect=mysql_real_connect()

    std::cout<<"aaaa";
}
