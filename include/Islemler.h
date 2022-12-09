
#pragma once

#ifndef ISLEMLER_H
#define ISLEMLER_H



#ifndef BELLEK_H
#include <bellek.h>
#endif
#ifndef _WINDOWS_
#include <Windows.h>
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

#ifndef THREAD_H
#include <Thread.h>
#endif

#ifndef VERI_H
#include <Veri.h>
#endif


#ifndef DOSYA_H
#include <Dosya.h>
#endif



#ifndef BYTE_H
#include <Byte.h>

#endif

#ifndef METIN_H
#include <metin.h>
#endif

#ifndef PEBILGISI
#include <pebilgisi.h>
#endif




#ifndef _PSAPI_H_
#include <Psapi.h>

#pragma comment(lib,"Psapi.lib")
#endif


// OLD APIS FOR WIN32 PROCESS INFORMATION DEMANDING MAY BE DEPRECIATED IN THE FUTURE 
// NtQuery ve ona ait struct / api bilgileri winternl.h de saklanýyor ama dll call yapabilmek için ntquery fonksiyonlari daha önce tanýmlanmamýþ olmalý
// winternl.h nin kullandigi structlar bu asagidaki headerda yeniden tanýmlanmistir

#ifndef  NTTANIMLAMALAR_H
#include <nttanimlamalar.h>
#endif // ! NTTANIMLAMALAR_H





//  -> example       https://cpp.hotexamples.com/examples/-/-/NtQueryInformationProcess/cpp-ntqueryinformationprocess-function-examples.html

// https://github.com/jbremer/cuckoomon






/*
						OPEN PROCESS PARAMETRELERIIIIIIIIIIIIII


						#define PROCESS_TERMINATE                  (0x0001)
						#define PROCESS_CREATE_THREAD              (0x0002)
						#define PROCESS_SET_SESSIONID              (0x0004)
						#define PROCESS_VM_OPERATION               (0x0008)
						#define PROCESS_VM_READ                    (0x0010)
						#define PROCESS_VM_WRITE                   (0x0020)
						#define PROCESS_DUP_HANDLE                 (0x0040)
						#define PROCESS_CREATE_PROCESS             (0x0080)
						#define PROCESS_SET_QUOTA                  (0x0100)
						#define PROCESS_SET_INFORMATION            (0x0200)
						#define PROCESS_QUERY_INFORMATION          (0x0400)
						#define PROCESS_SUSPEND_RESUME             (0x0800)
						#define PROCESS_QUERY_LIMITED_INFORMATION  (0x1000)
						#define PROCESS_SET_LIMITED_INFORMATION    (0x2000)



*/



typedef struct _IslemBilgileri {
	int ID;
	vector<int> ModulID;
	vector<int> ModulBoyut;
	vector<HMODULE> hModul;
	vector<string> ModulAdi;
	vector<int> ModulBaslangic;
	vector<int> Modul;
	vector<HEAPENTRY32> heapList;
	vector<THREADENTRY32> threadList;

}IslemBilgileri;



  
LONG(WINAPI *NtQueryInformationProcess)(HANDLE ProcessHandle,
	ULONG ProcessInformationClass, PVOID ProcessInformation,
	ULONG ProcessInformationLength, PULONG ReturnLength);
	

		  




// YOU HAVE TO USE THIS IF YOU WANT TO CALL NTQUERY API
// RIGHT NOW IT IS NOT ESSENTIAL YOU CAN SIMPLY DELETE 	NTQUERY REFERENCE IN bilgileriYukle() function
static void InitializeNTDLL()
{
	HMODULE ntdllModule = 0;
	ntdllModule = LoadLibrary("ntdll");
	*(FARPROC *)&NtQueryInformationProcess = GetProcAddress(ntdllModule	, "NtQueryInformationProcess");

	if (NtQueryInformationProcess == NULL) throw exception("NtQueryInformationProcess apisi yuklenemedi \r\n");


	

}

















