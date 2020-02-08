#ifndef YIGIN_H
#define YIGIN_H
#endif

#ifndef MAKROLAR_H
#define MAKROLAR_H
#include "Makrolar.h"
#endif
#ifndef BELLEK_H
#define fm_ASM
#include "bellek.h"
#endif
#ifndef BYTE_H
#include "Byte.h"
#endif

#pragma region ACIKLAMA
/*
     ***************   "Logos"   ***************

****** Header Genel Aciklama *******
#1 header "bellek.h"  ihtiyac duyar. Bu header 32 Bit Sistemde intel i5 uzerinde test edilmis assembly kodlarini kullanir
#2 32 Bit alti bir sistemde calismasi icin 16  bit assembly kodlari ile bellek.h fonksiyonlarini deðistir/Genislet ilebilir
#3 64 bit Sistemler icin bir deneme yapilmadi.64 Bit sistemde 64 bit assembly kodlari kullanilmasi daha elverisli olur.
#4 intel harici bir (x8086) islemcide calisip/calismamasi belli deðil.Bu tip bir kararsizliði önlemek icin #define bellek_funcmode fmCPP    yapabilirsiniz.


******* Bu header icin aciklamalar *******
#1 Bu header bir baskasi tarafindan genislet/deðistir ilebilir.
#2 Headerda kullanilan Bellek pointer(datasegment adresleri) tek bir arttirmada bellek_ptr blabla = Blablabellek + 1; Otomatik 1 DWORD Arttirir | blabla++; ayni sekilde.
#3 Virtual alloc kullanilmistir yani Ayri bir bellek sayfasi (Page) acar.


*/
#pragma endregion
#pragma region HEADER TANIMLAMALAR
//////////////////////////////////////////
#define TALEP_STANDART 4*1024
#define  RESERVE_STANDART 4*1024*1024
typedef int* bellek_ptr;
//////////////////////////////////////////
#pragma endregion
inline 
int usAl(int sayi,int us){
	int kopya = sayi;
	for(int sayac = 1;sayac < us;sayac++){
		kopya = sayi*kopya;
	}
	return kopya;
}



template <class T> class Yigin;





template <> class Yigin<int>{
public:

bellek_ptr bellek_Baslangic;
public:

bellek_ptr bellek_Son;
int BosAlan;	

public:
	Yigin(){
    bellek_Baslangic = bellekYarat(RESERVE_STANDART,TALEP_STANDART);
	bellek_Son = bellek_Baslangic;
	BosAlan = TALEP_STANDART / 4;
	};

public:
   int Ekle(int veri)
   {
	if(BosAlan <= 0){
		   bellek_Son = bellekGenislet(bellek_Son,TALEP_STANDART,PAGE_READWRITE);
		   BosAlan = TALEP_STANDART / 4;
	}
	bellek_veriTasi(bellek_Son,veri);
	BosAlan--;	
	bellek_Son++;
	return 1;
   };
   int operator[](int sira){
   return (sira > (bellek_Son - bellek_Baslangic)) ? 0 : *(bellek_Baslangic + sira);
   };
public:
	/// Kullanim:
	/*   int params[] = {0,1,2,9,dinamikint}; 
	     int sira = Array.SiraAl(params,5);
	*/
	int SiraAl(int param[],int Miktar) 
 	{
	bellek_ptr syc = bellek_Baslangic;
	for(;syc < bellek_Son;syc++)
	{
		if( ((*syc) ^ param[0]) > 0 ) continue;
		else {
			int kiyas = 0;
			for(int i = 1; i < Miktar;i++) {
				kiyas += (*(syc+i)) ^ (param[i]);
			}
			if(kiyas == 0) return (syc-bellek_Baslangic);
		}
	}
	return -1;
	}
public:
   int SiraAl(int veri){ 
	bellek_ptr syc = bellek_Baslangic;
	for(;syc < bellek_Son;syc++)
	{
		if( ((*syc) ^ veri) > 0 ) continue;
		else 
			return (syc-bellek_Baslangic);
	}
	return -1;
   };
public:
   int SiraAl(int Sira,int veri){
	   bellek_ptr syc = (bellek_Baslangic + Sira);
	for(;syc < bellek_Son;syc++)
	{
		
	if( ((*syc) ^ veri) > 0 ) continue;
		else 
			return (syc-bellek_Baslangic);
	}
	return -1;

   };
public:
	int Yerlestir(int Sira,int Veri){ // 1 Dwordluk veri Yazilicak  <-- Veri = int  
	  bellek_ptr hedefBellek = bellek_Baslangic + Sira; 
	  int gerikalan_Veri = (bellek_Son - hedefBellek);  // --> Artan veriyi hesapla (DWORD) 
	  if( !(gerikalan_Veri > 0 ) )  return -1; // --> Aralik Disinda mi ? 
	  if(BosAlan == 0){
	    bellek_Son = bellekGenislet(bellek_Son,TALEP_STANDART,PAGE_READWRITE);
		   BosAlan = TALEP_STANDART / 4;
	  }
	  hedefBellek += gerikalan_Veri;
	  bellek_veriTasiTers(hedefBellek,hedefBellek - 1 , gerikalan_Veri); // adresSira dan 1 DWORD sonrasina Kalan veriyi yaz <-- ÝNT, --> 1 DWORD Kaydir
	  bellek_veriTasi(hedefBellek-gerikalan_Veri,Veri); // --> Bosalan alana Veriyi yaz.
	  BosAlan--;
	  bellek_Son++;
	  return Sira;
	 
	};
	Yigin<int> operator=(Yigin<int> kopyala){
		return kopyala;
	};
public: 
	int Boyut(){
		return (bellek_Son - bellek_Baslangic);
	};

};


