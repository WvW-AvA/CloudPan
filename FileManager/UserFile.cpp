#include "UserFile.hpp"


char * FileManager::ReadFile(const char* path,int &outFileLength)
{
	FILE *fp=fopen(path,"rb");
	if(!fp)
	{
		std::cout<<"File "<<path<<" no found!!";
		return NULL;
	}
	fseek(fp,0,SEEK_END);
	outFileLength=ftell(fp);
	rewind(fp);
	char* file_buffer=new char[outFileLength+1];
	memset(file_buffer,0,outFileLength+1);
	fread(file_buffer,sizeof(char),outFileLength,fp);
	fclose(fp);
	return file_buffer;
}

vector<string> FileManager::str_split(const string& str,const string& pattern)
{
    char*strc=new char[strlen(str.c_str())+1];
    strcpy(strc,str.c_str());
    vector<string> result;
    char*tem=strtok(strc,pattern.c_str());
    while (tem!=NULL)
    {
        result.push_back(string(tem));
        tem=strtok(NULL,pattern.c_str());
    }
    delete[] strc;
    return result;
}

void UserFile::set_fileType(const string & str)
{
    if(str=="DIR")
        fileType=(FileType)DIR;
    else if(str=="text/plain")
        fileType=(FileType)txt;
    else if(str=="application/x-zip-compressed")
        fileType=(FileType)zip;
    else if(str=="application/octet-stream")
        fileType=(FileType)rar;
    else if(str=="video/mpeg4")
        fileType=(FileType)mp4;
    else if(str=="image/png")
        fileType=(FileType)png_show;
    else if(str=="application/png")
        fileType=(FileType)png_download;
    else if(str=="image/jpeg")
        fileType=(FileType)jpg;
    else if(str=="text/html")
        fileType=(FileType)html;
    else if(str=="application/x-msdownload")
        fileType=(FileType)exe;
    else
        fileType=(FileType)bin;
}  
FileType UserFile::get_fileType()
{
    return fileType;
}
string UserFile::get_fileType_str()
{
    switch (fileType)
    {
    case(FileType)DIR:
        return "DIR";
        break;
    case (FileType)txt:
        return "text/plain";
        break;
    case (FileType)zip:
        return "application/x-zip-compressed";
        break;
    case (FileType)rar:
        return "application/octet-stream";
        break;
    case (FileType)mp4:
        return "video/mpeg4";
        break;
    case (FileType)png_show:
        return "image/png";
        break;
    case (FileType)png_download:
        return "application/png";
        break;
    case (FileType)jpg:
        return "image/jpeg";
        break;
    case (FileType)html:
        return "text/html";
        break;
    case (FileType)exe:
        return "application/x-msdownload";
        break;
    default:
    return "application/octet-stream";
        break;
    }
}



bool FileManager::insertNodeFile(const UserFile& file)
{
DirNode *curr=&rootDir;
vector<string> separatedPath=str_split(file.filePath,"/");
int i=0;
pos: while(i<separatedPath.size()-1)
{
    
    for(auto v:curr->subDirs)
    {
        if(v->dirName==separatedPath[i])
        {
            curr=v;
            i++;
            goto pos;
        }
    }
    auto t= new DirNode;
    t->dirName=separatedPath[i];
    t->parentNode=curr;
    curr->subDirs.push_back(t);
    curr=curr->subDirs[curr->subDirs.size()-1];
    i++;
}
for(auto v:curr->files)
{
    if(v.fileName==separatedPath[i])
    {
        cout<<"Warning: File has existed.\n";
        return false;
    }
}
if(file.fileType==(FileType)DIR)
    curr->subDirs.push_back(new DirNode(curr,file.fileName));
else
    curr->files.push_back(file);
return true;
}
bool FileManager::addFile( UserFile & file)
{
    if(insertNodeFile(file))
    {
        string str( "\nFileName:"+file.fileName+
                    "\nFilePath:"+file.filePath+
                    "\nFileType:"+file.get_fileType_str()+
                    "\nSTOP" );
        if(fputs(str.c_str(),userFilLayers));
        {
            fclose(userFilLayers);
            this->userFilLayers=fopen(("../UserFile/"+owner->user_name+"+"+owner->user_email+"/fileLayer.txt").c_str(),"a+");
            return true;
        }
    }
    return false;
}
bool FileManager::addFile(const string & fileName,const string & filePath,const FileType fileType)
{
    UserFile* u=new UserFile(fileType,fileName,filePath);
    if (addFile(*u))
        return true;
    else
    {
        delete(u);
        return false;
    }
}
UserFile* FileManager::ReadUserFileInfo()
{
    UserFile *result=new UserFile();
    char tem[1000];
    
    while(true)
    {
        if(!fgets(tem,999,userFilLayers))
        return NULL;
        string t(tem);
        t.erase(remove(t.begin(),t.end(),'\n'),t.end());
        if(t=="STOP")
            break;
        auto v=str_split(t,":");
        while(v.size()<=1)
            v.push_back(string());
        if(v[0]=="FileName")
            result->fileName=v[1];
        else if(v[0]=="FilePath")
            result->filePath=v[1];
        else if(v[0]=="FileType")
            result->set_fileType(v[1]);
    }
    
    return result;
}

