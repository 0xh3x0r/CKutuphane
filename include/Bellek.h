
#pragma once
#ifndef BELLEK_H
#define BELLEK_H


#ifndef CAGLA
#include <cagla.h>
#endif



#ifndef _WINDOWS_
#include <Windows.h>
#endif





extern inline int* yiginAyir(int Byte_Boyut);
extern inline int* yiginYarat(int Byte_Boyut);
extern inline int* yiginAyir(HANDLE Heap,int Byte_Boyut);
extern inline int* veriTasi(int* hdfBellek,int* kynkBellek,int Byte_Boyut);
extern inline char* veriTasi(char* hdfBellek,char* kynkBellek,int Byte_Boyut);
extern inline void* veriTasi(void* hdfBellek,void* kynkBellek,int Byte_Boyut);
extern inline int yiginKaldir(HANDLE Heap,void* Bellek);
extern inline int yiginKaldir(void* Bellek);
extern inline int* bellekYarat(int* adres,int Byte_Boyut,int secenek,int izin);
extern inline int* bellekYarat(int Reserve_Boyut,int Talep_Boyut,int ekizin);
extern inline int* bellekGenislet(int* baslangic_Adres,int Byte_Boyut,int izin);
extern inline int* bellekKaldir(int* baslangic_Adres,int Byte_Boyut);
extern inline int* uzakBellekYarat(HANDLE hIslem,int* adres,int Byte_Boyut,int secenek,int izin);
extern inline int* uzakBellekYarat(HANDLE hIslem,int Reserve_Boyut,int Talep_Boyut,int izin);
extern inline int* uzakbellekGenislet(HANDLE hIslem,int* baslangic_Adres,int Byte_Boyut,int izin);
extern inline int* uzakbellekKaldir(HANDLE hIslem,int* baslangic_Adres,int Byte_Boyut);


#pragma comment(lib,"Bellek.lib")


 #endif BELLEK_H