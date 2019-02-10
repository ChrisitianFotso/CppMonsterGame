#include "Attack.h"
#include<fstream>
#include<cctype>
#include <cstdlib>
#include<iostream>

using namespace std;

Attack::Attack(int id,string fileName)
{


 string str2(""),str3(""),str4(""),str5("");
 int idf ;
 _pdb=0;
 ifstream file;
 file.open(fileName.c_str());

if (!file.is_open())
{
    cout << "Error Reading File in class <attack>" << endl;
    exit (EXIT_FAILURE);
}

while (!file.eof())
{
  string str;
  getline(file,str);
  if(str.size()>0)
  {
  stringstream ss;
  ss.str(str);
  ss>>idf>>str2>>str3>>str4>>str5;
  if(idf==id)
 {
   _id=id;
   _name=str2;
   if(isdigit(str3[0]))
  {
   _pdb=atoi(str3.c_str());
    if(str4 !="p" && str4!="")
       {
        _fs.setsf(str4);

           if(str5=="p")
           _priority=true;
           else
           _priority=false;
       }
    else
    {
    if (str4=="p")
    _priority=true;
    else
   _priority=false;
    }


  }
  else
  {
    if(str3 !="p" && str3!="")
   {
     _fs.setsf(str3);
     if(str4=="p")
         _priority=true;
    else
    _priority=false;
   }
    else
    {
    if (str3=="p")
    _priority=true;
    else
    _priority=false;
    }

  }

 break;
 }
}
 }
file.close();
}

Attack::Attack(const Attack & other):
_id(other._id),
_name(other._name),
_pdb(other._pdb),
_fs(other._fs),
_priority(other._priority)
{

}

string Attack:: getName()
{
 return _name;
}

int Attack:: getPdb()
{
 return _pdb;
}

FundamentalStat Attack:: getFs()
{
    return _fs;
}

bool Attack:: getPriority()
{
  return _priority;
}

int Attack::  getId()
{
 return _id;
}
