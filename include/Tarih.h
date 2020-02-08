#ifndef TARIH_H
#define TARIH_H
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif
#ifndef STRING_H
#include <string.h>
#endif
#ifndef _STRING_
#include <string>
#endif
using namespace std;


class Zaman
{

private:

int MiliSaniye;
int Saniye;
int Dakika;
int Saat;

public:

 Zaman()
 {
	 MiliSaniye = 0;
	 Saniye = 0;
	 Dakika = 0;
	 Saat = 0;

 }

inline void msArttir()
{

 MiliSaniye++;
 
 if(MiliSaniye == 1000)
 {
	 MiliSaniye = 0;
	 Saniye++;
 }


 if(Saniye == 60)
 {
	 Saniye = 0;
	 Dakika++;
 }
 

 if(Dakika == 60)
 {
	 Dakika = 0;
	 Saat++;

 }


}


inline void snArttir()
{
	Saniye++;
	if(Saniye == 60)
	{
		Saniye = 0;
		Dakika++;
	}


	if(Dakika == 60)
	{
		Dakika = 0;
		Saat++;

	}
}

void Sifirla()
{
	MiliSaniye = 0;
	Saniye = 0;
	Dakika = 0;
	Saat = 0;
}

string StringCevir()
{
 string Donus = "";
 char* cevirmebuffer = (char*) malloc(sizeof(int)*8+1);
 
 Donus += "Saat :";
 Donus.append(itoa(Saat,cevirmebuffer,10));
 Donus+= " ";

 Donus+= "Dakika :";
 Donus.append(itoa(Dakika,cevirmebuffer,10));
 Donus+= " ";

 Donus+= "Saniye :";
 Donus.append(itoa(Saniye,cevirmebuffer,10));
 Donus+= " ";

 Donus+="Milisaniye :";
 Donus.append(itoa(MiliSaniye,cevirmebuffer,10));

 free(cevirmebuffer);
 return Donus;

}

};















class Tarih
{
private : SYSTEMTIME* tarih;



public:
	Tarih(const FILETIME tm)
	{
	 // Bellege yukle
	 tarih = (SYSTEMTIME*) malloc(sizeof(SYSTEMTIME)); 

	 // Kullanici  icin gercek zamana cevir
	 FileTimeToLocalFileTime(&tm,(LPFILETIME)&tm);
	 
	 FileTimeToSystemTime(&tm,tarih);
	
	}



public:
	Tarih(const FILETIME* tm)
	{
	 tarih = (SYSTEMTIME*) malloc(sizeof(SYSTEMTIME)); // Bellege yukle

	 // Kullanici  icin gercek zamana cevir
	 FileTimeToLocalFileTime(tm,(LPFILETIME)tm);

	 FileTimeToSystemTime(tm,tarih);
	}









// Standart olarak 'gg.aa.yyyy ss:dd'  Formatinda cevirir.  Yani : (Gun.Ay.Yýl Saat:Dakika (24 Saatlik sistem))
public:
	string StringCevir()
	{
		
	  string Tarihstr = "";
      char* cevirmebuffer = (char*) malloc(sizeof(int)*8+1);
	  
	  // Gun
	  if(tarih->wDay < 10)
		  Tarihstr.append("0");
	  Tarihstr.append(itoa(tarih->wDay,cevirmebuffer,10));
	  Tarihstr.append(".");

	  // Ay
	  if(tarih->wMonth < 10)
		  Tarihstr.append("0");
	  Tarihstr.append(itoa(tarih->wMonth,cevirmebuffer,10));
	  Tarihstr.append(".");

	  // Yil
	  Tarihstr.append(itoa(tarih->wYear,cevirmebuffer,10));

	  // Saat ve dakika icin bosluk
	  Tarihstr.append(" "); 

	  // Saat
	  if(tarih->wHour < 10)
		  Tarihstr.append("0");
	  Tarihstr.append(itoa(tarih->wHour,cevirmebuffer,10));
	  Tarihstr.append(":");

	  // Dakika
	  if(tarih->wMinute < 10)
		  Tarihstr.append("0");

	  Tarihstr.append(itoa(tarih->wMinute,cevirmebuffer,10));


	  return Tarihstr;
	}
};