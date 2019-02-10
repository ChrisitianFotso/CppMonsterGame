#ifndef TEAM_H
#define TEAM_H

#include"Logger.h"
#include<string>
#include"Monster.h"
class Team : public Logger
{
    public:
    Team(std::string,std::ofstream* );
    ~Team();// destructore
    bool isDied();
    void addMonster(Monster* );
    void cancelMonters(Monster*);
    void changeMenu();
    void attackMenu();
    Monster* getActiveMonster() const;
    void setAttiveMonter(int );
    std::string getName() const;
    int getMonsterNumber() const;
    void sortMOnster();
    void changeMonster(int id);
    void choiseAttack(int );
    std::string str();
    bool change_available();

    private:

   std::vector <Monster*> _monsters;
   std::string _name;
   Monster* _active_monster;


};

#endif // TEAM_H
