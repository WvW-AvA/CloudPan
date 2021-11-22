#ifndef __CLOUDPAN_HPP
#define __CLOUDPAN_HPP
#include <iostream>
#include <mysql/mysql.h>
#include "UserManager/UserInfo.hpp"
using namespace std;

bool mySQLInit(MYSQL &mysql);
bool insertUserDataIntoSQL(MYSQL&mysql,const User & user);
User* readUserInfoFromSQL(MYSQL &mysql,string name);

#endif