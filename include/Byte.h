#pragma once
#ifndef BYTE_H
#define BYTE_H




// #define UNICODE 1

#ifndef  CAGLA
#include <cagla.h>
#endif // ! CAGLA

#pragma msg("BYTEH")

#ifndef  METIN_H
#include <metin.h>
#endif // ! METIN_H

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



















class Byte


{

public: int Boyut;
public: int* iVERI;
public: HANDLE Heap;









public:
	Byte()
	{
		// Y++;
		Heap = yiginYarat(0);
		Boyut = 0;
	}



public:
	Byte(byte_ptr Hedef) { // Özel type YIGIN.H için 
		Boyut = (int)(&Hedef);
		Hedef++;
		// 1 DWORD Boyut header
		iVERI = Hedef;
	}





public:		 	// BU SADECE STRING OLARAK TANININIR VE NULL TERMINETOR ILE YUKLENIR
	Byte(string& metin) {

	    
		Boyut = metin.length() + 1;
		Heap = yiginYarat(Boyut);
		iVERI = yiginAyir(Heap, Boyut);
		veriTasi(iVERI, (char*)metin.c_str(), Boyut);
	}



public:Byte(const char* Hedef)
	{
		// Y++;
		Heap = yiginYarat(0);
		if (Heap != 0)
		{
			Boyut = strlen(Hedef); // Null terminator yok
			iVERI = yiginAyir(Heap, Boyut);
			veriTasi(iVERI, (int*)Hedef, Boyut);
		}
	}




public:
	Byte(const Byte& Hedef)
	{
		iVERI = Hedef.iVERI;
		Boyut = Hedef.Boyut;
		Heap = Hedef.Heap;
	}






public:
	Byte(Byte* Hedef)
	{
		iVERI = Hedef->iVERI;
		Boyut = Hedef->Boyut;
		Heap = Hedef->Heap;
	}


//public:
//	Byte(VERI& veri) {
//		Heap = yiginYarat(0);
//		iVERI = yiginAyir(Heap,veri.boyut);
//		veriTasi(iVERI, veri.getData(), veri.boyut);
//	
//
//	}
//


	Byte & operator=(const int & Hedef)
	{
		if (Boyut > 0)
			yiginKaldir(Heap, iVERI);

		iVERI = yiginAyir(Heap, (sizeof(int)));
		Boyut = sizeof(int);

		veriTasi(iVERI, (int*)&Hedef, (sizeof(int)));
		return *this;
	};

	Byte & operator+=(const int & Hedef) {

		int* yeni_ptr = yiginAyir(Heap, (Boyut + (sizeof(int))));

		if (Boyut > 0) {
			veriTasi(yeni_ptr, iVERI, Boyut);
			yiginKaldir(Heap, iVERI);
		}

		veriTasi((int*)((char*)yeni_ptr + Boyut), (int*)Hedef, (Boyut + (sizeof(int))));
		Boyut += (sizeof(int));
		iVERI = yeni_ptr;
		return *this;
	};

	Byte& operator+=(const char* Hedef) {

		int Hedef_Boyut = strlen(Hedef);
		int* yeni_ptr = yiginAyir(Heap, (Boyut + Hedef_Boyut));
		if (Boyut > 0)
		{
			veriTasi(yeni_ptr, iVERI, Boyut);
			yiginKaldir(Heap, iVERI);
		}


		veriTasi((int*)((char*)yeni_ptr + Boyut), (int*)Hedef, Hedef_Boyut);
		Boyut += Hedef_Boyut;
		iVERI = yeni_ptr;
		return *this;
	}

	