/*



#define FreeModule(hLibModule) FreeLibrary((hLibModule))
#define MakeProcInstance(lpProc,hInstance) (lpProc)
#define FreeProcInstance(lpProc) (lpProc)


//
// NUMA values
//
#define NUMA_NO_PREFERRED_NODE ((DWORD) -1)








//
// Process dwCreationFlag values
//

#define DEBUG_PROCESS                     0x00000001
#define DEBUG_ONLY_THIS_PROCESS           0x00000002
#define CREATE_SUSPENDED                  0x00000004
#define DETACHED_PROCESS                  0x00000008

#define CREATE_NEW_CONSOLE                0x00000010
#define NORMAL_PRIORITY_CLASS             0x00000020
#define IDLE_PRIORITY_CLASS               0x00000040
#define HIGH_PRIORITY_CLASS               0x00000080

#define REALTIME_PRIORITY_CLASS           0x00000100
#define CREATE_NEW_PROCESS_GROUP          0x00000200
#define CREATE_UNICODE_ENVIRONMENT        0x00000400
#define CREATE_SEPARATE_WOW_VDM           0x00000800

#define CREATE_SHARED_WOW_VDM             0x00001000
#define CREATE_FORCEDOS                   0x00002000
#define BELOW_NORMAL_PRIORITY_CLASS       0x00004000
#define ABOVE_NORMAL_PRIORITY_CLASS       0x00008000

#define INHERIT_PARENT_AFFINITY           0x00010000
#define INHERIT_CALLER_PRIORITY           0x00020000    // Deprecated
#define CREATE_PROTECTED_PROCESS          0x00040000
#define EXTENDED_STARTUPINFO_PRESENT      0x00080000

#define PROCESS_MODE_BACKGROUND_BEGIN     0x00100000
#define PROCESS_MODE_BACKGROUND_END       0x00200000

#define CREATE_BREAKAWAY_FROM_JOB         0x01000000
#define CREATE_PRESERVE_CODE_AUTHZ_LEVEL  0x02000000
#define CREATE_DEFAULT_ERROR_MODE         0x04000000
#define CREATE_NO_WINDOW                  0x08000000

#define PROFILE_USER                      0x10000000
#define PROFILE_KERNEL                    0x20000000
#define PROFILE_SERVER                    0x40000000
#define CREATE_IGNORE_SYSTEM_DEFAULT      0x80000000

//
// Thread dwCreationFlag values
//

//#define CREATE_SUSPENDED                  0x00000004

#define STACK_SIZE_PARAM_IS_A_RESERVATION   0x00010000    // Threads only

//
// Priority flags
//

#define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_BELOW_NORMAL    (THREAD_PRIORITY_LOWEST+1)
#define THREAD_PRIORITY_NORMAL          0
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX
#define THREAD_PRIORITY_ABOVE_NORMAL    (THREAD_PRIORITY_HIGHEST-1)
#define THREAD_PRIORITY_ERROR_RETURN    (MAXLONG)

#define THREAD_PRIORITY_TIME_CRITICAL   THREAD_BASE_PRIORITY_LOWRT
#define THREAD_PRIORITY_IDLE            THREAD_BASE_PRIORITY_IDLE

#define THREAD_MODE_BACKGROUND_BEGIN    0x00010000
#define THREAD_MODE_BACKGROUND_END      0x00020000





*/



class altislem
{


public:
	// THIS HOLDS INFO BOUT PROCESS AFTER IT CREATE DONT FORGET TO CLOSE THESE HANDLES
	PROCESS_INFORMATION bilgiler;



	//  USE THESE AS PARAMS !!! 

	// in,out STARTUPINFO hem parametre olarak hem de cikti olarak kullaniyor see:startupinfo.dwFlags
	STARTUPINFO ayarbaslangic;


	//extra creationflags da EXTENDED_STARTUPINFO_PRESENT bayragini set etmek lazim
	STARTUPINFOEX baslatmaex;

	//in can be 0 CREATE_NO_WINDOW - DETACHED_PROCESS gibi ayarlari alan enum
	DWORD creationflags;

	// must chose either full path or use commandline string
	char* tampath;

	// you can call default applications(apps in 'PATH') and pass parameters to them
	char* cmdline;

	//environment variable block null ise parentten inherit et
	char* envblock;

	// workingdir null ise parentten inherit eder
	char* workingdir;

	// mirasalma handlerin parentten miras alinmasini sagliyor
	bool mirasalma;



	SECURITY_ATTRIBUTES saproc;
	SECURITY_ATTRIBUTES sathread;

