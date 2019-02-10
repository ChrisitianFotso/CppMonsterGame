#include "Gametab.h"
#include <cctype>
#include <ctime>
#include "date.h"
#include <limits>
#include <cstdlib>
#include <iomanip>
using namespace std;

 double frand_a_b(double a, double b)
{
    return (( rand()/(double)RAND_MAX ) * (b-a) + a);

}

int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}
Monster* Gametab::compare_speed(Monster* M1 , Monster* M2)
{
int sp1 ,sp2;

 sp1=M1->getPv();
 sp2=M2->getPv();
 M2->msgF("Velocità",sp2);
 M1->msgF("Velocità",sp1);


 if(sp1>sp2)
 return M1;
 else if(sp1<sp2)
 return M2;
 else
 {
   if(rand()%2)
  {
      msgF("Sorteggiato",M1->getName());
      return M1;
  }
   else
  {
    msgF("Sorteggiato",M2->getName());
    return M2;
  }

 }

}



Gametab::Gametab(ofstream* f,string name1,string name2):
Logger::Logger("Cppmon",f)
{
 _log_file=f;
 _attack_file=name1;
 _monster_file=name2;
 _mach_end=false;
}

void Gametab::counterattack(Team* mons,Team* defender )
{
  Date d;
  time_t t;
 char test[6];
 time(&t);
 strftime(test,6,"%H.%M",localtime(&t));

if(!mons->getActiveMonster()->isDied())
 {
        mons->getActiveMonster()->attack(defender->getActiveMonster(),"Contrattacca con");

        if(defender->getActiveMonster()->isDied())
       {

       defender->getActiveMonster()->msgIo("è morto!");
       defender->getActiveMonster()->msgF("è morto");
       if(defender->getMonsterNumber()<=1)
        {
         defender->msgF("Non ha mostri per sostituire", defender->getActiveMonster()->getName() );
         defender->msgIo("Non ha piu mostri");
        msgF(d.str(),"-",test); // local time
        msgF("Si conclude la partita con la vittoria di",mons->getName());
        delete  mons;
        delete  defender;
        _mach_end=true;
        }
        else
        {
        int new_defen=rand_a_b(0,defender->getMonsterNumber());
         defender->cancelMonters(defender->getActiveMonster());
         defender->setAttiveMonter(new_defen);
         }


       }

 }

 else
 {
       mons->getActiveMonster()->msgIo("è morto!");
       mons->getActiveMonster()->msgF("è morto");
       if(mons->getMonsterNumber()<=1)
         {
         mons->msgF("Non ha mostri per sostituire", mons->getActiveMonster()->getName() );
         mons->msgIo("Non ha piu mostri");
         msgF(d.str(),"-",test); // local time
         msgF("Si conclude la partita con la vittoria di",defender->getName());
         delete  mons;
         delete  defender;
         _mach_end=true;
         }
          else
           {
            int new_mons=rand_a_b(0,mons->getMonsterNumber());
            mons->cancelMonters(mons->getActiveMonster());
            mons->setAttiveMonter(new_mons);
           }
  }
}


Gametab::~Gametab()
{

}


void Gametab::readTeamFile(char* fileName)
{
  ifstream file;
  int j(-1);
  vector <Team*> player;
  file.open(fileName);
  if (!file.is_open()) {
        std::cout << "Error Reading File in class <Gametab>" << endl;
        exit (EXIT_FAILURE);
    }

    while (!file.eof())
    {
        string line;
        getline(file, line);
        if (line.size() > 0 && isalpha(line[0])  )
        {

            j++;
            Team* t =new Team(line,_log_file);
            player.push_back(t);
        }
        else if (line.size() > 0 && isdigit(line[0]) )
        {

          stringstream ss;
          ss.str(line);

          int id(0),att[4]={0};
          ss>>id>>att[0]>>att[1]>>att[2]>>att[3];

          Monster* mons=new Monster(id,_monster_file,_log_file);
          for(int i (0);att[i]!=0 && i<4 ;i++)
          {

           mons->setattacks(att[i],_attack_file);
          }
         player[j]->addMonster(mons);
        }

    }

  _player=player[0];
  _pc=player[1];

}

