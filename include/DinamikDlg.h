#pragma once

#ifndef DINAMIKDLG_H
#define DINAMIKDLG_H

#ifndef _AFXDLL
#define _AFXDLL
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

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


public: CDinamikDlg():CDialog()
{
	NesneSayisi = 0;
	BufferUzunlugu = 0;
	KullanilanBufferUzunlugu = 0;
	dialogTemplate = NULL;

}


public:
	bool NesneEkle(CString Baslik,WORD NesneTipi,short Uzunluk,short Genislik ,short y,short x,WORD ID ,DWORD Style = NULL,DWORD exStyle=NULL);
	
	~CDinamikDlg(void);
	
	virtual INT_PTR DoModal();


    // Template Bufferi Dword duzenine sokar
	void VeriyiHizala(int Byte_Boyut);

	void MetinEkle(LPCSTR Metin);

	// Template Buffera Veri ekler
	void VeriEkle(void* veri, int Byte_Boyut);

	// Template bufferda Belirtilen uzunlukta alan yaratir doldurur 
	void BosluklariDoldur(int Byte_Boyut);


protected:
	    DLGTEMPLATE* dialogTemplate;

	private:



    int BufferUzunlugu;
    int KullanilanBufferUzunlugu;
};
#pragma comment(lib,"DinamikDlg")
#endif
