#include "CloudPan.hpp"



bool mySQLInit(MYSQL &mysql)
{
    if(mysql_library_init(0,NULL,NULL))
    {
        cout<<"could not initialize MySQL Library\n";
        return 0;
    }
    mysql_init(&mysql);

    if(mysql_real_connect(&mysql,"127.0.0.1","root","20020508","test",3306,NULL,0)==NULL)
    {
        cout<<"Could not connect MySQL\n";
        return 0;
    }
    if(mysql_query(&mysql,"use CloudPan"))
    {
        cout<<"Could not find database CloudPan!\n";
        return 0;
    }
    return 1;
}
User* readUserInfoFromSQL(MYSQL &mysql,string name)
{
    User *result= new User();
    MYSQL_RES *res;
    MYSQL_ROW row;
    string tem("select * from UserInfo where name =\""+name+"\"");
    if(mysql_query(&mysql,tem.c_str()))
    {
        cout<<"Could not Read UserInfo from databases\n";
        return result;
    }
    if(!(res=mysql_use_result(&mysql)))
    {
        cout<<"User "+name+" could not find!\n";
        return result;
    }
    
    row=mysql_fetch_row(res);
    result->set_id(stoi(row[0]));
    result->user_email=row[1];
    result->user_name=row[2];
    result->user_passward_hash=row[3];
    return result;
}
bool insertUserDataIntoSQL(MYSQL&mysql,const User & user)
{
    string tem("insert into UserInfo (name,email,passward)value(\""+
                        user.user_name+'\"'+
                    ",\""+user.user_email+'\"'+
                    ",\""+user.user_passward_hash+"\")");
    
    if(mysql_query(&mysql,tem.c_str()))
    {
        cout<<"Fault to insert User!\n";
        return 0;
    }
    return 1;
}



int main(int argc,char * argv[])
{
    MYSQL mysql;
    User test("sss","wdasd","sdfasdasd");
    if(!mySQLInit(mysql))
        return 1;
    if(insertUserDataIntoSQL(mysql,test))
    {
        User *tem= readUserInfoFromSQL(mysql,"sss");
        cout<<tem;
    }
    mysql_close(&mysql);
    return 0;
}