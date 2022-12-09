#pragma once
/*


#ifndef HAZIRFONKSIYONLAR_H



#define HAZIRFONKSIYONLAR_H

/*

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif


#ifndef _STRING_
#include <string>
#endif
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#ifndef __ATLCONV_H__
#include <atlconv.h>
#endif

#ifndef _VECTOR_
#include <vector>
#endif





#ifndef  CAGLA
#include <cagla.h>
#endif // ! CAGLA




namespace metinislemleri
{


	using namespace std;

	// ===========================================================================================================================================

	// String icin structlar

	// Herhangi bir Metin(string) degiskeninde ki bilgileri depolar.


	typedef struct MetinBilgileri
	{
		vector<int> SatirBaslangicList;
		vector<int> SatirUzunluklari;
		int EnzunSatir;
		int SatirSayisi;

	};




	// ====================================================================================================================================


	// String Isleme Kodlari:


	//Str Parametresiyle Gonderilmis veride Kelime1 ve Kelime2 arasinda ki veriyi Sonuc parametresiyle gonderilmis degiskene yazar bulunamazsa -1 doner
	extern inline int KelimeArasi(const char* Kelime1, const char* Kelime2, string Str, string &Sonuc);

	//Str Parametresiyle Gonderilmis veride Baslangic indexinden sonra ki Kelime1 ve Kelime2 arasinda ki veriyi Sonuc parametresiyle gonderilmis degiskene yazar bulunamazsa -1 doner
	extern inline int KelimeArasi(const char* Kelime1, const char* Kelime2, string Str, string &Sonuc, int Baslangic);

	// Belirtilen kelimeyi Baslangictan sonra Tekrar sayisi kadar sonrasinda Hedef stringinde arar.
	// Kelimenin baslangic adresini doner
	extern inline int KelimeBul(string Kelime, string Hedef, int TekrarSayisi, int Baslangic);

	//Str parametresiyle gonderilmis veride Kelime1 ve Kelime2 Arasinda ki veriyi YeniVeri parametresiyle gonderilmis veriyle degistirir basarisiz olursa false doner
	extern inline bool KelimeArasi_Degistir(char* Kelime1, char* Kelime2, string &Str, string YeniVeri);

	//Str parametresiyle gonderilmis veride Baslangic indexinden sonra ki Kelime1 ve Kelime2 Arasinda ki veriyi YeniVeri parametresiyle gonderilmis veriyle degistirir basarisiz olursa false doner
	extern inline bool KelimeArasi_Degistir(char* Kelime1, char* Kelime2, string &Str, string YeniVeri, int Baslangic);

	// Metin Parametresiyle gonderilen metnin bilgilerini alir.
	extern inline MetinBilgileri MetinBilgileriAl(string& Metin);
	// ===========================================================================================================================================


	// Byte-Gigabyte gibi buyuk verileri okunabilir hale getirir.Boyut(Bit olceginde) parametresiyle gonderilmis veriyi direk stringe Boyut + '.' + Kalan + MB-GB-Byte vs... biciminde cevirir 
	extern inline string BoyutCevir(unsigned __int64 Boyut);


	// ===========================================================================================================================================
	// Yardimci Kodlar:

	// GetLastError() Komutunu calistirir ve donen hata kodunu Isletim sisteminin dilinde ki aciklamaya cevirir
	extern inline string  SonHataMesaji();


	// ==========================================================================================================================================







	/*
	string Kemal =  "Aslan 1 Kaplan Aslan 2 Kaplan";

	string Sonuc = "";
	int dnm = KelimeArasi("Aslan","Kaplan",Kemal,Sonuc);
	int dnm2 = KelimeArasi("Aslan","Kaplan",Kemal,Sonuc,dnm);
	*/
	inline int KelimeArasi(const char* Kelime1, const char* Kelime2, string Str, string &Sonuc)
	{

		int basIndex = Str.find(Kelime1);
		if (basIndex >= 0) {

			basIndex += strlen(Kelime1);
			int Son = Str.find(Kelime2, basIndex);

			if (Son >= 0) { Sonuc = Str.substr(basIndex, (Son - basIndex)); return Son + 1; }
			else { Sonuc = ""; return -1; };

		}
		else { Sonuc = ""; return -1; }


	};

	 /*




	// Kelime2 index + 1 Döner(byBass Index)
	inline int KelimeArasi(const char* Kelime1, const char* Kelime2, string Str, string &Sonuc, int Baslangic)
	{

		int basIndex = Str.find(Kelime1, Baslangic);
		if (basIndex >= 0) {

			basIndex += strlen(Kelime1);
			int Son = Str.find(Kelime2, basIndex);

			if (Son >= 0) { Sonuc = Str.substr(basIndex, (Son - basIndex)); return Son + 1; }
			else { Sonuc = ""; return -1; };

		}
		else { Sonuc = ""; return -1; }


	};
	// Kelime2 index + 1 Döner(byBass Index)














	inline bool KelimeArasi_Degistir(char* Kelime1, char* Kelime2, string &Str, string YeniVeri)
	{
		int basIndex = Str.find(Kelime1);
		if (!(basIndex >= 0))
			return false;

		basIndex += strlen(Kelime1);
		int Son = Str.find(Kelime2, basIndex);
		if (!(Son >= 0))
			return false;

		Str.erase(basIndex, (Son - basIndex));
		Str.insert(basIndex, YeniVeri);

		return true;
	}

	/**
	* Uzerine Yazmaz.
	* Kullanim:
	* string dnm = "Kelime1VeriKelime2";
	* int donus = KelimeArasi_Degistir("Kelime1","Kelime2",dnm,"YeniDeger");
	* Sonuc : Kelime1YeniDegerKelime2
	**/
	inline bool KelimeArasi_Degistir(char* Kelime1, char* Kelime2, string &Str, string YeniVeri, int Baslangic)
	{
		int basIndex = Str.find(Kelime1, Baslangic);
		if (!(basIndex >= 0))
			return false;

		basIndex += strlen(Kelime1);
		int Son = Str.find(Kelime2, basIndex);
		if (!(Son >= 0))
			return false;

		Str.erase(basIndex, (Son - basIndex));
		Str.insert(basIndex, YeniVeri);

		return true;
	}


	int KelimeBul(string Kelime, string Hedef, int TekrarSayisi, int Baslangic)
	{
		int Index = Hedef.find(Kelime, Baslangic);

		if (Index == -1)
			return -1;

		for (int i = 0; i < TekrarSayisi; i++)
		{

			Index += Kelime.length();

			Index = Hedef.find(Kelime, Index);
			if (Index == -1)
				return -1;

		}

		return Index;
	}






	inline MetinBilgileri MetinBilgileriAl(string& Str)
	{

		MetinBilgileri metinBilgileri;
		int SatirBaslangic = 0;
		int SatirIndex = -1;
		int SatirSayisi = -1;

		int EnUzunSatir = 0;
		SatirIndex = KelimeBul("\n", Str, 0, SatirBaslangic) + 1;

		while (SatirIndex != 0)
		{
			SatirSayisi++;

			int SatirUzunluk = SatirIndex - SatirBaslangic;


			metinBilgileri.SatirBaslangicList.push_back(SatirBaslangic);
			metinBilgileri.SatirUzunluklari.push_back((SatirUzunluk));

			if (metinBilgileri.EnzunSatir < SatirUzunluk)
				metinBilgileri.EnzunSatir = SatirUzunluk;



			SatirBaslangic = SatirIndex;
			SatirIndex = KelimeBul("\n", Str, SatirSayisi, SatirBaslangic) + 1;
		}

		metinBilgileri.SatirSayisi = SatirSayisi + 1;

		metinBilgileri.EnzunSatir = (SatirSayisi == 0) ? Str.length() : metinBilgileri.EnzunSatir;

		return metinBilgileri;

	}






}





