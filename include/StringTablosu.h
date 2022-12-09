#ifndef STRINGTABLE_H
#define STRINGTABLE_H

#ifndef _INC_STRING
#include <string.h>
#endif

#ifndef  _IOSTREAM_
#include <iostream>
#endif
using namespace std;

#ifndef BYTE_H
#include <Byte.h>
#endif

#ifndef HAZIRFONKSIYONLAR_H
#include <HazirFonksiyonlar.h>
#endif


/*
======================================================================================================================================

Aciklama :
KONSOL VEYA HERHANGI BIR METIN BELGESI ICIN STRING TABLO CIZER
Konsol uygulamalarinda Konsol Bufferini Tabloya gore ayarlamak gerekiyor.

=========================================================================================
Ornegin:



StringTablo tablo;
tablo.SutunEkle("Personel");
tablo.SutunEkle("Soy Adi");

tablo.NesneEkle(0,"Mehmet Suleyman Abdullah");
tablo.NesneEkle(1,"Bilmemkim");

tablo.NesneEkle(0,"Fatih");
tablo.NesneEkle(1,"Ak");

// Konsolu tabloya gore ayarla
COORD cord;
cord.X = tablo.TabloGenislik;
cord.Y = tablo.TabloUzunluk;
SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),cord);

cout<<((string)tablo).c_str();


*/








typedef int Ilk_NesneOffset;


typedef struct StrSutun
{
 int Index;
 int Uzunluk;
 int EkUzunluk;
 int NesneSayisi;
 int OffsetSonrakiSutun;
 Ilk_NesneOffset   offsIlkNesne;
 char* Baslik;

};



typedef int Sonraki_NesneOffset;




typedef struct Nesne
{
	int Uzunluk;
	Sonraki_NesneOffset offsSonrakiNesne;
	char* Deger;
};








