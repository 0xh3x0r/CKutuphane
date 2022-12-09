#pragma once

#pragma region TANIMLAMALAR




#pragma once
#ifndef DOSYA_H
#define DOSYA_H

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef BYTE_H
#include <Byte.h>
#endif

#ifndef _INC_STRING
#include <string.h>
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef EKLENTILER
#include <eklentiler.hpp>
#endif

#ifndef METIN_H
#include <metin.h>
#endif

using namespace std;
#pragma endregion
/*
////////////////////// Kullanim ///////////////////////


  

/////////////////////////// Kullanim /////////////////
*/

typedef WIN32_FILE_ATTRIBUTE_DATA dosyaozellikleri32;



static const DWORD desired_access = FILE_GENERIC_EXECUTE | FILE_GENERIC_READ | FILE_GENERIC_WRITE;

static const DWORD file_share = FILE_SHARE_READ | FILE_SHARE_WRITE;

static const DWORD fileflags = FILE_ATTRIBUTE_NORMAL;




typedef struct dosya {


public:
	DWORD Paylasim;
	bool erisimvar;
	LONG boyut;
	Metin DosyaYolu;
	Metin DosyaYoluUzun;
	dosyaozellikleri32 ozellikler;

	// can be changed 
	DWORD accesstype;
	DWORD dwFlags;
	DWORD acmaTipleri;



	_SECURITY_ATTRIBUTES secattr;

	dosya()
	{
		secattr.bInheritHandle = TRUE;
		secattr.nLength = sizeof(SECURITY_ATTRIBUTES);
	

		secattr.lpSecurityDescriptor = 0;
		accesstype = desired_access;
		Paylasim = file_share;
		dwFlags = fileflags;
		acmaTipleri = CREATE_NEW;

	}



};

