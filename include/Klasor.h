#pragma once

#ifndef KLASOR_H
#define KLASOR_H
#endif
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#ifndef _INC_SHELLAPI
#include <ShellAPI.h>
#endif

#ifndef HAZIRFONKSIYONLAR_H
#include <HazirFonksiyonlar.h>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef ZAMANLAYICI_H
#include <Zamanlayici.h>
#endif
using namespace std;
typedef int FiltreDahil;
typedef int FiltreHaric;








// Klasor Nesnesinin uzaktan aktarilmasi icin nesneleri barindiran metin
// Eger Klasor Nesnesine bu struct atanýr ise Klasor Nesnesi struct u olusturan Klasor Nesnesinin bir kopyasi olur.
typedef struct KlasorString 
{

string Veri;


KlasorString(string Param)
{
 Veri = Param;
}


KlasorString(void)
{

Veri = "";

}

operator string()
{

 return Veri;

}

};



//======================================================< TIPLER >=========================================================


typedef struct TasimaRutiniParametrer
{

 string  KaynakYol;
 string  HedefYol;
 ULONG Islenen;
 ULONGLONG Toplam;
 DWORD CagrilmaNedeni;
 void* EkParam;
}KopyalamaRutiniParametreler;


// ============================================ Parametre CagrilmaNedeni Sabitler ==========================================

        #define DOSYA_MEVCUT       0
        #define KOPYALAMA_BASARILI 1
        #define KOPYALAMA_BITTI	   2




// ==================================================================================================================================





// Islem tamamlandiginda cagrilir.
// Baska Nesnelerden islem hakkinda bilgi almak icin kullanilabilir
// Eger false doner ise bir sonra ki islem iptal edilir
// True doner ise islem tamamlanana kadar veya iptal edilene kadar devam eder.
typedef int(*KopyalamaCallback)(KopyalamaRutiniParametreler& Params );


// ============================================ Kopyalama Callback Geri Donus Sabitleri  =============================================
       
            #define KOPYALAMA_IPTAL            0
            #define KOPYALAMA_DEVAM            1
            #define KOPYALAMA_TUMUNE_EVET      2

// ===================================================================================================================================





typedef struct TasimaIslemiParametreler
{
	vector<string> DosyaYoluList;
	vector<string> KlasorYoluList;
	string HedefKlasor;
	bool UzerineYaz;
	void* EkParams;
	

};

typedef struct KopyalamaIslemiParametreler : TasimaIslemiParametreler
{
	KopyalamaCallback Kopyalama_Callback;

};























// Dosya-Klasor ozellikleri

#define OZELLIK_SADECEOKUNUR            0x00000001  
#define OZELLIK_GIZLI                   0x00000002
#define OZELLIK_SISTEM                  0x00000004  
#define OZELLIK_KLASOR                  0x00000010  
#define OZELLIK_ARSIV                   0x00000020     
#define OZELLIK_DONANIM                 0x00000040  
#define OZELLIK_NORMAL                  0x00000080  
#define OZELLIK_GECICI                  0x00000100  
#define OZELLIK_SIKISTIRILMIS           0x00000800  
#define OZELLIK_CEVRIMDISI              0x00001000  
#define OZELLIK_SIRALANMAMISICERIK      0x00002000  
#define OZELLIK_SIFRELI                 0x00004000  



typedef struct StrKlasorElementi
{
	string Ad;
	DWORD Boyut;
	DWORD Ozellikler;
	FILETIME OlusturmaTarihi;
	FILETIME SonYazmaTarihi;
	FILETIME SonErisimTarihi;
}StrDosya,StrKlasor;





typedef struct KlasorIcerik
{
	vector<StrDosya> Dosyalar;
	vector<StrKlasor> Klasorler;

};















static bool KlasorListele(string HedefKlasor,KlasorIcerik& klasorIcerik)
{


	WIN32_FIND_DATAA FindFileData;
	HedefKlasor.append("*");
	HANDLE hAra = INVALID_HANDLE_VALUE;
	hAra = FindFirstFileA(HedefKlasor.c_str(),&FindFileData);
	HedefKlasor.erase(HedefKlasor.length()-1,1);
	if(hAra == INVALID_HANDLE_VALUE)
		return false;

	if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{

		// '.' ve '..' Klasorlerini gosterme
		if(!((strcmp(FindFileData.cFileName,".") == 0) || (strcmp(FindFileData.cFileName,"..") == 0)))
		{

			StrKlasor klasor;

			klasor.Ad = FindFileData.cFileName;
			klasor.Boyut = FindFileData.nFileSizeHigh;

			klasor.OlusturmaTarihi = FindFileData.ftCreationTime;
			klasor.SonErisimTarihi = FindFileData.ftLastAccessTime;
			klasor.SonYazmaTarihi =  FindFileData.ftLastWriteTime;
			klasor.Ozellikler = FindFileData.dwFileAttributes;

			klasorIcerik.Klasorler.push_back(klasor);


		}


	}
	else
	{
		StrDosya dosya;

		dosya.Ad = FindFileData.cFileName;
		dosya.Boyut = FindFileData.nFileSizeLow;

		dosya.OlusturmaTarihi = FindFileData.ftCreationTime;
		dosya.SonErisimTarihi = FindFileData.ftLastAccessTime;
		dosya.SonYazmaTarihi =  FindFileData.ftLastWriteTime;
		dosya.Ozellikler = FindFileData.dwFileAttributes;

		klasorIcerik.Dosyalar.push_back(dosya);
	}








	while(FindNextFileA(hAra,&FindFileData) != 0)
	{

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

			// '.' ve '..' Klasorlerini gosterme
			if(!((strcmp(FindFileData.cFileName,".") == 0) || (strcmp(FindFileData.cFileName,"..") == 0)))
			{

				StrKlasor klasor;

				klasor.Ad = FindFileData.cFileName;
				klasor.Boyut = FindFileData.nFileSizeHigh;

				klasor.OlusturmaTarihi = FindFileData.ftCreationTime;
				klasor.SonErisimTarihi = FindFileData.ftLastAccessTime;
				klasor.SonYazmaTarihi =  FindFileData.ftLastWriteTime;
				klasor.Ozellikler = FindFileData.dwFileAttributes;

				klasorIcerik.Klasorler.push_back(klasor);

			}


		}
		else
		{
			StrDosya dosya;

			dosya.Ad = FindFileData.cFileName;
			dosya.Boyut = FindFileData.nFileSizeLow;

			dosya.OlusturmaTarihi = FindFileData.ftCreationTime;
			dosya.SonErisimTarihi = FindFileData.ftLastAccessTime;
			dosya.SonYazmaTarihi =  FindFileData.ftLastWriteTime;
			dosya.Ozellikler = FindFileData.dwFileAttributes;

			klasorIcerik.Dosyalar.push_back(dosya);
		}
	}

	FindClose(hAra);


	return true;


}


