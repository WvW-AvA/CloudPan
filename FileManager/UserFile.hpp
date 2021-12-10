#ifndef __USERFILE_HPP
#define __USERFILE_HPP
#include<iostream>
#include <sys/stat.h>
#include <sys/types.h>

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

    UserFile(/* args */);
    ~UserFile();
};

UserFile::UserFile(/* args */)
{
}

UserFile::~UserFile()
{
}


#endif