class Dosya : public dosya {


public:
HANDLE hDosya;
// is set if hanle opened by class is read only
bool readonly;




Dosya(Metin _DosyaYolu)
{
	DosyaYolu = _DosyaYolu;
	hDosya = INVALID_HANDLE_VALUE;



}

Dosya( char* _DosyaYolu) :dosya()
{

	DosyaYolu = _DosyaYolu;
	hDosya = INVALID_HANDLE_VALUE;


}

Dosya(HANDLE pHandle) :hDosya(pHandle) {

	VERI data = VERI(255);

	
	if (!DosyaYaratAc())
	{
		int donus = GetShortPathNameA(DosyaYolu.c_str(), data, 255);
		DosyaYolu = data.asString();


		DurumGuncelle();
	}

}





Dosya() : dosya()
{
hDosya = NULL;
}





public:	inline	bool DosyaYarat()
{
	hDosya = CreateFileA(DosyaYolu.c_str(),accesstype,Paylasim,&secattr,CREATE_ALWAYS,dwFlags,0);
if(hDosya != INVALID_HANDLE_VALUE)
	return true;
else
return false;
}

public: inline bool DosyaYaratAc() {





	

	hDosya = CreateFileA(DosyaYolu.c_str(), accesstype, Paylasim, 0, acmaTipleri, dwFlags, 0);
	


	if (hDosya == INVALID_HANDLE_VALUE)
	{
		int hata = GetLastError();
		if (hata == ERROR_FILE_EXISTS || hata == ERROR_ALREADY_EXISTS)
		{
			acmaTipleri = OPEN_EXISTING;
			hDosya = CreateFileA(DosyaYolu.c_str(), accesstype, Paylasim, 0, acmaTipleri, dwFlags, 0);

			if (hDosya == INVALID_HANDLE_VALUE)
			{
				hata = GetLastError();
				if (hata == ERROR_SHARING_VIOLATION)  // if file is being used by another process try to open a read only handle
				{
					accesstype = FILE_GENERIC_READ;
					hDosya = CreateFileA(DosyaYolu.c_str(), accesstype, Paylasim, 0, acmaTipleri, dwFlags, 0);

					if (hDosya == INVALID_HANDLE_VALUE)  // uncontrollable error log last error and return false
					{
						// suprahata << winerrormessage();
						return false;

				   }
					else 
					{
						readonly = true; // açilan handle read only
						DurumGuncelle();
						return true;
					}

				}
			

			}

		}
	}



	if (hDosya != INVALID_HANDLE_VALUE) {
	
		DurumGuncelle();
		return true;

	}

	return false;
}






bool DosyaAc()

{
	hDosya = CreateFileA(DosyaYolu.c_str(),accesstype,Paylasim,&secattr,acmaTipleri,dwFlags,0);
	if(hDosya != INVALID_HANDLE_VALUE)
		return true;
	else
		return false;
}

int DosyaYaz(const Byte& VERI){
	   
	   DWORD yazilan;
	   bool ret = 0;

	   ret = WriteFile(hDosya, (LPCVOID)(char*)VERI.iVERI, VERI.Boyut, &yazilan, 0);
	   return ret;
}

// Read files into Veri it allocates buffer itself returns bytes 
int DosyaOku(Byte &VERI){ 
	
		int ret = 0;
		if (this->DosyaYolu != "" && this->hDosya == INVALID_HANDLE_VALUE) // eger dosya yolu girilmis ama acilmamissa dosyayi okumak icin acmayi dene basarisiz olursa false don
		{ 
			if (!this->DosyaAc())
			{
				return false;
			}
		} 
		
		
		VERI.YeniOlustur(DosyaBoyutu());
		DWORD okunan = 0;
		ret = ReadFile(hDosya, (LPVOID)(char*)VERI, VERI.Boyut, &okunan, 0);


		return okunan;
}

bool YenidenOlustur()
{
	this->DosyaKapat();
	if (this->DosyaSil()) {

		if (this->DosyaYaratAc()) {



			return true;
		}

	}

	this->DosyaAc();

	return false;
}

int DosyaSil()
{
	this->DosyaKapat();
	int ret = 0;

	if(DosyaYolu != "")
	 ret = DeleteFileA(DosyaYolu.c_str());

	return ret;
}

inline int DosyaBoyutu()
{
	boyut = GetFileSize(hDosya,0);
	int ret = boyut;
	return ret;
}



inline
int DosyaKapat()
{	

	int ret = 0;
	ret  = CloseHandle(hDosya);

	hDosya = INVALID_HANDLE_VALUE;
	return ret;
}



inline void DurumGuncelle() {

	if (hDosya != INVALID_HANDLE_VALUE)

	{
	
		int ret = DosyaBoyutu();
		boyut = ret;


		ret = GetFileAttributesEx(DosyaYolu, GET_FILEEX_INFO_LEVELS::GetFileExInfoStandard, &this->ozellikler);
		
		if (ret == false) 
		{

			this->erisimvar = false;
			// suprahata << winerrormessage();
		}
}

	this->erisimvar = true;
}




operator HANDLE() {

	return this->hDosya;
}






};


class Uygulama
{

public:
	Uygulama()
	{


	}

public:
 static string DosyaYoluAl()
  {
    char DosyaYolu[260];
    GetModuleFileNameA( NULL, DosyaYolu, MAX_PATH );
    string::size_type pos = string( DosyaYolu ).find_last_of( "\\/" );
    return string( DosyaYolu ).substr( 0, pos);
  }


static BOOL KaynakIsimleriListeleFunc(  HMODULE hModule,LPSTR lpszType, LPSTR lpszName,LONG_PTR lParam) 

	{
	  vector<Metin>* KaynakAdlari = (vector<Metin>*)lParam;
	  if(!IS_INTRESOURCE(lpszName))
	  KaynakAdlari->push_back(lpszName);
	  else
		  KaynakAdlari->push_back(((int)lpszName));
	  return TRUE;
	}
public:
	vector<string> KaynakAdlariListele(LPCSTR KaynakTipi)
	{								   
		 vector<string> KaynakAdlari;
		 EnumResourceNamesA(NULL,KaynakTipi,(ENUMRESNAMEPROCA)KaynakIsimleriListeleFunc,(LONG_PTR)&KaynakAdlari);
		 return KaynakAdlari;

	}



};
#endif
