#ifndef BYTE_H
#include "Byte.h"
#endif

 char Bytes[] = {
	0x68,0x00,     // Push_offs
	0xFF,0x15,0x00, // Call_near
	0xE9,0x00, // Jmp
	0xC7,0x05,0x00, // mov_offs
	0xAB,0xAB,0xAB,0xAB, // Dword Terminator
	0xAB,0xAB,0xAB,0xAB
};



Byte offset_sira_list(Byte Kod_,int Boyut)
{
	Byte veri;
	Byte Kod;

	Kod.Ekle(Kod_,Boyut);

	int index = 0;
	if(Kod.Boyut <= 0)
	return veri;

	veri = Kod.bitisAl((char*)Bytes);

	return veri;
}









void baseaddres_degistir_list(Byte Kod,Byte OffsetList,int eski_BaseAddres,int yeni_BaseAddres)
{
	int adr = 0;
	
	for(int i = 0;i < OffsetList.Boyut;i = i+ 4){ // Byte sýnýfý boyutu byte olarak hesaplar(DWORD a çevir) --> 4 arttýr(Kalan olamaz(Hepsi DWORD))

	int indx = (int)*OffsetList[i];

	 adr = *(int*)Kod[indx];
	 adr = ((adr - eski_BaseAddres)+yeni_BaseAddres);
	 *(int*)(Kod[indx]) = adr;
	}

}