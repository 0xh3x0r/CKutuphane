#pragma once
#ifndef MULTITHREADSERVER_H
#define MULTITHREADSERVER_H
#ifndef SOCKET_H
#include <Socket.h>
#endif

#ifndef _IOSTREAM_
#include <iostream>
using namespace std;
#endif



#ifndef THREAD_H
#include <Thread.h>
#endif

#ifndef METIN_H
#include <Metin.h>
#endif

#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _ALGORITHM_
#include <algorithm>
#endif




/*
	SERVER PARAMETRELERI MEMORY LEAK'A NEDEN OLUYOR OLABILIR(Parametreler degiskeni , surekli newleme var ve delete yok)

*/


typedef GelenSocket* GidenSocket; // Karmasa olmamasi icin

typedef struct _GidenBaglantiBilgiler{
	int ID;
	int Sýra;
	GidenSocket gSock;
}GidenBaglantiBilgiler;






typedef struct _BaglantiKabulBilgiler{
	vector<int>* IDList;
    vector<GelenSocket>* socketlistesi;
	Server* serverSocket;
	GelenSocket* gSock;
	Mutex* bilgilerMutex;
	string IP;
	Metin PORT;
}BaglantiKabulBilgiler;





// Standart Kimlik atama islemleri 
static void BaglantiKabul(BaglantiKabulBilgiler bilgiler) 
{
	if(bilgiler.IDList->size() == 0)
		bilgiler.IDList->push_back(0);
	else
		bilgiler.IDList->push_back(bilgiler.IDList->size()-1);
	bilgiler.socketlistesi->push_back(*bilgiler.gSock);

}

// Event tanimlamalari
typedef void (*BaglantiKabulEvent)(BaglantiKabulBilgiler&);
typedef void (*BaglantiGittiEvent)(GidenBaglantiBilgiler&);


class MultiThreadServer
{



static void ServerIslemleri(int* Parametreler){
		
		BaglantiKabulEvent baglantiKabulEvent = (BaglantiKabulEvent)*Parametreler;
		Parametreler--;
		Server* serverSocket = (Server*)(*Parametreler);
		Parametreler--;
		vector<GelenSocket>* socketlist = (vector<GelenSocket>*)*Parametreler;
		Parametreler--;
		vector<int>* IDList = (vector<int>*)*Parametreler;
		Parametreler--;
		Mutex* bilgilerMutex = (Mutex*)*Parametreler;

Tekrar: 
		GelenSocketBilgiler gSockb;
		SOCKET s = serverSocket->kabulBaslat(gSockb);
	
	 
	   
		if(s != INVALID_SOCKET)
		{
			bilgilerMutex->Bekle();
			GelenSocket* gSock = new GelenSocket(s);
			BaglantiKabulBilgiler* kBilgiler = new BaglantiKabulBilgiler();
			kBilgiler->IDList = IDList;
			kBilgiler->socketlistesi = socketlist;
			kBilgiler->gSock = gSock;
			kBilgiler->IP = gSockb.host_ip;	

			kBilgiler->PORT = (htons(gSockb.PORT));
			bilgilerMutex->Serbest();
			if(baglantiKabulEvent == NULL)
			BaglantiKabul(*kBilgiler);
			else
			{
				kBilgiler->bilgilerMutex = bilgilerMutex;
				Thread thKimlik;
				thKimlik.Baslat(&*kBilgiler,baglantiKabulEvent);
			}

		}
		goto Tekrar;
	}

public:
	BaglantiKabulEvent BaglantiKabul_Event;
	BaglantiGittiEvent BaglantiGitti_Event;
	vector<int> IDList;
	vector<GelenSocket> socketlist;
	Server* server;
	int Durum;
	int* Parametreler;
	Mutex* bilgilerMutex;


private:
	Thread serverThread;




public:
	MultiThreadServer(int PORT)
	{
        Durum = -1;
	
		BaglantiKabul_Event = NULL;
		BaglantiGitti_Event = NULL;
		// Pointerlarý NULL olarak yükle herhangi bir fonksiyon atandý mý testi yapabilmek için.
		bilgilerMutex = (Mutex*)(int*)malloc(sizeof(Mutex));
		*bilgilerMutex = Mutex();
		server = (Server*)(int*)malloc(sizeof(Server));
		*server = Server(PORT);
		// Server socketi dinlemedeyse hazir konumuna gec.( Baglanti kabulu Baslat() Fonksiyonu ile yapilir )
		if(server->Durum == SERVER_DINLEMEDE)
	    Durum = 1;



	}




// Eger gonderilecek tum parametreler ayarlanmazsa access violation alý	
public: void Baslat()
	{
		if(Durum == 1)
		{
	    // Server islemlerini yapýcak fonksiyona gerekli pointerlarý gonder.

	    Parametreler = (int*) malloc(sizeof(int*) *5);
	    *Parametreler =(int)&(*bilgilerMutex);
	    Parametreler++;
	    *Parametreler = (int)&IDList;
		Parametreler++;
	    *Parametreler= (int)&socketlist;
	    Parametreler++;
	    *Parametreler = (int)&(*server);
		Parametreler++;
		*Parametreler = (int)BaglantiKabul_Event;
	     serverThread.Baslat(Parametreler,(int*)ServerIslemleri);
	     Durum = 2;	
		}
	}




public: void Durdur()
	{
		if(Durum = 2)
		{
		serverThread.Durdur();
		Durum = 3;
		}
	}




public: void Devam()
	{
		if(Durum = 3)
		{
		serverThread.Devam();
		Durum = 2;
		}
	}








public: bool rnVeriAl(int ID,Byte &Veri)
	{
	bilgilerMutex->Bekle();

	int index =  ( std::find(IDList.begin(),IDList.end(),ID) - IDList.begin() );
	GelenSocket Socket = socketlist[index].socket_;
	bilgilerMutex->Serbest();
		   
	
	int gVeri = Socket.rnVeriAl(Veri);
	if(gVeri > 0)
	{
	 return 1;
	}
	else
	{
		bilgilerMutex->Bekle();



		IDList.erase(IDList.begin()+index);
		
		socketlist.erase(socketlist.begin()+index);
		bilgilerMutex->Serbest();
		if(BaglantiGitti_Event != NULL)
		{
		GidenBaglantiBilgiler bilgiler;
		bilgiler.ID = ID;
		bilgiler.Sýra = index;
		bilgiler.gSock = &Socket;
		BaglantiGitti_Event(bilgiler);
		}

		
		return 0;
	}


	}





public: bool rnVeriGonder(int ID,Byte Veri){

if(Veri.Heap)
{

	bilgilerMutex->Bekle();

	int index = ( std::find(IDList.begin(),IDList.end(),ID) - IDList.begin() );
	GelenSocket Socket = socketlist[index].socket_;

	bilgilerMutex->Serbest();

	Veri +="\r\n";
	int gVeri = Socket.veriGonder(Veri,Veri.Boyut);
	if(gVeri > 0)
	{
	 return 1;
	}
	else
	{
		bilgilerMutex->Bekle();
		


		IDList.erase(IDList.begin()+index);
		
		socketlist.erase(socketlist.begin()+index);
		bilgilerMutex->Serbest();
		if(BaglantiGitti_Event != NULL)
		{
		GidenBaglantiBilgiler bilgiler;
		bilgiler.ID = ID;
		bilgiler.Sýra = index;
		bilgiler.gSock = &Socket;
		BaglantiGitti_Event(bilgiler);
		}
		
		

		return 0;
	}
}
			return 0;
}
	






};


#endif