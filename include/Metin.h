#pragma message("METINH")

#pragma once
#ifndef METIN_H
#define METIN_H

// DISABLE STUPID CRT WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#ifndef  CAGLA
#include <cagla.h>
#endif //  CAGLA


// THIS IS A MICROSOFT HEADER WATCHOUT
#ifndef __ATLCONV_H__
#include <atlconv.h>
#endif

#ifndef _SSTREAM_
#include <sstream>
#endif


namespace cagla
{

	class Metin : public string
	{



	public:


		Metin(const char* VERI) :string(VERI) {}


		Metin(string strVERI) :string(strVERI) {}


		Metin(char* VERI) :string(VERI) { }

		Metin(wstring wstr) : string()
		{
			USES_CONVERSION;

			string hedef = W2A(wstr.c_str());

			this->append(hedef);


		}

		Metin() :string() {};

		Metin(const int& integer) : string(to_string(integer)) {}

		Metin(const long& integer) : string(to_string(integer)) {}

		Metin(const long long& integer) : string(to_string(integer)) {}

		Metin(const long double& integer) : string(to_string(integer)) {}


		Metin(vector<char> & charArray) : string() {
			Metin metin;

			for (size_t i = 0; i < charArray.size(); i++)
			{
				metin += charArray[i];
			}
			*this = metin;

		}

		// ?????????
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
		operator char*()
		{
			return (char*)this->c_str();
		}

	public:
		operator string*()
		{
			return this;
		}

	public:operator wstring()

	{
		USES_CONVERSION;
		wstring myStr = A2W(this->c_str());
		return myStr;
	}


	public: Metin& operator= (const int& rval)
	{
		*this = to_string(rval);


		return *this;
	}

	public: Metin& operator += (const int& rval)
	{

		this->append(to_string(rval));

		return *this;


	}


	public: Metin& operator+=(const Metin& rval)
	{

		this->ekle(rval);
		return *this;

	}



	public: Metin& operator+(const Metin rvalue) {


		this->append(rvalue);
		return *this;

	}


	public: Metin& operator<<(Metin rvalue)
	{
		if (rvalue.size() != 0)
			this->ekle(rvalue);
		return *this;

	}






	public: Metin& operator<<(const int rval)
	{

		this->append(to_string(rval));


		return *this;

	}

	public: Metin& operator<<(const char*& str) {
		string strr = str;

		if (strr.size() > 0)
			this->ekle(strr);

		return *this;
	}



	public: void ekle(const Metin& str) {

		if (str.size() != 0)
			this->insert(this->size(), str.c_str());

	}


	public: Metin& SayiAl(int deger, int SayiSistemi = 10)
	{
		char* cevir = (char*)malloc(8 * sizeof(int));
		_itoa(deger, cevir, SayiSistemi);

		int boyut = strlen(cevir);

		if (boyut > 0)
		{
			this->append(cevir, boyut);
		}

		delete cevir;
		return *this;

	}



	public: Metin& SayiAl(long deger, int SayiSistemi = 10) {

		char* cevir = (char*)malloc(8 * sizeof(unsigned long));
		_ltoa(deger, cevir, SayiSistemi);

		int boyut = strlen(cevir);

		if (boyut > 0)
		{
			this->append(cevir, boyut);

		}
		return *this;

	}



	public: Metin& SayiAl(long long deger, int SayiSistemi = 10) {

		char* cevir = (char*)malloc(8 * sizeof(long long));
		int a = 1;

		_i64toa(deger, cevir, SayiSistemi);
		int boyut = strlen(cevir);

		if (boyut > 0)
		{
			this->append(cevir, boyut);

		}

		delete cevir;
		return *this;

	}




	public: Metin& SayiAl(double deger)
	{

		this->append(std::to_string(deger));

		return *this;

	}


