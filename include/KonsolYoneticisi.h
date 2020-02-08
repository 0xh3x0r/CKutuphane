#pragma once
#ifndef KONSOLYONETICISI_H
#define KONSOLYONETICISI_H
#endif

#ifndef HAZIRFONKSIYONLAR_H
#include <HazirFonksiyonlar.h>
#endif

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

using namespace std;

#ifndef _INC_STRING
#include <string.h>
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef _INC_IO
#include <io.h>
#endif

#ifndef  _INC_FCNTL
#include <fcntl.h>
#endif



typedef void (*KomutCallback)(vector<string> ParametreList);

class KonsolYoneticisi
{



private: HANDLE GirdiHandle;
private: HANDLE CiktiHandle;

vector<string> KomutList;
vector<int> ParametreAdetList;
vector<KomutCallback> KomutCallbackList;

public:
	// True yapilirsa konsol sonsuz donguden cikar veya KomutIsleme sadece bir kere yapilir
	bool KomutIslemeIptal;


public: KonsolYoneticisi()
		{
		  GirdiHandle = GetStdHandle(STD_INPUT_HANDLE);
		  CiktiHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		  KomutIslemeIptal =  false;
		  // Standart Komutlari ekle
		  KomutList.push_back("tmz");
		  KomutCallbackList.push_back(Komut_KonsolTemizle);
          ParametreAdetList.push_back(0);
		  
		  KomutList.push_back("cls");
		  KomutCallbackList.push_back(Komut_KonsolTemizle);
		  ParametreAdetList.push_back(0);

		  KomutList.push_back("cikis");
		  KomutCallbackList.push_back(Komut_Cikis);
		  ParametreAdetList.push_back(0);

		  KomutList.push_back("exit");
		  KomutCallbackList.push_back(Komut_Cikis);
		  ParametreAdetList.push_back(0);

		 bool Sonuc =  _setmode(_fileno(stdout),_O_U16TEXT);
		   if(Sonuc == false)
		   cout<<SonHataMesaji()<<"\r\n";
		}





public: bool KomutAta(string KomutAdi,int ParametreSayisi,KomutCallback fonksiyon)
		{
		 KomutList.push_back(KomutAdi);
		 ParametreAdetList.push_back(ParametreSayisi);
		 KomutCallbackList.push_back(fonksiyon);
		 return true;
		}


public: void KomutlariIsle()
		{
		
		   while(~KomutIslemeIptal)
		   {
			
			string Komut;
			wcout<<">";
			cin>>Komut;
			int AtananKomutSayisi = KomutList.size();
			bool KomutTanindi = false;
			for(int i = 0; i < AtananKomutSayisi;i++ )
			{
		     	if(Komut == KomutList[i])
				{
			     KomutTanindi = true;
				 getline(cin,Komut);


				 int ParametreSayisi = 0;
				 vector<string> GonderilecekParametreler;

				 int ParametreIndex = Komut.find(' ')+1;
				
				 while(ParametreIndex != 0)
				 {
					 Komut = Komut.substr(ParametreIndex,Komut.length());

					 GonderilecekParametreler.push_back(Komut);
					 ParametreIndex = Komut.find(' ',ParametreIndex)+1;
					 ParametreSayisi++;
				 }




				  if(ParametreSayisi == ParametreAdetList[i])
				  {
						KomutCallback CagrilacakParametre = KomutCallbackList[i];
					    wcout<<"\r\n";
						CagrilacakParametre(GonderilecekParametreler);
				  }
				  else
				  {

				  wcout<<"Hata : Göndermiþ Olduðunuz Parametre Sayýsý Uyuþmuyor!\r\n";
				  }


				
				
				
				}




			}

			if(KomutTanindi == false)
			{
				wcout<<L"Hata : Komut tanýnamadý\r\n";
			}


		}
		}


static void Komut_KonsolTemizle(vector<string> ParametreList)
{
			system("cls");
			
}



static void Komut_Cikis(vector<string> ParametreList)
{

		ExitProcess(0);
}

};