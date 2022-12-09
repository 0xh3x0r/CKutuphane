#pragma once
#ifndef SOCKET_H
#define SOCKET_H

#pragma comment(lib, "wininet.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#pragma comment(lib, "iphlpapi")


// MAKE SURE THAT WINSOCK.H DOESNT GET INCLUDED BEFORE THIS HEADER! IF WINDOWS.H included before this HEADER IT WILL REDIFINE WINSOCK APIS!



#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#ifndef _IOSTREAM_
#include <iostream>
using namespace std;
#endif

#ifndef _WINSOCK2API_
#include <winsock2.h>
#endif

#ifndef _WS2TCPIP_H_
#include <ws2tcpip.h>
#endif

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif


#ifndef _INC_STDIO
#include <stdio.h>
#endif

#ifndef __IPHLPAPI_H__
#include <iphlpapi.h>
#endif

#ifndef _WININET_
#include <WinInet.h>
#endif


#ifndef THREAD_H
#include <Thread.h>
#endif


#define SOCKET_YUKLENEMEDI (-3)
#define BAGLANTI_VAR (1)
#define BAGLANTI_BASARISIZ (-4)
#define SOCKET_HATASI (-1)
#define BAGLANTI_YOK (-2)
#define SOCKET_KAPATILDI (-5)
#define SERVER_DINLEMEDE (2)
#define SERVER_BINDHATA (-6)
#define SERVER_HAZIR (3)
#define P_BITIS ("\r\n")
#define ZAMANASIMI 10 



class Socket{

 typedef void (*VeriAlindiEvent)(int& Byte_Boyut,Socket&);
 typedef void (*VeriGonderildiEvent)(int& Byte_Boyut,Socket&);


public:
	int Durum;
	WSAData str_Ws; 
	SOCKET socket_;
	struct sockaddr_in struct_socketVeri;
	struct hostent* hostbilgi;
	char* Domain_IP;
	int PORT;

public : VeriAlindiEvent veriAlindiEvent;

public : VeriGonderildiEvent veriGonderildiEvent;



public: Socket()
	{
		 veriAlindiEvent = NULL;
		 veriGonderildiEvent = NULL;
	}




public: Socket(char* _Domain_IP,int _PORT) 
{

	Domain_IP = _Domain_IP;
	PORT = _PORT; 
	veriAlindiEvent = NULL;
	veriGonderildiEvent = NULL;
	WSAStartup(MAKEWORD(2,2),&str_Ws);
	socket_ = INVALID_SOCKET;
	socket_ = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

	if(socket_ == INVALID_SOCKET){
		WSACleanup();
	Durum = SOCKET_YUKLENEMEDI;
	} 

    if((struct_socketVeri.sin_addr.S_un.S_addr = inet_addr(Domain_IP)) == 0xffffffff) // IP Çevirilemiyor Domain çevirmeyi dene
	if((hostbilgi = (hostent*)gethostbyname(Domain_IP)) == 0)
	Durum = BAGLANTI_BASARISIZ; 
	else
	{
	struct_socketVeri.sin_addr.S_un.S_addr = *(u_long *)hostbilgi->h_addr_list[0];
	struct_socketVeri.sin_port = htons((unsigned short) PORT);
	struct_socketVeri.sin_family = AF_INET;
    
	int zamanasimi_ms = 300000;  
    setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO,(const char*)&zamanasimi_ms,sizeof(int));
	if(!connect(socket_,(struct sockaddr*)&struct_socketVeri,sizeof(struct_socketVeri)))// 0 = Baðli
	Durum = BAGLANTI_VAR;
	else
		Durum = BAGLANTI_BASARISIZ;
	}
	else // IP
	{
	
	struct_socketVeri.sin_port = htons((unsigned short) PORT);
	struct_socketVeri.sin_family = AF_INET;
	int zamanasimi_ms = 300000;  
    setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO,(const char*)&zamanasimi_ms,sizeof(int));
	if(!connect(socket_,(struct sockaddr*)&struct_socketVeri,sizeof(struct_socketVeri)))// 0 = Baðli
	Durum = BAGLANTI_VAR;
	else
		Durum = BAGLANTI_BASARISIZ;
	}
	
}



