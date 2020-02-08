#pragma once
#ifndef BYTE_H
#define BYTE_H


// #define UNICODE 1

#ifndef BELLEK_H
#include <bellek.h>
#endif


/*

*                  AÇIKLAMA
* Byte class inin kullanýmý bittikten sonra Kaldir() Fonksiyonu ile Heap sonlandirilmali.
* Y,K deðiþkenleri leak tespit etmek içindir.dilenirse kaldýrýlabilir.

*/

typedef int* byte_ptr;
typedef char* str;



// int Y = 0; 
// int K = 0; 

class Byte { 
	
public  : int Boyut;
private : int* veri;
public : HANDLE Heap;
		 

public:
 Byte(byte_ptr Hedef){ // Özel type YIGIN.H için 
       Boyut = (int)(&Hedef);
	   Hedef++;
	   // 1 DWORD Boyut header
	   veri = Hedef;
}

public:
 Byte(char* Hedef){

	 Heap = yiginYarat(0);
    Boyut = char_boyut(Hedef);
	veri = yiginAyir(Heap,Boyut);
	veriTasi(veri,(int*)Hedef,Boyut);
}	
public:
Byte(const char* Hedef)
{
	// Y++;
	Heap = yiginYarat(0);
	if(Heap != 0)
	{
	Boyut = strlen(Hedef); // Null terminator yok
	veri = yiginAyir(Heap,Boyut); 
	veriTasi(veri,(int*)Hedef,Boyut);
	}
}
public:
 Byte(const Byte& Hedef)
 {
	 veri = Hedef.veri;
	 Boyut = Hedef.Boyut;
	 Heap = Hedef.Heap;
 }
public:
 Byte()
 {
	// Y++;
    Heap = yiginYarat(0);
	Boyut = 0;
 }
		   public:
			   Byte(Byte* Hedef)
			   {
	 veri = Hedef->veri;
	 Boyut = Hedef->Boyut;
	 Heap = Hedef->Heap;
			   }



 Byte & operator=(const int & Hedef)
	{
	    if(Boyut > 0) 
	    yiginKaldir(Heap,veri);

		veri = yiginAyir(Heap,(sizeof(int)));
		Boyut = sizeof(int);
		
		veriTasi(veri,(int*)&Hedef,(sizeof(int)));
		return *this;
	};

 Byte & operator+=(const int & Hedef){
	  
	 int* yeni_ptr = yiginAyir(Heap,( Boyut + (sizeof(int))) );

	 if(Boyut > 0){  
     veriTasi(yeni_ptr,veri,Boyut);
	 yiginKaldir(Heap,veri);
	 }

	 veriTasi((int*)((char*)yeni_ptr+Boyut),(int*)Hedef,( Boyut + (sizeof(int))));
	 Boyut += (sizeof(int));
	 veri = yeni_ptr;
	 return *this;
  };

 Byte& operator+=(char* Hedef){
	
	 int Hedef_Boyut = char_boyut(Hedef);
	 int* yeni_ptr = yiginAyir(Heap,( Boyut + Hedef_Boyut) );
	  if(Boyut > 0)  
	  {
	 veriTasi(yeni_ptr,veri,Boyut);
	 yiginKaldir(Heap,veri);
	  }
	                   
	 
	 veriTasi((int*)((char*)yeni_ptr+Boyut),(int*)Hedef,Hedef_Boyut);
	 Boyut += Hedef_Boyut;
	 veri = yeni_ptr;
	 return *this;
  }

 Byte& operator+=(const char* Hedef){
 int Hedef_Boyut = strlen(Hedef);
 int* yeni_ptr = yiginAyir(Heap,( (Boyut + Hedef_Boyut) ));

 if(Boyut > 0)  {

     veriTasi(yeni_ptr,veri,Boyut);
	 yiginKaldir(Heap,veri);
	  }

	 veriTasi((int*)((char*)yeni_ptr+Boyut),(int*)Hedef,Hedef_Boyut);
	 Boyut += Hedef_Boyut;
	 veri = yeni_ptr;
	 return *this;
  }

