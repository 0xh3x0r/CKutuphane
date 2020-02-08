#pragma once

#ifndef FTPPROT_H
#include "ftpprot.h"
#endif

void thread_Vekil_rnVeriAl(VekilParams &params)
    {
		params.Donus = params.istemci->rnVeriAl(*params.veri);
	    params.istemci->BaglantiKapat();
    }


void thread_Vekil_VeriGonder(VekilParams &params)
   {
	   int Giden = 0;
	   if(params.EK_PARAM == 0)
	   {
		    params.Donus = params.istemci->veriGonder(*params.veri,(*params.veri).Boyut);
	   }
	   else{
		   params.Donus = 1;
	   while(Giden < (*params.veri).Boyut)
	   {  
		  char* veri;
		  veri = (char*)*params.veri;
		  int _Giden =0;
		  _Giden = params.istemci->retveriGonder((veri+Giden),(*params.veri).Boyut-Giden);
		  if(_Giden > 0){
			  
			  params.Veri_Gonderildi(_Giden,params.EK_PARAM); // Veri_Gonderildi Event
		  Giden += _Giden;
		  }
		  else{
			  int hata = WSAGetLastError();
			  int hata2 = GetLastError();
			  params.Donus = 0; break;}
		 
	   }
	    
		}

	   if(params.Aktarim_Tamamlandi != 0)
	   params.Aktarim_Tamamlandi(params.Donus,params.EK_PARAM);
	   params.istemci->BaglantiKapat();
	   /*
	   FtpIstemci* ftp;
	   ftp = (FtpIstemci*)params.Ptr;
	   char* Temizle = (char*)malloc(255);
	   ftp->veriAl(Temizle);
	   */
	   delete params.istemci;
	   delete &params;
	   ExitThread(0);
   }


void thread_Vekil_VeriAl(VekilParams &params)
    {
		params.Donus = params.istemci->veriAl(*params.veri,(*params.veri).Boyut);
	
    }