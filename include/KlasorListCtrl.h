#pragma once

#define _AFXDLL

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifndef KLASORLISTCTRL_H
#define KLASORLISTCTRL_H
#endif

#ifndef KLASOR_H
#include <Klasor.h>
#endif

#ifndef _ALGORITHM_
#include <algorithm>
#endif
#ifndef TARIH_H
#include "Tarih.h"
#endif
#ifndef _VECTOR_
#include <vector>
#endif
using namespace std;


/*   
* ==================================================================================================
*    
*    Aciklama:
*    CListCtrl uzerinde Dosya ve Klasorleri Goruntulemek icin Hazirlanmistir.(Overlock makinesi ayaginiza geldi)
*  
*  Gereksinimler :
*
*  1.) Klasor.h
*  2.) MFC Kutuphanesi
*  3.) Standart C++ 
*
* Klasorislemleri.h:
*  Header icinde ki Klasor ve Volume classi Klasorleri ve Bilgisayarda ki Volumeleri listeler
*  Ayni zamanda string donusumu yaparak import ve export islemi yapilabilir
*  Boylelikle uzaktan aktarim yapilarak classlar kullanilabilir.
*
*
*
* Kullanim:
* KlasorListCtrl.cpp ve Header klasore dahil edin.
* CListCtrl eklenir resource manajerden add variable(deðiþken atama) yaparak deðiþkeni ekleyin ve tipini CListCtrl yerine KlasorListCtrl yapin
* rootKlasorGoster ve klasorGoster callbacklerine kendi yazdiginiz gosterme islemini yapicak fonksiyonu atayin.
* KlasorList icinde ki IleriButton ve GeriButton a resource menejerden eklenen herhangi bir button atanabilir tek yapilmasi gereken buttonun click eventinda IleriButton ise Ileri fonksiyonun cagrilmasidir.
* Eger Ileri veya Geri buttonlari tanimlanmazsa sorun cikmaz herhangi biri tanimlanip digeri tanimlanmazsa hata olabilir.
* AdresCubugu sinifi KlasorListCtrl objesine ataktindaktan sonra bu objeye baglanmalidir.Geri kalan islemleri otomatik yapar.
* 
*
* 
* Kullanim Ornegi ;
*
*
*

// Callback fonksiyonlarinin tanimlanma sekli boyle olmali
// Bu callback listede ki bir klasore cift tiklandiginda veya ileri - geri - adrescubugu nesnelerinden cagrilir

void KlasorGoster(string& KlasorYolu,KlasorList& List)
{
    // Nesneden gelen Klasor Adresi
	Klasor k1 = KlasorYolu.c_str(); 


	// Listele fonksiyonu filtre uyguluyor bu secenege bagli
	k1.Listele(-1,OZELLIK_GIZLI | OZELLIK_SIFRELI | OZELLIK_SISTEM); 
	
	 // Nesneye klasoru aktaran fonksiyon.
	List.KlasorGoster(k1);
}






// Ayni sekilde ilk belirlenen Bilgisayarim gibi bir sanal klasor olusturur.

void RootKlasorGoster(KlasorList& klasorlist)
{
	Volume vol; 
	vol.Listele();
	klasorlist.RootKlasor(vol);

}


BOOL CDenemeMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Hard diskleri - CD-Roomlari goruntulemek icin
	Volume volume;

	// Nesneler atanir(Secenege bagli olarak)
	klasorListesi.GeriButton = &geributton;
	
	klasorListesi.IleriButton = &ileributton;
	// Adres cubugu 
	klasorListesi.adresCubugu = &adrescubugu;

	// atandiktan sonra kendiside bu class a baglanmalidir.
	adrescubugu.KlasorListBagla(klasorListesi);

	// Fonksiyonlar atanir
    klasorListesi.rootKlasorGoster = RootKlasorGoster;

	klasorListesi.klasorGoster = KlasorGoster;
	
	// Hard diskler listelendi
	volume.Listele();
	
	if(volume.veri.length() > 0)
	{
	// Goster
	klasorListesi.RootKlasor(volume);
	
	}	
	

	return TRUE; 
}



// KlasorListesi degiskenine atanan ileri buttonun click olayi

void CDenemeMFCDlg::Ileri_Button1_Click()
{
	klasorListesi.Ileri();
 
}





void CDenemeMFCDlg::Geri_Button1_Click()
{
	klasorListesi.Geri();
	
}




// Gorunum stilleri CListCtrl classinda tanimlanan stillerle ayni
// GORUNUM_EXLORER Buyuk simgeleri kullanir 

void CDenemeMFCDlg::OnBnClickedStexplorer()
{
	klasorListesi.GorunumStiliDegistir(GORUNUM_EXPLORER);
}




// Liste seklinde ki ayrintili gorunum 

void CDenemeMFCDlg::OnBnClickedStliste()
{
	
	klasorListesi.GorunumStiliDegistir(GORUNUM_LISTE);
}



*===================================================================================================
*/











