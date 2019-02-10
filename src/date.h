#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include <string>
class Date {
public:

    // Dafault Constructor, set the date to the actual date
    Date();

    // Constructor, pass the date in the form of dd,mm,yyyy
    // Note that the program crashes if the date is not valid...
    Date(int d, int m, int y);

    // Copy Constructor
    Date(const Date & to_copy);


    // Getters
    int year() const;
    int month() const;
    int day() const;


    // return the year from the date d, if d it not passed, it returns the year from now.
    // Usefull to compute the age of a persone, where this is the person's birth date
    int yearsFrom(Date d=Date() ) const;

    // return the date as a string in the form dd/mm/yyyy
    // Useful to print on the screen
    std::string str() const;


private:
    bool _isValid() const;

    int _year;
    int _month;
    int _day;
};



#endif // DATE_H_INCLUDED
