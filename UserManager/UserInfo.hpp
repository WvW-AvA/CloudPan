#ifndef __USERINFO_HPP
#define __USERINFO_HPP
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <mysql/mysql.h>
using namespace std;
class  User
{
private:
    int id;
public:

    
    string user_name;
    string user_email;
    string user_passward_hash;

    User(const string & user_name,const string & user_email ,const string &user_passward_hash )
    {
        this->user_name=user_name;
        this->user_email=user_email;
        this->user_passward_hash=user_passward_hash;
    }

    User()
    {
        this->id=0;
        this->user_email="";
        this->user_name="";
        this->user_passward_hash="";
    }
    int get_id(){return this->id;}
    void set_id(int id){this->id=id;}
    friend ostream & operator<<(ostream &os ,User * User)
    {
        return os<<User->id<<" "<<User->user_email<<" "<<User->user_name<<" "<<User->user_passward_hash<<"\n"; 
    }
    ~ User()
    {
    }    
};


class UserManager
{
private:
     map<User,FILE*> user_FILE_map;
     MYSQL mysql;
     bool mySQLInit(MYSQL &mysql);
public:
    bool checkPassward(const string name,const string passward,User &userOut);
    bool userSignUp(const User & user);
    bool insertUserDataIntoSQL(const User & user);
    User* readUserInfoFromSQL(string name);

    UserManager()
    {
       if(!mySQLInit(mysql))
       {
           delete(this);
       }
    }

    ~UserManager()
    {
       mysql_close(&mysql);
    }

};



#endif