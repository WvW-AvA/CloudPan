#include "CloudPan.hpp"

string creat_html_model(const string &title, const string& body)
{
    string res("\
    <!DOCTYPE html>\
    <html>\
    <head>\
    <meta charset=\"utf-8\">\
    <title>"+title+"</title>\
    </head>\
    <body>\
    "+body+"\
    </body>\
    </html>");
    return res.c_str();
}

string creat_Dir_html(DirNode* dir)
{
    string str("<h1>"+dir->dirName+"<h1>\n<p>"+dir->toStr()+"<p>\n");
    return creat_html_model("DirLayer",str);
}

string creat_Login_html(bool status)
{
    string a;
    if(status)
        a="Success,please...";
    else 
        a="Failed";
    return creat_html_model("logView","<p1>"+a+"<p1>");
}

string creat_SignUp_html(bool status)
{
    string a;
    if(status)
        a="Success,please back and login again";
    else 
        a="Failed";
    return creat_html_model("logView","<p1>"+a+"<p1>");
}


string creat_CurrentDir_html(DirNode *current)
{
    return creat_html_model("DirView","<p1>"+current->toStr()+"<p1>");
}

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


void CloudPan::getLoginView(const httplib::Request &req, httplib::Response &rsp)
{
    int size;
    char* str=FileManager::ReadFile("../LoginIn.html",size);
    rsp.set_content(str,size,"text/html");
    rsp.status=200;
}

void CloudPan::testView(const httplib::Request& req,httplib::Response& rsp)
{
    
}

void CloudPan::loginView(const httplib::Request& req,httplib::Response& rsp)
{
    SignInData tem(req);
    User *user;
    if(userManager.checkPassward(tem.userName,tem.password,&user))
    {
        cout<<user<<"Succed SingIn\n";
        user->fileManager=new FileManager(user);
        userManager.users.push_back(User(*user));
        acceptUserRequest(userManager.users[userManager.users.size()-1]);
        rsp.set_content(creat_Dir_html(user->fileManager->currDir),"text/html");
    }else
    {
        rsp.set_content(creat_Login_html(false),"text/html");
    }
    rsp.status=200;
}

void CloudPan::signUpView(const httplib::Request& req,httplib::Response& rsp)
{
    SignInData tem(req);
    User user(tem.userName,tem.email,tem.password);
    if(userManager.userSignUp(user))
    {
       rsp.set_content(creat_SignUp_html(true),"text/html");
    }else
    {
        rsp.set_content(creat_SignUp_html(false),"text/html");
    }
    rsp.status=200;
}

void CloudPan::cloudPanView(User& user,const httplib::Request& req,httplib::Response& rsp)
{
    EventData event(req);
    if(event.event=="OpenDir")
    {
        if(user.fileManager&&user.fileManager->enterDir(event.dirName))
        {
            cout<<&user<<"Open Dir"<<event.dirName<<"Succeed";
            rsp.set_content(creat_Dir_html(user.fileManager->currDir),"text/html");
        }
        else
        {
            rsp.set_content(creat_SignUp_html(false),"text/html");
        }
    }
    else if(event.event=="Download")
    {
        if(user.fileManager->downloadFile_str(event.dirName,rsp))
        {

        }
        else
        {
            rsp.set_content(creat_html_model("Transform File","Failed"),"text/html");
        }
    }
    else if(event.event=="CreatDir")
    {
        user.fileManager->creatDir(event.dirName);
        cout<<&user<<"Creat Dir"<<event.dirName<<"Succeed";
        rsp.set_content(creat_Dir_html(user.fileManager->currDir),"text/html");
    }
    else 
    {
        rsp.set_content(creat_SignUp_html(false),"text/html");
    }
    rsp.status=200;
}

void CloudPan::acceptUserRequest(User& user)
{
    
    server.Get("/"+user.user_name,[&](const httplib::Request& req,httplib::Response& rsp){
        cloudPanView(user,req,rsp);
    });
    server.Post("/"+user.user_name,[&](const httplib::Request& req,httplib::Response& rsp){
        cout<<"\nPostGet\n";
        cloudPanView(user,req,rsp);
    });
}
int main(int argc,char * argv[])
{
    // User *test=new User("dsd","dsda","dsadasda");
    // //UserManager * userManager=new UserManager();
    // test->fileManager=new FileManager(test);
    // cout<<test->fileManager->currDir;
    // string tem;
    // while(getline(cin,tem)&&test->fileManager->enterDir(tem))
    // {
    //     cout<<test->fileManager->addFile("1111","4SD/DW/1111",FileType::jpg);
    //     cout<<test->fileManager->currDir;
    // }
    CloudPan pan;
    return 0;
}