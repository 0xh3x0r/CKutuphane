#pragma once
#ifndef THREAD_H
#define THREAD_H
#pragma region TANIMLAMALAR
#ifndef BYTE_H
#include <Byte.h>
#endif
#ifndef _WINDOWS_
#define _WINDOWS_
#include <Windows.h>
#endif
#ifndef _IOSTREAM_
#include <iostream>
using namespace std;
#endif
#pragma endregion

typedef LPVOID Parametreler;

 typedef struct _Veritasiyici
{
	Parametreler veri;
	bool y?klendi;
}Veritasiyici;
 #pragma region _Veritasiyici A??klama
/* A?IKLAMA!
 E?er Bir thread fonksiyonuna char* gibi veriler parametre olarak yollanacaksa
 Program threadin ?a?r?ld?g? fonksiyonu terk etti?inde bu char* free edilir
 Ve dolay?s?yla thread bu char* veriyi kullan?rken hata olu?ur.
 Bu struct ile Gerekli veri thread de kopyalan?r ve kopyalama i?lemi bitince 
 y?klendi true yap?l?r program bu de?i?keni bekler t?m veriler kopyalan?nca ??k???n? yapabilir.

 Kullan?m:

Thread t;
			Veritasiyici g?venli_parametre;
			g?venli_parametre.veri = (Parametreler)Fonksiyon.c_str();
			g?venli_parametre.y?klendi = false;
			t.Baslat(&g?venli_parametre,(int*)MesajGoster);
			while(!g?venli_parametre.y?klendi) { Sleep(100); }; // Threade g?nderilen parametreler thread da kopyaland? m?
			                                                    // Thread y?klendi Art?k normal ak??a devam edilebilir


 ?a??r?lan Fonksiyon

 inline int MesajGoster(Veritasiyici &g?venliparam){

	string Param = (char*)g?venliparam.veri;
	g?venliparam.y?klendi = true;
	MessageBoxA(NULL,Param.c_str(),"",0);

	return 1;
}

*/
#pragma endregion

class Thread
{
public:
HANDLE hThread;
int Durum;
public:
  Thread()
  {
	hThread =(HANDLE) -1;
	Durum = -5;
	  // Hi?bir?ey yap
  }


public: void UzakThreadBaslat(Parametreler params,void* Fonksiyon,HANDLE hIslem)
  {
	  hThread = CreateRemoteThread(hIslem,NULL,0,
		  (LPTHREAD_START_ROUTINE)(DWORD WINAPI)Fonksiyon,params,0,NULL);
	  if(hThread == INVALID_HANDLE_VALUE)
		  Durum = -5;
		else
        Durum = 1;
  }
public:
	void Baslat(Parametreler params,void* Fonksiyon)
	{
	  hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Fonksiyon,params,0,NULL);
     if(hThread == INVALID_HANDLE_VALUE)
	  Durum = -5;
	else
     Durum = 1;
	};
public:
	void Durdur()
	{
		SuspendThread(hThread);
	Durum = 0;
	}
public:
	void Devam()
	{
		ResumeThread(hThread);
	Durum = 1;
	}
public:
	void Kaldir()
	{
		TerminateThread(hThread,1);
		CloseHandle(hThread);
		Durum = -5;
	}
 


operator HANDLE(){
	return hThread;
}
operator HANDLE&(){
	return hThread;
}
operator HANDLE*(){
	return &hThread;
}

operator const HANDLE(){

	return hThread;
}
};


class Mutex
{
public:
	HANDLE hMutex;

public:
	Mutex()
	{
		hMutex = CreateMutexA(NULL,FALSE,NULL);
	};

public:
	bool Bekle()
	{
		DWORD Sonuc;
       Tekrar:
		Sonuc = WaitForSingleObject(hMutex,INFINITE);
		if(Sonuc == 0) // Obje serbest de?il tekrar dene
	    return 1;
		else if(Sonuc == WAIT_ABANDONED)
			ExitThread(0);
	
		goto Tekrar;

	}
public:
	void Serbest()
	{
		if(!ReleaseMutex(hMutex))
		{
          int hata = GetLastError();

		}
	}
public:
	void Kapat()
	{
		if(hMutex != INVALID_HANDLE_VALUE)
		{
		CloseHandle(hMutex);
		}
	}
};


typedef struct _MutexParam
{
	Mutex *mutex;
	Parametreler veri;

}MutexParam;








class ThreadListesi
{
private:
	HANDLE* hList;
private:
	Thread* tl;
public:
	int Adet;
Byte byte;
public:
	ThreadListesi(int adet)
	{
		byte.YeniOlustur(sizeof(Thread) * adet);
		

	for(int i =0 ; i < adet; i++){
		Thread t;
		byte.Ekle((char*)&t,sizeof(t));
	}// Son
	tl = (Thread*)(char*)byte;
	Adet=adet;
} // Constructor

public:
ThreadListesi()
{
 Adet = 0;

}
public:
	Thread& operator[](int Sira)
	{
		
		return tl[Sira];
	};

public:
	inline 
		void hlistguncelle()
	{
          	 hList = (HANDLE*)yiginAyir((sizeof(int)*Adet));
   for(int i = 0;i<Adet;i++){
	   hList[i] = tl[i].hThread;
   }
  
	}
public: 
	operator HANDLE*()
	{
	hlistguncelle();
	return (HANDLE*)hList;

	}

	public:
	int ThreadBekle(int adet)
	{
		hlistguncelle();
		
Tekrar:
		int kadet = adet;
		for(int i = 0; i < adet;i++)
		{
			DWORD sonuc = 0;
			GetExitCodeThread(hList[i],&sonuc);
		if( sonuc != STILL_ACTIVE )
			kadet--;
		}
		if(kadet == 0)
		return 1;
		else
			goto Tekrar;
	}
public:
	void ThreadEkle()
	{ 

       if(Adet != 0){
		Thread t;
		byte.Ekle((char*)&t,sizeof(Thread));
		Adet++;
		tl = (Thread*)(char*)byte;
		
}
else
{
   Thread t;
   byte.Ekle((char*)&t,sizeof(Thread));
   tl = (Thread*)(char*)byte;
   Adet++;
   

}

	}

	~ThreadListesi()
	{
		free(hList);
		free(tl);
		byte.Kaldir();

	}
};
#endif THREAD_H