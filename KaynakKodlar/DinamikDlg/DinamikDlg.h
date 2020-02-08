#pragma once

#ifndef DINAMIKDLG_H
#define DINAMIKDLG_H
#endif

#ifndef __AFXDLGS_H__
#include "afxdlgs.h"
#endif



// <<<<<<<<<<<<<<<<<<< Nesne tipleri >>>>>>>>>>>>>>>>>>>>>>>>

#define NESNE_BUTTON      0x0080
#define NESNE_EDITBOX     0x0081
#define NESNE_STATIC      0x0082
#define NESNE_LISTBOX     0x0083
#define NESNE_SCROLLBAR   0x0084
#define NESNE_COMBOBOX    0x0085

// --------------------------------------------------------



class CDinamikDlg :
	public CDialog
{

public: int NesneSayisi;




public:
	CDinamikDlg(CWnd* hParent,CString PencereBaslik,int Genislik,int Yukseklik,int y,int x,DWORD Style,WORD FontBoyutu = 8,CString Font = "MS Sans Serif",DWORD exStyle = NULL);





public:
	bool NesneEkle(CString Baslik,WORD NesneTipi,short Uzunluk,short Genislik ,short y,short x,WORD ID ,DWORD Style = NULL,DWORD exStyle=NULL);
	
	~CDinamikDlg(void);
	
	virtual INT_PTR DoModal();


    // Bufferi Dword duzenine sokar
	void VeriyiHizala(int Byte_Boyut);

	void MetinEkle(LPCSTR Metin);

	// Veri ekler
	void VeriEkle(void* veri, int Byte_Boyut);

	// Belirtilen uzunlukta bosluklari doldurur 
	void BosluklariDoldur(int Byte_Boyut);

	private:

    DLGTEMPLATE* dialogTemplate;

    int BufferUzunlugu;
    int KullanilanBufferUzunlugu;
};