// Socket classinin constructorsuz sonradan baslatilabilmesi icin ek islevsellik(Constructor ile ayni islevi goruyor)
// Durum degiskenini ayarliyor
public: void Baslat(char* _Domain_IP, int _PORT)
{

	Domain_IP = _Domain_IP;
	PORT = _PORT;
	veriAlindiEvent = NULL;
	veriGonderildiEvent = NULL;
	WSAStartup(MAKEWORD(2, 2), &str_Ws);
	socket_ = INVALID_SOCKET;
	socket_ = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (socket_ == INVALID_SOCKET) {
		WSACleanup();
		Durum = SOCKET_YUKLENEMEDI;
	}

	if ((struct_socketVeri.sin_addr.S_un.S_addr = inet_addr(Domain_IP)) == 0xffffffff) // IP Çevirilemiyor Domain çevirmeyi dene
		if ((hostbilgi = (hostent*)gethostbyname(Domain_IP)) == 0)
			Durum = BAGLANTI_BASARISIZ;
		else
		{
			struct_socketVeri.sin_addr.S_un.S_addr = *(u_long *)hostbilgi->h_addr_list[0];
			struct_socketVeri.sin_port = htons((unsigned short)PORT);
			struct_socketVeri.sin_family = AF_INET;

			int zamanasimi_ms = 300000;
			setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&zamanasimi_ms, sizeof(int));
			if (!connect(socket_, (struct sockaddr*)&struct_socketVeri, sizeof(struct_socketVeri)))// 0 = Baðli
				Durum = BAGLANTI_VAR;
			else
				Durum = BAGLANTI_BASARISIZ;
		}
	else // IP
	{

		struct_socketVeri.sin_port = htons((unsigned short)PORT);
		struct_socketVeri.sin_family = AF_INET;
		int zamanasimi_ms = 300000;
		setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&zamanasimi_ms, sizeof(int));
		if (!connect(socket_, (struct sockaddr*)&struct_socketVeri, sizeof(struct_socketVeri)))// 0 = Baðli
			Durum = BAGLANTI_VAR;
		else
			Durum = BAGLANTI_BASARISIZ;
	}


}


public:
	void bilgiAl(){ // structVeri struct una atar.

		int boyut = sizeof(struct_socketVeri);
        getsockname(socket_,(struct sockaddr*)&struct_socketVeri,&boyut);
	}




// Veri gonderilene kadar bekler
int veriGonder(char* veri,int Byte_Boyut){

	int yollanan = 0;
	while(yollanan < Byte_Boyut)
	
	{
	 yollanan += send(socket_,veri,Byte_Boyut,0);
	
	 if(yollanan < 0)
		{ Durum = BAGLANTI_YOK; return -1; }
	
	 if(veriGonderildiEvent != NULL)
	 {
		 veriAlindiEvent(yollanan,*this);

	 }

	} // w1
	 return yollanan; // Gönderildi!
}







// Her paketi gönderdikten sonra geri döner veriGonderildiEvent tetiklenmez
int retveriGonder(char* veri,int Byte_Boyut)
{
if(Byte_Boyut > 32000)
	Byte_Boyut = 32000;
int Giden = 0;
Giden += send(socket_,veri,Byte_Boyut,0);
return Giden;

}




// Veri gonderdikten sonra geri doner event Tetiklenmez
public: int veriAl(char* veri)
	{
		int gByte = recv(socket_,veri,255,0);
	    if(gByte <= 0)
		{
			Durum = BAGLANTI_YOK; return -1;
		}
		
		return gByte;
	}






 // Byte_Boyut kadar veri gelene kadar bekler 
public: int veriAl(char* veri,int Byte_Boyut)
{
	int gByte = 0;
   while(gByte < Byte_Boyut)
   {
   
	int gbSayi = recv(socket_,veri,(Byte_Boyut-gByte),0);
    veri += gbSayi;
   
   if(gbSayi <= 0)
   { 
	 Durum = BAGLANTI_YOK; return -1;
   
   }

   gByte += gbSayi;
  
  if(veriAlindiEvent != NULL)
  {
	  veriAlindiEvent(gbSayi,*this);
  }


   }
    veri -= gByte;
    return gByte;
}







// Socket te bekleyen okunmamýþ verinin boyutunu alýr
int PaketKontrol()
{
	u_long Boyut = NULL;
	ioctlsocket(socket_,FIONREAD,&Boyut);
	return (int)Boyut;
}






// Arta kalmýs veri varsa temizle
void PaketTemizle(){

	int Sonuc = PaketKontrol();
	if(Sonuc)
	{
    char* TemizlemeBuffer = (char*) malloc(Sonuc);
	recv(socket_,TemizlemeBuffer,Sonuc,0);
	}
}