	Byte& operator+=(const Byte& Hedef) {


		int* yeni_ptr = yiginAyir(Heap, (Boyut + Hedef.Boyut));
		if (Boyut > 0)  // VERI var ise eski VERIyi ekle  
		{
			veriTasi(yeni_ptr, iVERI, Boyut);
			yiginKaldir(Heap, iVERI);
		}

		// -> Byte olarak(char) Ekle (int*) + 1 1 DWORD ekler
		veriTasi((int*)((char*)yeni_ptr + Boyut), Hedef.iVERI, Hedef.Boyut);
		Boyut += Hedef.Boyut;
		iVERI = yeni_ptr;
		return *this;
	}



/*
	Byte& operator=(VERI* Bellek)
	{
		yiginKaldir(Heap, iVERI);
		Boyut = Bellek->boyut;
		iVERI = yiginAyir(Heap, Boyut);
		veriTasi(iVERI, (int*)Bellek, Boyut);
		return *this;
	}*/




	operator int*() {
		return iVERI;
	}

	operator int() {
		return (int)(*iVERI);
	}



	char* operator[](int Sira)
	{
		return(((char*)iVERI + Sira));
	}




	operator char*() {
		return ((char*)iVERI);

	}
	// char* çevirme		



	////////////////////// FONKSÝYONLAR /////////////////////


private: void oncekiniKaldir()
	{
		if (Boyut > 0)
		{
			yiginKaldir(Heap, iVERI);
			Boyut = 0;


		}
	}


public:
	void YeniOlustur(int Byte_Boyut) {
		if (Boyut > 0) {
			yiginKaldir(Heap, iVERI);
			Boyut = 0;
		}
		iVERI = yiginAyir(Heap, Byte_Boyut);
		Boyut = Byte_Boyut;
	}

public:
	Byte bitisAl(char* cogulVERI,int Boyut) // cogulVERI (2x) 0xABABABAB ile biten VERIler olmalý!(heap alloc terminator)
	{
		int VERI_boyut = Boyut;


		int boyut_ = VERI_boyut;
		const char* _VERI = cogulVERI; // VERIyi boyutuyla kýyaslayip sonradan tekrar baþa sarabilmek için kopya deðiþkenler
		char* Kopya = ((char*)iVERI);
		int index = 0;
		Byte donus;

		// Tekrar:         // Eðer ilk byte eþit sonrasý uyuþmuyorsa buraya gelip döngüden devam et
		while (index < Boyut) {


			int sayac = 0;

			while (sayac <= boyut_) { // cogulVERI deki tum VERIleri dene.

				int VERIboyut = (strlen(_VERI)); // Ilk VERInin boyutu
				sayac += VERIboyut + 1;

				if (Byte_Kiyasla(Kopya, VERIboyut, (char*)_VERI))
				{
					_VERI = cogulVERI;
					donus.Ekle(index + VERIboyut);
					break;

				}


				_VERI = (_VERI + sayac); // Sonra ki VERIye gec. 

			}

			_VERI = cogulVERI;
			index++;
			Kopya++;
		}

		return donus;

	}





