#include "Monster.h"
#include<cstdlib>
#include <ctime>
using namespace std;



double frand_u_b(double a, double b)
{
 return (( rand()/(double)RAND_MAX ) * (b-a) + a);
}

std::string getSecondWord(std::string fileName,int id)
{
 std::ifstream file;
 int idf;
 std::string str1;
 file.open(fileName.c_str());

if (!file.is_open())
{
    std::cout << "Error Reading File in class <Monster>" << endl;
    exit (EXIT_FAILURE);
}

while (!file.eof())
{
 std::string str;
 getline(file,str);
 if(str.size()>0)
 {
  stringstream ss;
  ss.str(str);
  ss>>idf>>str1;
  if(idf==id)
    {
     break;
    }
 }
}
file.close();

 return str1;
}



Monster::Monster(int id,string fileName,ofstream * f):
Logger(getSecondWord(fileName,id),f)
{

 string str1("");
 int idf(0),ps(0),pa(0),pd(0),pv(0) ;
 ifstream file;
 file.open(fileName.c_str());

if (!file.is_open())
{
    cout << "Error Reading File in class <Monster>" << endl;
    exit (EXIT_FAILURE);
}

while (!file.eof())
{
  string str;
  getline(file,str);

 if(str.size() >0)
 {
 stringstream ss;
  ss.str(str);
  ss>>idf>>str1>>ps>>pa>>pd>>pv;
  if(idf==id)
 {
   _id=id;
   _name=str1;
   _ps=ps;
   _pa=pa;
   _pd=pd;
   _pv=pv;
   _pa_beg=pa;
   _pd_beg=pd;
   _pv_beg=pv;

 break;
 }

 }
}

file.close();
}

void Monster::gettingDamage(int damage )
{
 _ps-=damage;
}

void Monster::actualSpeed(int n)
{
_pv*=pow(2,n);
}

void Monster::actualHealthPoint(int n )
{

}

void Monster::actualDefencePoint(int n)
{
_pd*=pow(2,n);
}

void Monster::actualAttackPoint(int n)
{
_pa*=pow(2,n);
}

void Monster::attackSel(int x)
{
 _attack_selected=_attacks[x];
}

void Monster::restoreSF()
{
 _pa=_pa_beg;
 _pd=_pd_beg;
 _pv=_pv_beg;
}

bool Monster::isDied() const
{
return _ps<=0;
}

void Monster::attack(Monster* opponent,string str)
{
 double x=frand_u_b(0.8,1.0);
 int damage;
 msgIo("usa",_attack_selected->getName());

      damage=((_pa*_attack_selected->getPdb()*x)/opponent->getPd());
      opponent->gettingDamage(damage);

      opponent->msgIo("danno",damage);
       if(_attack_selected->getPdb()!=0)
    {
      msgF(str,_attack_selected->getName(),"infliggendo all’avversario un danno di",damage,"PS");
    }
  if(_attack_selected->getFs().getReceiver()=="attaccante")
  {
    fs_regulator(_attack_selected,opponent);
  }

  else if(_attack_selected->getFs().getReceiver()=="difensore")
  {
   opponent->fs_regulator(_attack_selected,opponent->getAdress());
  }

  opponent->msgF("Nuovi PS",opponent->getPs());


}

void Monster:: setattacks (int id,string filename)
{
 Attack* att=new Attack(id,filename);
 _attacks.push_back(att);
}

Monster::~Monster()
{
 for(int i(0);i<_attacks.size();i++)
 {
  delete _attacks[i] ;
 }
delete _attack_selected;
_attacks.clear();
}


int Monster::getPs() const
{
    return _ps;
}

int Monster::getPa() const
{
   return _pa;
}

int Monster::getPd() const
{
    return _pd;
}

int Monster::getPv() const
{
    return _pv;
}

string  Monster::getName() const
{
 return _name;
}

int  Monster::getId() const
{
  return _id;
}


