#ifndef MONSTER_H
#define MONSTER_H

#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include"Logger.h"
#include"Attack.h"
#include"vector"
#include<cmath>


class Monster : public Logger
{
    public:
    Monster(int id,std::string fileName,std::ofstream* f);
    ~Monster();
    void gettingDamage(int );
    void actualSpeed(int );
    void actualHealthPoint(int );
    void actualDefencePoint(int );
    void actualAttackPoint(int );
    void attackSel(int  );
    void restoreSF();
    Monster* getAdress() ;
    void fs_regulator(Attack* atk,Monster*);
    bool isDied() const;
    void attack(Monster* opponent ,std::string str);
    void setattacks (int ,std::string);
    void menuMonsters();
    int getAttaksNumber();
    std::string str();
    Attack* getAttackSelected();

    //getters
    int getPs() const;
    int getPa() const;
    int getPd() const;
    int getPv() const;
    std::string getName() const;
    int getId() const;
    private :
std::vector <Attack*> _attacks;
int _id;
std::string _name;
int _ps;
int _pa;
int _pd;
int _pv;
int _pa_beg;
int _pd_beg;
int _pv_beg;
Attack* _attack_selected;
};

#endif // MONSTER_H