static ULONGLONG KlasorBoyutuHesapla(string HedefKlasor)
{
	KlasorIcerik icerik;

	ULONGLONG Boyut = 0;

	if(KlasorListele(HedefKlasor,icerik))
	{


		int DosyaSayisi = icerik.Dosyalar.size();

		for(int i = 0; i < DosyaSayisi;i++)
		{
			Boyut += icerik.Dosyalar[i].Boyut;
		}



		int KlasorSayisi = icerik.Klasorler.size();



		for(int i = 0; i < KlasorSayisi;i++)
		{

			string AltKlasor = HedefKlasor;
			AltKlasor += icerik.Klasorler[i].Ad;
			AltKlasor += "\\";

			Boyut += KlasorBoyutuHesapla(AltKlasor);


		}




	}


	return Boyut;
}

static ULONGLONG KlasorBoyutuHesapla(vector<string> KlasorList)
{
	ULONGLONG Boyut = 0;
	int Adet = KlasorList.size();


	for(int i = 0; i < Adet; i++)
	{

		Boyut += KlasorBoyutuHesapla(KlasorList[i]);

	}
	return Boyut;
}

static inline ULONGLONG DosyaBoyutuHesapla(vector<StrDosya> DosyaOzellikleri)
{
	ULONGLONG Boyut = 0;
	int DosyaSayisi = DosyaOzellikleri.size();

	for(int i = 0; i < DosyaSayisi; i++ )
	{
		Boyut += DosyaOzellikleri[i].Boyut;
	}

   return Boyut;
}

static string DosyaAdiAl(string DosyaYolu)
{
	string Donus = "";

	int Index = DosyaYolu.rfind("\\")+1;


	if(Index > 0)
		Donus = DosyaYolu.substr(Index,DosyaYolu.length());


	return Donus;
}

inline static bool DosyaOzellikleriAl(string DosyaYolu,StrDosya&  DosyaOzellikleri)
{
	WIN32_FILE_ATTRIBUTE_DATA dosyaOzellikleri;
	if(GetFileAttributesEx(DosyaYolu.c_str(), GetFileExInfoStandard,&dosyaOzellikleri))
	{

	 DosyaOzellikleri;

	DosyaOzellikleri.Ad = DosyaAdiAl(DosyaYolu);
	DosyaOzellikleri.Boyut = dosyaOzellikleri.nFileSizeLow;
	DosyaOzellikleri.OlusturmaTarihi = dosyaOzellikleri.ftCreationTime;
	DosyaOzellikleri.SonErisimTarihi = dosyaOzellikleri.ftLastAccessTime;
	DosyaOzellikleri.SonYazmaTarihi = dosyaOzellikleri.ftLastAccessTime;
	DosyaOzellikleri.Ozellikler = dosyaOzellikleri.dwFileAttributes;
	return true;

	}

	else
	{

		return false;

	}
}



inline static bool DosyaOzellikleriAl(vector<string> DosyaYoluList,vector<StrDosya>& DosyaOzellikleriList)
{
	int Adet = DosyaYoluList.size();

	for(int i = 0; i  < Adet ;i++)
	{

		 StrDosya DosyaOzellikleri;
		if(DosyaOzellikleriAl(DosyaYoluList[i],DosyaOzellikleri))
		{

		  DosyaOzellikleriList.push_back(DosyaOzellikleri);


		}
		else
			return false;

	}

	 return true;
}



static string KlasorAdiAl(string KlasorYolu)
{

	string KlasorAdi = "";			

	int SonKlasorIndex = KlasorYolu.rfind("\\",KlasorYolu.find_last_of("\\")-1);

	if(SonKlasorIndex > -1)
		KlasorAdi = KlasorYolu.substr(SonKlasorIndex+1,(KlasorYolu.find_last_of("\\")-SonKlasorIndex)-1);

	return KlasorAdi;
}






