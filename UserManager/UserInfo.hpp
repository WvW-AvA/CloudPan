#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <mysql/mysql.h>

#include "../httplib.h"
#include "../FileManager/UserFile.hpp"
using namespace std;

struct SignInData;

class  User
{
private:
    int id;
public:
    string user_name;
    string user_email;
    string user_passward_hash;
    FileManager * fileManager;
    

    User(const string & user_name,const string & user_email ,const string &user_passward_hash )
    {
        this->user_name=user_name;
        this->user_email=user_email;
        this->user_passward_hash=user_passward_hash;
        fileManager=new FileManager(this);
        cout<<"User object init OK!\n";
    }

    // User(const User & v)
    // {
    //     this->user_name=v.user_name;
    //     this->user_email=v.user_email;
    //     this->user_passward_hash=v.user_passward_hash;
    //     this->fileManager=new FileManager(*v.fileManager);
    //     cout<<"User object copy OK!\n";
    // }
    // User& operator=(const User& v)
    // {
    //     if(this!=&v)
    //     {
    //     this->user_name=v.user_name;
    //     this->user_email=v.user_email;
    //     this->user_passward_hash=v.user_passward_hash;
    //     this->fileManager=new FileManager(*v.fileManager);
    //     cout<<this<<"  User object assign OK!\n";
    //     }
    //     return *this;
    // }

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
        return os<<User->id<<" Name:"<<User->user_name<<" Email:"<<User->user_email<<" Passward:"<<User->user_passward_hash<<"\n"; 
    }
    ~ User()
    {
        cout<<"User object release OK!\n";
        //delete(fileManager);
    }    
};


class UserManager
{
private:
     MYSQL mysql;
     bool mySQLInit(MYSQL &mysql);
     
public:
    map<string,User> users;
    //DataBase Part
    bool checkPassward(const SignInData  data);
    bool userSignUp(const SignInData  user);
    bool insertUserDataIntoSQL(const SignInData  user);
    SignInData readUserInfoFromSQL(string name);
    UserManager()
    {
       if(!mySQLInit(mysql))
       {
          delete(this);
       }
       cout<<"UserManager Init Succeed\n";
    }

    ~UserManager()
    {
       mysql_close(&mysql);
    }

};

