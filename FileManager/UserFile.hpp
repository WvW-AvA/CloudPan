#ifndef __USERFILE_HPP
#define __USERFILE_HPP

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <algorithm>
#include <time.h>
#include "../httplib.h"
#include "../UserManager/UserInfo.hpp"
using namespace std;
enum FileType
{
    txt=3,
    zip=1,
    jpg=2,
    bin=0,
    exe=4,
    html=5,
    png_show=6,
    png_download=7,
    mp4=8,
    rar=9
};
class UserFile
{
private:
    FileType fileType;
public:
    
    string fileName;
    string filePath;

    void set_fileType(const string & str);
    FileType get_fileType();
    string get_fileType_str();
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
    string dirName;
    DirNode* parentNode;
    vector<DirNode*> subDirs;
    vector<UserFile> files;

    string toStr()
    {
        string str;
        if(this->parentNode!=NULL)
            str=str+"..\n";
        for(auto v:this->subDirs)
            str+="Dir:"+v->dirName+'\n';
        for(auto v:this->files)
            str+="File:"+v.fileName+'\n';
        str+='\n';
        return str;
    }
    DirNode()
    {
        dirName="ROOT";
        parentNode=NULL;
    }
    DirNode(DirNode *parent,const string& name)
    {
        dirName=name;
        parentNode=parent;
    }
    friend ostream& operator<<(ostream& os,DirNode* node)
    {
        os<<"----------------"+node->dirName+"-------------\n";
        if(node->parentNode!=NULL)
            os<<"..\n";
        for(auto v:node->subDirs)
            os<<"Dir:"+v->dirName<<'\n';
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
    User* owner;
    DirNode* currDir;
    string fileDirPath;
    FILE* userFileLog;
    FILE* userFilLayers;
    
    static char * ReadFile(const char* path,int &outFileLength);
    static vector<string> str_split(const string& str,const string& pattern);
    void fileLog(const string & discribe);
    string getPath(const UserFile &file);
    bool insertNodeFile(const UserFile &file);
    bool addFile(UserFile & file);
    bool addFile(const string & fileName,const string & filePath,const FileType fileType);
    bool enterDir(const string & dirName);
    void creatDir(const string & dirName);
    UserFile& getUserFileWithName(string & name);
    bool downloadFile(UserFile & file,httplib::Response &res);
    bool downloadFile_str(string & fileName,httplib::Response &res);
    bool uploadFile(const UserFile & file);
    
    FileManager(User* whose)
    {
        this->owner=whose;
        this->fileDirPath="../UserFile/"+whose->user_name+"+"+whose->user_email+"/Data";
        this->userFileLog =fopen(("../UserFile/"+owner->user_name+"+"+owner->user_email+"/filelog.txt").c_str(),"a+");
        this->userFilLayers=fopen(("../UserFile/"+owner->user_name+"+"+owner->user_email+"/fileLayer.txt").c_str(),"a+");
        buildTree();
        cout<<"BuildTreeSucceed";
        rootDir.dirName="ROOT";
        rootDir.parentNode=NULL;
        currDir=&rootDir;
    }

    ~FileManager()
    {
        // fclose(userFileLog);
        // fclose(userFilLayers);
        // delete(currDir);
    }
};




#endif