			// Kelime1 = <ASD> 
			// Kelime 2 = </ASD>
			// YeniVERI = "HELLO WORLD"
			// <ASD>HELO WORLD</ASD> çýktýsýný VERIr
			// iki kelime arasýna  yeni metin ekler
			bool KelimeArasi_Degistir(char* Kelime1, char* Kelime2, Metin YeniVERI, int Baslangýc)
			{
				int basIndex = this->find(Kelime1, Baslangýc);
				if (!(basIndex >= 0))
					return false;

				basIndex += strlen(Kelime1);
				int Son = this->find(Kelime2, basIndex);
				if (!(Son >= 0))
					return false;

				this->erase(basIndex, (Son - basIndex));
				this->insert(basIndex, YeniVERI);

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


			void Sil(Metin& silinecekMetin)
			{
				int index = this->find(silinecekMetin, 0);

				if (index > -1)
				{

					this->erase(index, silinecekMetin.length());
				}


			}


			// Metinin Ýcerisinde EskiDeger ile eslesen ilk kelimeyi YeniDeger ile degistirir
			void Degistir(char* EskiDeger, char* YeniDeger)
			{
				int  boyutEskiDeger = strlen(EskiDeger);

				int iEskiDeger = this->Bul(EskiDeger, 0);
				this->erase(iEskiDeger, boyutEskiDeger);
				this->insert(iEskiDeger, YeniDeger);

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


			// Metinin icerisindeki Kelime1 ve Kelime2 arasindaki degeri alýr ve tüm eslesmeleri metinden siler
			vector<Metin> TumunuSil(char* Kelime1, char* Kelime2)
			{
				vector<Metin> araliklar;
				Metin VERI = "";
				VERI = this->KelimeArasý(Kelime1, Kelime2);
				while (VERI != "")
				{
					araliklar.push_back(VERI);
					Metin butun_satir = (Kelime1 + VERI + Kelime2);
					int index = this->Bul(butun_satir);
					this->erase(index, index + butun_satir.length());
					VERI = this->KelimeArasý(Kelime1, Kelime2);
				}
				return araliklar;
			}


			/*
			Kelime1 = Starting string
			Kelime2 = Ending word

			eger kelime2 = 0x0(NULL) | "" ise -> baslangic indexden sona kadar okur.
			*/
			Metin KelimeArasý(const char* Kelime1, const char* Kelime2, int baslangic_index = 0)
			{
				Metin sonuc = "";
				int basIndex = this->find(Kelime1);

				if (basIndex >= 0) {

					basIndex += strlen(Kelime1);
					int Son = (*Kelime2 != NULL) ? this->find(Kelime2, basIndex) : this->length();	   // if Kelime2 = NUL then -> search till end : get kelime2 index

					if (Son >= 0) { sonuc = this->substr(basIndex, (Son - basIndex)); return sonuc; }
					else { sonuc = ""; };

				}
				else { sonuc = ""; }

				return sonuc;
			};



			// attention this returns only the pointer !
			char* operator[](int index)
			{
				char* myptr = (char*)(this + index);

				return myptr;

			}


			// Kelime1 ve Kelime2 nin arasýndaki degeri alýr output a yazar Kelime2 nin indexi doner
			int KelimeArasý(const char* Kelime1, const char* Kelime2, Metin &sonuc, int baslangicIndex = 0)
			{

				int basIndex = this->find(Kelime1, baslangicIndex);

				if (basIndex >= 0) {

					basIndex += strlen(Kelime1);
					int Son = this->find(Kelime2, basIndex);

					if (Son >= 0) {

						sonuc = this->substr(basIndex, (Son - basIndex));


						return Son;
					}
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
			vector<Metin> IleBitenler(const char* Kelime, int baslangic_index = 0)
			{
				int basIndex = baslangic_index;
				int wordsize = strlen(Kelime);
				int ToplamBoyut = this->size();
				vector<Metin> arrMetin;
				int kelimeIndex = -1;


			Tekrar:
				kelimeIndex = this->find(Kelime, basIndex);
				while (kelimeIndex > 0 && kelimeIndex < ToplamBoyut)
				{

					if (kelimeIndex != -1)
					{
						Metin kelime = this->substr(basIndex, kelimeIndex - basIndex);
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


			int SayiCevirint() {

				int deger = atoi(this->c_str());

				return deger;
			}

			long SayiCevirlong() {


				long deger = _atoi64(this->c_str());



			}

			double SayiCevirdouble()
			{

				_CRT_DOUBLE dbl;

				_atodbl(&dbl, *this);

				return dbl.x;
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


			~Metin() {

				int why = 1;

			}







	};














	/*
	KULLANIM ORNEK :
	dikkat : makro sonuna ';' eklenirse '<<' operatoruyle coklu kullanilamaz

	#define mp(x) mbirlestir(#x,"=",x) << mbirlestir("\r\n")

	int a = 1;
	int b = 2;

	Metin cikti = "";
	cikti << mp(a) << mp(b);
	output:
	a = 1
	b = 2

	otomatik satir sonu istemiyorsan mbirlestir("\r"\n") yi kaldýrabilirsin
	*/

	// birden fazla metini birlestirebilmek icin variadic fonksiyonlar
	// cevirme islemini string stream yapiyor sstream headerina ihtiyac var
	// degiskenleri bitirebilmek icin recursion yapiyor overloadi silinmemeli!

	template< typename T >
	inline Metin mbirlestir(const T& t)
	{
		std::stringstream string_stream;
		string_stream << t;
		return string_stream.str();
	}

	template< typename T, typename ... Args >
	inline Metin mbirlestir(const T& first, Args ... args)
	{
		return mbirlestir(first) + mbirlestir(args...);
	}

	#define mp(x) mbirlestir(#x,"=",x) << mbirlestir("\r\n")






}





#endif