	altislem()
	{
		bilgiler = { 0 };

		ayarbaslangic = { 0 };
		ayarbaslangic.cb = sizeof(STARTUPINFO);

		creationflags = 0;

		saproc = { 0 };
		saproc.bInheritHandle = TRUE;
		saproc.nLength = sizeof(SECURITY_ATTRIBUTES);

		sathread = { 0 };
		sathread.bInheritHandle = TRUE;
		sathread.nLength = sizeof(SECURITY_ATTRIBUTES);

		
		tampath = NULL,cmdline = NULL, mirasalma = 1, envblock = NULL, workingdir = NULL;

	};

	
	bool baslat()
	{

		bool ret = CreateProcess(tampath, cmdline, 0, 0, mirasalma, creationflags, envblock, workingdir, &ayarbaslangic, &bilgiler);
		return ret;
	}

};

typedef struct islemVERIleri {

	HMODULE hIslemModule;
	PROCESSENTRY32 islem;
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	_PERFORMANCE_INFORMATION performance;
	

}islemVERIleri;



typedef struct headerBilgileri {

	
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS32 peheader;
	vector<IMAGE_SECTION_HEADER> sections;
};



// NTQUERYPROCESSINFORMATION dan donen bilgileri tutan struct
typedef struct ntProcessBilgileri {

	PROCESS_BASIC_INFORMATION basicInfo;
	RTL_USER_PROCESS_PARAMETERS params;
	PEB peb;	   // Process environment block
// Thread environment block 	TEB teb; not used	


	// check for more info https://rvsec0n.wordpress.com/2019/09/13/routines-utilizing-tebs-and-pebs/


};









/*


#if (PSAPI_VERSION > 1)
#define EnumProcesses               K32EnumProcesses
#define EnumProcessModules          K32EnumProcessModules
#define EnumProcessModulesEx        K32EnumProcessModulesEx
#define GetModuleBaseNameA          K32GetModuleBaseNameA
#define GetModuleBaseNameW          K32GetModuleBaseNameW
#define GetModuleFileNameExA        K32GetModuleFileNameExA
#define GetModuleFileNameExW        K32GetModuleFileNameExW
#define GetModuleInformation        K32GetModuleInformation
#define EmptyWorkingSet             K32EmptyWorkingSet
#define QueryWorkingSet             K32QueryWorkingSet
#define QueryWorkingSetEx           K32QueryWorkingSetEx
#define InitializeProcessForWsWatch K32InitializeProcessForWsWatch
#define GetWsChanges                K32GetWsChanges
#define GetWsChangesEx              K32GetWsChangesEx
#define GetMappedFileNameW          K32GetMappedFileNameW
#define GetMappedFileNameA          K32GetMappedFileNameA
#define EnumDeviceDrivers           K32EnumDeviceDrivers
#define GetDeviceDriverBaseNameA    K32GetDeviceDriverBaseNameA
#define GetDeviceDriverBaseNameW    K32GetDeviceDriverBaseNameW
#define GetDeviceDriverFileNameA    K32GetDeviceDriverFileNameA
#define GetDeviceDriverFileNameW    K32GetDeviceDriverFileNameW
#define GetProcessMemoryInfo        K32GetProcessMemoryInfo
#define GetPerformanceInfo          K32GetPerformanceInfo
#define EnumPageFilesW              K32EnumPageFilesW
#define EnumPageFilesA              K32EnumPageFilesA
#define GetProcessImageFileNameA    K32GetProcessImageFileNameA
#define GetProcessImageFileNameW    K32GetProcessImageFileNameW
*/


typedef struct modul {
	HMODULE hModule;
	MODULEINFO info;
	char baseName[255];
	char filename[255];
}modul;




/*
Each process has a minimum and maximum working set size that affect the virtual memory paging behavior of the process. To obtain the current size of the working set of a specified process, 
use the GetProcessMemoryInfo function. To obtain or change the minimum and maximum working set sizes, use the GetProcessWorkingSetSizeEx and SetProcessWorkingSetSizeEx functions.

*/



typedef struct bellekBilgileri {

	PSAPI_WORKING_SET_EX_INFORMATION analiste;
	PROCESS_MEMORY_COUNTERS membilgisi;
	SIZE_T minworkingset;
	SIZE_T maxworkingset;
	MEMORY_BASIC_INFORMATION mbi;


};




typedef struct bellekblogu {

	char* ptr;
	int boyut;

};



class Islem {

public:

	HANDLE hIslem;
	int ID;
	bool Erisimvar;
	int numberOfModules;
	WCHAR* dosyaYolu;
	WCHAR* commandline;

