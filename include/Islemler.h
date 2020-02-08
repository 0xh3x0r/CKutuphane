#ifndef ISLEMLER_H
#define ISLEMLER_H
#endif

#ifndef BELLEK_H
#include <bellek.h>
#endif
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef HAZIRFONKSIYONLAR_H
#include <HazirFonksiyonlar.h>
#endif

#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _INC_TOOLHELP32
#include <tlhelp32.h>
#endif
#ifndef _INC_TCHAR
#include <tchar.h>
#endif
#ifndef _PSAPI_H_
#pragma comment(lib,"Psapi.lib")
#include <Psapi.h>
#endif


class Islemler
{
 typedef struct _IslemListesi{
	 vector<int> IslemID;
	 vector<int> ThreadSayisi;
	 vector<int> ModulID;
	 vector<int> heapID;
	 vector<int> UstIslem;
	 vector<int> flags;
	 vector<int> cUsage;
	 vector<string> IslemAdi;
	 vector<int> Boyut;
	 vector<long> BaseClass;


 }IslemListesi;
 public:
	 IslemListesi islemlistesi;

public:
	int IslemleriListele()
{
  HANDLE hProcessSnap;
  PROCESSENTRY32 pe32;
  
//  DWORD dwPriorityClass;
  hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
  if(hProcessSnap == INVALID_HANDLE_VALUE)
  { CloseHandle(hProcessSnap); return 0; }
  pe32.dwSize = sizeof(PROCESSENTRY32);
  if(!Process32First(hProcessSnap,&pe32))
  { CloseHandle(hProcessSnap); return 0; }
 
  do
  {  
	  // Kopyala
	  islemlistesi.IslemID.push_back(pe32.th32ProcessID);
	  
	  islemlistesi.UstIslem.push_back(pe32.th32ParentProcessID);

	  islemlistesi.IslemAdi.push_back(pe32.szExeFile);
	 
	  islemlistesi.ThreadSayisi.push_back(pe32.cntThreads);
	  
	  islemlistesi.ModulID.push_back(pe32.th32ModuleID);
	  
	  islemlistesi.heapID.push_back(pe32.th32DefaultHeapID);

	  islemlistesi.cUsage.push_back(pe32.cntUsage);
	  
	  islemlistesi.BaseClass.push_back(pe32.pcPriClassBase);

	  islemlistesi.flags.push_back(pe32.dwFlags);
	  
	  islemlistesi.Boyut.push_back(pe32.dwSize);
   
  }
  while(Process32Next(hProcessSnap,&pe32));
  CloseHandle(hProcessSnap); return 1;
}

inline
	int IslemKapat(int id,int &CikisKodu)
	{

	   if(TerminateProcess(OpenProcess(PROCESS_TERMINATE,false,id),CikisKodu))
		   return 1;
	   else
		return 0;
	}

inline
	int IslemKapat(HANDLE hIslem,int &CikisKodu)
	{
	   if(TerminateProcess(hIslem,CikisKodu))
		   return 1;
	   else
		return 0;
	}

inline
	int IslemKapat(int id)
	{

	   if(TerminateProcess(OpenProcess(PROCESS_TERMINATE,false,id),NULL))
		   return 1;
	   else
		return 0;
	}

inline
	int IslemKapat(HANDLE hIslem)
	{
	   if(TerminateProcess(hIslem,NULL))
		   return 1;
	   else
		return 0;
	}
inline
	int ISIM_id(char* IslemAdý){
		int Boyut = islemlistesi.IslemID.size();
		for(int i = 0; i < Boyut;i++){
			string dnm = islemlistesi.IslemAdi[i];
			if( (islemlistesi.IslemAdi[i].compare(IslemAdý)) == 0) 
			return (islemlistesi.IslemID[i]);
		
	}
		return -1;
}

inline 
	bool ID_handle(int id,HANDLE &hIslem){


		hIslem = OpenProcess(PROCESS_ALL_ACCESS,false,id);
		if(hIslem != INVALID_HANDLE_VALUE)
		return 1;
		else
		return 0;
}

