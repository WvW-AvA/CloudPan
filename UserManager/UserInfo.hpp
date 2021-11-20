#ifndef __USERINFO_HPP
#define __USERINFO_HPP
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
class  User
{
private:
    
public:

    string user_name;
    string user_email;
    string user_passward_hash;
    

     User(string & user_name,string & user_email,string &user_passward_hash );
    ~ User();
};

User::User(string & user_name,string & user_email,string &user_passward_hash )
{
    this->user_name=user_name;
    this->user_email=user_email;
    this->user_passward_hash=user_passward_hash;
}

User::~ User()
{
}

class UserManager
{
private:
     map<User,FILE*> user_FILE_map;
     FILE * users_passward_record;
public:
    bool check_Passward(User &user);
    string user_Sign_Up(User & user);
    
    UserManager(string const user_record_file_path);
    ~UserManager();
};

UserManager::UserManager( string const user_record_file_path)
{
    users_passward_record=fopen(user_record_file_path.c_str(),"rw");
    if(!users_passward_record)
    {

    }
}

UserManager::~UserManager()
{
    fclose(users_passward_record);
}

#endif