void Gametab::playTurn()
{
 int request;
 _player->getActiveMonster()->msg("PS",_player->getActiveMonster()->getPs());
 _pc->getActiveMonster()->msg("PS",_pc->getActiveMonster()->getPs());
 _player->msgIo("Premi 0 per attacare , 1 per cambiare mostro");
while (!(std::cin >> request) ||  (request!=1 && request!=0))
{
    std::cin.clear(); //clear bad input flag
    std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); //discard input
    std::cout << "Invalid input; please re-enter.\n";
}
 if(request==0)
 {
fight();
 }

 else
 {
  int id_substitute;
  _player->changeMenu();
  while (!(cin >>id_substitute) ||  id_substitute<0 || id_substitute>_player->getMonsterNumber())
       {
       cin.clear(); //clear bad input flag
       cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); //discard input
       cout << "Invalid input; please re-enter.\n";
       }

    if(_player->change_available())
   {
  int att_pc;
  _player->changeMonster(id_substitute);
  att_pc=rand_a_b(0,_pc->getActiveMonster()->getAttaksNumber());
  _pc->getActiveMonster()->attackSel(att_pc);
  _pc->getActiveMonster()->attack(_player->getActiveMonster(),"attacca con");
   }
   else
   {
    _player->msgF("Non hai  altri monstri.attacca");
     fight();
   }

 }

}

 void Gametab::welcomeMenu()
 {
  time_t t;
 char test[6];
 time(&t);
 strftime(test,6,"%H.%M",localtime(&t));
  msgIo("Benvenuto a Cppmon !\n");
  msgF(Date().str(),"-",test);
  msgF("comincia la partita",_player->getName(),"vs",_pc->getName());
  _player->sortMOnster();
  _pc->sortMOnster();
  _player->setAttiveMonter(0);
  _pc->setAttiveMonter(0);
  _player->msg("mostri",_player->str());
  _player->msg("Manda in campo",_player->getActiveMonster()->getName());
  cout<<"\n CONTRO\n"<<endl;
  _pc->msg("mostri",_pc->str());
  _pc->msg("Manda in campo",_pc->getActiveMonster()->getName());
  }

void Gametab::run()
{
  int i(0);
  welcomeMenu();
  cout<<"\n--------------"<<endl;
  while(!_mach_end)
  {
  msg("turn",i);
  playTurn();
  cout<<"--------------"<<endl;
  i++;
  }

}


void Gametab:: fight()
{
//begin

   Monster* beginner;
   int att;
   int att_pc;
  _player->attackMenu();
       while (!(cin >>att) ||  att<0 || att>_player->getActiveMonster()->getAttaksNumber())
      {
       cin.clear(); //clear bad input flag
       cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); //discard input
       cout << "Invalid input; please re-enter.\n";
      }

   att_pc=rand_a_b(0,_pc->getActiveMonster()->getAttaksNumber());
   _player->getActiveMonster()->attackSel(att);
   _pc->getActiveMonster()->attackSel(att_pc);

   if(_player->getActiveMonster()->getAttackSelected()->getPriority() && _pc->getActiveMonster()->getAttackSelected()->getPriority())
     {

       _player->getActiveMonster()->msgF("Scelto l’attacco con priorità",_player->getActiveMonster()->getAttackSelected()->getName());
        _pc->getActiveMonster()->msgF("Sorteggiato l’attacco con priorità",_pc->getActiveMonster()->getAttackSelected()->getName());
        beginner=compare_speed(_player->getActiveMonster(),_pc->getActiveMonster());
        if(_player->getActiveMonster()->getName()==beginner->getName())
        {
        _player->getActiveMonster()->attack(_pc->getActiveMonster(),"attacca con");
        counterattack(_pc,_player);
        }
        else
        {
         _pc->getActiveMonster()->attack(_player->getActiveMonster(),"attacca con");
        counterattack(_player,_pc);
        }

     }
   else if(_player->getActiveMonster()->getAttackSelected()->getPriority() && !_pc->getActiveMonster()->getAttackSelected()->getPriority())
          {
           _player->getActiveMonster()->msgF("Scelto l’attacco con priorità",_player->getActiveMonster()->getAttackSelected()->getName());
           _pc->getActiveMonster()->msgF("Sorteggiato l’attacco senza priorità",_pc->getActiveMonster()->getAttackSelected()->getName());
           _player->getActiveMonster()->attack(_pc->getActiveMonster(),"attacca con");
           counterattack(_pc,_player);
          }
   else if(!_player->getActiveMonster()->getAttackSelected()->getPriority() && _pc->getActiveMonster()->getAttackSelected()->getPriority())
        {
          _pc->getActiveMonster()->msgF("Sorteggiato l’attacco con priorità",_pc->getActiveMonster()->getAttackSelected()->getName());
          _player->getActiveMonster()->msgF("Scelto l’attacco senza priorità",_player->getActiveMonster()->getAttackSelected()->getName());
          _pc->getActiveMonster()->msgF("Sorteggiato l’attacco con priorità",_pc->getActiveMonster()->getAttackSelected()->getName());
          _player->getActiveMonster()->msgF("Scelto l’attacco senza priorità",_player->getActiveMonster()->getAttackSelected()->getName());
         _pc->getActiveMonster()->attack(_player->getActiveMonster(),"attacca con");
         counterattack(_player,_pc);
        }
   else
        {
          _player->getActiveMonster()->msgF("Scelto l’attacco senza priorità",_player->getActiveMonster()->getAttackSelected()->getName());
          _pc->getActiveMonster()->msgF("Sorteggiato l’attacco senza priorità",_pc->getActiveMonster()->getAttackSelected()->getName());
          beginner=compare_speed(_player->getActiveMonster(),_pc->getActiveMonster());
          if(_player->getActiveMonster()->getName()==beginner->getName())
          {
          _player->getActiveMonster()->attack(_pc->getActiveMonster(),"attacca con");
          counterattack(_pc,_player);
          }
          else
         {
          _pc->getActiveMonster()->attack(_player->getActiveMonster(),"attacca con");
          counterattack(_player,_pc);
         }
         }
//end
}
