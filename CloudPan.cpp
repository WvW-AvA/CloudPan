#include "CloudPan.hpp"




int main(int argc,char * argv[])
{
    User test("dsd","dsda","dsadasda");
    //UserManager * userManager=new UserManager();
    FileManager *manager=new FileManager(test);
    manager->showCurrentDir();
    return 0;
}