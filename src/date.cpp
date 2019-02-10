//
//  date.cpp
//  date
//
//  Created by Ludovico Russo on 18/03/15.
//  Copyright (c) 2015 Ludovico Russo. All rights reserved.
//

#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "date.h"

using namespace std;

int current_day() {
    time_t t = time(0);
    struct tm * now = localtime( & t );
    return now->tm_mday;
}

int current_month() {
    time_t t = time(0);
    struct tm * now = localtime( & t );
    return now->tm_mon + 1;
}

int current_year() {
    time_t t = time(0);
    struct tm * now = localtime( & t );
    return now->tm_year + 1900;
}

Date::Date():   _day(current_day()),
                _month(current_month()),
                _year(current_year())
{
}

Date::Date(const Date & to_copy):   _day(to_copy.day()),
                                    _month(to_copy.month()),
                                    _year(to_copy.year())
{
}

Date::Date(int d, int m, int y): _year(y),
                                 _month(m),
                                 _day(d)
{
    if ( !_isValid()) {
        throw std::invalid_argument("Date not valid!");
    }
}

// Getter Function
int Date::year() const {
    return _year;
}

int Date::month() const {
    return _month;
}
int Date::day() const {
    return _day;
}


int Date::yearsFrom(Date d ) const {
    int ret = d.year() - _year;
    if (d.month() < _month || (d.month() == _month && d.day() < _day) ) {
        ret--;
    }
    return ret;
}

std::string Date::str() const {
    std::stringstream ss;
    ss << setw(2) << setfill('0')<<_day << " " << setw(2) << setfill('0')<< _month << " " << setw(4) << _year;
    return ss.str();
}

bool Date::_isValid() const {
    if (_year < 1500) return false;
    if (_month > 12 || _month <1) return false;
    if (_day >31 || _day <1) return false;
    if (( _day ==31 && ( _month == 2 || _month == 4 || _month == 6 || _month == 9 || _month == 11) )) return false;
    if ( _day == 30 && _month == 2) return false;

    if ( _day == 29 && _month == 2 && (!(_year % 4 == 0) || (_year % 100 == 0))) return false;

    return true;
}
