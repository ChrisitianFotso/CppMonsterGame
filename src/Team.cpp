#include "Team.h"

using namespace std;
Team::Team(string name,ofstream* f):
Logger::Logger(name,f)
{
 _name=name;   //ctor
}

Team::~Team()
{
 for(int i(0);i<_monsters.size();i++)
 {
 delete _monsters[i];
 }
 delete _active_monster;
 _monsters.clear();
}



bool Team::isDied()
{
 return _monsters.size()<=0;
}

void Team::addMonster(Monster* mons )
{
    _monsters.push_back(mons);
}

void Team:: cancelMonters(Monster* mons)
{
  vector <Monster*> tmp;
  for(int i(0);i<_monsters.size();i++)
     {
      if(_monsters[i]!=mons)
       {
        tmp.push_back(_monsters[i]);
       }
     }
  _monsters.clear();
  _monsters=tmp;
}
string Team:: getName() const
{
return _name;
}

int Team::getMonsterNumber() const
{
 return _monsters.size();
}

 void Team::setAttiveMonter(int id )
 {
     _active_monster=_monsters[id];

 }

 void Team::sortMOnster()
 {
   int i,j;
  Monster* tmp;
  for(i=1;i<_monsters.size();i++)
    {
     tmp=_monsters[i];
     for(j=i;(j>0 && tmp->getId()<_monsters[j-1]->getId());j--)
     {
      _monsters[j]=_monsters[j-1];
     }
     _monsters[j]=tmp;
    }
 }

 void Team::changeMenu()
 {
 msgIo("Possibili mostri","");
 for(int i(0);i<_monsters.size();i++)
 {
   if(_monsters[i]!=_active_monster)
   cout<<i<<"> "<<_monsters[i]->getName()<<endl;
 }
 }

 void Team::attackMenu()
 {
  msgIo("Possibili attachi","")  ;
  _active_monster->menuMonsters();
 }

 void Team::changeMonster(int id)
 {

   Monster* tmp;
   tmp=_active_monster;
   _active_monster=_monsters[id];
   msgF("Sostituzione",tmp->getName(),"per",_active_monster->getName());
   tmp->restoreSF();
   msgF("Statistiche di",tmp->getName(),"riportate a",tmp->str());

 }

 void Team::choiseAttack(int x )
 {
  _active_monster->attackSel(x);
 }

string Team:: str()
{
  stringstream ss;
  for(int i(0);i<_monsters.size();i++)
  {
   if(i!=_monsters.size()-1)
   ss<<_monsters[i]->getName()<<" ";
   else
   ss<<_monsters[i]->getName();
  }
return ss.str();
}

Monster* Team::getActiveMonster() const
{
  return _active_monster;
}

bool Team::change_available()
{
 return _monsters.size()>1 ;
}
