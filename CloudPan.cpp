#include "CloudPan.hpp"




int main(int argc,char * argv[])
{
    User test("dsd","dsda","dsadasda");
    //UserManager * userManager=new UserManager();
    FileManager *manager=new FileManager(test);
    cout<<manager->currDir;
    string tem;
    while(getline(cin,tem)&&manager->enterDir(tem))
    {
        manager->addFile("1111","4SD/DW/1111",FileType::jpg);
        cout<<manager->currDir;
    }
    return 0;
}