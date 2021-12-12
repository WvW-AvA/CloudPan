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

string creat_Dir_html(DirNode& dir)
{
    string str("<h1>"+dir.dirName+"<h1>\n<p>"+dir.toStr()+"<p>\n");
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



void CloudPan::loginView(const httplib::Request& req,httplib::Response& rsp)
{
    SignInData tem(req);
    User *user;
    if(userManager->checkPassward(tem.userName,tem.password,user))
    {
        user->fileManager=new FileManager(user);
        userManager->users.push_back(user);
        rsp.set_content(creat_Login_html(true),"text/html");
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
    if(userManager->userSignUp(user))
    {
       rsp.set_content(creat_SignUp_html(true),"text/html");
    }else
    {
        rsp.set_content(creat_SignUp_html(false),"text/html");
    }
    rsp.status=200;
}

void CloudPan::cloudPanView(const httplib::Request& req,httplib::Response& rsp)
{

}


int main(int argc,char * argv[])
{
    // User test("dsd","dsda","dsadasda");
    // //UserManager * userManager=new UserManager();
    // FileManager *manager=new FileManager(test);
    // cout<<manager->currDir;
    // string tem;
    // while(getline(cin,tem)&&manager->enterDir(tem))
    // {
    //     cout<<manager->addFile("1111","4SD/DW/1111",FileType::jpg);
    //     cout<<manager->currDir;
    // }
    CloudPan pan;
    return 0;
}