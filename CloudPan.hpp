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
    UserManager* userManager;
    httplib::Server server;
public:
    void loginView(const httplib::Request &req, httplib::Response &rsp);
    void signUpView(const httplib::Request& req,httplib::Response& rsp);
    void cloudPanView(const httplib::Request& req,httplib::Response& rsp);

    CloudPan()
    {
        userManager=new UserManager();
        server.Get("/",bind(&CloudPan::loginView,this,placeholders::_1,placeholders::_2));

        server.listen("0.0.0.0",8000);
        pause();
    }
    ~CloudPan()
    {
        delete(&server);
        delete(userManager);
    }
};





#endif