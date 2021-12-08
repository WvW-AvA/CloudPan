#include "UserInfo.hpp"


bool UserManager::mySQLInit(MYSQL &mysql)
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


bool UserManager::checkPassward(const string name,const string passward,User & userOut)
{
    User* tem=readUserInfoFromSQL(name);
    if(passward==tem->user_passward_hash)
        {
            userOut=*tem;
            return true;
        }
    else
        return false;
}
bool UserManager::userSignUp(const User & user)
{
    return  insertUserDataIntoSQL(user);
}
User* UserManager::readUserInfoFromSQL(string name)
{
    User *result= new User();
    MYSQL_RES *res;
    MYSQL_ROW row;
    string tem("select * from UserInfo where name =\""+name+"\"");
    if(mysql_query(&mysql,tem.c_str()))
    {
        cout<<"Could not Read UserInfo from databases\n";
        delete(result);
        return nullptr;
    }
    if(!(res=mysql_use_result(&mysql)))
    {
        cout<<"User "+name+" could not find!\n";
        delete(result);
        return nullptr;
    }
    
    row=mysql_fetch_row(res);
    result->set_id(stoi(row[0]));
    result->user_email=row[1];
    result->user_name=row[2];
    result->user_passward_hash=row[3];
    return result;
}
bool UserManager::insertUserDataIntoSQL(const User & user)
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