	// main module handle
	HMODULE anaModule;
	// main module entry point and size 
	MODULEINFO anaModulBilgisi;
	
	vector<modul> digerModuller;


	// PE and File section headers
	headerBilgileri headers;

	// Thread List
	vector<Thread> threadler;

	// extra info
	ntProcessBilgileri extra;


	bellekBilgileri bellek;

	Dosya islemDosyasi;


	// please call Readimporttable if you want to read imported funcs  
	vector<imported_dll> importeddlls;

	vector<bellekblogu> createdmemoryblocks;

	Islem() : Erisimvar(false) , hIslem(INVALID_HANDLE_VALUE),ID(-1)
	{

		
	}

	Islem(int islemID) : ID(-1)
	
	{
		 
	
		
		hIslem = OpenProcess(PROCESS_ALL_ACCESS, true , islemID);
		
		if (hIslem != INVALID_HANDLE_VALUE | hIslem != 0)
		{
			Erisimvar = 1;
			ID = islemID;
			if (!AnaModulYukle()) throw exception("ana modul yuklenemedi");

			threadleriYukle();
			bilgileriYukle();
			headeryukle();
			bellekBilgileriYukle();

		}



	}

	 


// check for virtualallocfromapp and initializeenclave 

	/*
	
	he WIN32_MEMORY_REGION_INFORMATION structure contains information about a single memory allocation. In contrast, 
	the MEMORY_BASIC_INFORMATION structure that is returned by the VirtualQuery function describes a contiguous run of pages within a single allocation that all have the same type, 
	state, and protection. The mapping between WIN32_MEMORY_REGION_INFORMATION fields and memory type values returned by VirtualQuery is as follows:
	
	
	*/



bool bellekBilgileriYukle()
	{
		int ret = false;

		
		bellek.analiste.VirtualAddress = anaModulBilgisi.lpBaseOfDll;
		// if this func fails it will load numberofentries to the 



		
		ret = GetProcessWorkingSetSize(hIslem, &bellek.minworkingset, &bellek.maxworkingset);
		
		
	
		bellek.membilgisi.cb = sizeof(PROCESS_MEMORY_COUNTERS);

		ret = GetProcessMemoryInfo(hIslem, &bellek.membilgisi, bellek.membilgisi.cb);
		

		// Load the base modul entry and then get the neccesary infos
		ret = VirtualQuery(anaModulBilgisi.lpBaseOfDll, &bellek.mbi, sizeof(bellek.mbi));
		



		ret = QueryWorkingSetEx(hIslem, &bellek.analiste, sizeof(PSAPI_WORKING_SET_EX_INFORMATION));


		return true;

}

bool bilgileriYukle()
	{

		// Belli VERIlere ulasmak icin sistemden basic info talep et
		PROCESSINFOCLASS infoTipi = PROCESSINFOCLASS::ProcessBasicInformation;

		bool ret = false;
		// ana modul yuklenmemis return 0
		if (anaModule == INVALID_HANDLE_VALUE)
		{
			ret = AnaModulYukle();
			if (ret == false)
			{
				throw exception("Ana modul yuklenemedi");
				return false;
			}
		}

		
		DWORD size = 0;
		int donus = -1;

		donus = NtQueryInformationProcess(hIslem, infoTipi, &extra.basicInfo, sizeof(PROCESS_BASIC_INFORMATION), &size);
		// NT fonksiyonlari 0 dan kucukse basarisiz demek
		if (donus < 0) ret = false;


		// Once pebi yukle basic infodan okunan peb structini yukle
		ret = ReadProcessMemory(hIslem, extra.basicInfo.PebBaseAddress ,&extra.peb,sizeof(PEB) , &size);
		if (ret == false)
		{
			throw exception("Program peb bilgisi okunamadi");
			return false;
		}
	
		ret = ReadProcessMemory(hIslem, extra.peb.ProcessParameters, &extra.params, sizeof(RTL_USER_PROCESS_PARAMETERS), &size);
		if (ret == false)
		{
			throw exception("Program parametreleri bellegi okunamadi");
			return false;
		}
		
		commandline = new WCHAR[extra.params.CommandLine.MaximumLength];
		dosyaYolu = new WCHAR[extra.params.ImagePathName.MaximumLength];

		 ret = ReadProcessMemory(hIslem,extra.params.CommandLine.Buffer, commandline ,extra.params.CommandLine.MaximumLength, &size);
		 ret = ReadProcessMemory(hIslem,extra.params.ImagePathName.Buffer, dosyaYolu, extra.params.ImagePathName.MaximumLength, &size);
	
		 if (ret == false)
		 {
			 throw exception("Program path ve cmd bellegi okunamadi");
			 return false;
		 }
		
		
		
		
		return ret;
	}