static bool DosyaKopyala(vector<string> KaynakDosyaYolu,string HedefKlasorYolu,bool& Tumune_Evet,KopyalamaCallback Kopyalama_Callback = NULL,void* EkParam = NULL,ULONGLONG ToplamBoyut = 0)
{

	 vector<StrDosya> Dosyalar;
	DosyaOzellikleriAl(KaynakDosyaYolu,Dosyalar);

	int DosyaSayisi = Dosyalar.size();

	for(int i = 0; i < DosyaSayisi;i++)
	{
		
	

        string HedefDosyaYolu = HedefKlasorYolu;
	    HedefDosyaYolu += Dosyalar[i].Ad;

		if(CopyFileA(KaynakDosyaYolu[i].c_str(),HedefDosyaYolu.c_str(),(!Tumune_Evet)))
		{

			if(Kopyalama_Callback != NULL)
			{

				KopyalamaRutiniParametreler params;

				params.HedefYol = HedefDosyaYolu;
				params.KaynakYol = KaynakDosyaYolu[i];
				params.CagrilmaNedeni = KOPYALAMA_BASARILI;
				params.Islenen = Dosyalar[i].Boyut;
				params.Toplam  = ToplamBoyut;
				params.EkParam = EkParam;


				int GeriDonus = Kopyalama_Callback(params);

				if(GeriDonus == KOPYALAMA_IPTAL)
					return false;




			}


		}
		else if((GetLastError() == ERROR_FILE_EXISTS))
		{


			if( Kopyalama_Callback != NULL )


			{


				KopyalamaRutiniParametreler params;

				params.HedefYol = HedefDosyaYolu;
				params.KaynakYol = KaynakDosyaYolu[i];
				params.CagrilmaNedeni = DOSYA_MEVCUT;
				params.Islenen = Dosyalar[i].Boyut;
				params.Toplam  = ToplamBoyut;
				params.EkParam = EkParam;


				int Cevap = Kopyalama_Callback(params);

				if(Cevap == KOPYALAMA_IPTAL)
					return false; 


				if(Cevap == KOPYALAMA_TUMUNE_EVET)
					Tumune_Evet = true;


				if(CopyFileA(KaynakDosyaYolu[i].c_str(),HedefDosyaYolu.c_str(),false))
				{
					params.CagrilmaNedeni = KOPYALAMA_BASARILI;

					Cevap =  Kopyalama_Callback(params);
					if(Cevap == KOPYALAMA_IPTAL)
						return false;

				}


			}

			else
				return false;

		}
		else
			return false;
	}


	 return true;
}

static bool KlasorKopyala(string KaynakKlasorYolu,string HedefKlasorYolu,bool& Tumune_Evet,bool UzerineYaz = FALSE,ULONGLONG TasinacakDosyalarBoyut = 0,KopyalamaCallback Kopyalama_Callback = NULL,void* EkParam = NULL)
{
	string KlasorAdi = KlasorAdiAl(KaynakKlasorYolu);

	if(KlasorAdi == "")
		return false;

	string YeniKlasorYolu = HedefKlasorYolu;
	YeniKlasorYolu += KlasorAdi;
	YeniKlasorYolu += "\\";
	CreateDirectoryA(YeniKlasorYolu.c_str(),NULL);


	KlasorIcerik kaynakKlasorIcerik;

	KlasorListele(KaynakKlasorYolu,kaynakKlasorIcerik);

	int KlasorSayisi = kaynakKlasorIcerik.Klasorler.size();


	for(int i = 0; i < KlasorSayisi;i++)
	{
		string AltKlasorYolu = KaynakKlasorYolu;
		AltKlasorYolu += kaynakKlasorIcerik.Klasorler[i].Ad;
		AltKlasorYolu+= "\\";

		if(!KlasorKopyala(AltKlasorYolu,YeniKlasorYolu,Tumune_Evet,UzerineYaz,TasinacakDosyalarBoyut,Kopyalama_Callback,EkParam))
			return false;
	}


	int DosyaSayisi = kaynakKlasorIcerik.Dosyalar.size();

	for(int i = 0; i < DosyaSayisi;i++)
	{
		string KaynakDosyaYolu = KaynakKlasorYolu;
		string HedefDosyaYolu = YeniKlasorYolu;



		KaynakDosyaYolu += kaynakKlasorIcerik.Dosyalar[i].Ad;
		HedefDosyaYolu += kaynakKlasorIcerik.Dosyalar[i].Ad;



		if(CopyFileA(KaynakDosyaYolu.c_str(),HedefDosyaYolu.c_str(),(!Tumune_Evet)))
		{

			if(Kopyalama_Callback != NULL)
			{

				KopyalamaRutiniParametreler params;

				params.HedefYol = HedefDosyaYolu;
				params.KaynakYol = KaynakDosyaYolu;
				params.CagrilmaNedeni = KOPYALAMA_BASARILI;
				params.Islenen = kaynakKlasorIcerik.Dosyalar[i].Boyut;
				params.Toplam  = TasinacakDosyalarBoyut;
				params.EkParam = EkParam;


				int GeriDonus = Kopyalama_Callback(params);

				if(GeriDonus == KOPYALAMA_IPTAL)
					return false;




			}


		}
		else if((GetLastError() == ERROR_FILE_EXISTS))
		{


			if( Kopyalama_Callback != NULL )


			{


				KopyalamaRutiniParametreler params;

				params.HedefYol = HedefDosyaYolu;
				params.KaynakYol = KaynakDosyaYolu;
				params.CagrilmaNedeni = DOSYA_MEVCUT;
				params.Islenen = kaynakKlasorIcerik.Dosyalar[i].Boyut;
				params.Toplam  = TasinacakDosyalarBoyut;
				params.EkParam = EkParam;


				int Cevap = Kopyalama_Callback(params);

				if(Cevap == KOPYALAMA_IPTAL)
					return false; 


				if(Cevap == KOPYALAMA_TUMUNE_EVET)
					Tumune_Evet = true;


				if(CopyFileA(KaynakDosyaYolu.c_str(),HedefDosyaYolu.c_str(),false))
				{
					params.CagrilmaNedeni = KOPYALAMA_BASARILI;

					Cevap =  Kopyalama_Callback(params);
					if(Cevap == KOPYALAMA_IPTAL)
						return false;

				}


			}

			else
				return false;

		}
		else
			return false;
	}

	 return true;
}