	// Cogul VERI = string dizesi. index in tersine baslangic degil VERInin bittigi noktayi dondurur.
public:
	Byte Bul(char* cogulVERI) // cogulVERI 0x00 ile biten VERIler olmalý!(STRING)
	{
		int VERI_boyut = strlen(cogulVERI);


		int boyut_ = VERI_boyut;
		const char* _VERI = cogulVERI; // VERIyi boyutuyla kýyaslayip sonradan tekrar baþa sarabilmek için kopya deðiþkenler
		char* Kopya = ((char*)iVERI);
		int index = 0;
		Byte donus;

		// Tekrar:         // Eðer ilk byte eþit sonrasý uyuþmuyorsa buraya gelip döngüden devam et
		while (index < Boyut) {


			int sayac = 0;

			while (sayac <= boyut_) { // cogulVERI deki tum VERIleri dene.

				int VERIboyut = (strlen(_VERI)); // Ilk VERInin boyutu
				sayac += VERIboyut + 1;

				if (Byte_Kiyasla(Kopya, VERIboyut, (char*)_VERI))
				{
					_VERI = cogulVERI;
					donus.Ekle(index);
					break;

				}


				_VERI = (_VERI + sayac); // Sonra ki VERIye gec. 

			}

			_VERI = cogulVERI;
			index++;
			Kopya++;
		}

		return donus;

	}
	// Cogul VERI = string dizesi.

public:
	// Yýgýnda integer ara.
	int Bul(int VERI)
	{
		int* Kopya = (int*)iVERI;
		int index = 0;
		while (index < Boyut) {
			if ((*Kopya) == VERI)
				return index;
			index++;
			Kopya++;
		}
		return -1;
	}


public:
	// Returns string's offset in the memory
	int Bul(const char* VERI, int Baslangic_Index)
	{
		int VERI_boyut = strlen(VERI);
		int boyut_ = VERI_boyut;
		const char* _VERI = VERI; // VERIyi boyutuyla kýyaslayip sonradan tekrar baþa sarabilmek için kopya deðiþkenler

		if (Baslangic_Index >= Boyut)
			return -1;

		char* Kopya = ((char*)iVERI + Baslangic_Index);
		int index = Baslangic_Index;
	Tekrar:         // Eðer ilk byte eþit sonrasý uyuþmuyorsa buraya gelip döngüden devam et
		while (index < Boyut) {

			if (((*Kopya) == (*_VERI))) {

				while (boyut_ > 1) { // Ilk kýyaslama zaten yapýldý o yüzden boyut > 1  

					_VERI++;
					boyut_--;
					Kopya++;

					if (!((*Kopya) == (*_VERI))) {
						index += VERI_boyut - boyut_;
						_VERI = VERI;
						boyut_ = VERI_boyut;

						goto Tekrar;
					}

				}
				// Tüm kýyaslamalar bitti Tüm VERIyi kýyaslýyacak döngü burda sona erer! (VERInin tümünü hesaplasa bile VERInin baþladýðý sýra numarasýný dönecek)

				return index;
			}

			index++;
			Kopya++;
		}
		return -1;
	}
	// Baslangic noktasi ile string ara


public: void Ekle(const Byte& VERI)
{
	int* yeni_ptr = yiginAyir(Heap, (Boyut + VERI.Boyut));
	if (Boyut > 0)  // VERI var ise eski VERIyi ekle  
	{
		veriTasi(yeni_ptr, iVERI, Boyut);
		yiginKaldir(Heap, iVERI);
	}


	veriTasi((int*)((char*)yeni_ptr + Boyut), VERI.iVERI, VERI.Boyut);
	Boyut += VERI.Boyut;
	iVERI = yeni_ptr;
}





		// Bellek blogu ekle
		void Ekle(char* VERI, int Byte_Boyut)
		{
			int* yeni_ptr = yiginAyir(Heap, (Boyut + Byte_Boyut));

			if (Boyut > 0)  // VERI var ise eski VERIyi ekle  
			{
				veriTasi(yeni_ptr, iVERI, Boyut);
				yiginKaldir(Heap, iVERI);
			}

			veriTasi(((char*)yeni_ptr + Boyut), (char*)VERI, Byte_Boyut);
			Boyut += Byte_Boyut;
			iVERI = yeni_ptr;
		}


		// Sayisal bir deger ekle
		void Ekle(int VERI)
		{
			int* yeni_ptr = yiginAyir(Heap, (Boyut + sizeof(int)));

			if (Boyut > 0)  // VERI var ise eski VERIyi ekle  
			{
				veriTasi(yeni_ptr, iVERI, Boyut);
				yiginKaldir(Heap, iVERI);
			}
			*((int*)((char*)yeni_ptr + Boyut)) = VERI; // Boyut byte olarak hesaplandýgýndan (char*) olarak arttýr pointerý ve 4 byte(dword) olarak(int*) düzenle
			Boyut += sizeof(int);
			iVERI = yeni_ptr;
		}





		// Word ekle
		void Ekle(WORD VERI)
		{
			int* yeni_ptr = yiginAyir(Heap, (Boyut + sizeof(WORD)));

			if (Boyut > 0)  // VERI var ise eski VERIyi ekle  
			{
				veriTasi(yeni_ptr, iVERI, Boyut);
				yiginKaldir(Heap, iVERI);
			}
			*((int*)((char*)yeni_ptr + Boyut)) = VERI; // Boyut byte olarak hesaplandýgýndan (char*) olarak arttýr pointerý ve 4 byte(dword) olarak(int*) düzenle
			Boyut += sizeof(WORD);
			iVERI = yeni_ptr;
		}