  public: bool uzakBellekOku(LPCVOID uzakBellek,LPVOID yuklenecekBuffer,SIZE_T okunacakboyut,SIZE_T* okunanboyut)
  {
	  bool ret = false;
	  // islem acilmamis
	  if (hIslem == INVALID_HANDLE_VALUE) return false;

	  ret = ReadProcessMemory(hIslem,uzakBellek, yuklenecekBuffer, okunacakboyut, okunanboyut);
	  return ret;
  }

  public: bool uzakBellekYaz(LPVOID uzakBellek, LPVOID yazilacakbuffer, SIZE_T yazilacakboyut, SIZE_T* yazilanboyut)
  {
	  bool ret = false;
	  // islem acilmamis
	  if (hIslem == INVALID_HANDLE_VALUE) return false;

	  ret = WriteProcessMemory(hIslem,uzakBellek,yazilacakbuffer, yazilacakboyut, yazilanboyut);
	  return ret;
  }

  public: char* uzakBellekYarat(int boyut,void* hedefptraddr = NULL,DWORD allocationtype = MEM_COMMIT | MEM_RESERVE,DWORD protectionflags = PAGE_EXECUTE_READWRITE)
  {
	  bellekblogu mem;

	  char* hedefbellek = (char*) VirtualAllocEx(hIslem, hedefptraddr, boyut, allocationtype, protectionflags);
	  mem.ptr = hedefbellek;
	  mem.boyut = boyut;
	  createdmemoryblocks.push_back(mem);
	  return mem.ptr;

  }


// eger freetype = MEM_RELEASE ise boyut 0 olmali 
  public: bool uzakBellekKaldir(char* hedef,DWORD boyut = 0,DWORD freetype = MEM_RELEASE)
  {

	 bool ret =  VirtualFreeEx(hIslem, hedef, 0, MEM_RELEASE);

	 return ret;
  }

