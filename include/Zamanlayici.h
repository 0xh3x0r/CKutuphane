#ifndef ZAMANLAYICI_H
#define ZAMANLAYICI_H
#endif

#ifndef THREAD_H
#include <Thread.h>
#endif

#ifndef TARIH_H
#include <Tarih.h>
#endif







class Zamanlayici:public Zaman
{

Thread SaymaThread;
public: 
Zamanlayici():Zaman()
{

}


void Baslat()
{
   
   SaymaThread.Baslat(this,Say);

}

void Durdur()
{
  SaymaThread.Kaldir();

}




private:
	static void Say(Zamanlayici* Sayac)
	{

	 while(true)
	 {
	  Sayac->msArttir();
	  Sleep(1);
	 }


	 }

};