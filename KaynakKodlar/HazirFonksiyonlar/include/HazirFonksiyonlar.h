#pragma once
#ifndef HAZIRFONKSIYONLAR_H
#define HAZIRFONKSIYONLAR_H
#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

extern char* int_char(int Deger);
extern char* int_char(int Deger,int sayiSistemi);

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
extern inline int KelimeArasý(const char* Kelime1,const char* Kelime2,string Str,string &Sonuc);

//Str Parametresiyle Gonderilmis veride Baslangic indexinden sonra ki Kelime1 ve Kelime2 arasinda ki veriyi Sonuc parametresiyle gonderilmis degiskene yazar bulunamazsa -1 doner
extern inline int KelimeArasý(const char* Kelime1,const char* Kelime2,string Str,string &Sonuc,int Baslangýc);

// Belirtilen kelimeyi Baslangictan sonra Tekrar sayisi kadar sonrasinda Hedef stringinde arar.
// Kelimenin baslangic adresini doner
extern inline int KelimeBul(string Kelime,string Hedef,int TekrarSayisi,int Baslangic);

//Str parametresiyle gonderilmis veride Kelime1 ve Kelime2 Arasinda ki veriyi YeniVeri parametresiyle gonderilmis veriyle degistirir basarisiz olursa false doner
extern inline bool KelimeArasi_Degistir(char* Kelime1,char* Kelime2,string &Str,string YeniVeri);

//Str parametresiyle gonderilmis veride Baslangic indexinden sonra ki Kelime1 ve Kelime2 Arasinda ki veriyi YeniVeri parametresiyle gonderilmis veriyle degistirir basarisiz olursa false doner
extern inline bool KelimeArasi_Degistir(char* Kelime1,char* Kelime2,string &Str,string YeniVeri,int Baslangýc);

// Metin Parametresiyle gonderilen metnin bilgilerini alir.
extern inline MetinBilgileri MetinBilgileriAl(string& Metin);
// ===========================================================================================================================================





// ===========================================================================================================================================
// Yardimci Kodlar:

// GetLastError() Komutunu calistirir ve donen hata kodunu Isletim sisteminin dilinde ki aciklamaya cevirir
extern inline string  SonHataMesaji();


// ==========================================================================================================================================















// ===========================================================================================================================================
// Cevirme Kodlari :

extern inline string wchar_char(wstring wstr);
extern inline string int_str(int deger);
extern inline string ulong_str(unsigned long deger);
extern inline string uint64_str(unsigned __int64 deger);


extern wstring string_wstring(string str);
extern inline int str_int(char* veri);
extern inline int str_int(string veri);
extern inline unsigned long str_ulong(string veri);
extern inline unsigned __int64 str_uint64(string veri);
extern wchar_t *string2wchar_t(const string &str);


// ===========================================================================================================================================







// ===========================================================================================================================================

// Matematiksel
extern inline unsigned __int64 UsAl(unsigned __int64 Us,unsigned __int64 Sayi);
extern inline unsigned __int64 HaneKaldýr(unsigned __int64 Sýra,unsigned __int64 Sayý); // Soldan baslayarak
extern inline unsigned __int64 HaneKaldýr(unsigned __int64 Sýra,unsigned __int64 Sayý,unsigned __int64 Bolen);
// Byte-Gigabyte gibi buyuk verileri okunabilir hale getirir.Boyut(Bit olceginde) parametresiyle gonderilmis veriyi direk stringe Boyut + '.' + Kalan + MB-GB-Byte vs... biciminde cevirir 
extern inline string BoyutCevir(unsigned __int64 Boyut);

// ===========================================================================================================================================


#pragma comment (lib,"HazirFonksiyonlar")
#endif