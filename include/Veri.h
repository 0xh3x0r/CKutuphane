
#pragma once
#pragma message("VERIH <- TRY NOT TO USE THIS use bayt instead")
#ifndef VERI_H





// DEPENDS ON ->
/*
CAGLA.H
METIN.H
BELLEK.H

*/


#define VERI_H



#ifndef CAGLA
#include <cagla.h>
#endif

#ifndef METIN_H
#include <metin.h>
#endif

#ifndef BYTE_H
#include <byte.h>
#endif

using namespace std;


static const int magicNumber = 0x3FB33713;
static const int smagicNumber = 0x3FB33713;



using namespace cagla;


typedef struct veriblock

{

	// 3FB33713 -> lil endian 1337b33f
	unsigned long magicNumber;

	// verinin boyutu structin degil
	unsigned long boyut;

	char* veriptr;



public:
	veriblock() : magicNumber(smagicNumber), boyut(sizeof(veriblock))
	{

	}




public:
	veriblock(const veriblock& veri) = delete;


public: bool checkMagic()
{


	if (magicNumber == smagicNumber)
		return true;
	
	else 
		return false;
}


public: void Kaldir()
{
	if (boyut > 0) {

		int* ptr =(int*) &veriptr;
		// delete veriptr
		int* ret = bellekKaldir(ptr, boyut);
		boyut = 0;
	
	}
}



}mem;






class VERI
{



public:
	unsigned long boyut;
	veriblock* data;

public: VERI()
{
	data = new veriblock();
	boyut = 0;
}

public: VERI(const string& metin)
{
	data = VeriOlustur(metin.length() + 1);
	this->tasi((void*)metin.c_str(), metin.length());
	if (!checkMagic()) throw bad_cast();

}


public: VERI(VERI* pveri)
{
	this->data = pveri->data;
	this->boyut = data->boyut;

	if (!checkMagic(data)) throw bad_cast();
}


public:
	VERI(int boyut)
	{
		this->data = VeriOlustur(boyut);
	}


public:
	VERI(veriblock* pveri) : data(pveri)
	{
		if (!checkMagic(pveri)) throw bad_cast();
	}



public: ~VERI()
{
	if (data->boyut > 0) 
	{
		data->Kaldir();

	}



}

public: int Bul(veriblock* pveri)
{
	if (data->boyut < pveri->boyut) return -1;



	int veriboyut1 = data->boyut;
	int veriboyut2 = pveri->boyut;

	int index = 0;
	char ilkVERI = (char)pveri->veriptr;

Tekrar:

	if (index == veriboyut1) return -1;

	// ilk 1 byte i bul
	index = Bul(ilkVERI, index);
	if (index == -1) return -1;

	int kalan1 = (veriboyut1 - index) % 4;
	int kalan2 = veriboyut2 % 4;

	if (kalan1 == 0 && kalan2 == 0)
	{

		if (dwordkiyasla((int*)pveri->veriptr, pveri->boyut, index) == true)
			return index;
		else { index += 4; goto Tekrar; }

	}


	kalan1 = (veriboyut1 - index) % 2;
	kalan2 = (veriboyut2 % 2);

	if (kalan1 == 0 && kalan2 == 0)
	{


		if (wordkiyasla((short*)&pveri->veriptr, pveri->boyut, index) == true)
		{

			return index;
		}
		else { index += 2; goto Tekrar; }

	}
	// word yada dword olarak kiyaslayamazsan byte olarak kiyasla 
	if (bytekiyasla(pveri->veriptr, pveri->boyut, index) == true)
	{
		return index;
	}
	else { index += 1; goto Tekrar; };






	return -1;
}

public: static bool VERIkiyasla(veriblock* VERI1, veriblock* VERI2)
{


	if (VERI1->boyut != VERI2->boyut) return false;

	int bytecount = VERI1->boyut; // reel VERI boyutunu al
	int counter = (bytecount < 4) ? 1 : bytecount / 4; // integer olarak kiyaslanacak

	int* data1 = (int*)VERI1->veriptr;
	int* data2 = (int*)VERI2->veriptr;

	for (size_t i = 0; i < counter; i++)
	{
		if (*data1 != *data2) return false;
	}

	return true;

}




public:
	bool checkMagic()
	{

		if (data->magicNumber == magicNumber)
			return true;


		return false;

	}






public: void ata(char* VERI, int Boyut)
{
	this->data->Kaldir();

	data = VeriOlustur(Boyut);
	tasi(VERI, Boyut);


}


public: char* getData()
{

	return (char*)&data->veriptr;
}

public: Metin asString() {

	string met = "";
	long boyut = strlen((char*)&this->data->veriptr);
	if (boyut > 0)
		met.insert(met.size(), this->getData(), boyut + 1);
	else return "";
	return met;

}




