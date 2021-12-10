#ifndef __USERFILE_HPP
#define __USERFILE_HPP
#include<iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include "../httplib.h"
#include "../UserManager/UserInfo.hpp"
using namespace std;
enum FileType
{
    txt,
    file,
    jpg,
};

class UserFile
{
private:
    
public:
    FileType fileType;
    string fileName;
    string filePath;
    
    UserFile::UserFile(FileType filetype,const string & fileName,const string& filePath);
    ~UserFile();
};

UserFile::UserFile(FileType filetype,const string & fileName,const string& filePath)
{
    this->fileName=fileName;
    this->filePath=filePath;
    this->fileType=filetype;
}

UserFile::~UserFile()
{
}

class FileManager
{
private:
    /* data */
public:
    User owner;
    string fileDirPath;
    FILE* userFileLog;
    
    void DownloadFile(const UserFile & file);
    void UploadFile(const UserFile & file);
    FileManager(User& whose);
    ~FileManager();
};

FileManager::FileManager(User& whose)
{
    this->owner=whose;
    this->fileDirPath="/home/mua/Backend/CloudPan/UserFile/"+owner.user_name+"+"+owner.user_email;
    userFileLog =fopen((this->fileDirPath+"filelog.txt").c_str(),"a+");
}

FileManager::~FileManager()
{

}


#endif