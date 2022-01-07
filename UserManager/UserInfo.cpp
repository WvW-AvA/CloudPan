#include "UserInfo.hpp"
#include "../CloudPan.hpp"
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


bool UserManager::checkPassward(const SignInData  data)
{
    SignInData tem=readUserInfoFromSQL(data.userName);
    if(data.password==tem.password)
        {
            return true;
        }
    else
        return false;
}

bool UserManager::userSignUp(const  SignInData user)
{
    bool res= insertUserDataIntoSQL(user);
    if(res)
    {
        mkdir(("/home/mua/Backend/CloudPan/UserFile/"+user.userName+"+"+user.email).c_str(),S_IRWXU);
        mkdir(("/home/mua/Backend/CloudPan/UserFile/"+user.userName+"+"+user.email+"/Data").c_str(),S_IRWXU);
        auto tem= fopen(("/home/mua/Backend/CloudPan/UserFile/"+user.userName+"+"+user.email+"/filelog.txt").c_str(),"w");
        fclose(tem);
        tem= fopen(("/home/mua/Backend/CloudPan/UserFile/"+user.userName+"+"+user.email+"/fileLayer.txt").c_str(),"w");
        fclose(tem);
    }
    return res;
}

SignInData UserManager::readUserInfoFromSQL(string name)
{
    SignInData result;
    MYSQL_RES *res;
    MYSQL_ROW row;
    string tem("select * from UserInfo where name =\""+name+"\"");
    cout<<tem<<'\n';
    if(mysql_query(&mysql,tem.c_str()))
    {
        cout<<"Could not Read UserInfo from databases\n";
        return result ;
    }
    if(!(res=mysql_use_result(&mysql)))
    {
        cout<<"User "+name+" could not find!\n";
        return result;
    }
    
    row=mysql_fetch_row(res);
    result.email=row[2];
    result.userName=row[1];
    result.password=row[3];
    mysql_free_result(res);
    return result;
}

bool UserManager::insertUserDataIntoSQL(const SignInData  user)
{
    string tem("insert into UserInfo (name,email,passward)value(\""+
                        user.userName+'\"'+
                    ",\""+user.email+'\"'+
                    ",\""+user.password+"\")");
    
    if(mysql_query(&mysql,tem.c_str()))
    {
        cout<<"Fault to insert User!\n";
        return 0;
    }
    return 1;
}
