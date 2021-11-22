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
     FILE * users_passward_record;
public:
    bool check_Passward(User &user);
    string user_Sign_Up(User & user);
    
    UserManager( string const user_record_file_path)
    {
        users_passward_record=fopen(user_record_file_path.c_str(),"rw");
        if(!users_passward_record)
        {

        }
    }

    ~UserManager()
    {
        fclose(users_passward_record);
    }

};



#endif