// Akim(Paket)(\r\n)(0x0d , 0x0a) Sonlandirici gelene Kadar tekrar eder.
int rnVeriAl(Byte &veri)
{
	
	int donus = 0;
    Byte veri2; // *
	veri2.YeniOlustur(65536);
    
Tekrar:
	donus = recv(socket_,veri2,65536,0);
	if(donus > 0)
	{
	*(char*)veri2[donus] = '\x00'; // Doðru kiyaslama için Null terminator byte ekle
	  if((strcmp((veri2[donus-2] ),"\r\n")) != 0) // Sonda \r\n var mi ?
	  {
		 
		  veri.Ekle(veri2,donus);
		  
		  if(veriAlindiEvent != NULL)
			  veriAlindiEvent(donus,*this);

		  goto Tekrar;
	  }
	  else // \r\n var
	  {

          veri.Ekle(veri2,donus-2); // Bypass Akim(Paket)(\r\n)(0x0d , 0x0a) 
		  veri2.Kaldir();
		  return veri.Boyut;
	  }
	}

	else{
		veri2.Kaldir(); Durum = BAGLANTI_YOK; return -1;
	}
	
	
	
}





// \r\n Veri gelene kadar bekler
public: bool Bekle()
	{
		Byte veri;
		if(this->rnVeriAl(veri) >= 0)
		{ veri.Kaldir(); return true; }
		else
		{ veri.Kaldir(); return false; }

	}

// Socketleri senkronize edebilmek icin Bekleyen Socketi Hazir konumuna gecirmek icin \r\n gonderir
public: bool Hazýr()
	{
	  char* Veri = "\r\n";
	  if(this->veriGonder(Veri,2) >= 0)
		  return true;
	  else
		  return false;
	}

public: void TekrarBaglan()
{
 
	this->BaglantiKapat();
 socket_ = INVALID_SOCKET;
 socket_ = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
 if((struct_socketVeri.sin_addr.S_un.S_addr = inet_addr(Domain_IP)) == 0xffffffff) // IP Çevirilemiyor Domain çevirmeyi dene
	if((hostbilgi = (hostent*)gethostbyname(Domain_IP)) == 0)
	Durum = BAGLANTI_BASARISIZ; 
	else
	{
	struct_socketVeri.sin_addr.S_un.S_addr = *(u_long *)hostbilgi->h_addr_list[0];
	struct_socketVeri.sin_port = htons((unsigned short) PORT);
	struct_socketVeri.sin_family = AF_INET;
	if(!connect(socket_,(struct sockaddr*)&struct_socketVeri,sizeof(struct_socketVeri)))// 0 = Baðli
	Durum = BAGLANTI_VAR;
	else
		Durum = BAGLANTI_BASARISIZ;
	}
	else // IP
	{
	
	struct_socketVeri.sin_port = htons((unsigned short) PORT);
	struct_socketVeri.sin_family = AF_INET;
	if(!connect(socket_,(struct sockaddr*)&struct_socketVeri,sizeof(struct_socketVeri)))// 0 = Baðli
	Durum = BAGLANTI_VAR;
	else
		Durum = BAGLANTI_BASARISIZ;
	}
 
}

public: void BaglantiKapat()
{
 if(!closesocket(socket_))
  Durum = SOCKET_KAPATILDI;
 else
  Durum = SOCKET_HATASI;

}


};


	typedef struct GelenSocketBilgiler{
		char* host_ip;
		short PORT;

	} GelenSocketBilgileri;


class Server{

