#ifndef __CLOUDPAN_HPP
#define __CLOUDPAN_HPP
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





#endif