void FileManager::buildTree()
{
    char filePath[1000];
    while(auto value=ReadUserFileInfo())
    {
        cout<<"inser";
         insertNodeFile(*value);
    }
}
bool FileManager::enterDir(const string & dirName)
{
    if(dirName==".."&&currDir->parentNode!=NULL)
    {
        currDir=currDir->parentNode;
        return true;
    }
    for(auto v:currDir->subDirs)
    {
        if(v->dirName==dirName)
        {
            currDir=v;
            return true;
        }
    }
    return false;
}
string FileManager::getPath(const UserFile &file)
{
    return fileDirPath+'/'+file.filePath;
}
void  FileManager::fileLog(const string & fileEvent)
{
    string str;
    time_t *t;
    time(t);
    str="Time:"+string(asctime(localtime(t)))+'\n';
    str+="User:"+owner->user_name+'\n';
    str+="FileEvent:"+fileEvent+'\n';
    fputs(str.c_str(),userFileLog);
}
bool FileManager::downloadFile(UserFile & file,httplib::Response &rsp)
{
    int file_Size;
    char* file_Buffer=ReadFile(getPath(file).c_str(),file_Size);
    cout<<"\nRead File Done\n";
    if(!file_Buffer)
    {
        fileLog(file.filePath+" could not find!");
        return false;
    }
    rsp.set_content(file_Buffer,file_Size,file.get_fileType_str().c_str());
    rsp.status=200;
    delete(file_Buffer);
    return true;
}
bool FileManager::downloadFile_str(string & fileName,httplib::Response &res)
{
    UserFile* tem;
    if(tem=getUserFileWithName(fileName))
        return downloadFile(*tem,res);
    else
        return false;
}
UserFile* FileManager::getUserFileWithName(string & name)
{
    UserFile* tem;
    for(auto value:currDir->files)
    {
        if(value.fileName==name)
        {
            tem=new UserFile(value);
            cout<<"\n getNameSucceed\n";
            return tem;
        }
    }
    return nullptr;
}
bool FileManager::uploadFile(httplib::MultipartFormData & file)
{
    DirNode* tem=currDir;
    string str;
    while(tem->parentNode)
    {
        str=tem->dirName+'/'+str;
        tem=tem->parentNode;
    }
    UserFile userFile(file.content_type,file.filename,str+file.filename);
    if(addFile(userFile))
    {
        ofstream ofs(fileDirPath+'/'+userFile.filePath,ios::binary);
        ofs<<file.content;
        ofs.close();
        cout<<"done";
        return true;
    }
    return false;
        
}
void FileManager::creatDir(const string & dirName)
{
    DirNode* tem=currDir;
    string str;
    while(tem->parentNode)
    {
        str=tem->dirName+'/'+str;
        tem=tem->parentNode;
    }
    if(addFile(dirName,str+dirName,(FileType)DIR))
        mkdir((fileDirPath+'/'+str+dirName).c_str(),S_IRWXU);
}
