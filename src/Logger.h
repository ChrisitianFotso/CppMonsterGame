#ifndef LOGGER_H
#define LOGGER_H

#include<fstream>
#include<string>
#include<iostream>

class Logger
{
    public:
   Logger(std::string name , std::ofstream *file=NULL);

   template <class T>
   void msg(T message )
   {
   std::cout<<"["<<_name<<"] "<<message<<std::endl;
   *_file<<"["<<_name<<"] "<<message<<std::endl;
   }

  template <class T1,class T2>
  void msg(T1 message1 , T2 message2 )
  {
   std::cout<<"["<<_name<<"] "<<message1<<" : "<<message2<<std::endl;
   *_file<<"["<<_name<<"] "<<message1<<" : "<<message2<<std::endl;
  }

   template <class T3>
   void msgIo(T3 message )
   {
   std::cout<<"["<<_name<<"] "<<message<<std::endl;
   }

   template <class C1,class C2>
   void msgIo(C1 text1 , C2 text2)
   {
   std::cout<<"["<<_name<<"] "<<text1<<" : "<<text2<<std::endl;
   }

   template <class T4>
   void msgF(T4 message )
   {
   *_file<<"["<<_name<<"] "<<message<<std::endl;
   }

   template <class T5,class T6>
   void msgF(T5 message1 , T6 message2 )
   {
   *_file<<"["<<_name<<"] "<<message1<<" "<<message2<<std::endl;
   }

      template <class T7,class T8,class T9>
   void msgF(T7 message1 , T8 message2, T9 message3 )
   {

   *_file<<"["<<_name<<"] "<<message1<<" "<<message2<<" "<<message3<<std::endl;
   }

      template <class T10,class T11,class T12,class T13>
   void msgF(T10 message1 , T11 message2, T12 message3,T13 message4 )
   {

   *_file<<"["<<_name<<"] "<<message1<<" "<<message2<<" "<<message3<<" "<<message4<<std::endl;
   }

      template <class T14,class T15,class T16,class T17,class T18>
   void msgF(T14 message1 , T15 message2, T16 message3,T17 message4,T18 message5 )
   {

   *_file<<"["<<_name<<"] "<<message1<<" "<<message2<<" a "<<message3<<" "<<message4<<" "<<message5<<std::endl;
   }

 private:
 std:: ofstream *_file;
 std:: string _name ;

    private:
};

#endif // LOGGER_H






