#ifndef ATTACK_H
#define ATTACK_H

#include"FundamentalStat.h"
#include<string>

#include<sstream>

class Attack
{
    public:

    Attack(int id,std::string fileName);
    Attack(const Attack & other);
    int  getId();
    std::string getName();
    int getPdb();
    FundamentalStat getFs();
    bool getPriority();
    private:

    int _id;
    std::string _name;
   int _pdb;
   FundamentalStat _fs;
   bool _priority;
};

#endif // ATTACK_H