		// bu üzerine yazmiyor
		void DegisEkle(Byte degisecekVERI, Byte hedefVERI, int Startindex = 0)
		{
			int gerekliekAlan = hedefVERI.Boyut - degisecekVERI.Boyut;

			char* yeni_ptr = (char*)yiginAyir(this->Boyut + gerekliekAlan);
			char* eski_VERI = (char*)this->iVERI;
			int yeni_boyut = this->Boyut + gerekliekAlan;
			int  index = this->Bul(degisecekVERI, Startindex);

			if (index > 0) veriTasi(yeni_ptr, iVERI, index);
			for (int i = index; i < yeni_boyut; i++)
			{
				*((char*)yeni_ptr + i + gerekliekAlan) = *((char*)this->iVERI + i); //shift data
			}
			veriTasi(yeni_ptr + index, hedefVERI, hedefVERI.Boyut);
			yiginKaldir(Heap, iVERI);
			iVERI = (int*)yeni_ptr;

		}



		// Belirtilen indexten sonrasini VERI ile degistir(Uzerine yazar)
		void Degistir(char* VERI, int Index, int Byte_Boyut)
		{


			int EkAlan = ((Index + 1 + Byte_Boyut) > Boyut) ? (Byte_Boyut - (Boyut - (Index + 1))) : 0;
			int* yeni_ptr = iVERI;

			if (EkAlan)
			{
				yeni_ptr = yiginAyir(Heap, (Boyut + EkAlan));

				// VERI var ise eski VERIyi ekle 
				if (Boyut > 0)
				{
					veriTasi(yeni_ptr, iVERI, Boyut);
					yiginKaldir(Heap, iVERI);
				}
			}
			veriTasi((int*)((char*)yeni_ptr + Index), (int*)VERI, Byte_Boyut);
			Boyut += EkAlan;
			iVERI = yeni_ptr;



		}









		// Belirtilen indexten sonrasini VERI ile degistir(Uzerine yazar) 
		void Degistir(int VERI, int Index)
		{

			int Byte_Boyut = sizeof(int);
			int EkAlan = ((Index + 1 + Byte_Boyut) > Boyut) ? (Byte_Boyut - (Boyut - (Index + 1))) : 0;
			int* yeni_ptr = iVERI;
			if (EkAlan)
			{
				yeni_ptr = yiginAyir(Heap, (Boyut + EkAlan));

				// VERI var ise eski VERIyi ekle 
				if (Boyut > 0)
				{
					veriTasi(yeni_ptr, iVERI, Boyut);
					yiginKaldir(Heap, iVERI);

				}

			}
			veriTasi(((char*)yeni_ptr + Index), (char*)&VERI, Byte_Boyut);
			Boyut += EkAlan;
			iVERI = yeni_ptr;



		}





		// Belirtilen indexten sonrasini VERI ile degistir(Uzerine yazar) 
		void Degistir(WORD VERI, int Index)
		{

			int Byte_Boyut = sizeof(WORD);
			int EkAlan = ((Index + 1 + Byte_Boyut) > Boyut) ? (Byte_Boyut - (Boyut - (Index + 1))) : 0;
			int* yeni_ptr = iVERI;
			if (EkAlan)
			{
				yeni_ptr = yiginAyir(Heap, (Boyut + EkAlan));

				// VERI var ise eski VERIyi ekle 
				if (Boyut > 0)
				{
					veriTasi(yeni_ptr, iVERI, Boyut);
					yiginKaldir(Heap, iVERI);

				}

			}
			veriTasi(((char*)yeni_ptr + Index), (char*)&VERI, Byte_Boyut);
			Boyut += EkAlan;
			iVERI = yeni_ptr;

		}


		//// Belirtilen veri blogunu offsetdeki adrese kopyalar 
		//// Eger hedef veri Byte classýnýn boyutundan buyukse sadece var olan bellek alani kadar yazar
		//void Tasi(int offset, VERI* hedef)
		//{
		//	int maxbellek = Boyut - offset;
		//	
		//	int nbytestowrite = maxbellek;