namespace cevirmeislemleri {


	// ===========================================================================================================================================
	// Cevirme Kodlari :

	extern inline string wchar_char(wstring wstr);
	extern inline string int_str(int deger);
	extern inline string ulong_str(unsigned long deger);
	extern inline string uint64_str(unsigned __int64 deger);
	extern inline string long_str(long deger, int ondaliksayisi);
	inline string double_str(double deger);



	extern wstring string_wstring(string str);
	extern inline int str_int(char* veri);
	extern inline int str_int(string veri);
	extern inline unsigned long str_ulong(string veri);
	extern inline unsigned __int64 str_uint64(string veri);
	extern wchar_t *string2wchar_t(const string &str);


	// ===========================================================================================================================================











	inline string wchar_char(wstring wstr)
	{
		string str = "";
		str.assign(wstr.begin(), wstr.end());
		return str;
	}



	inline string int_str(int deger)
	{
		char* cevir = (char*)malloc(8 * sizeof(int));
		_itoa(deger, cevir, 10);
		return cevir;
	}



	inline string ulong_str(unsigned long deger)
	{
		char* cevir = (char*)malloc(8 * sizeof(unsigned long));
		_ltoa(deger, cevir, 10);
		return cevir;
	}



	inline string uint64_str(unsigned __int64 deger)
	{
		char* cevir = (char*)malloc(8 * sizeof(unsigned __int64));
		_i64toa_s(deger, cevir, (8 * sizeof(unsigned __int64)), 10);
		return cevir;
	}


