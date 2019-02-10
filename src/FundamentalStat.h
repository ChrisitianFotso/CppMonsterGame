#ifndef FUNDAMENTALSTAT_H
#define FUNDAMENTALSTAT_H

#include<string>

class FundamentalStat
{
    public:
FundamentalStat();
FundamentalStat(const FundamentalStat & other);
std::string getReceiver();
void  setsf(std::string );
std::string getsf_hurted();
int getdamage();

    private:
std::string _receiver;
std::string _sf_hurted;
int _damage;
};

#endif // FUNDAMENTALSTAT_H
