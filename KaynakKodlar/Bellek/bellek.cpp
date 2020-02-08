#pragma once
#include "stdafx.h" // ProjectDir Additional Include Directory olarak eklenmeli



int* yiginAyir(int Byte_Boyut)
{
return (int*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,Byte_Boyut);
}




inline int* yiginYarat(int Byte_Boyut)
{
 return (int*)HeapCreate(0,Byte_Boyut,0);
}




inline int* yiginAyir(HANDLE Heap,int Byte_Boyut)
{
	if((int)Heap == -1 || (int)Heap == 0)
	{
		return NULL;
	}
	   return (int*)HeapAlloc(Heap,HEAP_ZERO_MEMORY,Byte_Boyut);
}




inline int* veriTasi(int* hdfBellek,int* kynkBellek,int Byte_Boyut)
{
	return (int*)memcpy(hdfBellek,kynkBellek,Byte_Boyut);
}


inline char* veriTasi(char* hdfBellek,char* kynkBellek,int Byte_Boyut)
{
	return (char*)memcpy(hdfBellek,kynkBellek,Byte_Boyut);
}


inline void* veriTasi(void* hdfBellek,void* kynkBellek,int Byte_Boyut)
{
	return memcpy(hdfBellek,kynkBellek,Byte_Boyut);
}



inline int yiginKaldir(HANDLE Heap,void* Bellek)
{
      if((int)Heap == -1 || (int)Heap == 0)
	   throw ("Kotu heap!");
	  return(HeapFree(Heap,0,Bellek));
}




inline int yiginKaldir(void* Bellek)
{
		return(HeapFree(GetProcessHeap(),0,Bellek)); 
}




inline int* bellekYarat(int* adres,int Byte_Boyut,int secenek,int izin) // örn bellekYarat(0,100,MEM_RESERVE,PAGE_READWRITE) bellek adresi döndürür.secenek parametresine göre yapilan iþlem deðiþir.
{
	return((int*)VirtualAlloc(adres,Byte_Boyut,secenek,izin));
}




inline int* bellekYarat(int Reserve_Boyut //(Byte) uygun = 4*1024*1024(4 GB)
	,int Talep_Boyut,int ekizin) // Minumum oluþturulacak bellek = ( 1024 * 4 ) 
{
	LPVOID bellek = VirtualAlloc(0,Reserve_Boyut,MEM_RESERVE,PAGE_NOACCESS);
    return((int*)VirtualAlloc(bellek,Talep_Boyut,MEM_COMMIT,PAGE_READWRITE | DWORD(ekizin)));
}





inline int* bellekGenislet(int* baslangic_Adres,int Byte_Boyut,int izin)
{
 return((int*)VirtualAlloc(baslangic_Adres,Byte_Boyut,MEM_COMMIT,izin));
}





inline	int* bellekKaldir(int* baslangic_Adres,int Byte_Boyut) // Seçenek = MEM_DECOMMIT = 0x4000 veya MEM_RELEASE = 0x8000
 {
	 return((int*)VirtualFree(baslangic_Adres,Byte_Boyut,MEM_RELEASE));
 }



inline int* uzakBellekYarat(HANDLE hIslem,int* adres,int Byte_Boyut,int secenek,int izin)
{
	 return((int*)VirtualAllocEx(hIslem,adres,Byte_Boyut,secenek,izin));
}

inline int* uzakBellekYarat(HANDLE hIslem,int Reserve_Boyut //(Byte) uygun = 4*1024*1024(4 GB)
	,int Talep_Boyut,int izin) // Minumum oluþturulacak bellek = ( 1024 * 4 ) 
{
	LPVOID bellek = VirtualAllocEx(hIslem,0,Reserve_Boyut,MEM_RESERVE,PAGE_NOACCESS);
	(int*)VirtualAllocEx(hIslem,bellek,Talep_Boyut,MEM_COMMIT,izin);
    return (int*)bellek;
}



inline int* uzakbellekGenislet(HANDLE hIslem,int* baslangic_Adres,int Byte_Boyut,int izin)
{
 return((int*)VirtualAllocEx(hIslem,baslangic_Adres,Byte_Boyut,MEM_COMMIT,izin));
}



inline int* uzakbellekKaldir(HANDLE hIslem,int* baslangic_Adres,int Byte_Boyut)
{
	 return((int*)VirtualFreeEx(hIslem,baslangic_Adres,Byte_Boyut,MEM_RELEASE));
}