static bool KlasorDosyaKopyala(KopyalamaIslemiParametreler& Params)
{

  vector<StrDosya> DosyaOzellikleri;
  DosyaOzellikleriAl(Params.DosyaYoluList,DosyaOzellikleri);

  ULONGLONG ToplamBoyut = DosyaBoyutuHesapla(DosyaOzellikleri);
  ToplamBoyut += KlasorBoyutuHesapla(Params.KlasorYoluList);

  if(!DosyaKopyala(Params.DosyaYoluList,Params.HedefKlasor,Params.UzerineYaz,Params.Kopyalama_Callback,Params.EkParams,ToplamBoyut))
	  return false;

  int KlasorSayisi = Params.KlasorYoluList.size();

  for(int i = 0; i < KlasorSayisi;i++ )
  {
	  if(!KlasorKopyala(Params.KlasorYoluList[i],Params.HedefKlasor,Params.UzerineYaz,false,ToplamBoyut,Params.Kopyalama_Callback,Params.EkParams))
		  return false;
  }

  KopyalamaRutiniParametreler callBackParams;
  
  
  callBackParams.HedefYol = "";
  callBackParams.KaynakYol = "";
  callBackParams.Islenen = 0;
  callBackParams.Toplam = 0;

  callBackParams.EkParam = Params.EkParams;

  callBackParams.CagrilmaNedeni = KOPYALAMA_BITTI;

  Params.Kopyalama_Callback(callBackParams);


  free(&Params);
  return true;


}