	inline int str_int(char* veri)
	{
		return(atoi(veri));

	}

	inline unsigned long str_ulong(string veri)
	{

		return(atol(veri.c_str()));

	}

	inline int str_int(string veri)
	{
		char* pveri = (char*)veri.c_str();

		return atoi(pveri);
	}


	inline unsigned __int64 str_uint64(string veri)
	{
		char* pveri = (char*)veri.c_str();

		return _atoi64(pveri);

	}






	wchar_t *string2wchar_t(const string &str)
	{
		wchar_t wchar[260];
		int index = 0;
		while (index < str.size())
		{
			wchar[index] = (wchar_t)str[index];
			++index;
		}
		wchar[index] = 0;
		return wchar;
	}


	wstring string_wstring(string Str)
	{
		USES_CONVERSION;
		wstring myStr = A2W(Str.c_str());
		return myStr;
	}






	inline string double_str(double deger)
	{

		Byte data;

		data.YeniOlustur(255);

		int decimal = 1;
		int sgned = 1;

		_ecvt_s(data.getdata(), data.Boyut, deger, 1, &decimal, &sgned);

		string str = data.StringCevir();
		data.Kaldir();


		return str;
	}





	inline string long_str(long deger, int ondaliksayisi)
	{
		Byte bits;

		bits.YeniOlustur(255);

		ltoa(deger, bits.getdata(), ondaliksayisi);

		string ret = bits.StringCevir();


		bits.Kaldir();
		return ret;

	}








	inline string BoyutCevir(unsigned __int64 Boyut)
	{
		using namespace matematikselislemler;
		using namespace cevirmeislemleri;
		string sBoyut = "";
		if (Boyut >= 1073741824)
		{
			unsigned __int64 Kalan = Boyut % 1073741824;
			unsigned __int64 Artan = ((Kalan * 100) / 1073741824);
			sBoyut = uint64_str(Boyut / 1073741824);
			sBoyut += ".";
			sBoyut += uint64_str(Artan);
			sBoyut.append(" GB");

		}
		else if (Boyut >= 1048576)
		{
			int Kalan = Boyut % 1048576;
			unsigned __int64 Artan = ((Kalan * 100) / 1048576);
			sBoyut = uint64_str(Boyut / 1048576);
			sBoyut += ".";
			sBoyut += uint64_str(Artan);
			sBoyut.append(" MB");

		}
		else if (Boyut >= 1024)
		{
			int Kalan = Boyut % 1024;
			unsigned __int64  Artan = ((Kalan * 100) / 1024);
			sBoyut = cevirmeislemleri::uint64_str(Boyut / 1024);
			sBoyut += ".";
			sBoyut += uint64_str(Artan);
			sBoyut.append(" KB");

		}
		else if (Boyut < 1024)
		{

			sBoyut = uint64_str(Boyut);
			sBoyut.append(" Byte");

		}

		return sBoyut;
	}






}





namespace matematikselislemler {


	// ===========================================================================================================================================

	// Matematiksel
	extern inline unsigned __int64 UsAl(unsigned __int64 Us, unsigned __int64 Sayi);
	extern inline unsigned __int64 HaneKaldir(unsigned __int64 Sira, unsigned __int64 Sayi); // Soldan baslayarak
	extern inline unsigned __int64 HaneKaldir(unsigned __int64 Sira, unsigned __int64 Sayi, unsigned __int64 Bolen);


	// ===========================================================================================================================================


	inline unsigned __int64 UsAl(unsigned __int64 Us, unsigned __int64 Sayi)
	{
		for (int i = 1; i < Us; i++)
		{
			Sayi *= Sayi;

		}
		return Sayi;
	}


	inline unsigned __int64 HaneKaldir(unsigned __int64 Sira, unsigned __int64 Sayi)
	{
		int Max = UsAl(Sira, 10) - 1;
		while (Sayi > Max)
		{
			Sayi /= 10;
		}
		return Sayi;
	}


	inline unsigned __int64 HaneKaldir(unsigned __int64 Sira, unsigned __int64 Sayi, unsigned __int64 Bolen)
	{
		int Max = UsAl(Sira, Bolen) - 1;
		while (Sayi > Max)
		{
			Sayi /= Bolen;
		}
		return Sayi;
	}




}




*/

































































































	inline string SonHataMesaji()
	{
		LPVOID lpMsgBuf;
		DWORD SonHata = GetLastError();

		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			SonHata,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&lpMsgBuf,
			0, NULL);

		string HataMesaji = "Hata : ";
		HataMesaji += (LPSTR)lpMsgBuf;
		HataMesaji += "\r\n";
		HataMesaji += "Son Hata kodu : ";
		HataMesaji += ulong_str(SonHata);
		return HataMesaji;
	}













#endif

*/