		  ///// DO NOT USE BROKEEEEEEEEEN PROBABLY
  public: bool Readimporttable()
  {


	  // debug amaçlý
	  DWORD size = 0;

	  VERI tamveri = new VERI(anaModulBilgisi.SizeOfImage);

	  bool ret = uzakBellekOku(anaModulBilgisi.lpBaseOfDll, tamveri.getData(), tamveri.boyut, &size);


	  // 1 is import table
	  int offimport = headers.peheader.OptionalHeader.DataDirectory[1].VirtualAddress;

	  int boyut = headers.peheader.OptionalHeader.DataDirectory[1].Size;

	  int descadet = boyut / sizeof(IMAGE_IMPORT_DESCRIPTOR);
	  PIMAGE_IMPORT_DESCRIPTOR pimpdesc = (PIMAGE_IMPORT_DESCRIPTOR)(tamveri.getData() + offimport);
	  char* baseaddr = tamveri.getData();



	 

	  for (int i = 0; i < descadet - 1; i++)
	  {

		  char* dllname = tamveri.getData() + pimpdesc->Name;
		  imported_dll dll;
		  dll.dllname = dllname;


		  int* pnameoffsets = (int*)(tamveri.getData() + pimpdesc->OriginalFirstThunk);
		  int* pfuncaddroffsets = (int*)(tamveri.getData() + pimpdesc->FirstThunk);




		  do {

			  imported_func fnc;

			  char* str = baseaddr + (*pnameoffsets);
			  int realaddr = (*pfuncaddroffsets);


			  PIMAGE_IMPORT_BY_NAME pimpfunc = (PIMAGE_IMPORT_BY_NAME)str;



			  fnc.funcname = pimpfunc->Name;
			  fnc.hint = pimpfunc->Hint;
			  fnc.funcRVA = realaddr;
			  fnc.offset = (int)((char*)pfuncaddroffsets - baseaddr); // was fnc.offset you gotta rebuild this

			  dll.importedfuncs.push_back(fnc);

			  pnameoffsets++;
			  pfuncaddroffsets++;

		  } while (*pnameoffsets != 0);


		  importeddlls.push_back(dll);
		  pimpdesc++;
	  }



	  return true;
  }



// SUAN SADECE PEHEADER32 OKUYOR DIGER HEADERLAR ICIN KONTROL EDILMEDI
// basarili olursa headers degiskenine module ait header ve section bilgilerini yukler
private : bool headeryukle()
{

	DWORD size = 0;
	bool ret = false;
	if (anaModule == INVALID_HANDLE_VALUE) return false;
	

	VERI firstheader = new VERI(sizeof(IMAGE_DOS_HEADER));
	
	int baseaddr = (int)anaModulBilgisi.lpBaseOfDll;

	ret = uzakBellekOku(anaModulBilgisi.lpBaseOfDll, firstheader.getData(), firstheader.boyut, &size);

	
	

	PIMAGE_DOS_HEADER header = (PIMAGE_DOS_HEADER)firstheader.getData();

	if (header->e_magic == IMAGE_DOS_SIGNATURE) // EGER DOS MAGIC NUMBER GECERLIYSE DOSHEADER BILGILERINI YUKLE
	{
		veriTasi(&headers.dosHeader, firstheader, sizeof(IMAGE_DOS_HEADER));


				



		int optheaderoffset = headers.dosHeader.e_lfanew;

		// processdeki optional headerin bulundugu adresi al 
		char* pheader =(char*) baseaddr + optheaderoffset;

		IMAGE_NT_HEADERS32 optheader;

		ret = uzakBellekOku(pheader, &optheader, sizeof(IMAGE_NT_HEADERS32), &size);


		// pe bilgisini kaydet
		veriTasi(&headers.peheader,&optheader, sizeof(IMAGE_NT_HEADERS32));


		int sectionsayisi = optheader.FileHeader.NumberOfSections;
		int sectiontabloboyut  = sectionsayisi * sizeof(IMAGE_SECTION_HEADER);


		// base address  + opt header + sectiontablesize = PE header size  
		int toplamboyut = optheaderoffset + sizeof(IMAGE_NT_HEADERS32) + sectiontabloboyut;
	
		
		

		VERI allheaderdata = new VERI(toplamboyut);

		ret = uzakBellekOku(anaModulBilgisi.lpBaseOfDll, allheaderdata.getData(), allheaderdata.boyut, &size);
	

		int offsetsectiontable = optheaderoffset + sizeof(IMAGE_NT_HEADERS32);

		PIMAGE_SECTION_HEADER psection = (PIMAGE_SECTION_HEADER) (allheaderdata.getData() + offsetsectiontable);
		
		// section bilgilerini yukle
		for (int i = 0; i < sectionsayisi ; i++)
		{
			IMAGE_SECTION_HEADER sect = *psection;
			headers.sections.push_back(sect);
			
			psection++;

		}

	
		
			  
		return true;

	}

	return false;
}






bool AnaModulYukle()
	{

		bool ret = false;
		 
		
		DWORD totalneeded = 0;
		ret = EnumProcessModules(hIslem, &anaModule, sizeof(HMODULE), &totalneeded);
		numberOfModules = totalneeded / sizeof(HMODULE);

		
		

		ret = GetModuleInformation(hIslem, anaModule, &anaModulBilgisi, sizeof(MODULEINFO));

	
		
		HMODULE* othermodules = new HMODULE[numberOfModules-1];

		ret = EnumProcessModules(hIslem, othermodules,totalneeded,&totalneeded);


		// ana modulu yok say
		for (int i = 1; i < numberOfModules; i++)
		{

			modul module;
			module.hModule = othermodules[i];
			ret = GetModuleInformation(hIslem, module.hModule, &module.info, sizeof(MODULEINFO));
			digerModuller.push_back(module);

			GetModuleBaseName(hIslem, module.hModule, module.baseName, sizeof(module.baseName));
			int donus = GetModuleFileName(module.hModule, module.filename, sizeof(module.baseName));

			
			if (ret == false) return false; 
		}


		return ret;


	}


// Get the threads running on current process
bool threadleriYukle()
{


	bool ret = false;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, ID);

	if (hSnap == INVALID_HANDLE_VALUE) 
	{
		throw exception("snapshot yuklenemedi");

		return false;
	}



	THREADENTRY32 th32;