#pragma region Byte

template <> class Yigin<Byte>
{
	
#pragma region Standart
 byte_ptr bellek_Baslangic;
 byte_ptr bellek_Son;
 int BosAlan;

	public:
	Yigin(){
    bellek_Baslangic = bellekYarat(RESERVE_STANDART,TALEP_STANDART);
	bellek_Son = bellek_Baslangic;
	BosAlan = TALEP_STANDART / 4;
	};

#pragma endregion

public:
   int Ekle(Byte Veri)
   {
	   if(BosAlan <= Veri.Boyut){
		   bellek_Son = bellekGenislet(bellek_Son,TALEP_STANDART,PAGE_READWRITE);
		   BosAlan = TALEP_STANDART / 4; // --> 1 Dword(4 Byte)
	}
	

	   bellek_veriTasi(bellek_Son,Veri.Boyut);// --> Boyutu basa göm.
	bellek_Son++; 
	BosAlan--; 
	bellek_veriTasi2(bellek_Son,Veri,Veri.Boyut);
	BosAlan = BosAlan - Veri.Boyut;
	bellek_Son += (Veri.Boyut % 4 == 0) ? (Veri.Boyut / 4) : (Veri.Boyut / 4 ) + 1;
	return 1;
   };
   //***
   Byte operator[](int Sira) //****
   {
	   byte_ptr syc = bellek_Baslangic;
	   int sayac2 = 0; // 0 dan basla saymaya
	   for(;syc < bellek_Son;syc++){
		  if(sayac2 == Sira){
			  return(Byte)(syc);
		  }
		  syc = ((int)(*syc) % 4 == 0) ? (byte_ptr) (syc + ((*syc) / 4 )) : (byte_ptr)(syc + (*syc / 4) + 1);
		  
		   sayac2++;
	   }
	  
   };
   int SiraAl(Byte Veri)
   {
     byte_ptr syc = bellek_Baslangic;
	 int  kalan = (Veri.Boyut % 4);
	 int gercekboyut = (!kalan) ? (Veri.Boyut / 4) : ((Veri.Boyut / 4) + 1 );
	 int sira = -1;
	 while(syc < bellek_Son){
cikis:
		 if(((*syc) ^ Veri.Boyut) == 0){  // k1
			 int boyut_Kalansiz = (!kalan) ? gercekboyut  : gercekboyut  - 1; // Kalanli ise son DWORD alma.
			 syc++; // Orjinal veri baslangicana gec.
			 byte_ptr ptr_kopya = Veri; // Kiyaslamak icin Veri pointerinin kopyasi.
			 while(boyut_Kalansiz > 0){ 
				 if((*syc) != (*ptr_kopya)){ // Kiyaslama
					 sira++;
					 syc += (!kalan) ? boyut_Kalansiz : (boyut_Kalansiz + 1);
					 goto cikis;
				 }
			  boyut_Kalansiz--;
			  syc++;  ptr_kopya++;
			 } // döngu1

			 if(kalan){
			   int sabit = (usAl(16,(2 * kalan)) - 1 );                  
			   if(((*syc) & sabit ) == ((*ptr_kopya) & sabit )){
			   sira++;
			   return sira; // Bulundu 
			   }
			   else{
				     sira++;
					 syc += (!kalan) ? boyut_Kalansiz : (boyut_Kalansiz + 1);
					 goto cikis;
			   } // cikis

			}
		 sira++;
		 return sira; //Zaten Kalansiz olarak kiyaslandi
		 }
		 else{ //k1
			 syc = ((*syc) + syc); // Bellek bloðunu bypass et.
		 }
	 }
	 return -1;
   };
   	Yigin<Byte> operator=(Yigin<Byte> kopyala){
		return kopyala;
	};
   public: 
	int Boyut(){ // Yanlis!!
		return (bellek_Son - bellek_Baslangic);
	};
};