 Byte& operator+=(const Byte& Hedef){
	
	 
	 int* yeni_ptr = yiginAyir(Heap,( Boyut + Hedef.Boyut) );
	  if(Boyut > 0)  // Veri var ise eski veriyi ekle  
	  {
	 veriTasi(yeni_ptr,veri,Boyut);
	 yiginKaldir(Heap,veri);
	  }
	
	                    // -> Byte olarak(char) Ekle (int*) + 1 1 DWORD ekler
	  veriTasi((int*)((char*)yeni_ptr+Boyut),Hedef.veri,Hedef.Boyut);
	 Boyut += Hedef.Boyut;
	 veri = yeni_ptr;
	 return *this;
  }


Byte& operator=(char* Bellek)
{
  if(Boyut > 0)
	  yiginKaldir(Heap,veri);

  Boyut = char_boyut(Bellek);
  veri = yiginAyir(Heap,Boyut);
  veriTasi(veri,(int*)Bellek,Boyut);
  return *this;
}


 Byte& operator=(const char* Bellek)
	{
	  yiginKaldir(Heap,veri);
	  Boyut = strlen(Bellek); // + Null Byte yok
	  veri = yiginAyir(Heap,Boyut);
	  veriTasi(veri,(int*)Bellek,Boyut);
	  return *this;
	}
 



 operator int*(){
		return veri;
	}
 
  operator int(){
		return (int)(*veri);
	} 
 


  char* operator[](int Sira)
  {
	return(((char*)veri+Sira));
  }

 
 

