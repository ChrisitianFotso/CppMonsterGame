#include "FundamentalStat.h"

using namespace std;

FundamentalStat::FundamentalStat():
_receiver(""),
_sf_hurted(""),
_damage(0)
{

}

FundamentalStat::FundamentalStat(const FundamentalStat & other):
_receiver(other._receiver),
_sf_hurted(other._sf_hurted),
_damage(other._damage)
{

}

string FundamentalStat:: getReceiver()
{
 return _receiver;
}

string  FundamentalStat:: getsf_hurted()
{
 return _sf_hurted;
}

int FundamentalStat:: getdamage()
{
    return _damage;
}

void FundamentalStat:: setsf(string str)
{
 int counter(0);
 int tmp(0);
 if(str[0]=='a')
 {_receiver="attaccante";}
 else
 {_receiver="difensore";}

 for(int i(str.size()-1); str[i]=='-'||str[i]=='+';i--)
  {
    tmp=i;
      if(str[i]=='-')
      counter--;
      else
      counter++;
  }
  _damage=counter;
  if(str[tmp-1]=='D')
  _sf_hurted="PD";
  else if (str[tmp-1]=='V')
  _sf_hurted="PV";
  else
  _sf_hurted="PA";
}