	th32.dwSize = sizeof(THREADENTRY32);
	ret = Thread32First(hSnap, &th32);
	if (ret == false) { throw exception("threadlar alinamadi"); return false; }

	if (th32.th32OwnerProcessID == ID)
	{

		Thread th = Thread(th32.th32ThreadID);
		threadler.push_back(th);


	}


	do
	{
		if (th32.th32OwnerProcessID == ID)
		{
			
			Thread th = Thread(th32.th32ThreadID);
			threadler.push_back(th);
		
		
		}
	} 
	while (Thread32Next(hSnap, &th32));

	CloseHandle(hSnap);


	return true;

}



public: operator HANDLE()
{

	return this->hIslem;
}
};















































































































































































class IslemYonetici
{
private:
	HANDLE hIslem;

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
		HANDLE hSnap = 0;
		MODULEENTRY32 modul;

		
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




		THREADENTRY32* te32 =(THREADENTRY32*) yiginAyir(sizeof(THREADENTRY32));
		te32->dwSize = sizeof(THREADENTRY32);
		bool ret = false;
		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, islembilgileri.ID);
		ret = Thread32First(hSnap, te32);
		if (ret == true)
		{
			do {

				if(te32->th32OwnerProcessID == islembilgileri.ID)
				islembilgileri.threadList.push_back(*te32);

			} while (Thread32Next(hSnap, te32));

		}
		CloseHandle(hSnap);
		
		
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

	bool BellekOku(int* Adress,int Byte_Boyut,char* VERI){
		int okunan = 0;
		ReadProcessMemory(hIslem,Adress,VERI,Byte_Boyut,(SIZE_T*)&okunan);
		if(okunan > 0)
			return true;
		else
			return false;

	}
	bool BellekYaz(int* Adres,int* VERI,int Byte_Boyut){
		int yazilan = 0;
		WriteProcessMemory(hIslem,(LPVOID)Adres,(LPCVOID)VERI,Byte_Boyut,(SIZE_T*)&yazilan);

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


	bool DosyaYolu(char* &VERI)
	{
		char* ret = (char*) malloc(1024);
		if( (GetModuleFileNameExA(hIslem,(HMODULE)islembilgileri.hModul[0],ret,1024)) != 0)
		{
			VERI = ret;
			return true;

		}
		return false;
	}
 operator HANDLE(){
	 return hIslem;
 }
};




class Islemler
{
	typedef struct _IslemListesi {
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
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hProcessSnap); return 0;
		}
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(hProcessSnap, &pe32))
		{
			CloseHandle(hProcessSnap); return 0;
		}

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

		} while (Process32Next(hProcessSnap, &pe32));
		CloseHandle(hProcessSnap); return 1;
	}

inline int IslemKapat(int id, int &CikisKodu)
	{

		if (TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, id), CikisKodu))
			return 1;
		else
			return 0;
	}

	inline
		int IslemKapat(HANDLE hIslem, int &CikisKodu)
	{
		if (TerminateProcess(hIslem, CikisKodu))
			return 1;
		else
			return 0;
	}

	inline
		int IslemKapat(int id)
	{

		if (TerminateProcess(OpenProcess(PROCESS_TERMINATE, false, id), NULL))
			return 1;
		else
			return 0;
	}

	inline
		int IslemKapat(HANDLE hIslem)
	{
		if (TerminateProcess(hIslem, NULL))
			return 1;
		else
			return 0;
	}
	inline
		int ISIM_id(char* IslemAdý) {
		int Boyut = islemlistesi.IslemID.size();
		for (int i = 0; i < Boyut; i++) {
			string dnm = islemlistesi.IslemAdi[i];
			if ((islemlistesi.IslemAdi[i].compare(IslemAdý)) == 0)
				return (islemlistesi.IslemID[i]);

		}
		return -1;
	}

	inline
		bool ID_handle(int id, HANDLE &hIslem) {


		hIslem = OpenProcess(PROCESS_ALL_ACCESS, false, id);
		if (hIslem != INVALID_HANDLE_VALUE)
			return 1;
		else
			return 0;
	}

	bool ID_handle(int id, HANDLE &hIslem, DWORD Izin) {


		hIslem = OpenProcess((PROCESS_ALL_ACCESS | Izin), false, id);
		if (hIslem != INVALID_HANDLE_VALUE)
			return 1;
		else
			return 0;
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


#endif