  operator char*(){  
	  return ((char*)veri);

  }
 // char* çevirme		
 

  
////////////////////// FONKSÝYONLAR /////////////////////
public:
void YeniOlustur(int Byte_Boyut){
	if(Boyut > 0){
  yiginKaldir(Heap,veri);
	Boyut = 0;
	}
  veri = yiginAyir(Heap,Byte_Boyut);
  Boyut = Byte_Boyut;
 }

public:
	Byte bitisAl(char* cogulVeri) // cogulVeri (2x) 0xABABABAB ile biten veriler olmalý!(heap alloc terminator)
	{
	int veri_boyut = char_boyut(cogulVeri);


	int boyut_ = veri_boyut;
	const char* _veri = cogulVeri; // Veriyi boyutuyla kýyaslayip sonradan tekrar baþa sarabilmek için kopya deðiþkenler
	char* Kopya = ((char*)veri);
	int index = 0;
	Byte donus;

// Tekrar:         // Eðer ilk byte eþit sonrasý uyuþmuyorsa buraya gelip döngüden devam et
while(index < Boyut){

	
	  int sayac = 0;

	while(sayac <= boyut_){ // cogulVeri deki tum verileri dene.
   
   int veriboyut = (strlen(_veri)); // Ilk verinin boyutu
   sayac += veriboyut+1;

   if(Byte_Kiyasla(Kopya,veriboyut,(char*)_veri))
   {
    _veri = cogulVeri;
	donus.Ekle(index+veriboyut);
	break;

   }

  
   _veri = (_veri + sayac); // Sonra ki veriye gec. 
   
   }

	 _veri = cogulVeri;
	 index++;
	 Kopya++;
	}

	return donus;

	}
	// Cogul veri = string dizesi. index in tersine baslangic degil verinin bittigi noktayi dondurur.

public:
	Byte Bul(char* cogulVeri) // cogulVeri 0x00 ile biten veriler olmalý!(STRING)
	{
	int veri_boyut = char_boyut(cogulVeri);


	int boyut_ = veri_boyut;
	const char* _veri = cogulVeri; // Veriyi boyutuyla kýyaslayip sonradan tekrar baþa sarabilmek için kopya deðiþkenler
	char* Kopya = ((char*)veri);
	int index = 0;
	Byte donus;

// Tekrar:         // Eðer ilk byte eþit sonrasý uyuþmuyorsa buraya gelip döngüden devam et
while(index < Boyut){

	
	  int sayac = 0;

	while(sayac <= boyut_){ // cogulVeri deki tum verileri dene.
   
   int veriboyut = (strlen(_veri)); // Ilk verinin boyutu
   sayac += veriboyut+1;

   if(Byte_Kiyasla(Kopya,veriboyut,(char*)_veri))
   {
    _veri = cogulVeri;
	donus.Ekle(index);
	break;

   }

  
   _veri = (_veri + sayac); // Sonra ki veriye gec. 
   
   }

	 _veri = cogulVeri;
	 index++;
	 Kopya++;
	}

	return donus;

	}
	// Cogul veri = string dizesi.

public:
int Bul(int Veri)
{
	int* Kopya = (int*)veri;
	int index = 0;
	while(index < Boyut){
		if((*Kopya)==Veri)
			return index;
	 index++;
	 Kopya++;
	}
	return -1;
}
// Yýgýnda integer ara.

public:
int Bul(const char* Veri,int Baslangic_Index)
{
	int veri_boyut = strlen(Veri);
	int boyut_ = veri_boyut;
	const char* _veri = Veri; // Veriyi boyutuyla kýyaslayip sonradan tekrar baþa sarabilmek için kopya deðiþkenler

    if(Baslangic_Index >= Boyut)
	return -1;

	char* Kopya = ((char*)veri+Baslangic_Index);
	int index = Baslangic_Index;
Tekrar:         // Eðer ilk byte eþit sonrasý uyuþmuyorsa buraya gelip döngüden devam et
while(index < Boyut){

if(((*Kopya) == (*_veri))){

while(boyut_ > 1){ // Ilk kýyaslama zaten yapýldý o yüzden boyut > 1  
   
   _veri++; 
   boyut_--; 
   Kopya++; 
    
if(!((*Kopya) == (*_veri))){ 
	   index += veri_boyut - boyut_;
	   _veri = Veri;
	   boyut_ = veri_boyut;

	   goto Tekrar; }
   
   }
// Tüm kýyaslamalar bitti Tüm veriyi kýyaslýyacak döngü burda sona erer! (Verinin tümünü hesaplasa bile verinin baþladýðý sýra numarasýný dönecek)

  return index; 
} 

	 index++;
	 Kopya++;
	}
	return -1;
}
// Baslangic noktasi ile string ara


public: void Ekle(const Byte& Veri)
{
	int* yeni_ptr = yiginAyir(Heap,( Boyut + Veri.Boyut) );
	  if(Boyut > 0)  // Veri var ise eski veriyi ekle  
	  {
	 veriTasi(yeni_ptr,veri,Boyut);
	 yiginKaldir(Heap,veri);
	  }
	                 
	 
	  veriTasi((int*)((char*)yeni_ptr+Boyut),Veri.veri,Veri.Boyut);
	  Boyut += Veri.Boyut;
	 veri = yeni_ptr;
}





// Bellek blogu ekle
void Ekle(char* Veri,int Byte_Boyut)
{
	 int* yeni_ptr = yiginAyir(Heap,( Boyut + Byte_Boyut) );

	  if(Boyut > 0)  // Veri var ise eski veriyi ekle  
	  {
	 veriTasi(yeni_ptr,veri,Boyut);
	 yiginKaldir(Heap,veri);
	  }
	                 
	  veriTasi(((char*)yeni_ptr+Boyut),(char*)Veri,Byte_Boyut);
	 Boyut += Byte_Boyut;
	 veri = yeni_ptr;
}


// Sayisal bir deger ekle
void Ekle(int Veri)
{
	 int* yeni_ptr = yiginAyir(Heap,( Boyut + sizeof(int)) );
	 
	  if(Boyut > 0)  // Veri var ise eski veriyi ekle  
	  {
	 veriTasi(yeni_ptr,veri,Boyut);
	 yiginKaldir(Heap,veri);
	  }
	 *((int*)((char*)yeni_ptr+Boyut)) = Veri; // Boyut byte olarak hesaplandýgýndan (char*) olarak arttýr pointerý ve 4 byte(dword) olarak(int*) düzenle
	 Boyut += sizeof(int);
	 veri = yeni_ptr;
}





// Word ekle
void Ekle(WORD Veri)
{
	 int* yeni_ptr = yiginAyir(Heap,( Boyut + sizeof(WORD)) );
	 
	  if(Boyut > 0)  // Veri var ise eski veriyi ekle  
	  {
	 veriTasi(yeni_ptr,veri,Boyut);
	 yiginKaldir(Heap,veri);
	  }
	 *((int*)((char*)yeni_ptr+Boyut)) = Veri; // Boyut byte olarak hesaplandýgýndan (char*) olarak arttýr pointerý ve 4 byte(dword) olarak(int*) düzenle
	 Boyut += sizeof(WORD);
	 veri = yeni_ptr;
}









// Belirtilen indexten sonrasini Veri ile degistir(Uzerine yazar)
void Degistir(char* Veri,int Index,int Byte_Boyut)
{


	int EkAlan = ((Index+1 + Byte_Boyut) > Boyut ) ? ( Byte_Boyut - (Boyut - ( Index+1 )) ) : 0;
	 int* yeni_ptr = veri;

	 if(EkAlan)
	 {
		yeni_ptr = yiginAyir(Heap,( Boyut + EkAlan) );
	   
	 // Veri var ise eski veriyi ekle 
	  if(Boyut > 0)   
	  {
	   veriTasi(yeni_ptr,veri,Boyut);
	   yiginKaldir(Heap,veri);
	  }
	 }               
	 veriTasi(  (int*)((char*)yeni_ptr+Index)   ,    (int*)Veri,Byte_Boyut);
	 Boyut += EkAlan;
	 veri = yeni_ptr;



}









// Belirtilen indexten sonrasini Veri ile degistir(Uzerine yazar) 
void Degistir(int Veri,int Index)
{

	int Byte_Boyut = sizeof(int);
	int EkAlan = ((Index+1 + Byte_Boyut) > Boyut ) ? ( Byte_Boyut - (Boyut - ( Index+1 )) ) : 0;
	 int* yeni_ptr = veri;
	 if(EkAlan)
	 {
		yeni_ptr = yiginAyir(Heap,( Boyut + EkAlan) );
	  
	  	 // Veri var ise eski veriyi ekle 
	  if(Boyut > 0)   
	  {
	   veriTasi(yeni_ptr,veri,Boyut);
	   yiginKaldir(Heap,veri);
	  
	  }

	 }
	  veriTasi(  ((char*)yeni_ptr+Index)   ,    (char*)&Veri,Byte_Boyut);
	  Boyut += EkAlan;
	  veri = yeni_ptr;



}





// Belirtilen indexten sonrasini Veri ile degistir(Uzerine yazar) 
void Degistir(WORD Veri,int Index)
{

	int Byte_Boyut = sizeof(WORD);
	int EkAlan = ((Index+1 + Byte_Boyut) > Boyut ) ? ( Byte_Boyut - (Boyut - ( Index+1 )) ) : 0;
	 int* yeni_ptr = veri;
	 if(EkAlan)
	 {
		yeni_ptr = yiginAyir(Heap,( Boyut + EkAlan) );
	  
	  	 // Veri var ise eski veriyi ekle 
	  if(Boyut > 0)   
	  {
	   veriTasi(yeni_ptr,veri,Boyut);
	   yiginKaldir(Heap,veri);
	  
	  }

	 }
	  veriTasi(  ((char*)yeni_ptr+Index)   ,    (char*)&Veri,Byte_Boyut);
	  Boyut += EkAlan;
	  veri = yeni_ptr;

}




