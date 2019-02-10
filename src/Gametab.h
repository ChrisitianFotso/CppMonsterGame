#ifndef GAMETAB_H
#define GAMETAB_H

#include"Team.h"
#include"Logger.h"
#include "date.h"
#include"Monster.h"

class Gametab : public Logger
{
    public:
    Gametab(std::ofstream *f,std::string name1,std::string name2);
    ~Gametab();

    void run();
    void readTeamFile(char* );

    private:
std::string _attack_file;
std::string _monster_file;
std::ofstream* _log_file;
Team* _player;
Team* _pc;
bool _mach_end;
void welcomeMenu();
void counterattack(Team* mons,Team* defender ) ;
Monster* compare_speed(Monster* M1 , Monster* M2);
void fight();
void playTurn();
};

#endif // GAMETAB_H
