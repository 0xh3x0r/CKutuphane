#include "stdafx.h"



CDinamikDlg::CDinamikDlg(CWnd* Parent,CString PencereBaslik,int Genislik,int Yukseklik,int y,int x,DWORD Style,WORD FontBoyut,CString Font,DWORD exStyle):CDialog()
{

	KullanilanBufferUzunlugu = sizeof(DLGTEMPLATE);
	BufferUzunlugu = KullanilanBufferUzunlugu;

	dialogTemplate = (DLGTEMPLATE*)malloc(BufferUzunlugu);

	NesneSayisi = 0;


	
	 
	dialogTemplate->x = x;
	dialogTemplate->y = y;
	dialogTemplate->cx =Genislik;
	dialogTemplate->cy = Yukseklik;
	dialogTemplate->cdit = 0;
	dialogTemplate->dwExtendedStyle = 0;
	dialogTemplate->style = Style;
	
    VeriEkle("\x0",sizeof(WORD)); // Menu yok
	VeriEkle("\x0",sizeof(WORD)); // Ozel bir sinif yok 

	MetinEkle(PencereBaslik); // Basligi Ekle
	VeriEkle(&FontBoyut,sizeof(WORD));
	MetinEkle(Font);
		
}


bool CDinamikDlg::NesneEkle(CString Baslik,WORD NesneTipi,short Uzunluk,short Genislik,short y,short x,WORD ID,DWORD Style,DWORD exStyle)
{

	DLGITEMTEMPLATE Nesne;
	Nesne.cx = Genislik;
	Nesne.cy = Uzunluk;
	Nesne.x= x;
	Nesne.y= y;
	Nesne.id = ID;
	Nesne.dwExtendedStyle = exStyle;
	Nesne.style = Style;			 
    

	VeriyiHizala(sizeof(DWORD));
	
	VeriEkle(&Nesne,sizeof(DLGITEMTEMPLATE));


	WORD preType = 0xFFFF;
	
	VeriEkle(&preType,sizeof(WORD));
	
	VeriEkle(&NesneTipi,sizeof(WORD));
	

	
	MetinEkle(Baslik);

	WORD baslangicVerisi = 0;
	VeriEkle(&baslangicVerisi, sizeof(WORD));

	dialogTemplate->cdit++;

	NesneSayisi++;
	return true;
}


CDinamikDlg::~CDinamikDlg(void)
{
	free(dialogTemplate);
}


INT_PTR CDinamikDlg::DoModal()
{	


	// TODO: Add your specialized code here and/or call the base class
	// bool Donus = this->InitModalIndirect(((DLGTEMPLATE*)(char*)DLGTemplate));


	bool Donus = this->InitModalIndirect(dialogTemplate);										 
	return CDialog::DoModal();
}




void CDinamikDlg::MetinEkle(LPCSTR Metin)
{
          int Uzunluk = MultiByteToWideChar(CP_ACP, 0, Metin, -1, NULL, 0);

		  WCHAR* wideString = (WCHAR*)malloc(sizeof(WCHAR) * Uzunluk);
		  MultiByteToWideChar(CP_ACP, 0, Metin, -1, wideString, Uzunluk);

		  VeriEkle(wideString, Uzunluk * sizeof(WCHAR));
          free(wideString);

}




void CDinamikDlg::VeriEkle(void* Veri,int Byte_Boyut)
{
         BosluklariDoldur(Byte_Boyut);

		 memcpy((char*)dialogTemplate + KullanilanBufferUzunlugu, Veri, Byte_Boyut);
		 KullanilanBufferUzunlugu += Byte_Boyut;

}



void CDinamikDlg::VeriyiHizala(int Byte_Boyut)
{
 int paddingSize = KullanilanBufferUzunlugu % Byte_Boyut;
  if (paddingSize != 0)
        {
			BosluklariDoldur(paddingSize);
			KullanilanBufferUzunlugu += paddingSize;
        }

}




void CDinamikDlg::BosluklariDoldur(int Byte_Boyut)
{
	if (Byte_Boyut + KullanilanBufferUzunlugu > BufferUzunlugu)
        {
        
            BufferUzunlugu += Byte_Boyut * 2;

            void* yeniBuffer = malloc(BufferUzunlugu);
			memcpy(yeniBuffer, dialogTemplate, KullanilanBufferUzunlugu);
            
            free(dialogTemplate);
            dialogTemplate = (DLGTEMPLATE*)yeniBuffer;

        }	

}