class Klasor
{
public:
vector<string> DosyaAdlari;
public:
vector<DWORD> DosyaBoyutlari;
public:
vector<DWORD> DosyaOzellikleri;
public:
vector<FILETIME> DosyaOlusturmaTarihi;
public:
vector<FILETIME> DosyaSonYazmaTarihi;
public:
vector<FILETIME> DosyaSonErisimTarihi;
public:
vector<string> KlasorAdlari;
public:
vector<DWORD> KlasorBoyutlari;
public:
vector<DWORD> KlasorOzellikleri;
public:
vector<FILETIME> KlasorOlusturmaTarihi;
public:
vector<FILETIME> KlasorSonYazmaTarihi;
public:
vector<FILETIME> KlasorSonErisimTarihi;
public:
 string Adres;
public:
 string veri;

public: Klasor(void)
		{
			Adres = "";
			veri = "";
		}

public: Klasor(const char* _Adres)
{
Adres = _Adres;

}

public: Klasor(string _Adres)
{
Adres = _Adres;

}

public: Klasor(KlasorString strveri)
{
Cevir(strveri);
	
}


public: void KlasorStringOlustur()
	{
		veri = "";
		int KlasorSayisi = KlasorAdlari.size();
		int DosyaSayisi = DosyaAdlari.size();
	
	for(int i = 0; i < KlasorSayisi;i++)
	{
		veri += "tp:k;";
		veri += "ad:"; 
		veri+= KlasorAdlari[i];
		veri+= ";";
        
		veri+= "ozlk:";
		veri+= ulong_str(KlasorOzellikleri[i]);
		veri += ";";

		veri+= "byt:";
		veri+= ulong_str(KlasorBoyutlari[i]);
		veri+= ";"; 
		veri+= "otrh:";
		veri+= ulong_str(KlasorOlusturmaTarihi[i].dwHighDateTime);
		veri+= "||";
		veri+= ulong_str(KlasorOlusturmaTarihi[i].dwLowDateTime);
		veri+=";";


		veri+= "sytrh:";
		veri+= ulong_str(KlasorSonYazmaTarihi[i].dwHighDateTime);
		veri+= "||";
		veri+= ulong_str(KlasorSonYazmaTarihi[i].dwLowDateTime);
		veri+= ";";

		veri+= "setrh:";
		veri+= ulong_str(KlasorSonErisimTarihi[i].dwHighDateTime);
		veri+= "||";
		veri+= ulong_str(KlasorSonErisimTarihi[i].dwLowDateTime);
		veri+=";";
		veri += "\r\n";


	}



		for(int i = 0; i < DosyaSayisi;i++)
	{
		veri += "tp:d;";
		veri += "ad:"; 
		veri+= DosyaAdlari[i];
		veri+= ";";
        
		veri+= "ozlk:";
		veri+= ulong_str(DosyaOzellikleri[i]);
		veri += ";";

		veri+= "byt:";
		veri += ulong_str(DosyaBoyutlari[i]);
		veri+=";";

		veri+= "otrh:";
		veri+= ulong_str(DosyaOlusturmaTarihi[i].dwHighDateTime);
		veri+= "||";
		veri+= ulong_str(DosyaOlusturmaTarihi[i].dwLowDateTime);
		veri+=";";


		veri+= "sytrh:";
		veri+= ulong_str(DosyaSonYazmaTarihi[i].dwHighDateTime);
		veri+= "||";
		veri+= ulong_str(DosyaSonYazmaTarihi[i].dwLowDateTime);
		veri+= ";";

		veri+= "setrh:";
		veri+= ulong_str(DosyaSonErisimTarihi[i].dwHighDateTime);
		veri+= "||";
		veri+= ulong_str(DosyaSonErisimTarihi[i].dwLowDateTime);
		veri+=";";
		veri += "\r\n";


	}

}












public: bool Cevir(string strveri)
{
	string Satýr = "";
	int index = 0;
	int Boyut = strveri.size();
	while(index < Boyut || index != -1)
	{

	index = KelimeArasi("tp:","\r\n",strveri,Satýr,index);
	if(index == -1)
    return false;

	if((Satýr.compare(0,2,"k;") == 0))
	{
		int index_satir = Satýr.find(";");
		if(index_satir == -1)
        return false;
		string KlasorAdi = "";
		
		index_satir = KelimeArasi("ad:",";",Satýr,KlasorAdi,index_satir);
	    if(index_satir == -1)
        return false;
		KlasorAdlari.push_back(KlasorAdi);

		string KlasorOzellik = "";
		index_satir = KelimeArasi("ozlk:",";",Satýr,KlasorOzellik,index_satir);
	    if(index_satir == -1)
        return false;
		KlasorOzellikleri.push_back(str_ulong(KlasorOzellik));

		string KlasorBoyut = "";
		index_satir = KelimeArasi("byt:",";",Satýr,KlasorBoyut,index_satir);
	    if(index_satir == -1)
        return false;		
		KlasorBoyutlari.push_back(str_ulong(KlasorBoyut));

		string KlasorOlusturmaTarihiHigh = "";
		index_satir = KelimeArasi("otrh:","|",Satýr,KlasorOlusturmaTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;		
		FILETIME ftKlasorOlusturmaTarihi;
		ftKlasorOlusturmaTarihi.dwHighDateTime = str_ulong(KlasorOlusturmaTarihiHigh);

	    string KlasorOlusturmaTarihiLow = "";
		index_satir = KelimeArasi("|",";",Satýr,KlasorOlusturmaTarihiLow,index_satir);
	    if(index_satir == -1)
        return false;		
		ftKlasorOlusturmaTarihi.dwLowDateTime = str_ulong(KlasorOlusturmaTarihiLow);
		KlasorOlusturmaTarihi.push_back(ftKlasorOlusturmaTarihi);
	    
		
		
		
		string KlasorSonYazmaTarihiHigh = "";
		index_satir = KelimeArasi("sytrh:","|",Satýr,KlasorSonYazmaTarihiHigh,index_satir);
        if(index_satir == -1)
        return false;		
		FILETIME ftKlasorSonYazmaTarihi;
		ftKlasorSonYazmaTarihi.dwHighDateTime = str_ulong(KlasorSonYazmaTarihiHigh);

	    string KlasorSonYazmaTarihiLow = "";
		index_satir = KelimeArasi("|",";",Satýr,KlasorSonYazmaTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;
		ftKlasorSonYazmaTarihi.dwLowDateTime = str_ulong(KlasorSonYazmaTarihiLow);
		KlasorSonYazmaTarihi.push_back(ftKlasorSonYazmaTarihi);



		string KlasorSonErisimTarihiHigh = "";
		index_satir = KelimeArasi("setrh:","|",Satýr,KlasorSonErisimTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;		
		FILETIME ftKlasorSonErisimTarihi;
		ftKlasorSonErisimTarihi.dwHighDateTime = str_ulong(KlasorSonErisimTarihiHigh);

	    string KlasorSonErisimTarihiLow = "";
		index_satir = KelimeArasi("|",";",Satýr,KlasorSonErisimTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;
		ftKlasorSonErisimTarihi.dwLowDateTime = str_ulong(KlasorSonErisimTarihiLow);
		KlasorSonErisimTarihi.push_back(ftKlasorSonErisimTarihi);
	}
	else if((Satýr.compare(0,2,"d;") == 0))
	{
		int index_satir = Satýr.find(";");
		string DosyaAdi = "";
		
		index_satir = KelimeArasi("ad:",";",Satýr,DosyaAdi,index_satir);
		if(index_satir == -1)
        return false;
		DosyaAdlari.push_back(DosyaAdi);

		string DosyaOzellik = "";
		index_satir = KelimeArasi("ozlk:",";",Satýr,DosyaOzellik,index_satir);
	    if(index_satir == -1)
        return false;
		DosyaOzellikleri.push_back(str_ulong(DosyaOzellik));

		string DosyaBoyut = "";
		index_satir = KelimeArasi("byt:",";",Satýr,DosyaBoyut,index_satir);
	    if(index_satir == -1)
        return false;
		DosyaBoyutlari.push_back(str_ulong(DosyaBoyut));

		string DosyaOlusturmaTarihiHigh = "";
		index_satir = KelimeArasi("otrh:","|",Satýr,DosyaOlusturmaTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;		
		FILETIME ftDosyaOlusturmaTarihi;
		ftDosyaOlusturmaTarihi.dwHighDateTime = str_ulong(DosyaOlusturmaTarihiHigh);

	    string DosyaOlusturmaTarihiLow = "";
		index_satir = KelimeArasi("|",";",Satýr,DosyaOlusturmaTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;
		ftDosyaOlusturmaTarihi.dwLowDateTime = str_ulong(DosyaOlusturmaTarihiLow);
		DosyaOlusturmaTarihi.push_back(ftDosyaOlusturmaTarihi);
	    
		
		
		
		string DosyaSonYazmaTarihiHigh = "";
		index_satir = KelimeArasi("sytrh:","|",Satýr,DosyaSonYazmaTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;		
		FILETIME ftDosyaSonYazmaTarihi;
		ftDosyaSonYazmaTarihi.dwHighDateTime = str_ulong(DosyaSonYazmaTarihiHigh);

	    string DosyaSonYazmaTarihiLow = "";
		index_satir = KelimeArasi("|",";",Satýr,DosyaSonYazmaTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;
		ftDosyaSonYazmaTarihi.dwLowDateTime = str_ulong(DosyaSonYazmaTarihiLow);
		DosyaSonYazmaTarihi.push_back(ftDosyaSonYazmaTarihi);



		string DosyaSonErisimTarihiHigh = "";
		index_satir = KelimeArasi("setrh:","|",Satýr,DosyaSonErisimTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;		
		FILETIME ftDosyaSonErisimTarihi;
		ftDosyaSonErisimTarihi.dwHighDateTime = str_ulong(DosyaSonErisimTarihiHigh);

	    string DosyaSonErisimTarihiLow = "";
		index_satir = KelimeArasi("|",";",Satýr,DosyaSonErisimTarihiHigh,index_satir);
	    if(index_satir == -1)
        return false;
		ftDosyaSonErisimTarihi.dwLowDateTime = str_ulong(DosyaSonErisimTarihiLow);
		DosyaSonErisimTarihi.push_back(ftDosyaSonErisimTarihi);
	}
	}
return true;
}







private : inline void ÝcerikTemizle()
{
	veri = "";
	vector<string>().swap(KlasorAdlari);
	vector<DWORD>().swap(KlasorBoyutlari);
	vector<DWORD>().swap(KlasorOzellikleri);
	KlasorOlusturmaTarihi.clear();
	KlasorSonErisimTarihi.clear();
	KlasorSonYazmaTarihi.clear();
	DosyaAdlari.clear();
	DosyaBoyutlari.clear();
	DosyaOzellikleri.clear();
	DosyaOlusturmaTarihi.clear();
	DosyaSonErisimTarihi.clear();
	DosyaSonYazmaTarihi.clear();


}



public:
	bool Listele()
	{
	ÝcerikTemizle();
    WIN32_FIND_DATAA FindFileData;
	Adres.append("*");
	HANDLE hAra = INVALID_HANDLE_VALUE;
	hAra = FindFirstFileA(Adres.c_str(),&FindFileData);
	Adres.erase(Adres.length()-1,1);
	if(hAra == INVALID_HANDLE_VALUE)
		return false;



		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		
		 // '.' ve '..' Klasorlerini gosterme
		 if(!((strcmp(FindFileData.cFileName,".") == 0) || (strcmp(FindFileData.cFileName,"..") == 0)))
		 {
	     
		 KlasorAdlari.push_back(FindFileData.cFileName);
	     KlasorBoyutlari.push_back(FindFileData.nFileSizeLow);
		 KlasorOzellikleri.push_back(FindFileData.dwFileAttributes);
		 KlasorOlusturmaTarihi.push_back(FindFileData.ftCreationTime);
		 KlasorSonErisimTarihi.push_back(FindFileData.ftLastAccessTime);
		 KlasorSonYazmaTarihi.push_back(FindFileData.ftLastWriteTime);
		 
		 }
		
		
		}
		else
		{
         DosyaAdlari.push_back(FindFileData.cFileName);
	     DosyaBoyutlari.push_back(FindFileData.nFileSizeLow);
		 DosyaOzellikleri.push_back(FindFileData.dwFileAttributes);
		 DosyaOlusturmaTarihi.push_back(FindFileData.ftCreationTime);
		 DosyaSonErisimTarihi.push_back(FindFileData.ftLastAccessTime);
		 DosyaSonYazmaTarihi.push_back(FindFileData.ftLastWriteTime);
		}








	while(FindNextFileA(hAra,&FindFileData) != 0)
	{
		
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

					 // '.' ve '..' Klasorlerini gosterme
		 if(!((strcmp(FindFileData.cFileName,".") == 0) || (strcmp(FindFileData.cFileName,"..") == 0)))
		 {
	     
		 KlasorAdlari.push_back(FindFileData.cFileName);
	     KlasorBoyutlari.push_back(FindFileData.nFileSizeLow);
		 KlasorOzellikleri.push_back(FindFileData.dwFileAttributes);
		 KlasorOlusturmaTarihi.push_back(FindFileData.ftCreationTime);
		 KlasorSonErisimTarihi.push_back(FindFileData.ftLastAccessTime);
		 KlasorSonYazmaTarihi.push_back(FindFileData.ftLastWriteTime);
		 
		 }


		}
		else
		{
         DosyaAdlari.push_back(FindFileData.cFileName);
	     DosyaBoyutlari.push_back(FindFileData.nFileSizeLow);
		 DosyaOzellikleri.push_back(FindFileData.dwFileAttributes);
		 DosyaOlusturmaTarihi.push_back(FindFileData.ftCreationTime);
		 DosyaSonErisimTarihi.push_back(FindFileData.ftLastAccessTime);
		 DosyaSonYazmaTarihi.push_back(FindFileData.ftLastWriteTime);
		}
	}

	FindClose(hAra);

	if((KlasorOzellikleri.size() || KlasorOzellikleri.size()))
	KlasorStringOlustur();

	// Bos oldugunu belirt rnVeri gonderen socketlerde hata olmamasi icin.Fonksiyonun true donmesi klasorun var oldugu anlamina geliyor fakat Veri bos olursa uzaktan aktarmada sorun oluyor
	else
		veri = "BOS\r\n";
	
	
	return true;
	}



public:
	bool Listele(FiltreDahil FILTRE_DAHIL,FiltreHaric FILTRE_HARIC)
	{
		ÝcerikTemizle();
		WIN32_FIND_DATAA FindFileData;
		Adres.append("*");
		HANDLE hAra = INVALID_HANDLE_VALUE;
		hAra = FindFirstFileA(Adres.c_str(),&FindFileData);
		Adres.erase(Adres.length()-1,1);
		if(hAra == INVALID_HANDLE_VALUE)
			return false;



		if( (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&  (FindFileData.dwFileAttributes && FILTRE_DAHIL) && (!(FindFileData.dwFileAttributes & FILTRE_HARIC) ) )
		{

			// '.' ve '..' Klasorlerini gosterme
			if(!((strcmp(FindFileData.cFileName,".") == 0) || (strcmp(FindFileData.cFileName,"..") == 0)))
			{

				KlasorAdlari.push_back(FindFileData.cFileName);
				KlasorBoyutlari.push_back(FindFileData.nFileSizeHigh);
				KlasorOzellikleri.push_back(FindFileData.dwFileAttributes);
				KlasorOlusturmaTarihi.push_back(FindFileData.ftCreationTime);
				KlasorSonErisimTarihi.push_back(FindFileData.ftLastAccessTime);
				KlasorSonYazmaTarihi.push_back(FindFileData.ftLastWriteTime);

			}


		}
		else if((FindFileData.dwFileAttributes & FILTRE_DAHIL) && (!(FindFileData.dwFileAttributes & FILTRE_HARIC) ))
		{
			DosyaAdlari.push_back(FindFileData.cFileName);
			DosyaBoyutlari.push_back(FindFileData.nFileSizeLow);
			DosyaOzellikleri.push_back(FindFileData.dwFileAttributes);
			DosyaOlusturmaTarihi.push_back(FindFileData.ftCreationTime);
			DosyaSonErisimTarihi.push_back(FindFileData.ftLastAccessTime);
			DosyaSonYazmaTarihi.push_back(FindFileData.ftLastWriteTime);
		}








		while(FindNextFileA(hAra,&FindFileData) != 0)
		{


			if( (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&  (FindFileData.dwFileAttributes && FILTRE_DAHIL) && (!(FindFileData.dwFileAttributes & FILTRE_HARIC) ) )
			{

				// '.' ve '..' Klasorlerini gosterme
				if(!((strcmp(FindFileData.cFileName,".") == 0) || (strcmp(FindFileData.cFileName,"..") == 0)))
				{

					KlasorAdlari.push_back(FindFileData.cFileName);
					KlasorBoyutlari.push_back(FindFileData.nFileSizeHigh);
					KlasorOzellikleri.push_back(FindFileData.dwFileAttributes);
					KlasorOlusturmaTarihi.push_back(FindFileData.ftCreationTime);
					KlasorSonErisimTarihi.push_back(FindFileData.ftLastAccessTime);
					KlasorSonYazmaTarihi.push_back(FindFileData.ftLastWriteTime);

				}

			}

			else if((FindFileData.dwFileAttributes & FILTRE_DAHIL) && (!(FindFileData.dwFileAttributes & FILTRE_HARIC) ))
			{

				DosyaAdlari.push_back(FindFileData.cFileName);
				DosyaBoyutlari.push_back(FindFileData.nFileSizeLow);
				DosyaOzellikleri.push_back(FindFileData.dwFileAttributes);
				DosyaOlusturmaTarihi.push_back(FindFileData.ftCreationTime);
				DosyaSonErisimTarihi.push_back(FindFileData.ftLastAccessTime);
				DosyaSonYazmaTarihi.push_back(FindFileData.ftLastWriteTime);


			}

		}

		FindClose(hAra);
		KlasorStringOlustur();
	}




















public:
	// Su an ki klasorun boyutunu hesaplar
	// Alt klasorlerin boyutlarini hesaplamaz
	ULONGLONG KlasorBoyutu()
	{

		ULONGLONG Boyut = 0;
		int Sayac = DosyaAdlari.size();
		for(int i = 0; i < Sayac; i++)
		{
		 Boyut += DosyaBoyutlari[i];
		}

		return Boyut;



	}


 public: 
	 // Eger HedefKlasor parametresi gonderilmez ise Nesnenin bagli oldugu klasoru(Adres in atandigi) hesaplar
	 // Alt klasorler ile birlikte hesaplar
	 ULONGLONG ToplamKlasorBoyutu()
	 {
		 Zamanlayici gecenSure;
		 gecenSure.Baslat();
		 ULONGLONG Boyut = KlasorBoyutuHesapla(Adres);
		 gecenSure.Durdur();

		 wcout<<string_wstring(gecenSure.StringCevir())<<"\r\n";
		 return Boyut;
	 }




public:
	// Ozellikler parametresi gonderilmez ise Klasor standart ozellikler ile yaratilir
	bool KlasorYarat(string KlasorAdi,LPSECURITY_ATTRIBUTES Ozellikler = NULL)
	{
	   	 string KlasorYolu = Adres;
		 KlasorYolu += KlasorAdi;
		return CreateDirectoryA(KlasorYolu.c_str(),Ozellikler);
	}

















 public:
	 bool Kopyala(string KaynakKlasorAdi,string HedefKlasorAdi,bool Tumune_Evet = FALSE,bool UzerineYaz = FALSE,KopyalamaCallback KontrolFonksiyonu = NULL,void* EkParam = NULL)
	 {
	 	  string KaynakKlasorYolu = Adres;
		  string HedefKlasorYolu = Adres;
		  
		  KaynakKlasorYolu += KaynakKlasorAdi;
		  HedefKlasorYolu +=  HedefKlasorAdi;
		  
		  KaynakKlasorYolu += "\\";
		  HedefKlasorYolu += "\\";

		  ULONGLONG TasinacakDosyalarBoyut = KlasorBoyutuHesapla(KaynakKlasorYolu);
		  return(KlasorKopyala(KaynakKlasorYolu,HedefKlasorYolu,Tumune_Evet,UzerineYaz,TasinacakDosyalarBoyut,KontrolFonksiyonu,EkParam));
	 }











};

typedef string VolumeString;














class Volume
{
public:
vector<string> VolumeList;
public:
vector<string> VolumeAdlari;
public:
vector<unsigned __int64> VolumeBoyut;
public:
vector<unsigned __int64> VolumeBosAlan;
public:
vector<DWORD> VolumeOzellikleri;
public:
VolumeString veri;




public:
	Volume()
	{

	}





public:
	Volume(VolumeString strveri)
	{

		Cevir(strveri);
	}





public: void IcerikTemizle()
{
	VolumeList.clear();
	VolumeAdlari.clear();
	VolumeBosAlan.clear();
	VolumeBoyut.clear();
	VolumeOzellikleri.clear();


}
public: void VolumeStringOlustur()
	{
		int VolumeSayisi = VolumeList.size();
		veri = "";
		for(int i = 0; i < VolumeSayisi;i++)
		{
			veri+= "ad:";
			veri+= VolumeAdlari[i];
			veri+= ";";

			veri+="byt:";
			veri+= uint64_str(VolumeBoyut[i]);
			veri+=";";

			veri+="kbyt:";
			veri+=uint64_str(VolumeBosAlan[i]);
			veri+=";";
										
			veri+="ozlk:";
			veri+=ulong_str(VolumeOzellikleri[i]);
			veri+=";";

			veri+="pth:";
			veri+=VolumeList[i];
			veri+=";";

			veri+="\r\n";


		}



	}

public: bool Cevir(VolumeString strveri)
{
	string Satýr = "";
	int index = 0;
	int Boyut = strveri.size();
	
	while(index <  Boyut || index != -1)
	{

	index = KelimeArasi("","\r\n",strveri,Satýr,index);
	if(index == -1)
		return false;

	int satir_index = 0;
	string sVolumeAdi="";
	satir_index = KelimeArasi("ad:",";",Satýr,sVolumeAdi,satir_index);
	if(satir_index == -1)
		return false;
	VolumeAdlari.push_back(sVolumeAdi);

    string sVolumeBoyut = "";
		satir_index = KelimeArasi("byt:",";",Satýr,sVolumeBoyut,satir_index);
	if(satir_index == -1)
		return false;
	VolumeBoyut.push_back(str_uint64(sVolumeBoyut));

	string sVolumeBosAlan = "";
		satir_index = KelimeArasi("kbyt:",";",Satýr,sVolumeBosAlan,satir_index);
	if(satir_index == -1)
		return false;
	VolumeBosAlan.push_back(str_uint64(sVolumeBosAlan));

	string sVolumeOzellik = "";
		satir_index = KelimeArasi("ozlk:",";",Satýr,sVolumeOzellik,satir_index);
	if(satir_index == -1)
		return false;
	VolumeOzellikleri.push_back(str_ulong(sVolumeOzellik));

	string sVolumePath = "";
		satir_index = KelimeArasi("pth:",";",Satýr,sVolumePath,satir_index);
	if(satir_index == -1)
		return false;
	VolumeList.push_back(sVolumePath);

	}
	 return true;
}






inline bool VolumeYolAdi(char* VolumePath,LPCH &VolumeAdi)
{
	VolumeAdi = NULL;
	DWORD pUzunluk = 0;
	Tekrar:
	int Sonuc = GetVolumePathNamesForVolumeNameA(VolumePath,VolumeAdi,(pUzunluk*2),&pUzunluk);
	if(((!Sonuc) && (GetLastError() == ERROR_MORE_DATA)) )
	{
	int Boyut = pUzunluk*2; 
	VolumeAdi = (LPCH) malloc(Boyut); 
	goto Tekrar;
	}
	else if(!Sonuc)
	return false;

	return true;
}













public: bool Listele()
{
    IcerikTemizle(); 
    char* VolumePath = (char*) malloc(1024);
	DWORD Uzunluk = 1024;
	HANDLE hAra = FindFirstVolumeA(VolumePath,Uzunluk);
	if(hAra == INVALID_HANDLE_VALUE)
		return false;
	VolumeList.clear();

do
{
	LPCH VolumeAdi = NULL;

	if(!VolumeYolAdi(VolumePath,VolumeAdi))
	return false;

	


	string Ad = VolumeAdi;
		
	if(Ad == "") // Program icin ozel ayrilmis sanal bir volume var bunu es gec.
	continue;
    
	SHFILEINFOA info;
	memset(&info,0,sizeof(info));
	SHGetFileInfoA(VolumeAdi,0,&info,sizeof(info),(SHGFI_DISPLAYNAME | SHGFI_ATTRIBUTES));


	VolumeList.push_back(VolumeAdi);
	VolumeAdlari.push_back(info.szDisplayName);
	VolumeOzellikleri.push_back(info.dwAttributes);

    unsigned __int64 Kullanilan_Alan,Bos_Alan,Cagirana_Bos_Alan;

	if(GetDiskFreeSpaceExA(VolumeAdi,(ULARGE_INTEGER*)&Cagirana_Bos_Alan,(ULARGE_INTEGER*)&Kullanilan_Alan,(ULARGE_INTEGER*)&Bos_Alan))
	{
		VolumeBosAlan.push_back(Bos_Alan);
		VolumeBoyut.push_back(Kullanilan_Alan);
	}
	else
	{
		VolumeBosAlan.push_back(0);
		VolumeBoyut.push_back(0);

	}

	}
	while(FindNextVolumeA(hAra,VolumePath,Uzunluk));
	FindVolumeClose(hAra);
	VolumeStringOlustur();
	return true;


	}

};