		// always returns ptr which points to data itself

		////////////////////////////////////////////////////// CONVERSATION OPERATORS 

		operator int() {

			int sayi = (int)*data->veriptr;

			return sayi;
		}

		operator void*()
		{
			return (void*)(&data->veriptr);
		}


		operator char*()
		{
			return (char*)&data->veriptr;
		}

		operator int*()
		{

			return (int*)&data->veriptr;
		}

		operator Metin() {

			string met = "";
			long boyut = strlen((char*)&this->data->veriptr);
			if (boyut > 0)
				met.insert(met.size(), this->getData(), boyut + 1);
			else return "";
			return met;

		}



		operator VERI*()
		{

			return this;
		}


		operator veriblock*() {

			return this->data;
		}











		///////////////////////////////////// PRIVATESSSSSSSSSSSSSSSSSSSSSSSSS




private: bool kiyasla(veriblock* pveri)
{

	if (data->boyut != pveri->boyut) return false;

	int bytecount = data->boyut - sizeof(VERI); // reel VERI boyutunu al
	int counter = (bytecount < 4) ? 1 : bytecount / 4; // integer olarak kiyaslanacak

	int* data1 = (int*)data->veriptr;
	int* data2 = (int*)pveri->veriptr;

	for (int i = 0; i < counter; i++)
	{
		if (*data1 != *data2) return false;

		data1++;
		data2++;
	}

	return true;



}


		 // get the index of character in data
public: inline int Bul(char VERI, int startindex)
{
	char* temp = (char*)(&data->veriptr + startindex);
	for (int i = 0; i < data->boyut; i++)
	{
		if (*temp == VERI) return i;

		temp++;
	}

	return -1;

}


		// hedef in nBytes kadar VERIsini classdaki VERIyle kýyasla
private: inline bool bytekiyasla(char* hedef, int nBytes, int startindex = 0)
{

	int reelveriboyut = data->boyut;

	if ((startindex + nBytes) > reelveriboyut) return -1;

	char* _VERI = (char*)(&data->veriptr + startindex);


	{
		while (nBytes > 0)
		{
			if (((*hedef) != (*_VERI)))
				return false;
			nBytes--;
			hedef++;
			_VERI++;
		}
		return true;

	}

}

		 // 2 byte kiyaslama yapar
private: inline bool wordkiyasla(short* hedef, int nBytes, int startindex = 0)
{

	int reelveriboyut = data->boyut;

	if ((startindex + nBytes) > reelveriboyut) return false;

	char* dataptr = (char*)&data->veriptr;
	dataptr += startindex;
	short* _VERI = (short*)dataptr;


	{
		while (nBytes > 0)
		{
			if (((*hedef) != (*_VERI)))
				return false;
			nBytes -= 2;
			hedef++;
			_VERI++;
		}
		return true;

	}

}

		 // 4 byte kiyaslama yapar
private: inline bool dwordkiyasla(int* hedef, int nBytes, int startindex = 0)
{

	int reelveriboyut = data->boyut;

	if ((startindex + nBytes) > reelveriboyut) return false;

	char* dataptr = (char*)&data->veriptr;
	dataptr += startindex;

	int* _VERI = (int*)dataptr;


	{
		while (nBytes > 0)
		{
			if (((*hedef) != (*_VERI)))
				return false;
			nBytes -= 4;
			hedef++;
			_VERI++;
		}
		return true;

	}

}


private:
	bool checkMagic(char* VERI)
	{


		if (((veriblock*)VERI)->magicNumber == magicNumber)
			return true;

		return false;


	}

private:
	bool checkMagic(veriblock* VERI)
	{


		if (((veriblock*)VERI)->magicNumber == magicNumber)
			return true;

		return false;


	}



protected: veriblock* VeriOlustur(int Boyut)
{
	int reelboyut = Boyut + sizeof(veriblock);

	this->data = (veriblock*)yiginAyir(reelboyut);
	data->boyut = Boyut;
	data->magicNumber = magicNumber;
	this->boyut = data->boyut;

	return data;
}


protected : void tasi(void* VERI, int Boyut)
{
	if (Boyut > this->data->boyut) throw "Bellek tasmasi";

	int* dst = (int*)&this->data->veriptr;

	veriTasi(dst, (int*)VERI, Boyut);



}





 



};



#endif