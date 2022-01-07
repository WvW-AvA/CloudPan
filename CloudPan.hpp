#pragma once 

#include <iostream>
#include <mysql/mysql.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "httplib.h"
#include "UserManager/UserInfo.hpp"
#include "FileManager/UserFile.hpp"
#define CPPHTTPLIB_OPENSSL_SUPPORT
using namespace std;

struct SignInData
{
    string userName;
    string password;
    string email;
    SignInData(const httplib::Request& req)
    {
        userName = req.get_header_value("UserName");
        password=req.get_header_value("Passward");
        email=req.get_header_value("Email");
        cout<<"SignInData OK\n";
    }
    SignInData()
    {
        
    }
};

struct EventData
{
    string event;
    string dirName;
    string fileName;
    EventData(const httplib::Request& req)
    {
        event = req.get_header_value("Event");
        dirName=req.get_header_value("dirName");
        fileName=req.get_header_value("fileName");
        cout<<"EventData OK\n";
    }
};


class CloudPan
{
private:
    UserManager userManager;
    httplib::Server server;
public:
    void testView(const httplib::Request &req, httplib::Response &rsp);
    void loginView(const httplib::Request &req, httplib::Response &rsp);
    void getLoginView(const httplib::Request &req, httplib::Response &rsp);
    void signUpView(const httplib::Request& req,httplib::Response& rsp);
    void cloudPanView(User& user,const httplib::Request& req,httplib::Response& rsp);
    void acceptUserRequest(User& user);
    CloudPan()
    {
        
        server.Get("/",[&](const httplib::Request& req,httplib::Response& rsp){
            getLoginView(req,rsp);
        });
        server.Post("/",[&](const httplib::Request& req,httplib::Response& rsp){
            loginView(req,rsp);
        });
        server.listen("0.0.0.0",8080);
    }
    ~CloudPan()
    {
        
    }
};
