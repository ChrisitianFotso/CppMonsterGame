#include <iostream>
#include "Gametab.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    srand(time(NULL));
    ofstream file;
    file.open("log.txt");
    if(!file.is_open())
    {
     cout<<"error file"<<endl;
    }
    Gametab obj(&file,"attacchi.txt","mostri.txt");
    obj.readTeamFile("squadre.txt");
    obj.run();
    file.close();
    return 0;
}
