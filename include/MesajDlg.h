 #pragma once

#ifndef DINAMIKDLG_H
#include <dinamikdlg.h>
#endif

#ifndef HAZIRFONKSIYONLAR_H
#include <HazirFonksiyonlar.h>
#endif

#ifndef MESAJDLG_H
#define MESAJDLG_H
#endif

/*
  Kullanim Ornegi :


  	CMesajDlg MesajKutusu("Dosya mevcut var olan ile degistirilsin mi ?","Dosya Mevcut!","Ýptal","Evet","Tümüne Evet",CMesajDlg::ID_BUTTON3);
	INT_PTR Sonuc = MesajKutusu.DoModal();
	if(Sonuc == CMesajDlg::ID_BUTTON1)
	{

	 MessageBox("Islem iptal edildi");

	}
	if(Sonuc == CMesajDlg::ID_BUTTON2)
	{

		MessageBox("Sadece bu dosya icin kabul ettiniz");
	}
	if(Sonuc == CMesajDlg::ID_BUTTON3)
	{

		MessageBox("Tüm Dosyalar icin kabul ettiniz");
	}




*/





// 3 Buttonlu MessageBox cakmasi sinif
class CMesajDlg :
	public CDinamikDlg
{

public:

	enum
	{
	 ID_BUTTON1 = 1,
	 ID_BUTTON2 = 2,
	 ID_BUTTON3 = 3,
	 ID_TEXT_STATIC = 4,
	};






    // Eger Button Basliklari belirtilmez ise Class Bu buttonlari yaratmaz 
	// Sagdan sola ilk button 1.buttondur - 1.Button Iptal buttonu olarak varsayilabilir.
	// DefButton parametresi ID olarak gonderilmelidir Standart Olarak BUTTON1
	CMesajDlg(CString Mesaj,CString Baslik="",CString Button1Baslik = "",CString Button2Baslik = "",CString Button3Baslik = "",int DEFBUTTON = ID_BUTTON1);
	CMesajDlg(void);
	~CMesajDlg(void);

public:
	DECLARE_MESSAGE_MAP()
	// DoModal Islemi Standart ID(IDOK-IDCANCEL gibi)'e sahip olmayan Buttonlarda Dialogu sonlandirmiyor Button3 ten geri donmesi icin Click Olayi düzenlemesi.
	afx_msg void Button3Tiklandi();



};

// CMesajDlg gostermek icin hazir fonksiyon
// Eger Button basliklari belirtilmez ise button yaratilmaz!
// Secili button otomatik olarak Yaratilmis Button Sirasi en buyuk olan atanir.
// Geri Donus : Tiklanan Button
extern inline int MesajKutusu(string Mesaj,string Baslik = "",string Button1Baslik = "",string Button2Baslik = "",string Button3Baslik = "");

#pragma comment(lib,"MesajDlg")