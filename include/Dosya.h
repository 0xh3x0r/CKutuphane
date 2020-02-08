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

#ifndef HAZIRFONKSIYONLAR_H
#include <HazirFonksiyonlar.h>
#endif

using namespace std;
#pragma endregion
/*
////////////////////// Kullanim ///////////////////////


  

/////////////////////////// Kullanim /////////////////
*/


class Dosya {
public:
HANDLE hDosya;
public: string DosyaYolu;
DWORD Paylasim;
Dosya( string _DosyaYolu)
{
	DosyaYolu = _DosyaYolu;
	hDosya = INVALID_HANDLE_VALUE;
	Paylasim = FILE_SHARE_READ;
}

Dosya( char* _DosyaYolu)
{
	DosyaYolu = _DosyaYolu;
	hDosya = INVALID_HANDLE_VALUE;
	Paylasim = FILE_SHARE_READ;
}



Dosya()
{
hDosya = NULL;
}



inline
bool DosyaYarat()
{
	hDosya = CreateFileA(DosyaYolu.c_str(),(GENERIC_READ | GENERIC_WRITE),Paylasim,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
if(hDosya != INVALID_HANDLE_VALUE)
	return true;
else
return false;
}

inline
bool DosyaYaratAc(){
	hDosya = CreateFileA(DosyaYolu.c_str(),(GENERIC_READ | GENERIC_WRITE),Paylasim,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
 if(hDosya != INVALID_HANDLE_VALUE )
	 return true;
 hDosya = CreateFileA(DosyaYolu.c_str(),(GENERIC_READ | GENERIC_WRITE),Paylasim,0,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);
 if(hDosya != INVALID_HANDLE_VALUE)
	 return true;
 return false;
};

bool DosyaAc(){
	hDosya = CreateFileA(DosyaYolu.c_str(),(GENERIC_READ | GENERIC_WRITE),Paylasim,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hDosya != INVALID_HANDLE_VALUE)
		return true;
	else
		return false;
}

int DosyaYaz(Byte veri){
	   
	   DWORD yazilan;
	   return(WriteFile(hDosya,(LPCVOID)(char*)veri,veri.Boyut,&yazilan,0));
}

int DosyaOku(Byte &veri){ // Dosyayi sonunda kapamaz
	    veri.YeniOlustur(DosyaBoyutu());
	    DWORD okunan = 0;
	    return(ReadFile(hDosya,(LPVOID)(char*)veri,veri.Boyut,&okunan,0));
}

int DosyaSil()
{
	return(DeleteFileA(DosyaYolu.c_str()));

}

inline
int DosyaBoyutu(){
	return(GetFileSize(hDosya,0));
}
inline
int DosyaKapat()
{				  
	return(CloseHandle(hDosya));
	hDosya = INVALID_HANDLE_VALUE;
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
	  vector<string>* KaynakAdlari = (vector<string>*)lParam;
	  if(!IS_INTRESOURCE(lpszName))
	  KaynakAdlari->push_back(lpszName);
	  else
		  KaynakAdlari->push_back(int_str((int)lpszName));
	  return TRUE;
	}
public:
	vector<string> KaynakAdlariListele(LPCSTR KaynakTipi)
	{								   
		 vector<string> KaynakAdlari;
		 EnumResourceNamesA(NULL,KaynakTipi,(ENUMRESNAMEPROC)KaynakIsimleriListeleFunc,(LONG_PTR)&KaynakAdlari);
		 return KaynakAdlari;

	}



};
#endif
