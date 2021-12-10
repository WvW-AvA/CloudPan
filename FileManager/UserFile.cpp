#include "UserFile.hpp"

char * ReadFile(char* path,int &outFileLength)
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

vector<string> str_split(const string& str,const string& pattern)
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

void FileManager::insertNodeFile(const UserFile& file)
{
            DirNode *curr=&rootDir;
            vector<string> separatedPath=str_split(file.filePath,"/");
            int i;
pos:        for(i=0;i<separatedPath.size()-1;i++)
            {
                for(auto v:curr->subDirs)
                {
                    if(v->DirName==separatedPath[i])
                    curr=v;
                    goto pos;
                }
                auto t= new DirNode;
                t->DirName=separatedPath[i];
                curr->subDirs.push_back(t);
                curr=curr->subDirs[curr->subDirs.size()-1];
            }
            for(auto v:curr->files)
            {
               if(v.fileName==separatedPath[i])
               cout<<"Warning: File has existed.";
               return;
            }
           curr->files.push_back(file);
}
void FileManager::showCurrentDir()
{
    cout<<currDir->DirName<<"\n\n";
    for(auto v:currDir->subDirs)
    cout<<v->DirName;
    for(auto v:currDir->files)
    cout<<&v;
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
        if(v.size()==1)
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
         insertNodeFile(*value);
    }
}

void  FileManager::downloadFile(const UserFile & file)
{

}
void FileManager::uploadFile(const UserFile & file)
{

}
void FileManager::creatDir(const string & dirPath)
{
    mkdir((fileDirPath+dirPath).c_str(),S_IRWXU);
}