 // Bellegi belirtildigi kadar genisletir.Yuklenen bellek standart olarak 0x00 ile doldurulur
void BellekGenislet(int Byte_Boyut)
{

	

	int* yeni_ptr = yiginAyir(Heap,( Boyut + Byte_Boyut) );

	if(Boyut > 0)  // Veri var ise eski veriyi ekle  
	{
		veriTasi(yeni_ptr,veri,Boyut);
		yiginKaldir(Heap,veri);
	}
	Boyut += Byte_Boyut;
	veri = yeni_ptr;



}














inline int char_boyut(char* bellek){
		int* kopya = (int*)bellek;
		int boyut = 0; 
		while(true){
			if((*kopya) == 0xABABABAB){
			boyut = boyut*4;
			boyut++; // son 0xAB sayma!
			bellek = (char*)kopya;
			while((*bellek) == '\xAB'){
				bellek--; boyut--;   }
			return boyut;
			}
			boyut++;
		    kopya++;
		}
		

	}
// Yýgýn sonu hesapla 

inline int degiskenbitis_boyut(char* bellek,char Terminator){
		int boyut = 0; 
		while(true){
 			if((*bellek) == Terminator){
			boyut += 1; // Kýyaslanan veriyi say
			return boyut;
			}
			boyut++;
			bellek++;
		}
	}
// Belirtilen terminator ile verinin sonunu hesapla.

public:
const char*& StringCevir()
{
const char* yeni_ptr = 0;
if(Boyut > 0)  // Veri var ise eski veriyi ekle  
	  {
  yeni_ptr =(char*) yiginAyir(Heap,( Boyut + 1 ) );
	 veriTasi((int*)yeni_ptr,veri,Boyut);
}

return yeni_ptr;
}
// verinin sonuna Null Terminator ekle.



inline bool Byte_Kiyasla(char* hedef,int Byte_Boyut,char* veri)
{
	while(Byte_Boyut > 0)
	{
		if(((*hedef) != (*veri)))
			return false;
		Byte_Boyut--;
		hedef++;
		veri++;
	}
	return true;

}

void Kaldir()
{
	// K++;
	HeapDestroy(Heap);
    
//	if( (Y-K) > 15)
//	{
//		int abc = 2;
//		int b = 1;
//	}
	veri = 0;
	Boyut = 0;
    Heap = (HANDLE)-1;
}
// Heap i kaldir



////////////////////// FONKSÝYONLAR /////////////////////
};
#endif BYTE_H