void Monster::fs_regulator(Attack* atk,Monster* opponent)
{
if(atk->getFs().getsf_hurted()=="PD")
    {
     int tmp=_pd;
     if(atk->getFs().getdamage()==2)
      {
       actualDefencePoint(atk->getFs().getdamage());
       msgIo("PD","aumenta di molto");
         if(_pd>_pd_beg*8)
         {
           msgIo("PD","non può aumentare");
           msgF("I PD dovrebbero aumentare da",tmp,_pd,"ma non possono aumentare oltre",_pd_beg*8),
           _pd=_pd_beg*8;
           msgF("Nuovi PD",_pd);
           opponent->msgF("Nuovi PS",opponent->getPs());
         }
         else
         {
         msgF("I PD aumentano da",tmp,"a",_pd),
         opponent->msgF("Nuovi PS",opponent->getPs());
         }
     }
     else if(atk->getFs().getdamage()==1)
      {

         actualDefencePoint(atk->getFs().getdamage());
          msgIo("PD","aumenta");
           if(_pd>_pd_beg*8)
           {
            msgIo("PD","non può aumentare");
             msgF("I PD dovrebbero aumentare da",tmp,_pd,"ma non possono aumentare oltre",_pd_beg*8),
            _pd=_pd_beg*8;
           msgF("Nuovi PD",_pd);
           opponent->msgF("Nuovi PS",opponent->getPs());
           }
           else
          {
          msgF("I PD aumentano da",tmp,"a",_pd),
         opponent->msgF("Nuovi PS",opponent->getPs());
          }
      }
     else if(atk->getFs().getdamage()==-1)
      {
      actualDefencePoint(atk->getFs().getdamage());
       msgIo("PD","diminuisce");
           if(_pd<_pd_beg/8)
            {
           msgIo("PD","non può diminuire");
           msgF("I PD dovrebbero diminuire da",tmp,_pd,"ma non possono diminuire oltre",_pd_beg/8),
            _pd=_pd_beg/8;
            msgF("Nuovi PD",_pd);
             opponent->msgF("Nuovi PS",opponent->getPs());
            }
           else
          {
          msgF("I PD diminuiscono da",tmp,"a",_pd),
          opponent->msgF("Nuovi PS",opponent->getPs());
          }
      //hhhjj
      }
     else
      {
        actualDefencePoint(atk->getFs().getdamage());
        msgIo("PD","diminuisce di molto");
           if(_pd<_pd_beg/8)
            {
           msgIo("PD","non può diminuire");
           msgF("I PD dovrebbero diminuire da",tmp,_pd,"ma non possono diminuire oltre",_pd_beg/8),
            _pd=_pd_beg/8;
            msgF("Nuovi PD",_pd);
             opponent->msgF("Nuovi PS",opponent->getPs());
            }
           else
          {
          msgF("I PD diminuiscono da",tmp,"a",_pd),
          opponent->msgF("Nuovi PS",opponent->getPs());
          }
      }

     }
    if(atk->getFs().getsf_hurted()=="PV")
    {
     //actualSpeed(_attack_selected->getFs().getdamage());
    int tmp=_pv;
     if(atk->getFs().getdamage()==2)
      {
       actualSpeed(atk->getFs().getdamage());
       msgIo("PV","aumenta di molto");
         if(_pv>_pv_beg*8)
         {
           msgIo("PV","non può aumentare");
           msgF("I PV dovrebbero aumentare da",tmp,_pv,"ma non possono aumentare oltre",_pv_beg*8),
           _pv=_pv_beg*8;
           msgF("Nuovi PV",_pv);
            opponent->msgF("Nuovi PS",opponent->getPs());
         }
         else
         {
         msgF("I PV aumentano da",tmp,"a",_pv),
         opponent->msgF("Nuovi PS",opponent->getPs());
         }
     }
     else if(atk->getFs().getdamage()==1)
      {

         actualSpeed(atk->getFs().getdamage());
          msgIo("PV","aumenta");
           if(_pv>_pv_beg*8)
           {
            msgIo("PV","non può aumentare");
             msgF("I PV dovrebbero aumentare da",tmp,_pv,"ma non possono aumentare oltre",_pv_beg*8),
            _pv=_pv_beg*8;
           msgF("Nuovi PV",_pv);
           opponent->msgF("Nuovi PS",opponent->getPs());
           }
           else
          {
          msgF("I PV aumentano da",tmp,"a",_pv),
         opponent->msgF("Nuovi PS",opponent->getPs());
          }
      }
     else if(atk->getFs().getdamage()==-1)
      {
       actualSpeed(atk->getFs().getdamage());
       msgIo("PV","diminuisce");
           if(_pv<_pv_beg/8)
            {
           msgIo("PV","non può diminuire");
           msgF("I PV dovrebbero diminuire da",tmp,_pv,"ma non possono diminuire oltre",_pv_beg/8),
            _pv=_pv_beg/8;
            msgF("Nuovi PV",_pv);
             opponent->msgF("Nuovi PS",opponent->getPs());
            }
           else
          {
          msgF("I PV diminuiscono da",tmp,"a",_pv),
          opponent->msgF("Nuovi PS",opponent->getPs());
          }

      }
     else
      {
        actualSpeed(atk->getFs().getdamage());
        msgIo("PV","diminuisce di molto");
           if(_pv<_pv_beg/8)
            {
           msgIo("PV","non può diminuire");
           msgF("I PV dovrebbero diminuire da",tmp,_pv,"ma non possono diminuire oltre",_pv_beg/8),
            _pv=_pv_beg/8;
            msgF("Nuovi PV",_pv);
             opponent->msgF("Nuovi PS",opponent->getPs());
            }
           else
          {
          msgF("I PV diminuiscono da",tmp,"a",_pv),
          opponent->msgF("Nuovi PS",opponent->getPs());
          }
      }
    }
    if(atk->getFs().getsf_hurted()=="PA")
    {
        //actualSpeed(_attack_selected->getFs().getdamage());
    int tmp=_pa;
     if(atk->getFs().getdamage()==2)
      {
       actualAttackPoint(atk->getFs().getdamage());
       msgIo("PA","aumenta di molto");
         if(_pa>_pa_beg*8)
         {
           msgIo("PA","non può aumentare");
           msgF("I PA dovrebbero aumentare da",tmp,_pa,"ma non possono aumentare oltre",_pa_beg*8),
           _pa=_pa_beg*8;
           msgF("Nuovi PA",_pa);
            opponent->msgF("Nuovi PS",opponent->getPs());
         }
         else
         {
         msgF("I PA aumentano da",tmp,"a",_pa),
         opponent->msgF("Nuovi PS",opponent->getPs());
         }
     }
     else if(atk->getFs().getdamage()==1)
      {

         actualAttackPoint(atk->getFs().getdamage());
          msgIo("PA","aumenta");
           if(_pa>_pa_beg*8)
           {
            msgIo("PA","non può aumentare");
             msgF("I PA dovrebbero aumentare da",tmp,_pa,"ma non possono aumentare oltre",_pa_beg*8),
            _pa=_pa_beg*8;
           msgF("Nuovi PA",_pa);
           opponent->msgF("Nuovi PS",opponent->getPs());
           }
           else
          {
          msgF("I PA aumentano da",tmp,"a",_pa),
         opponent->msgF("Nuovi PS",opponent->getPs());
          }
      }
     else if(atk->getFs().getdamage()==-1)
      {
       actualAttackPoint(atk->getFs().getdamage());
       msgIo("PA","diminuisce");
           if(_pa<_pa_beg/8)
            {
           msgIo("PA","non può diminuire");
           msgF("I PA dovrebbero diminuire da",tmp,_pa,"ma non possono diminuire oltre",_pa_beg/8),
            _pa=_pa_beg/8;
            msgF("Nuovi PA",_pa);
             opponent->msgF("Nuovi PS",opponent->getPs());

            }
           else
          {
          msgF("I PA diminuiscono da",tmp,"a",_pa),
          opponent->msgF("Nuovi PS",opponent->getPs());
          }

      }
     else
      {
        actualAttackPoint(atk->getFs().getdamage());
        msgIo("PA","diminuisce di molto");
           if(_pa<_pa_beg/8)
            {
           msgIo("PA","non può diminuire");
           msgF("I PA dovrebbero diminuire da",tmp,_pa,"ma non possono diminuire oltre",_pa_beg/8),
            _pa=_pa_beg/8;
            msgF("Nuovi PA",_pa);
             opponent->msgF("Nuovi PS",opponent->getPs());
            }
           else
          {
          msgF("I PA diminuiscono da",tmp,"a",_pa),
          opponent->msgF("Nuovi PS",opponent->getPs());
          }
      }
    }
}

Monster* Monster::getAdress()
{
  return this;
}


void Monster::menuMonsters()
{
 for(int i(0);i<_attacks.size();i++)
 {
 stringstream ss;
 ss<<i<<"> ";
cout<<ss.str()<<_attacks[i]->getName()<<endl;
 }
}

int Monster::getAttaksNumber()
{
return _attacks.size();
}

string Monster::str()
{
 stringstream ss;
 ss<<_ps<<" "<<_pa<<" "<<_pd<<" "<<_pv;
 return ss.str();
}

 Attack* Monster::getAttackSelected()
 {
 return _attack_selected;
 }