		//	if (hedef->boyut <= maxbellek) nbytestowrite = hedef->boyut;


		//	char* ptrbase = (char*)iVERI;
		//	veriTasi(ptrbase + offset, hedef->getData(), nbytestowrite);
		//
		//
		//}

		void Tasi(int offset, char* hedef, int nbytes)
		{
			int maxbellek = Boyut - offset;

			int nbytestowrite = maxbellek;

			if (nbytes <= maxbellek) nbytestowrite = nbytes;

			char* ptrbase = (char*)iVERI;
			veriTasi(ptrbase + offset, hedef, nbytestowrite);

		}

		//void Tasi(int offset, VERI* hedef,int nbytes)
		//{
		//	int maxbellek = Boyut - offset;

		//	int nbytestowrite = maxbellek;

		//	if (nbytes <= maxbellek) nbytestowrite = nbytes;

		//	char* ptrbase = (char*)iVERI;
		//	veriTasi(ptrbase + offset , hedef->getData(), nbytestowrite);


		//}

		void Tasi(int offset, Byte& data)
		{

			int maxbellek = Boyut - offset;

			int nbytestowrite = maxbellek;

			if (data.Boyut <= maxbellek) nbytestowrite = data.Boyut;


			char* ptrbase = (char*)iVERI;
			veriTasi(ptrbase + offset, data.getdata(), nbytestowrite);

		}

		// Bellegi belirtildigi kadar genisletir.Yuklenen bellek standart olarak 0x00 ile doldurulur
		void BellekGenislet(int Byte_Boyut)
		{



			int* yeni_ptr = yiginAyir(Heap, (Boyut + Byte_Boyut));

			if (Boyut > 0)  // VERI var ise eski VERIyi ekle  
			{
				veriTasi(yeni_ptr, iVERI, Boyut);
				yiginKaldir(Heap, iVERI);
			}
			Boyut += Byte_Boyut;
			iVERI = yeni_ptr;



		}



		public: inline char* getdata()
		{


			return (char*)iVERI;
}





		// Yýgýn sonu hesapla 

inline int degiskenbitis_boyut(char* bellek, char Terminator) {
			int boyut = 0;
			while (true) {
				if ((*bellek) == Terminator) {
					boyut += 1; // Kýyaslanan VERIyi say
					return boyut;
				}
				boyut++;
				bellek++;
			}
		}
		// Belirtilen terminator ile VERInin sonunu hesapla.




		// Creates a new heap and might cause mem leak
public:
	string StringCevir()
	{
		const char* yeni_ptr = 0;
		int boyut = 0;
		if (Boyut > 0)  // VERI var ise eski VERIyi ekle  
		{
			boyut = strlen((char*)this->iVERI);
			yeni_ptr = (char*)yiginAyir(Heap, boyut+1);
			veriTasi((int*)yeni_ptr, iVERI, boyut+1);
			
		}

		string ret;
		ret.insert(0, yeni_ptr, boyut);

		return ret;
	}


public: operator string() {

	const char* yeni_ptr = 0;
	if (Boyut > 0)  // VERI var ise eski VERIyi ekle  
	{
		int boyut = strlen((char*)this->iVERI);
		yeni_ptr = (char*)yiginAyir(Heap, boyut + 1);
		veriTasi((int*)yeni_ptr, iVERI, boyut + 1);

	}

	return yeni_ptr;
}
	// VERInin sonuna Null Terminator ekle.



	inline bool Byte_Kiyasla(char* hedef, int Byte_Boyut, char* VERI)
	{
		while (Byte_Boyut > 0)
		{
			if (((*hedef) != (*VERI)))
				return false;
			Byte_Boyut--;
			hedef++;
			VERI++;
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
		iVERI = 0;
		Boyut = 0;
		Heap = (HANDLE)-1;
	}
	// Heap i kaldir



	////////////////////// FONKSÝYONLAR /////////////////////
};





#endif BYTE_H