// Class in KlasorGoster fonksiyonunun cagrildigi noktalari tespit etmesi icin durum sabitleri.

// ===================================================================================================

#define FONKSIYON_DIREK    1   // Fonksiyonun direk cagriliyor
#define FONKSIYON_GERI     2   // Geri  fonksiyonundan yapilan cagrilar icin
#define FONKSIYON_ILERI    4   // Ileri fonksiyonundan yapilan cagrilar icin
#define FONKSIYON_COMBOBOX 8   // Combobox tan yapilan cagrilar icin 

//=====================================================================================================




// ===================================================================================================

// Gorunum stillerini anlasilir yapabilmek icin 

  #define GORUNUM_EXPLORER 0
  #define GORUNUM_LISTE 1

// ===================================================================================================



class KlasorList;

//  Dogru calismasi icin KlasorList objesine Baglanmalidir
class AdresCubugu : public CComboBox
{
	KlasorList* klasorList;
public:
	AdresCubugu() : CComboBox()
	{
		klasorList = NULL;
		
	}




public: void DropDownListBoyut(int ItemSayisi)
	   
	 {
   
  CRect rctComboBox, rctDropDown;
  //Combo rect
  this->GetClientRect(&rctComboBox); 
  //DropDownList rect
  this->GetDroppedControlRect(&rctDropDown); 

  //Item yuksekligini al
  int itemYuksekligi = this->GetItemHeight(-1); 

  //Kordinatlari cevir
  this->GetParent()->ScreenToClient(&rctDropDown); 

  //Yuksekligi ayarla
  rctDropDown.bottom = rctDropDown.top + rctComboBox.Height() + itemYuksekligi*ItemSayisi; 
  // Uygula
  this->MoveWindow(&rctDropDown); 
  
}



public: void KlasorListBagla(KlasorList& List)
		{
		 klasorList = &List;

		}




// Index ten sonra ki butun itemleri temizler.Verilen indexi sayar
public:void GeriKalanlariTemizle(int Index)
	   {
		   int Boyut = this->GetCount();
		   if(Index > -1 && (Boyut - (Index)) > 0)
		   {
			   Boyut = Boyut -1;
			   for(int i = Boyut; i > Index;i--)
			   {
				   this->DeleteString(i);
			   }


		   }

	   }



	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchange();
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

class KlasorList : public CListCtrl
{

typedef void (*KlasorGosterIslemi)(string&,KlasorList&); 

typedef void (*RootKlasorGosterIslemi)(KlasorList&);

typedef void (*DosyaTiklandiEvent)(string&,KlasorList&);



// Simgeleri eklenen dosyalarin uzantilari
public: vector<string> Uzantilar;

// CListCtrl a kayit edilecek kucuk simgeleri barindiran ImageList.
public: CImageList* imglist;

// CListCtrl a kayit edilecek buyuk simgeleri barindiran ImageList.
public: CImageList* imglistbuyuk;

// Su anda kullanilan sutun sayisi
public: int SonSutunSayisi;

// Gosterilen Klasorun Adresi
public: string Adres;

// Su an ki klasorden once ziyaret edilmis klasorlerin listesi
public: vector<string> KlasorListGeri;

// Su an ki klasorden sonra ziyaret edilmis klasorlerin listesi
public: vector<string> KlasorListIleri;

// Kontrolde klasor uzerine tiklandiginda cagrilan callback ayni zamanda geri-ileri islemleri endirek olarak cagirir.
public: KlasorGosterIslemi klasorGoster;

// Dosyalarin uzerine tiklandiginda cagrilan callback.
public: DosyaTiklandiEvent dosyaTiklandiEvent;

// Geri fonksiyonu icin Callback eger tanimlanirsa Class otomatik olarak bu fonksiyon icinde ki islemleri kullanarak En basa doner.
public: RootKlasorGosterIslemi rootKlasorGoster;

// Otomatik olarak Class tarafindan kullanilabilen Button Sadece Click olayinda Ileri() Fonksiyonu cagrilirsa class Bu Nesneyi otomatik olarak Enable-Disable eder
public: CButton* IleriButton;

// Otomatik olarak Class tarafindan kullanilabilen Button Sadece Click olayinda Geri() Fonksiyonu cagrilirsa class Bu Nesneyi otomatik olarak Enable-Disable eder
public: CButton* GeriButton;

// Fonksiyonlar arasi haberlesme degiskeni - Cagrilan noktayi belirlemek icin
private : int Cagiran;

public : AdresCubugu* adresCubugu;




public:
	KlasorList() : CListCtrl()
	{
	 imglist = new CImageList();
	 imglist->Create(16,16, ILC_COLOR32 |ILC_MASK,0, 0);
	 imglist->SetBkColor(RGB(255,255,255));

	 imglistbuyuk = new CImageList();
	 
	 imglistbuyuk->Create(32,32,ILC_COLOR32 | ILC_MASK,0,0);
	 imglistbuyuk->SetBkColor(RGB(255,255,255));
	 Adres = "";
	 SonSutunSayisi = 0;
	 OzelResimYukle(""); // Volume iconu
	 OzelResimYukle("dir"); // Klasor iconu

	 IleriButton = NULL;
	 GeriButton = NULL;
	 klasorGoster = NULL;
	 rootKlasorGoster = NULL;
	 adresCubugu = NULL;
	 Cagiran = FONKSIYON_DIREK;
	}



private :  int ResimSira(string Uzanti)
		  {
			  
			  int Index = (find(Uzantilar.begin(),Uzantilar.end(),Uzanti) -Uzantilar.begin());
			  
			  if(Index != Uzantilar.size())
			  return Index;
			  else
			  return -1;

		  }




// Parametre bos ise Mount iconu "abc" "bla" gibi harf degeri alirsa klasor iconunu alir
private : bool OzelResimYukle(string Param)
{
	// Kucuk iconlari barindiran struct
	SHFILEINFO SmallIconInfo,
	// Buyuk iconlari barindiran struct	
	NormalIconInfo;

	memset(&SmallIconInfo,0,sizeof(SmallIconInfo));

	memset(&NormalIconInfo,0,sizeof(NormalIconInfo));

	SHGetFileInfo(Param.c_str(),OZELLIK_KLASOR, &SmallIconInfo, sizeof(SmallIconInfo), SHGFI_ICON | SHGFI_SMALLICON  | SHGFI_USEFILEATTRIBUTES);

	SHGetFileInfo(Param.c_str(),OZELLIK_KLASOR, &NormalIconInfo, sizeof(NormalIconInfo),  SHGFI_ICON  | SHGFI_USEFILEATTRIBUTES);

	if(SmallIconInfo.hIcon != INVALID_HANDLE_VALUE)
	{
	
	HICON Smallicon = SmallIconInfo.hIcon;
	imglist->Add(Smallicon);


	HICON Normalicon = NormalIconInfo.hIcon;

	if(Normalicon  != INVALID_HANDLE_VALUE)
	imglistbuyuk->Add(Normalicon);
	else
		imglistbuyuk->Add(Smallicon);

	return true;
	
	}

	else
		return false;
}



private : string UzantiAl(string DosyaAdi)
{
	int Index = DosyaAdi.rfind(".");
	if(Index != -1)
	{
		string Uzanti = DosyaAdi.substr(Index,DosyaAdi.length());
		return Uzanti;
	}
	else
		return "";

 }




private : bool ResimYukle(string Uzanti)
{
	// Kucuk iconlari barindiran struct
	SHFILEINFO SmallIconInfo,
	// Buyuk iconlari barindiran struct	
	NormalIconInfo;

	memset(&SmallIconInfo,0,sizeof(SmallIconInfo));

	memset(&NormalIconInfo,0,sizeof(NormalIconInfo));

	SHGetFileInfo(Uzanti.c_str(),OZELLIK_NORMAL, &SmallIconInfo, sizeof(SmallIconInfo), SHGFI_ICON | SHGFI_SMALLICON  | SHGFI_USEFILEATTRIBUTES);

	SHGetFileInfo(Uzanti.c_str(),OZELLIK_NORMAL, &NormalIconInfo, sizeof(NormalIconInfo),  SHGFI_ICON  | SHGFI_USEFILEATTRIBUTES);

	if(SmallIconInfo.hIcon != INVALID_HANDLE_VALUE)
	{
	
	HICON Smallicon = SmallIconInfo.hIcon;
	imglist->Add(Smallicon);


	HICON Normalicon = NormalIconInfo.hIcon;

	if(Normalicon  != INVALID_HANDLE_VALUE)
	imglistbuyuk->Add(Normalicon);
	else
		imglistbuyuk->Add(Smallicon);

	Uzantilar.push_back(Uzanti);
	return true;
	
	}
	else
		return false;
}



public : bool SutunlariKaldir()
		 {
			 this->DeleteAllItems();
			 for(int i = 0; i < SonSutunSayisi;i++)
			 {

				 this->DeleteColumn(0);
			 }
			
			 SonSutunSayisi = 0;
			 return true;
		 }



public : bool GorunumRoot()
		 {
		   SutunlariKaldir();
		   this->InsertColumn(0,"Ad",LVCFMT_LEFT,100);
	       this->InsertColumn(1,"Kullanilan Alan",LVCFMT_LEFT,100);
		   this->InsertColumn(2,"Bos Alan",LVCFMT_LEFT,100);
		   return true;

		 }


public : bool GorunumKlasor()
{
		   SutunlariKaldir();
		   this->InsertColumn(0,"Ad",LVCFMT_LEFT,100);
	       this->InsertColumn(1,"Boyut",LVCFMT_LEFT,100);
		   this->InsertColumn(2,"Olusturulma Tarihi",100);
		   this->InsertColumn(3,"Son Erisim Tarihi",100);
		   this->InsertColumn(4,"Son Yazma Tarihi",100);
		   
		   return true;
}
		 



private : void SutunlariBoyutlandir()
{
	for(int i = 0; i < this->SonSutunSayisi;i++)
	{
		this->SetColumnWidth(i,LVSCW_AUTOSIZE_USEHEADER);
	}	  
}



public: bool RootKlasor(Volume& Volumeler)
	{
		GorunumRoot();
		int Boyut = Volumeler.VolumeOzellikleri.size();
		for(int i = 0; i < Boyut;i++)
		{
				int SiraNum = this->GetItemCount();
				this->InsertItem(SiraNum,Volumeler.VolumeList[i].c_str(),0);
				this->SetItemText(SiraNum,1,BoyutCevir(Volumeler.VolumeBoyut[i]).c_str());
				this->SetItemText(SiraNum,2,BoyutCevir(Volumeler.VolumeBosAlan[i]).c_str());
				
		}

		Adres = "";
		KlasorListGeri.clear();

		if(GeriButton != NULL)
			GeriButton->EnableWindow(0);

		if(IleriButton != NULL && KlasorListIleri.size() == 0)
			IleriButton->EnableWindow(0);

		return true;
	}




public: void GorunumStiliDegistir(int Gorunum)
		{
			int Stil = this->GetStyle();
			Stil &= ~LVS_TYPEMASK;
			Gorunum |=  Stil;

			::SetWindowLong(this->m_hWnd,GWL_STYLE,Gorunum);
		}





public: bool KlasorGoster(Klasor& Klasorler)
	{
		GorunumKlasor();
	   int Boyut = Klasorler.KlasorOzellikleri.size();
		for(int i = 0; i < Boyut;i++)
		{
				int SiraNum = this->GetItemCount();
				int Count = imglist->GetImageCount();
				this->InsertItem(SiraNum,Klasorler.KlasorAdlari[i].c_str(),1);
			//  this->SetItemText(SiraNum,1,BoyutCevir(Klasorler.KlasorBoyutlari[i]).c_str());  // Klasor boyutlari genelde bos.
				this->SetItemText(SiraNum,1,"");
				this->SetItemText(SiraNum,2,((Tarih)Klasorler.KlasorOlusturmaTarihi[i]).StringCevir().c_str());
				this->SetItemText(SiraNum,3,((Tarih)Klasorler.KlasorSonErisimTarihi[i]).StringCevir().c_str());
				this->SetItemText(SiraNum,4,((Tarih)Klasorler.KlasorSonYazmaTarihi[i]).StringCevir().c_str());

		}

		Boyut = Klasorler.DosyaOzellikleri.size();

		for(int i = 0; i < Boyut;i++)
		{
			int Sýra;
			if((( Sýra = ResimSira(UzantiAl(Klasorler.DosyaAdlari[i]))) != -1))
			{
				int SiraNum = this->GetItemCount();
				this->InsertItem(SiraNum,Klasorler.DosyaAdlari[i].c_str(),Sýra+2); // +2 Orijinal Image list indexi Volume ve Klasor iconlari onceden eklendigi icin fark olusuyor
				this->SetItemText(SiraNum,1,BoyutCevir(Klasorler.DosyaBoyutlari[i]).c_str());
				this->SetItemText(SiraNum,2,((Tarih)Klasorler.DosyaOlusturmaTarihi[i]).StringCevir().c_str());
				this->SetItemText(SiraNum,3,((Tarih)Klasorler.DosyaSonErisimTarihi[i]).StringCevir().c_str());
				this->SetItemText(SiraNum,4,((Tarih)Klasorler.DosyaSonYazmaTarihi[i]).StringCevir().c_str());
			}
			else
			{
				if(ResimYukle(UzantiAl(Klasorler.DosyaAdlari[i]))) 
				{
				
			        int SiraNum = this->GetItemCount();
					this->InsertItem(SiraNum,Klasorler.DosyaAdlari[i].c_str(),Uzantilar.size()+1); // +2 fark var size oldugu icin -1 arada ki fark = +1
					this->SetItemText(SiraNum,1,BoyutCevir(Klasorler.DosyaBoyutlari[i]).c_str());
					this->SetItemText(SiraNum,2,((Tarih)Klasorler.DosyaOlusturmaTarihi[i]).StringCevir().c_str());
				    this->SetItemText(SiraNum,3,((Tarih)Klasorler.DosyaSonErisimTarihi[i]).StringCevir().c_str());
				    this->SetItemText(SiraNum,4,((Tarih)Klasorler.DosyaSonYazmaTarihi[i]).StringCevir().c_str());
				}

			}
		
		}

		Adres = Klasorler.Adres;
		


		SutunlariBoyutlandir();


		switch(Cagiran)
		{


		case FONKSIYON_DIREK:
		

		KlasorListGeri.push_back(Adres);
	   
		if(adresCubugu != NULL)
		{
			adresCubugu->AddString(Adres.c_str());
			adresCubugu->SetCurSel(adresCubugu->GetCount()-1);
		}

		if(GeriButton != NULL)
			GeriButton->EnableWindow(1);


		KlasorListIleri.clear();

		if(IleriButton != NULL)
			IleriButton->EnableWindow(0);

			break;


		}


		return true;
	

	}



public: void Ileri()
{

	
 if(KlasorListIleri.size() > 0 && klasorGoster != NULL && IleriButton != NULL)
 {
  Cagiran = FONKSIYON_ILERI;

    

		 KlasorListGeri.push_back(KlasorListIleri[KlasorListIleri.size()-1]);

		 if(adresCubugu != NULL)
		 {
			 adresCubugu->AddString(KlasorListIleri[KlasorListIleri.size()-1].c_str());
			 adresCubugu->SetCurSel(adresCubugu->GetCount()-1);
		 } 
		klasorGoster(KlasorListIleri[KlasorListIleri.size()-1],*this);
	     KlasorListIleri.pop_back();


	 if(GeriButton != NULL)
		 GeriButton->EnableWindow(1);
	 


	 if(KlasorListIleri.size() == 0)
	     IleriButton->EnableWindow(0);     

	 Cagiran = FONKSIYON_DIREK;
  }

		
		
}





public: void Geri()
{
	
	
	if(KlasorListGeri.size() > 1 && klasorGoster != NULL)
    {
		Cagiran = FONKSIYON_GERI;
		

		if(adresCubugu != NULL)
		{
			adresCubugu->DeleteString(adresCubugu->GetCount()-1);
			adresCubugu->SetCurSel(adresCubugu->GetCount()-1);
		
		}
		KlasorListIleri.push_back(KlasorListGeri[KlasorListGeri.size()-1]); // Su an ki klasoru kayit et
	    KlasorListGeri.pop_back();    // Ve listeden kaldir
		klasorGoster(KlasorListGeri[KlasorListGeri.size()-1],*this); // Liste su anda bir once ki klasoru gosteriyor ve o klasor gosterilecek
			   
			   if(IleriButton != NULL)
				   IleriButton->EnableWindow(1);
		  
		Cagiran = FONKSIYON_DIREK;
     }
	else if(KlasorListGeri.size()  == 1)
	{
	   if(adresCubugu != NULL)
		{
			adresCubugu->DeleteString(adresCubugu->GetCount()-1);
			adresCubugu->SetCurSel(adresCubugu->GetCount()-1);
		
		}
      KlasorListIleri.push_back(KlasorListGeri[KlasorListGeri.size()-1]);
	  KlasorListGeri.pop_back();

	  if(rootKlasorGoster != NULL)
	  rootKlasorGoster(*this);
	  
	  if(GeriButton != NULL)
		  GeriButton->EnableWindow(0);
	
	}

}






public: int InsertColumn(int nSira,LPCSTR Baslik,int Format = 0,int Genislik = -1,int iSubItem = -1)
{
		SonSutunSayisi++;
		return CListCtrl::InsertColumn(nSira,Baslik,Format,Genislik,iSubItem);

}




	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void PreSubclassWindow();
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	friend class AdresCubugu;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

#pragma comment (lib,"KlasorListCtrl")
