#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef BYTE_H
#include <Byte.h>
#endif

#ifndef METIN_H
#include <metin.h>
#endif


#ifndef VERI_H
#include <Veri.h>
#endif

// CUSTOM VALUE(variable) types that i used

#define REG_STRUCT 12







#define HKROOT (( HKEY ) (ULONG_PTR)((LONG)0x80000000) )
#define HKCU (( HKEY ) (ULONG_PTR)((LONG)0x80000001) )
#define HKLM (( HKEY ) (ULONG_PTR)((LONG)0x80000002) )
#define HKUSERS  (( HKEY ) (ULONG_PTR)((LONG)0x80000003) )
#define HKCONFIG (( HKEY ) (ULONG_PTR)((LONG)0x80000005) )


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


struct KayitDegisken {

	HKEY parent;
	Metin degiskenadi;
	// DONOT FORGET TO RELEASE THIS LATER!!!!
	Byte deger;

	DWORD tipi;
	DWORD index;



};

struct KAYIT {
	
	HKEY Anahtar;
	Metin kayitadi;

	// KAYDA BAGLI DIGER KAYITLAR VE DEGISKENLERIN SAYISI
	DWORD altkayitsayisi;
	DWORD degiskensayisi;


	KAYIT():Anahtar(0) {}

	DWORD degiskenadimaxboyut;

	// EN BUYUK ALT KAYIT ADI
	DWORD kayitadimaxboyut;


	// MAX DATA SIZES
	DWORD enbuyukdegisken;
	DWORD enbuyukclasstr;

	FILETIME ensonerisim;

};

class KayitDefteri{
public:
	HKEY Bolum;
public:
	KAYIT kayit;
	//HKEY Anahtar;
public:
	KayitDefteri(HKEY bolum){
	Bolum = bolum;
	}

public:
	KayitDefteri(){
		Bolum = HKCU;
	}


int KayýtYarat(Metin KayýtAdi)
	{
	DWORD disp = 0;
	RegCreateKeyEx(Bolum,KayýtAdi,0,0,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&kayit.Anahtar,&disp);
if(disp == REG_CREATED_NEW_KEY)
		return 1;
	else
		return 0;
	}



vector<KayitDegisken> degiskenlistele()


{
		int ret = -1;
		DWORD index = 0;
		vector<KayitDegisken> sonuc;

		int degiskenadet = kayit.degiskensayisi;
		int maxdata = kayit.enbuyukdegisken;
		int maxdegiskenadi = kayit.degiskenadimaxboyut;
		int maxkayitadi = kayit.enbuyukclasstr;


		for (size_t i = 0; i < degiskenadet; i++)
		{
			VERI bfrisim = VERI(maxdegiskenadi + 1);
			VERI bfrdeger = VERI(maxdata);

			DWORD bytisim = bfrisim.boyut;
			DWORD degerboyut = bfrdeger.boyut;

			DWORD veritipi;


			ret = RegEnumValue(kayit.Anahtar, index, bfrisim, &bytisim, 0, &veritipi, (LPBYTE)bfrdeger.getData(), &degerboyut);

			KayitDegisken dgskn;
			dgskn.deger.Ekle(bfrdeger.getData(), bfrdeger.boyut);

			dgskn.degiskenadi = bfrisim.asString();
			dgskn.parent = kayit.Anahtar;

			dgskn.tipi = veritipi;
			dgskn.index = i;
			sonuc.push_back(dgskn);
			index++;
		}


		return sonuc;
}




// KAYIT DEGISKENINDEKI BILGILERI GUNCELLER 
// KAYIT STRUCTUNUN DOGRU VE GECERLI BIR HKEY ANAHTARINA ISARET ETTIGINDEN EMIN OL
bool kayitbilgileriguncelle()
{

	int retCode = RegQueryInfoKeyA(
		kayit.Anahtar,                     
		NULL,                
		NULL,           
		NULL,                 
		&kayit.altkayitsayisi,              
		&kayit.kayitadimaxboyut,      
		&kayit.enbuyukclasstr,        
		&kayit.degiskensayisi,              
		&kayit.degiskenadimaxboyut,            
		&kayit.enbuyukdegisken,       
		0,    
		&kayit.ensonerisim);    


	if (retCode == ERROR_SUCCESS)
	{
		
		return true;
	}
	else
	{
		Metin hata = "bilgiler yuklenemedi lasterr: ";
		hata += GetLastError();
	}

}

bool KayýtAc(char* KayýtAdi,DWORD accessType = KEY_ALL_ACCESS)
	{

	int ret = RegOpenKeyEx(Bolum, KayýtAdi, 0, KEY_ALL_ACCESS, &kayit.Anahtar);
	if (ret == ERROR_SUCCESS)
	{
		kayitbilgileriguncelle();
		return true;
	}

	return false;
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
if(RegQueryValueEx(kayit.Anahtar,DegerAdý,0,0,0,&cbData) == ERROR_SUCCESS){ // Boyutu sorgula

	   deger.YeniOlustur(cbData); // Buffer oluþtur (Null byte sayma!)
if(RegQueryValueEx(kayit.Anahtar,DegerAdý,0,0,(LPBYTE)(char*)deger,&cbData) == ERROR_SUCCESS)
		return 1;
else    return 0;
}
else return 0;

}



int DegerYarat_Degistir(char* DegerAdý,Byte deger,DWORD DegerTipi = REG_NONE)
{

if(RegSetValueEx(kayit.Anahtar,DegerAdý,0,DegerTipi,(BYTE*)(char*)deger,deger.Boyut) == ERROR_SUCCESS)
		return 1;
else
		return 0;
	
}
int DegerSil(char* DegerAdý){
	if(RegDeleteKeyValue(kayit.Anahtar,0,DegerAdý) == ERROR_SUCCESS)
		return 1;
	else
		return 0;


}

void ReleaseHandles() {

	if (kayit.Anahtar != 0) RegCloseKey(kayit.Anahtar);
	
	
}

};