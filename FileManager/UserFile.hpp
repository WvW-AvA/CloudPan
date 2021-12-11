#ifndef __USERFILE_HPP
#define __USERFILE_HPP

#include<iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>
#include "../httplib.h"
#include "../UserManager/UserInfo.hpp"
using namespace std;
enum FileType
{
    txt=3,
    zip=1,
    jpg=2,
    bin=0
};

class UserFile
{
private:
    FileType fileType;
public:
    
    string fileName;
    string filePath;
    void set_fileType(const string & str)
    {
        if(str=="txt")
            fileType=(FileType)txt;
            else if(str=="zip")
            fileType=(FileType)zip;
            else if(str=="jpg")
            fileType=(FileType)jpg;
            else
            fileType=(FileType)bin;
    }
    FileType get_fileType()
    {
        return fileType;
    }
    string get_fileType_str()
    {
        switch (fileType)
        {
        case (FileType)txt:
            return "txt";
            break;
        case (FileType)zip:
            return "zip";
            break;
        case (FileType)jpg:
            return "jpg";
            break;
        default:
        return "bin";
            break;
        }
    }
    
    friend ostream & operator<< (ostream & os,UserFile* uf)
    {
        return os<<"\nFileName:"<<uf->fileName<<"\nFilePath:"<<uf->filePath<<"\nFileType:"<<uf->get_fileType_str();
    }
    UserFile(){}
    UserFile(FileType filetype,const string & fileName,const string& filePath)
    {
        this->fileName=fileName;
        this->filePath=filePath;
        this->fileType=filetype;
    }

    ~UserFile(){}
};
struct DirNode
{
    string DirName;
    vector<DirNode*> subDirs;
    vector<UserFile> files;

    friend ostream& operator<<(ostream& os,DirNode* node)
    {
        os<<"----------------"+node->DirName+"-------------\n";
        for(auto v:node->subDirs)
            os<<"Dir:"+v->DirName;
        for(auto v:node->files)
            os<<&v;
        os<<'\n';
        return os;
    }
};

class FileManager
{
private:
    DirNode rootDir;
    UserFile* ReadUserFileInfo();
    void buildTree();
public:
    User owner;
    DirNode* currDir;
    string fileDirPath;
    FILE* userFileLog;
    FILE* userFilLayers;


    void insertNodeFile(const UserFile &file);
    bool enterDir(const string & dirName);
    void creatDir(const string & dirPath);
    void downloadFile(const UserFile & file);
    void uploadFile(const UserFile & file);
    FileManager(User& whose)
    {
        this->owner=whose;
        this->fileDirPath="/home/mua/Backend/CloudPan/UserFile/"+owner.user_name+"+"+owner.user_email+"/Data";
        userFileLog =fopen(("/home/mua/Backend/CloudPan/UserFile/"+owner.user_name+"+"+owner.user_email+"/filelog.txt").c_str(),"a+");
        userFilLayers=fopen(("/home/mua/Backend/CloudPan/UserFile/"+owner.user_name+"+"+owner.user_email+"/fileLayer.txt").c_str(),"a+");
        buildTree();
        rootDir.DirName="ROOT";
        currDir=&rootDir;
    }

    ~FileManager(){}
};


#endif