class StringTablo
{


int SutunSayisi;
int SutunlarArasiBosluk;

DWORD SonNesneOffset;
string TabloStr;

private:
bool IlkNesne;
Byte SutunList;
Byte SutunBilgileri;
Byte NesneBilgileri;

public:
	int TabloGenislik;
	int TabloUzunluk;



public: StringTablo()
	{
		SutunSayisi = 0;
		SutunList.Ekle(0);
		SonNesneOffset = 0;
		SutunlarArasiBosluk = 15;
		TabloGenislik = 0;
		TabloUzunluk = 0;
	}





public: void SutunEkle(string SutunAdi)
		{


		   int SutunBoyut = (sizeof(StrSutun)+SutunAdi.length()+1);
		   int Offset = (*(int*)SutunList[SutunSayisi*sizeof(int)]);
		   SutunBilgileri.BellekGenislet(SutunBoyut);


		   StrSutun* YeniSutun = ((StrSutun*)((char*)SutunBilgileri+Offset));
		   
		   
			  
		   YeniSutun->Uzunluk = SutunAdi.length();
		   YeniSutun->EkUzunluk = SutunlarArasiBosluk;
		   YeniSutun->OffsetSonrakiSutun = -1;
		   // Basligi kopyala 
		   SutunAdi.copy((char*) &YeniSutun->Baslik,SutunAdi.length());
		   
 // Eger Sutun sayisi 0 degil ise once ki sutuna kendi offsetini yaz ve onceki sutuna gore indexini hesapla.
		  if(SutunSayisi != 0)
		  {
			  StrSutun* oncekiSutun = SutunAl(SutunSayisi-1);
			  oncekiSutun->OffsetSonrakiSutun = Offset;
			  YeniSutun->Index = (oncekiSutun->Uzunluk + oncekiSutun->EkUzunluk + oncekiSutun->Index); 
		  }
		  else
			  YeniSutun->Index = 0;


		   SutunList.Ekle(Offset + SutunBoyut); // Sonra ki Sutun icin offset
		   SutunSayisi++;
		   
		   TabloyuCiz();
		}

public: void NesneEkle(int Index_Sutun,string Deger)
		{

			int NesneBoyut = (sizeof(Nesne)+ Deger.length()+1);
			StrSutun* Sutun = SutunAl(Index_Sutun);


			int Offset = SonNesneOffset;

			NesneBilgileri.BellekGenislet(NesneBoyut); 

			Nesne* yeniNesne =(Nesne*)((char*)NesneBilgileri+Offset);

			yeniNesne->Uzunluk = Deger.length();

			Deger.copy((char*) &yeniNesne->Deger,Deger.length());







			// Daha sonra sutuna eklenicek nesnen buraya baglanicak
			yeniNesne->offsSonrakiNesne = -1;








			//==================================================================================================================
			// Nesne sayisi 0 ise Sutunun ilk nesnesi olarak ata degil ise Bir önce ki nesnenin sonra ki offsetine kendini yaz.
			if(Sutun->NesneSayisi == 0)

				Sutun->offsIlkNesne = Offset;

			else
			{
				NesneAl(Index_Sutun,Sutun->NesneSayisi-1)->offsSonrakiNesne = Offset;

			}
			// =========================================================================================================

			int UzunlukFarki = yeniNesne->Uzunluk - (Sutun->Uzunluk + Sutun->EkUzunluk);
			if(UzunlukFarki >= 0)
			{
				Sutun->EkUzunluk += (UzunlukFarki) + Sutun->EkUzunluk;
				SutunIndexleriniYenile(Sutun,0);

			}


			SonNesneOffset = Offset + NesneBoyut;
			Sutun->NesneSayisi++;
			TabloyuCiz();
		}

public: StrSutun* SutunAl(int Index)
		{
			return(StrSutun*)((char*)SutunBilgileri+(*(int*)(SutunList[(Index*sizeof(int))])));
		}






// Herhangi bir sutunun Uzunlugu degistirildiginde diger sutunlari kaydirabilmek icin indexlerini degistirir
private: void SutunIndexleriniYenile(StrSutun* DegisenSutun,int EklenecekGenislik)
		{
		 

	     if(DegisenSutun->offsIlkNesne != -1)
		 {

			int i = SutunSayisi-1;
		    StrSutun* pSutun = SutunAl(i);
		  do
		  {
			  i--;
			  StrSutun* pOnceki = SutunAl(i);
			  pSutun->Index = (pOnceki->Uzunluk + pOnceki->EkUzunluk + pOnceki->Index);
			  pSutun = pOnceki;
			  

		  }
		   while(i > 0);


		 }

		}


private: Nesne* NesneAl(int Index_Sutun,int Index_Nesne)
		 {
			 if(Index_Sutun < SutunSayisi)
			 {
			 StrSutun* Sutun = SutunAl(Index_Sutun);
			 if(Index_Nesne < Sutun->NesneSayisi)
			 {
				 Nesne* pNesne =(Nesne*) NesneBilgileri[Sutun->offsIlkNesne];
				 for(int i = 0; i < Index_Nesne;i++)
				 {
					 pNesne = (Nesne*)((char*)NesneBilgileri+pNesne->offsSonrakiNesne);

				 }

				 return pNesne;

			 }

			 
			 }
				 return 0;



		 }


// Tabloyu cizen genel fonksiyon
private: void TabloyuCiz()
		 {
			 TabloGenislik = 0;
			 TabloUzunluk = 0;
			 TabloStr = "";
//=====================================================================================================================================
// Sutunlari Ciz
		  
		   for(int i = 0; i < SutunSayisi;i++)
		   {
			   StrSutun* cizilecekSutun = SutunAl(i);
			   
			   string Baslik = (char*) &cizilecekSutun->Baslik;
			   Baslik.append(cizilecekSutun->EkUzunluk,' ');
			   
			   TabloStr.insert(cizilecekSutun->Index,Baslik);

			   TabloGenislik += (cizilecekSutun->Uzunluk + cizilecekSutun->EkUzunluk);
		   }
		   TabloStr += "\n";
		   TabloUzunluk++;
//======================================================================================================================================
// Sutunlari Ciz






// Sutun alti ayraclarini ciz
// ==================================================================================================================================



// Satiri olustur
             

			  int Index_Sutun_Alti_Satir = TabloStr.length();

			  // Alt satir icin Alani onceden yarat
			  TabloStr.append(TabloGenislik,' ');
 			   

		   // Sutunlarin altinda Baslik altlarina '-' Ayraclarini ekle
		   
		   for(int i = 0; i < SutunSayisi;i++)
		   {
			   StrSutun* cizilecekSutun = SutunAl(i);

			   string SutunAlti = "";
			   SutunAlti.append(cizilecekSutun->Uzunluk,'-');
			   TabloStr.replace((Index_Sutun_Alti_Satir + cizilecekSutun->Index),cizilecekSutun->Uzunluk,SutunAlti);
		   }

// Sutun alti ayraclarini ciz
// ==================================================================================================================================






// Nesneleri ciz
// ==================================================================================================================================

		   // Nesneerin yaziacagi satirarin adeti
		   int SatirSayisi = -1;
		   
		   for(int i = 0; i < SutunSayisi;i++)
		   {

			StrSutun* Sutun = SutunAl(i);

			for(int n = 0; n < Sutun->NesneSayisi;n++)
			{

				int CizilecekSatirBaslangic = 0;
				// Nesnenin eklenecegi satir henuz yok satiri olustur ve offseti al
				if(SatirSayisi < n)
				{

				 
				 TabloStr+="\n";
				 CizilecekSatirBaslangic  = TabloStr.length();
				 TabloStr.append(TabloGenislik,' ');  

				 SatirSayisi++;
				 TabloUzunluk++;
				}
				// Satir var 
				else
				{
					// Sutun alti satirdan sonra n inci sirada ki satirin offsetini al
					CizilecekSatirBaslangic = KelimeBul("\n",TabloStr,n,Index_Sutun_Alti_Satir)+1;

				}


			   Nesne* cizilecekNesne = NesneAl(i,n);
			   TabloStr.replace((CizilecekSatirBaslangic + Sutun->Index),cizilecekNesne->Uzunluk,(char*) &cizilecekNesne->Deger);


			}




		   }

// Nesneleri ciz
// ==================================================================================================================================


	   TabloStr+= "\n";
	   TabloUzunluk++;
		TabloGenislik += 50;
		TabloUzunluk += 50;
// Tablo gorunumu bozulmamasi icin tablo sonuna yeni satir ekle



		 }



private: inline StrSutun* OfsettenSutunAl(int Offset)
		{
		  return(StrSutun*)((char*)SutunBilgileri+Offset);

		}





public:operator string(){
	return TabloStr;
}
public:
	~StringTablo()
	{
		SutunBilgileri.Kaldir();
		NesneBilgileri.Kaldir();
		SutunList.Kaldir();
	}
};


#endif
