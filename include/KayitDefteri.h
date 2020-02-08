#ifndef _WINDOWS_
#include <Windows.h>
#endif
#ifndef BYTE_H
#include <Byte.h>
#endif

#define HKROOT (( HKEY ) (ULONG_PTR)((LONG)0x80000000) )
#define HKCONFIG (( HKEY ) (ULONG_PTR)((LONG)0x80000005) )
#define HKUSER (( HKEY ) (ULONG_PTR)((LONG)0x80000001) )
#define HKLM (( HKEY ) (ULONG_PTR)((LONG)0x80000002) )
#define HKUSERS  (( HKEY ) (ULONG_PTR)((LONG)0x80000003) )
#pragma region KULLANIM

/*
 Win7 Admin Haklarý Gerekli!

int main()
{
   
	KayýtDefteri kd(HKLM);
	if(!kd.KayýtAc("SOFTWARE\\ADeneme"))
	kd.KayýtYarat("SOFTWARE\\ADeneme");
	// Eðer yoksa ise yarat

	Byte deger = "KKctttv";

	kd.DegerYarat_Degistir("anahtar",deger);

	kd.DegerAc("anahtar",deger);

	kd.DegerSil("anahtar");
   
	kd.KayýtSil("SOFTWARE\\ADeneme");

}


*/
#pragma endregion
class KayýtDefteri{
public:
	HKEY Bolum;
public:
	HKEY Anahtar;
public:
	KayýtDefteri(HKEY bolum){
	Bolum = bolum;
	}

public:
	KayýtDefteri(){
		Bolum = HKUSER;
	}


int KayýtYarat(char* Kayýt)
	{
	DWORD disp = 0;
	RegCreateKeyEx(Bolum,Kayýt,0,0,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&Anahtar,&disp);
if(disp == REG_CREATED_NEW_KEY)
		return 1;
	else
		return 0;
	}
int KayýtAc(char* Kayýt)
	{
if(RegOpenKeyEx(Bolum,Kayýt,0,KEY_ALL_ACCESS,&Anahtar) == 0)
			return 1;
		else
			return 0;
	}
int KayýtSil(char* Kayýt){
if(RegDeleteKeyEx(Bolum,Kayýt,KEY_ALL_ACCESS,0) == ERROR_SUCCESS)
			return 1;
else
		    return 0;
	}
int DegerAc(char* DegerAdý,Byte &deger)
	{
	
	  
	   DWORD cbData;
if(RegQueryValueEx(Anahtar,DegerAdý,0,0,0,&cbData) == ERROR_SUCCESS){ // Boyutu sorgula

	   deger.YeniOlustur(cbData-1); // Buffer oluþtur (Null byte sayma!)
if(RegQueryValueEx(Anahtar,DegerAdý,0,0,(LPBYTE)(char*)deger,&cbData) == ERROR_SUCCESS)
		return 1;
else    return 0;
}
else return 0;

}
int DegerYarat_Degistir(char* DegerAdý,Byte deger)
{

if(RegSetValueEx(Anahtar,DegerAdý,0,REG_SZ,(BYTE*)(char*)deger,deger.Boyut) == ERROR_SUCCESS)
		return 1;
else
		return 0;
	
}
int DegerSil(char* DegerAdý){
	if(RegDeleteKeyValue(Anahtar,0,DegerAdý) == ERROR_SUCCESS)
		return 1;
	else
		return 0;

}
public:
	~KayýtDefteri()
	{
		if(Anahtar >0)
		RegCloseKey(Anahtar);
		if(Bolum>0)
		RegCloseKey(Bolum);
	}
};