    bool ID_handle(int id,HANDLE &hIslem,DWORD Izin){


		hIslem = OpenProcess( (PROCESS_ALL_ACCESS | Izin) ,false,id);
		if(hIslem != INVALID_HANDLE_VALUE)
		return 1;
		else
		return 0;
}
};

class Islem
{
private:
	HANDLE hIslem;

 typedef struct _IslemBilgileri{
	 int ID;
	 vector<int> ModulID;
	 vector<int> ModulBoyut;
	 vector<HMODULE> hModul;
	 vector<string> ModulAdi;
	 vector<int> ModulBaslangic;
	 vector<int> Modul;

 }IslemBilgileri;
public:
 IslemBilgileri islembilgileri;

public:
	bool IslemAc(int ID)
	{
		hIslem = OpenProcess(  MAXIMUM_ALLOWED,false,ID);
		HANDLE hSnap;
		MODULEENTRY32 modul;
		if(hIslem == INVALID_HANDLE_VALUE)
		return false; 
		islembilgileri.ID = ID;
		
		hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, ID );
		if(hSnap == INVALID_HANDLE_VALUE)
			{ CloseHandle(hSnap); return false; }

		modul.dwSize = sizeof(MODULEENTRY32);
	   if(!Module32First(hSnap,&modul))
		   { CloseHandle(hSnap); return false; }
	   do
	   {
		   islembilgileri.ModulID.push_back(modul.th32ModuleID);
		   islembilgileri.ModulBoyut.push_back(modul.modBaseSize);
		   islembilgileri.ModulAdi.push_back(modul.szModule);
		   islembilgileri.ModulBaslangic.push_back((int)modul.modBaseAddr);
		   islembilgileri.hModul.push_back(modul.hModule);
	   }
	   while(Module32Next(hSnap,&modul));
	
	   return true;
	 
	}
