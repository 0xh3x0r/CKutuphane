#pragma once

#ifndef EKLEDLG_H
#define EKLEDLG_H

#ifndef DINAMIKDLG_H
#include <dinamikdlg.h>
#endif

#ifndef STRING_H
#include <string.h>
#endif

#ifndef _STRING_
#include <string>
#endif
using namespace std;


// Basit bir metin girme dialogu
class CEkleDialog : public CDinamikDlg
{

 // DoModal() Isleminden sonra kutucuga girilmis veri buraya aktarilir
public:string GirilenMetin;

	CEkleDialog(CString MetinKutusuBaslik = "",CString PencereBaslik = "Metin Girin :",CString StaticTextBaslik =  "Metin :",CString EkleButtonBaslik = "Ekle",CString IptalButtonBaslik = "Ýptal");
	~CEkleDialog(void);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
#pragma comment(lib,"EkleDlg")
#endif