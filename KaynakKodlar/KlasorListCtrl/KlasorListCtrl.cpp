
#ifndef KLASORLISTCTRL_H
#include "KlasotListCtrl.h"
#endif

BEGIN_MESSAGE_MAP(KlasorList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &KlasorList::OnNMDblclk)
END_MESSAGE_MAP()







void KlasorList::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	this->SetImageList(this->imglist,LVSIL_SMALL);
	this->SetImageList(this->imglistbuyuk,LVSIL_NORMAL);
	this->SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	CListCtrl::PreSubclassWindow();
}


void KlasorList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE item = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		*pResult = 0;
		if(item->iItem != -1)
		{
			LVITEM Nesne;
			ZeroMemory(&Nesne,sizeof(LVITEM));
			Nesne.mask = LVIF_IMAGE;
			Nesne.iItem = item->iItem;
			this->GetItem(&Nesne);
			
			if((Nesne.iImage == 0) || (Nesne.iImage == 1)) // Volume veya Klasor ise
			{
				string NesneAdi = this->GetItemText(Nesne.iItem,0); 			 // Ad Sutunundan Klasor adini al
				if( (NesneAdi.length() > 0) && (klasorGoster !=  NULL) ) // Event tanimlandiysa ve NesneAdi bos degil ise
				{
		
				string KlasorAdi = this->Adres; // Eski yolu al

				if((NesneAdi.compare(NesneAdi.length()-1,1,"\\") != 0))
					NesneAdi.append("\\"); // Sonunda '\' yoksa ekle.

				KlasorAdi+= NesneAdi; // Yolu kayit et

				klasorGoster(KlasorAdi,*this); // Eventi tetikle
			

				}
			}
		   
			else			// Dosya Ise
			{

				if(dosyaTiklandiEvent != NULL)
				{
				  string DosyaYolu=this->Adres;
				  DosyaYolu += this->GetItemText(Nesne.iItem,0); 	
				  dosyaTiklandiEvent(DosyaYolu,*this);

				}

			}





		}
	*pResult = 0;
}
BEGIN_MESSAGE_MAP(AdresCubugu, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &AdresCubugu::OnCbnSelchange)
END_MESSAGE_MAP()


void AdresCubugu::OnCbnSelchange()
{
	int index = this->GetCurSel();
	
	
	if(index != -1 && klasorList != NULL && klasorList->klasorGoster != NULL)
	{
		this->klasorList->Cagiran = FONKSIYON_COMBOBOX;
		CString KlasorYolu;
		this->GetLBText(index,KlasorYolu);

		this->klasorList->klasorGoster((string)KlasorYolu,*this->klasorList);

		this->klasorList->KlasorListIleri.clear(); // Ileri klasorleri temizle

		this->GeriKalanlariTemizle(index); // Ileride kalan klasor listesini temizle

		klasorList->KlasorListGeri.erase(klasorList->KlasorListGeri.begin()+(index+1),klasorList->KlasorListGeri.end());
		// En son item kaldiysa onu secili yap
		int Boyut = GetCount();  
		if(Boyut)
		{
			this->SetCurSel(Boyut-1);
		}
		
		
		if(klasorList->IleriButton != NULL)
			klasorList->IleriButton->EnableWindow(0);

		this->klasorList->Cagiran = FONKSIYON_DIREK;
	}
}


void AdresCubugu::PreSubclassWindow()
{
	DropDownListBoyut(5); // 5 item gostericek sekilde ayarla
	CComboBox::PreSubclassWindow();
}



BOOL AdresCubugu::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)
	{
	case WM_KEYDOWN:

		if(pMsg->wParam == VK_RETURN)
		{ // Enter a basildi
			if(this->klasorList != NULL && this->klasorList->klasorGoster != NULL)
			{
				CString csAdres = "";
				this->GetWindowText(csAdres);
				if(csAdres != "")
				{

				 klasorList->klasorGoster((string)csAdres,*klasorList);
				}
				// Dogru don VK_RETURN ComboBox Parent windowa geciyor ve Dialog kapaniyor.
				return TRUE;
			}


		}

	break;

	}
	
	
	return CComboBox::PreTranslateMessage(pMsg);
}


BOOL KlasorList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		
		switch(pMsg->wParam)
		{



			// Sol yon tusuna basildi geri git
		case VK_LEFT:
			this->Geri();
			return TRUE;
			break;

			// Backspace tusuna basildi geri git
		case VK_BACK :
			this->Geri();
			return TRUE;
			break;


			// Sag yon tusuna basildi ileri git
		case VK_RIGHT:
			this->Ileri();
			return TRUE;
			break;


			// Enter tusuna basildi klasor islemleri
		case VK_RETURN:


		  if(GetSelectionMark() != -1)
		 {
			LVITEM Nesne;
			ZeroMemory(&Nesne,sizeof(LVITEM));
			Nesne.mask = LVIF_IMAGE;
			Nesne.iItem = GetSelectionMark();
			this->GetItem(&Nesne);
			
			if((Nesne.iImage == 0) || (Nesne.iImage == 1)) // Volume veya Klasor ise
			{
				string NesneAdi = this->GetItemText(Nesne.iItem,0); 			 // Ad Sutunundan Klasor adini al
				if( (NesneAdi.length() > 0) && (klasorGoster !=  NULL) ) // Event tanimlandiysa ve NesneAdi bos degil ise
				{
		
				string KlasorAdi = this->Adres; // Eski yolu al

				if((NesneAdi.compare(NesneAdi.length()-1,1,"\\") != 0))
					NesneAdi.append("\\"); // Sonunda '\' yoksa ekle.

				KlasorAdi+= NesneAdi; // Yolu kayit et

				klasorGoster(KlasorAdi,*this); // Eventi tetikle
			

				}
			}
			else			// Dosya Tiklandi
			{

				if(dosyaTiklandiEvent != NULL)
				{
				  string DosyaYolu=this->Adres;
				  DosyaYolu += this->GetItemText(Nesne.iItem,0); 	
				  dosyaTiklandiEvent(DosyaYolu,*this);

				}

			}


		}
               return TRUE;
               break;



		 // Yenileme yap
		case VK_F5:
			
			// Root klasor mu Normal Klasor mu ?
			if(Adres != "")
			{
												// Normal klasorde
			if(klasorGoster != NULL)
			{
				klasorGoster(this->Adres,*this);

			}

			}
			else
			{									// Root klasor
				if(rootKlasorGoster != NULL)
				{

					rootKlasorGoster(*this);

				}


			}


			break;


		  return TRUE;
			break;
		}


		break;
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}
