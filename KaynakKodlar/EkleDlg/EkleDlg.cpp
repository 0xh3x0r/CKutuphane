#include "stdafx.h"




CEkleDialog::CEkleDialog(CString MetinKutusuBaslik,CString PencereBaslik,CString StaticTextBaslik,CString EkleButtonBaslik,CString IptalButtonBaslik) : CDinamikDlg(NULL,PencereBaslik,174,53,0,1, WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | DS_CENTER | DS_SETFONT)
{
 NesneEkle(EkleButtonBaslik,NESNE_BUTTON,14,43,35,78,IDOK, WS_VISIBLE | BS_DEFPUSHBUTTON,0);
 NesneEkle(IptalButtonBaslik,NESNE_BUTTON,14,43,35,126,IDCANCEL, WS_VISIBLE,0);
 NesneEkle(StaticTextBaslik,NESNE_STATIC,8,36,12,6,3,WS_VISIBLE);
 NesneEkle(MetinKutusuBaslik,NESNE_EDITBOX,14,114,12,48,4,ES_AUTOHSCROLL | WS_VISIBLE | WS_BORDER);

}


CEkleDialog::~CEkleDialog(void)
{
}


void CEkleDialog::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	CWnd* GirdiTextBox = GetDlgItem(4);
	CString donenveri;
	GirdiTextBox->GetWindowTextA(donenveri);
	GirilenMetin = donenveri;
	CDinamikDlg::OnOK();
}


BOOL CEkleDialog::OnInitDialog()
{
	CDinamikDlg::OnInitDialog();
	CWnd* GirdiTextBox = GetDlgItem(4);
	GirdiTextBox->SetFocus();
	// TODO:  Add extra initialization here

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}