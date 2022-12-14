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
 Win7 Admin Haklar? Gerekli!

int main()
{
   
	Kay?tDefteri kd(HKLM);
	if(!kd.Kay?tAc("SOFTWARE\\ADeneme"))
	kd.Kay?tYarat("SOFTWARE\\ADeneme");
	// E?er yoksa ise yarat

	Byte deger = "KKctttv";

	kd.DegerYarat_Degistir("anahtar",deger);

	kd.DegerAc("anahtar",deger);

	kd.DegerSil("anahtar");
   
	kd.Kay?tSil("SOFTWARE\\ADeneme");

}


*/
#pragma endregion
class Kay?tDefteri{
public:
	HKEY Bolum;
public:
	HKEY Anahtar;
public:
	Kay?tDefteri(HKEY bolum){
	Bolum = bolum;
	}

public:
	Kay?tDefteri(){
		Bolum = HKUSER;
	}


int Kay?tYarat(char* Kay?t)
	{
	DWORD disp = 0;
	RegCreateKeyEx(Bolum,Kay?t,0,0,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&Anahtar,&disp);
if(disp == REG_CREATED_NEW_KEY)
		return 1;
	else
		return 0;
	}
int Kay?tAc(char* Kay?t)
	{
if(RegOpenKeyEx(Bolum,Kay?t,0,KEY_ALL_ACCESS,&Anahtar) == 0)
			return 1;
		else
			return 0;
	}
int Kay?tSil(char* Kay?t){
if(RegDeleteKeyEx(Bolum,Kay?t,KEY_ALL_ACCESS,0) == ERROR_SUCCESS)
			return 1;
else
		    return 0;
	}
int DegerAc(char* DegerAd?,Byte &deger)
	{
	
	  
	   DWORD cbData;
if(RegQueryValueEx(Anahtar,DegerAd?,0,0,0,&cbData) == ERROR_SUCCESS){ // Boyutu sorgula

	   deger.YeniOlustur(cbData-1); // Buffer olu?tur (Null byte sayma!)
if(RegQueryValueEx(Anahtar,DegerAd?,0,0,(LPBYTE)(char*)deger,&cbData) == ERROR_SUCCESS)
		return 1;
else    return 0;
}
else return 0;

}
int DegerYarat_Degistir(char* DegerAd?,Byte deger)
{

if(RegSetValueEx(Anahtar,DegerAd?,0,REG_SZ,(BYTE*)(char*)deger,deger.Boyut) == ERROR_SUCCESS)
		return 1;
else
		return 0;
	
}
int DegerSil(char* DegerAd?){
	if(RegDeleteKeyValue(Anahtar,0,DegerAd?) == ERROR_SUCCESS)
		return 1;
	else
		return 0;

}
public:
	~Kay?tDefteri()
	{
		if(Anahtar >0)
		RegCloseKey(Anahtar);
		if(Bolum>0)
		RegCloseKey(Bolum);
	}
};