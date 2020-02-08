#include "stdafx.h"

BEGIN_MESSAGE_MAP(CMesajDlg,CDialog)
	ON_BN_CLICKED(CMesajDlg::ID_BUTTON3,&CMesajDlg::Button3Tiklandi)
END_MESSAGE_MAP()

CMesajDlg::CMesajDlg(void)
{
}


CMesajDlg::~CMesajDlg(void)
{
}



CMesajDlg::CMesajDlg(CString Mesaj,CString Baslik,CString Button1Baslik,CString Button2Baslik,CString Button3Baslik,int DEFBUTTON) : CDinamikDlg(NULL,Baslik,243,63,10,10,WS_SYSMENU | WS_CAPTION | DS_CENTER | DS_SETFONT)
{

    MetinBilgileri metinBilgiler = MetinBilgileriAl((string)Mesaj.GetBuffer());
    //	 Mesaj Buyuklugune gore buyutmek icin Mesajin Bilgilerini al

	short EkUzunluk = (metinBilgiler.SatirSayisi * 8);	  // Font Buyuklugu * SatirSayisi = Uzunluk
	short EkGenislik = (metinBilgiler.EnzunSatir * 8);	  // EnUzunSatir(Satir Genisligi) * 8 = Genislik

	dialogTemplate->cx += EkUzunluk;
	dialogTemplate->cy += EkGenislik;

	

	NesneEkle(Mesaj,NESNE_STATIC,30 + EkUzunluk, 234 + EkGenislik ,6,6,ID_TEXT_STATIC,WS_VISIBLE);
	

	// Button3
	if(Button3Baslik != "")
	{

	DWORD button3Style = WS_VISIBLE;

	if(DEFBUTTON == ID_BUTTON3)
		button3Style |= BS_DEFPUSHBUTTON;
	
	NesneEkle(Button3Baslik,NESNE_BUTTON,14,50,46 + EkGenislik ,78 + EkUzunluk,ID_BUTTON3,button3Style,0);
	
	
	}


	// Button2
    if(Button2Baslik != "")
	{

	DWORD button2Style = WS_VISIBLE;

	if(DEFBUTTON == ID_BUTTON2)
		button2Style |= BS_DEFPUSHBUTTON;
	
	NesneEkle(Button2Baslik,NESNE_BUTTON,14,50,46 + EkGenislik ,132 + EkUzunluk,ID_BUTTON2,button2Style,0);
	
	
	}




	// Button1
	if(Button1Baslik != "")
	{

	DWORD button1Style = WS_VISIBLE;

	if(DEFBUTTON == ID_BUTTON1)
		button1Style |= BS_DEFPUSHBUTTON;
	
	NesneEkle(Button1Baslik,NESNE_BUTTON,14,50,46 + EkGenislik ,186 + EkUzunluk,ID_BUTTON1,button1Style,0);
	
	
	}

}



void CMesajDlg::Button3Tiklandi()
{
	EndDialog(ID_BUTTON3);
}

int MesajKutusu(string Mesaj,string Baslik /* = "" */,string Button1Baslik /* = "" */,string Button2Baslik /* = "" */,string Button3Baslik /* = "" */)
{
  int Secili_Button = 3;
  if(Button3Baslik == "")
	  Secili_Button--;

  if(Button2Baslik == "")
	  Secili_Button--;

  if(Button1Baslik == "")
	  Secili_Button--;


 CMesajDlg mesajKutusu((CString)Mesaj.c_str(),(CString)Baslik.c_str(),(CString)Button1Baslik.c_str(),(CString)Button2Baslik.c_str(),(CString)Button3Baslik.c_str(),Secili_Button);

 return mesajKutusu.DoModal();

}