public:
	bool BilgileriGüncelle()
	{
			HANDLE hSnap;
		MODULEENTRY32 modul;
		if(hIslem == INVALID_HANDLE_VALUE)
		{ CloseHandle(hSnap); return false; }

		
		hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, islembilgileri.ID );
		if(hSnap == INVALID_HANDLE_VALUE)
			{ CloseHandle(hSnap); return false; }

		modul.dwSize = sizeof(MODULEENTRY32);
	   if(!Module32First(hSnap,&modul))
		   { CloseHandle(hSnap); return false; }
	   do
	   {
		   
		   islembilgileri.ModulID.push_back(modul.th32ModuleID);
		   islembilgileri.ModulBoyut.push_back(modul.modBaseSize);
		   islembilgileri.ModulAdi.push_back(modul.szModule);
		   islembilgileri.ModulBaslangic.push_back((int)modul.modBaseAddr);
		   islembilgileri.hModul.push_back(modul.hModule);
	   }
	   while(Module32Next(hSnap,&modul));

	    CloseHandle(hSnap);
	   	hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPHEAPLIST, islembilgileri.ID );
		if(hSnap == INVALID_HANDLE_VALUE)
		{ CloseHandle(hSnap); return false; }
		HEAPENTRY32 heapbilgi;
		ULONG_PTR ptr=  NULL;

		if(!Heap32First(&heapbilgi,islembilgileri.ID ,ptr))
		{ CloseHandle(hSnap); return false; }
		
		do{
			int a = 1;
		}
		while(Heap32Next(&heapbilgi));
		
	}

	inline 
		int hmodul_isim(const char* ModulAdi)
	{
		int boyut = islembilgileri.ModulAdi.size();
		for(int i = 0; i < boyut;i++){
			if((islembilgileri.ModulAdi[i].compare(ModulAdi)) == 0)
				return ((int)islembilgileri.hModul[i]);
		}
		return -1;
	}

	inline 
		int modulbaslangicadress_isim(const char* ModulAdi)
	{
		int boyut = islembilgileri.ModulAdi.size();
		for(int i = 0; i < boyut;i++){
			if((islembilgileri.ModulAdi[i].compare(ModulAdi)) == 0)
				return (islembilgileri.ModulBaslangic[i]);
		}
		return -1;
	}
	inline 
		int modulboyut_isim(const char* ModulAdi)
	{
		int boyut = islembilgileri.ModulAdi.size();
		for(int i = 0; i < boyut;i++){
			if((islembilgileri.ModulAdi[i].compare(ModulAdi)) == 0)
				return (islembilgileri.ModulBoyut[i]);
		}
		return -1;
	}

	bool BellekOku(int* Adress,int Byte_Boyut,char* Veri){
		int okunan = 0;
		ReadProcessMemory(hIslem,Adress,Veri,Byte_Boyut,(SIZE_T*)&okunan);
		if(okunan > 0)
			return true;
		else
			return false;

	}
	bool BellekYaz(int* Adres,int* Veri,int Byte_Boyut){
		int yazilan = 0;
		WriteProcessMemory(hIslem,(LPVOID)Adres,(LPCVOID)Veri,Byte_Boyut,(SIZE_T*)&yazilan);

		if(yazilan)
			return true;
		else 
			return false;
	}

	int* BellekYarat(int Byte_Boyut)
	{
		return(uzakBellekYarat(hIslem,Byte_Boyut,Byte_Boyut,PAGE_EXECUTE_READWRITE)); // Kod gömebilmek için PAGE Execute ek iziniyle yarat
	}

	bool IslemYarat(char* DosyaYolu,char* Arg)
	{
		
		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		memset(&si,0,sizeof(si));
		si.cb = sizeof(si);
		
		 CreateProcessA(DosyaYolu,Arg,0,0,false,(CREATE_NO_WINDOW | CREATE_DEFAULT_ERROR_MODE | CREATE_NEW_CONSOLE),0,0,&si,&pi);
 		 int hata = GetLastError();
		 hIslem = pi.hProcess;
		 int ID = pi.dwProcessId;
		 if(hIslem == INVALID_HANDLE_VALUE)
		 return false;

		    HANDLE hSnap;
		    MODULEENTRY32 modul;
			islembilgileri.ID = ID;
		 	hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, ID );
		if(hSnap == INVALID_HANDLE_VALUE)
			{ CloseHandle(hSnap); return false; }

		modul.dwSize = sizeof(MODULEENTRY32);
	   if(!Module32First(hSnap,&modul))
		   { CloseHandle(hSnap); return false; }
	   do
	   {
		   islembilgileri.ModulID.push_back(modul.th32ModuleID);
		   islembilgileri.ModulBoyut.push_back(modul.modBaseSize);
		   islembilgileri.ModulAdi.push_back(modul.szModule);
		   islembilgileri.ModulBaslangic.push_back((int)modul.modBaseAddr);
		   islembilgileri.hModul.push_back(modul.hModule);
	   }
	   while(Module32Next(hSnap,&modul));

	   return true;
	}
	
	/// GERÝ DÖNÜÞLER

	int IslemKapat()
	{
		return(TerminateProcess(hIslem,0));
	}

	/*
	 Islem islem;
	  islem.IslemAc(pId);
	  char* ptr;
	  if(!islem.DosyaYolu(ptr))
		  return false;
	  MessageBoxA(0,ptr,0,0);
	*/
	bool DosyaYolu(char* &Veri)
	{
		char* ret = (char*) malloc(1024);
		if( (GetModuleFileNameExA(hIslem,(HMODULE)islembilgileri.hModul[0],ret,1024)) != 0)
		{
			Veri = ret;
			return true;

		}
		return false;
	}
 operator HANDLE(){
	 return hIslem;
 }
};

/*
    	hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPHEAPLIST, islembilgileri.ID );
		if(hSnap == INVALID_HANDLE_VALUE)
		{ CloseHandle(hSnap); return false; }
		HEAPENTRY32 heapbilgi;
		heapbilgi.dwSize = sizeof(HEAPENTRY32);
		ULONG_PTR ptr=  NULL;
		HEAPLIST32 hlist;
		hlist.dwSize = sizeof(HEAPLIST32);
		if(!Heap32ListFirst(hSnap,&hlist))
		{ CloseHandle(hSnap); return false; }

		if(!Heap32First(&heapbilgi,ID,hlist.th32HeapID))
		{ CloseHandle(hSnap); return false; }
		
		do{
			int a = 1;
		}
		while(Heap32ListNext(hSnap,&hlist));
*/