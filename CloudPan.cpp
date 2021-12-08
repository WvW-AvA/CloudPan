#include "CloudPan.hpp"




int main(int argc,char * argv[])
{
    // User test("dsd","dsda","dsadasda");
    UserManager* manager=new UserManager();
    // manager->insertUserDataIntoSQL(test);
     User * out=new User();
    // cout<<out;

    cout<<manager->checkPassward("sss","sdfasdasd",*out);
    cout<<'\n'<<out;
    return 0;
}