 WSAData str_Ws; 
 SOCKET	ServerSocket;
  struct sockaddr_in serverBilgileri;
 
public:
 int Durum;

public:
	Server()
	{
	 Durum = SERVER_HAZIR;
	}
public:
	Server(short PORT){
		WSAStartup(MAKEWORD(2,2),&str_Ws);
		ServerSocket = socket(AF_INET,SOCK_STREAM,0);
		if(ServerSocket == SOCKET_ERROR)
			Durum = SOCKET_YUKLENEMEDI;
		serverBilgileri.sin_addr.s_addr=INADDR_ANY;
		serverBilgileri.sin_family=AF_INET;
		serverBilgileri.sin_port = htons(PORT);
		if(!bind(ServerSocket,(struct sockaddr*)&serverBilgileri,sizeof(serverBilgileri)))
		Durum = SERVER_HAZIR;
		else
		Durum = SERVER_BINDHATA;
		if(!listen(ServerSocket,10))
			Durum = SERVER_DINLEMEDE;
		else
			Durum = SOCKET_HATASI;
	
	
	};
public:
	SOCKET kabulBaslat(GelenSocketBilgileri  &gBilgiler){

		 SOCKET g_baglanti_Socket;
        
		sockaddr_in gelenSock_bilgiler; int gBilgi_Boyut = sizeof(sockaddr_in);
		memset(&gelenSock_bilgiler,0x00,0x10);
                                                                             //** In&Out  
		g_baglanti_Socket = accept(ServerSocket,(struct sockaddr*)&gelenSock_bilgiler,&gBilgi_Boyut);	
		if(g_baglanti_Socket == SOCKET_ERROR)
		{
			int hata =GetLastError();

		}							  
		gBilgiler.host_ip = inet_ntoa(gelenSock_bilgiler.sin_addr);
		gBilgiler.PORT = gelenSock_bilgiler.sin_port;
		return g_baglanti_Socket;
	}
	public:
 
public:
	void Kapat()
	{
		closesocket(ServerSocket);
	};

};

/*
class GelenSocket
{

public:
	SOCKET gSock;
public:
	GelenSocket(SOCKET S)
	{
		gSock = S;
	};


	int veriGonder(char* veri,int Byte_Boyut){
    PaketTemizle();
	int yollanan = send(gSock,veri,Byte_Boyut,0);
	 return yollanan;
}

public:
int veriAl(char* veri,int Byte_Boyut)
{
	int gByte = 0;
   while(gByte < Byte_Boyut){
    int gbSayi = recv(gSock,veri,(Byte_Boyut-gByte),0);
    veri += gbSayi;
   if(gbSayi <= 0)
   { 
	 return -1; }

   gByte += gbSayi;
  
   }
    veri -= gByte;
    return gByte;
}
// Veri gelene kadar bekler.

int rnVeriAl(Byte &veri)
{

	int donus = 0;
    Byte veri2 = ""; // *
	if(veri2.Heap)
	{
	veri2.YeniOlustur(65536);
    
Tekrar:
	donus = recv(gSock,veri2,65536,0);
	if(donus > 0)
	{


	*(char*)veri2[donus] = '\x00'; // Doðru kiyaslama için Null terminator byte ekle


	if((strcmp((veri2[donus-2] ),"\r\n")) != 0 ) // Sonda \r\n var mi ?
	  {
		 
		  veri.Ekle(veri2,donus);
		  goto Tekrar;
	  }
	
	
	  else if(PaketKontrol() == 0) // Kalan veri yok ve  \r\n var
	  {
		  PaketTemizle();
          veri.Ekle(veri2,donus-2); // Bypass Akim(Paket)(\r\n)(0x0d , 0x0a) 
		  veri2.Kaldir();
		  return veri.Boyut;
	  }


	  else // Sonunda \r\n var ama Kalan verilerde var
	  {
		  veri.Ekle(veri2,donus);
		  goto Tekrar;

	  }



	}

	else{
		veri2.Kaldir();  return -1;
	}
}
return -1;
}
// Akim(Paket)(\r\n)(0x0d , 0x0a) Sonlandirici gelene Kadar tekrar eder.

public:
	bool Bekle()
	{
		Byte veri;
		if(this->rnVeriAl(veri) >= 0)
		{ veri.Kaldir(); return true; }
		else
		{ veri.Kaldir(); return false; }

	}

public:
	bool Hazýr()
	{
	  char* Veri = "\r\n";
	  if(this->veriGonder(Veri,2) >= 0)
		  return true;
	  else
		  return false;
	}

// Socket te bekleyen okunmamýþ verinin boyutunu alýr
int PaketKontrol()
{
	u_long Boyut = NULL;
	ioctlsocket(gSock,FIONREAD,&Boyut);
	return (int)Boyut;
}


// Arta Kalmýþ veri varsa temizle
void PaketTemizle(){

	int Sonuc = PaketKontrol();
	if(Sonuc)
	{
    char* TemizlemeBuffer = (char*) malloc(Sonuc);
	recv(gSock,TemizlemeBuffer,Sonuc,0);
	}
}


 public:
	void Kapat(){
closesocket(gSock);
}
};
*/

class GelenSocket : public Socket
{
public:
  GelenSocket(SOCKET S)
  {
	this->socket_ = S;
	veriAlindiEvent = NULL;
	veriGonderildiEvent = NULL;
  }



};
#endif