#pragma once

#ifndef _METIN_
#define _METIN_
#endif
#ifndef _STRING_
#include <string>
#endif

#ifndef _STDLIB_
#include <stdlib.h>
#endif

#ifndef _IOSTREAM_
#include <iostream>
#endif
#ifndef _VECTOR_
#include <vector>
#endif



// char ch = blabla[i]; // bu operatorde bir sýkýntý var!
// bazý noktalarda null terminator olmuyor 

using namespace std;
class Metin : public string
{



public:
	Metin(const char* veri) :string(veri){}
	Metin(string strveri) :string(strveri){}
	Metin(char* veri) :string(veri) { }
	Metin() :string() {};

	Metin(vector<char> & charArray) : string()  {
		Metin metin;

		for (size_t i = 0; i < charArray.size(); i++)
		{
			metin += charArray[i];
		}
		*this = metin;

	}

	Metin(char chr) : string() {
		Metin metin;
		metin += chr;
		*this = metin;
	}


public:
	operator string() {
		return *this;
	}



public:
	operator char*() {
		return (char*)this->c_str();
	}

public:
	operator string*()
	{
		return this;
	}

	// Kelime1 = <ASD> 
	// Kelime 2 = </ASD>
	// YeniVeri = "HELLO WORLD"
	// <ASD>HELO WORLD</ASD> çýktýsýný verir
	// iki kelime arasýna  yeni metin ekler
	bool KelimeArasi_Degistir(char* Kelime1, char* Kelime2, Metin YeniVeri, int Baslangýc)
	{
		int basIndex = this->find(Kelime1, Baslangýc);
		if (!(basIndex >= 0))
			return false;

		basIndex += strlen(Kelime1);
		int Son = this->find(Kelime2, basIndex);
		if (!(Son >= 0))
			return false;

		this->erase(basIndex, (Son - basIndex));
		this->insert(basIndex, YeniVeri);

		return true;
	}


	// if fails returns -1
	int Bul(char* Kelime, int Baslangic)
	{
		int Index = this->find(Kelime, Baslangic);

		return Index;

	}
	int Bul(char* Kelime)
	{
		int Index = this->find(Kelime, 0);

		if (Index == -1)
			return -1;

		return Index;
	}

	// Metinin Ýcerisinde EskiDeger ile eslesen ilk kelimeyi YeniDeger ile degistirir
	void Degistir(char* EskiDeger, char* YeniDeger)
	{
		int  boyutEskiDeger = strlen(EskiDeger);

		int iEskiDeger = this->Bul(EskiDeger, 0);
		this->erase(iEskiDeger, boyutEskiDeger);
		this->insert(iEskiDeger,YeniDeger);
		
	}

	void HepsiniDegistir(char* EskiDeger, char* YeniDeger)
	{

		int index = 0;
		int  boyutEskiDeger = strlen(EskiDeger);

		while (true)
		{
			index = this->Bul(EskiDeger, index);
			if (index == -1) break;
			this->erase(index, boyutEskiDeger);
			this->insert(index, YeniDeger);
			index += strlen(EskiDeger);
		}
	}

	// Metinin Kelime ile baslayip baslamadigini kontrol eder
	bool StartsWith(char* Kelime)
	{
	
		if (this->Bul(Kelime, 0) != 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	int toint()
	{
		return atoi(this->c_str());

	}

	// Metinin icerisindeki Kelime1 ve Kelime2 arasindaki degeri alýr ve tüm eslesmeleri metinden siler
	vector<Metin> TumunuAl(char* Kelime1, char* Kelime2)
	{
		vector<Metin> araliklar;
		Metin veri = "";
		veri= this->KelimeArasý(Kelime1, Kelime2);
		while (veri != "")
		{
			araliklar.push_back(veri);
			Metin butun_satir = (Kelime1 + veri + Kelime2);
			int index = this->Bul(butun_satir);
			this->erase(index, index + butun_satir.length());
			veri = this->KelimeArasý(Kelime1, Kelime2);
		}
		return araliklar;
	}


	/*
	Kelime1 = Starting string 
	Kelime2 = Ending word

	eger kelime2 = 0x0(NULL) | "" ise -> baslangic indexden sona kadar okur.
	*/
	Metin KelimeArasý(const char* Kelime1, const char* Kelime2,int baslangic_index = 0)
	{
		Metin sonuc = "";
		int basIndex = this->find(Kelime1);

		if (basIndex >= 0) {

			basIndex += strlen(Kelime1);
			int Son = (*Kelime2 != NULL) ? this->find(Kelime2, basIndex) : this->length();	   // if Kelime2 = NUL then -> search till end : get kelime2 index

			if (Son >= 0) { sonuc = this->substr(basIndex, (Son - basIndex)); return sonuc; }
			else { sonuc = ""; };

		}
		else { sonuc = "";}

		return sonuc;
	};

	// attention this returns only the pointer !
	char* operator[](int index)
	{
		char* myptr= (char*)(this + index);
		
		return myptr;

	}

  

	// Kelime1 ve Kelime2 nin arasýndaki degeri alýr output a yazar Kelime2 nin indexi doner
	int KelimeArasý(const char* Kelime1, const char* Kelime2, Metin &sonuc,int baslangicIndex = 0)
	{
	
		int basIndex = this->find(Kelime1,baslangicIndex);

		if (basIndex >= 0) {

			basIndex += strlen(Kelime1);
			int Son = this->find(Kelime2, basIndex);

			if (Son >= 0) {
				
				sonuc = this->substr(basIndex, (Son - basIndex));
		

				return Son; }
			else { return -1; };

		}
		else { return -1; }

		return -1;
	};


	// Kelime parametresinde belirtilen kelime ile biten kelimeyi getir   örneðin bir satýrý almak için blabla.IleBiten("\r\n")
	// baslangic index = optional
	// Basarisiz olursa "" dondurur
	Metin IleBiten(const char* Kelime, int baslangic_index = 0)
	{
		int basIndex = baslangic_index;

		int kelimeIndex = this->find(Kelime, basIndex);
		if (kelimeIndex != -1)
			Metin kelime = this->substr(basIndex, kelimeIndex);
		else
			return "";
	}





	// Kelime parametresinde belirtilen kelime ile tüm kelimeleri getir   örneðin bir metindeki tüm satýrlarý almak için blabla.IleBitenler("\r\n")
	// baslangic index = optional
	// Basarisiz olursa 0 size vector dondurur
	vector<Metin> IleBitenler(const char* Kelime,int baslangic_index = 0)
	{
		int basIndex = baslangic_index;
		int wordsize = strlen(Kelime);
		int ToplamBoyut = this->size();
		vector<Metin> arrMetin;
		int kelimeIndex = -1;


	Tekrar:
		 kelimeIndex = this->find(Kelime, basIndex);
		while(kelimeIndex > 0 && kelimeIndex < ToplamBoyut)
		{

		if (kelimeIndex != -1)
		{
			Metin kelime = this->substr(basIndex, kelimeIndex-basIndex);
			arrMetin.push_back(kelime);
		}
		else
		{
			return arrMetin;
		}
		basIndex = kelimeIndex + wordsize;
		goto Tekrar;


		}

		return arrMetin; // Succesfur
	}


	// returns lowercase version of current metin
	Metin lowercase()
	{
		string ret = "";
		for (size_t i = 0; i < this->size(); i++)
		{
			ret += tolower(this->at(i));
		}
	 
		return ret;
	}


};