#pragma region TANIMLAMALAR
#ifndef FTPPROT_H
#define FTPPROT_H

#ifndef _INC_STRING
#include <string.h>
#endif
#ifndef  _IOSTREAM_
#include <iostream>
using namespace std;
#endif

#ifndef SOCKET_H
#include <Socket.h>
#endif

#ifndef HAZIRFONKSIYONLAR_H
#include <HazirFonksiyonlar.h>
#endif


using namespace std;
#ifndef THREAD_H
#include <Thread.h>
#endif
#ifndef _VECTOR_
#include <vector>
#endif
#pragma endregion



#pragma region KULLANIM
/*
 FtpIstemci ftp("ftp.blabla.com",21);
	while(true)
	{
	if(ftp.Durum == BAGLANTI_VAR){

     if(ftp.Giris("KullaniciAdi","Þifre"))
	 cout<<"Giris Basarili"<<"\n";
	 if(ftp.KlasorDegistir("/htdocs")) 
	 cout<<"Klasor simdi : /htdocs"<<"\n";
	 else
     cout<<"Klasor Degistirme Basarisiz!"<<"\n";

	 tpKlasorBilgileri klasorbilgileri
    if(!ftp.KlasorBilgileri(root_klasor))
    return 0;

	 Byte dosya;
	 	int index = -1;
    if(( index = ftp.dosya_ara("license.txt",klasorbilgileri)))  // license.txt bulundu
    {                          
		Byte veri;
		veri.YeniOlustur(ftp.dosya_boyut_al(index,klasorbilgileri));

	 if(ftp.Download("license.txt",dosya))
		 cout<<"Download Tamamlandi!"<<"\n";
	 else
		 cout<<"Download Basarisiz"<<"\n";

	}
	 if(ftp.KlasorDegistir("/htdocs/ASD"))
		 cout<<"Klasor simdi : /ASD"<<"\n";
	 else
	  cout<<"Klasor Degistirme Basarisiz!"<<"\n";
	stDosyaYaz(stDosyaYaratAc("C:\\license.txt"),dosya);
	
	Byte dosyaveri;
	HANDLE hDosya = stDosyaAc("C:\\license.txt");
	dosyaveri.YeniOlustur(DosyaBoyutu(hDosya));
	stDosyaOku(hDosya,dosyaveri);
	if(ftp.Upload("license.txt",dosyaveri))
	 cout<<"Upload Tamamlandi!"<<"\n";
	else
		 cout<<"Upload Basarisiz!"<<"\n";
   }
  
	Sleep(5000);
	cout<<"Tekrar Deneniyor"<<"\n";
	ftp.TekrarDene();
	
	}


   tpKlasorBilgileri dnm;
   if(ftp.KlasorBilgileri(dnm))
   {
	   cout<<"Klasor bilgileri alindi"<<"\n";
	   cout<<"Dosyalar"<<"\n";
	   int Boyut = dnm.Dosyalar.size();
	   for(int i = 0; i < Boyut;i++){
		   cout<<dnm.Dosyalar[i].c_str()<<"\n";
	   }
	    cout<<"Klasorler"<<"\n";
	   Boyut = dnm.Dosyalar.size();
	   for(int i = 0; i < Boyut;i++){
		   cout<<dnm.Klasorler[i].c_str()<<"\n";
	   }
   }
   else
	   cout<<"Basarisiz";


*/

#pragma endregion

#pragma region FTP_MESAJLAR


#define FTP_HAZIR ("220")
#define FTP_BAGLANDI ("230")
#define FTP_SIFRE_GEREKLI ("331")
#define FTP_GIRIS_VAR ("530")
#define KMT_GIRIS ("USER ")
#define KMT_SIFRE ("PASS ")
#define KMT_KLASORBILGILERI ("MLSD")
#define KMT_KLASOR_OLUSTUR ("MKD ")
#define CVP_KLASOR_OLUSTUR ("257")
#define KMT_TYPE_BINARY ("TYPE I")
#define CVP_TYPE ("200")
#define KMT_PORT ("PORT ")
#define KMT_PASIF ("PASV ")
#define CVP_PASIF ("227")
#define KMT_KLASOR_DEGISTIR ("CWD ")
#define CVP_KLASOR_DEGISTIR ("250")
#define KMT_DOWNLOAD ("RETR ")
#define KMT_UPLOAD ("STOR ")
#define CVP_DOSYATRANSFER ("226")
#define KMT_SIL ("DELE ")
#define CVP_SIL ("250")
#define KMT_DOSYA_ISIM_DEGIS1 ("RNFR ")
#define CVP_DOSYA_ISIM_DEGIS1 ("350")
#define KMT_DOSYA_ISIM_DEGIS2 ("RNTO ")
#define CVP_DOSYA_ISIM_DEGIS2 ("250")
#pragma endregion
typedef struct _KlasorBilgileri{
	vector<string> Klasorler;
	vector<string> Dosyalar;
	vector<int> DosyaBoyutu;
} tpKlasorBilgileri;
typedef void (*Event)(int,char*);
typedef struct _VekilParams
{
	Socket* istemci;
	Byte* veri;
	int Donus;
	Event  Veri_Gonderildi;
	Event Aktarim_Tamamlandi;
	string DosyaAdi;
	char* EK_PARAM;
    int* Ptr;
}VekilParams; 
 
   extern void thread_Vekil_rnVeriAl(VekilParams &params);
   extern void thread_Vekil_VeriGonder(VekilParams &params);
   extern void thread_Vekil_VeriAl(VekilParams &params);


class FtpIstemci: public Socket
{

	/////////////////////////////////////////////////////////  MAKROLAR   ///////////////////////////////////////////////////////////

#define KomutGonder(Komut,Parametre) \
	{ \
     	Packet = Komut; \
		Packet.append(Parametre); \
		Packet.append(P_BITIS);   \
		this->veriGonder((char*)(Packet.data()),Packet.size());  \
}; \
	
   #define _KomutGonder(Komut) \
	{ \
     	Packet = Komut; \
		Packet.append(P_BITIS);   \
		this->veriGonder((char*)(Packet.data()),Packet.size());  \
   }; \

#define CevapAl()  \
	{   gVeri = (char*) malloc(255); \
		int Donus = this->veriAl(gVeri); \
		*(gVeri + Donus) = '\"'; Donus++; *(gVeri + Donus) = '\x00';\
	};   \

	
#define KomutGonder2(Komut,Parametre) \
	{ \
	Packet = Komut; \
	Packet.append(Parametre); \
	Packet.append(P_BITIS);   \
	ist.veriGonder((char*)(Packet.data()),Packet.size());  \
}; \

#define _KomutGonder2(Komut) \
	{ \
	Packet = Komut; \
	Packet.append(P_BITIS);   \
	ist.veriGonder((char*)(Packet.data()),Packet.size());  \
}; \

#define CevapAl2()  \
	{   gVeri = (char*) malloc(255); \
	int Donus = ist.veriAl(gVeri); \
	*(gVeri + Donus) = '\"'; Donus++; *(gVeri + Donus) = '\x00';\
};   \

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


public:
	char* Kullanici_Adi;
public:
	char* Sifre_;
public:
	string Klasor;
public:
	Event Veri_Gonderildi;
	Event Aktarim_Tamamlandi;
	FtpIstemci(char* Domain_IP,int PORT):Socket(Domain_IP,PORT)
	{
		Veri_Gonderildi = 0;
	    Aktarim_Tamamlandi = 0;
		Byte veri; // *
		this->rnVeriAl(veri); // Hoþgeldin mesajini geç
		veri.Kaldir();
	
	}

public:
	void TekrarDene()
	{
		this->TekrarBaglan();
		Byte veri; // *
		this->rnVeriAl(veri); // Hoþgeldin mesajini geç
		veri.Kaldir();

	}
public:
int Giris(char* KullaniciAdi,char* Sifre){ 
//////////////////////////////////////////////////////////////////////////
			    int k_adi_boyut = (strlen(KullaniciAdi));
				Kullanici_Adi = (char*) malloc(k_adi_boyut);
				memset(Kullanici_Adi,0,k_adi_boyut);
				strncpy(Kullanici_Adi,KullaniciAdi,k_adi_boyut+1);
				int sifre_boyut = (strlen(Sifre));
				Sifre_ = (char*) malloc(sifre_boyut);
				memset(Sifre_,0,sifre_boyut);
				strncpy(Sifre_,Sifre,sifre_boyut+1);
///////////////// Kullanici Adi Þifre Kaydet //////////////////////////
string Packet;
char* gVeri;
	     KomutGonder(KMT_GIRIS,KullaniciAdi); 
	     CevapAl();
if(gVeri <= 0) return 0;  // Baðlanti Kapandi
	    Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3); // Ýlk 3 Byte Al
if((Packet.compare(FTP_SIFRE_GEREKLI)) == 0){
				KomutGonder(KMT_SIFRE,Sifre);
		
		memset(gVeri,0,255); // GelenVeri Temizle
	    CevapAl();
if(gVeri <= 0) return 0;
		Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);
if((Packet.compare(FTP_BAGLANDI)) == 0){
                free(gVeri);
				return 1;
}


}
else if((Packet.compare(FTP_GIRIS_VAR)) == 0){
                free(gVeri);
				return 1;
}
        free(gVeri);
		return 0;
	};
	
public:
	int KlasorOlustur(string Klasor_Adi){
		char* gVeri;
		Klasor_Adi.insert(0,KMT_KLASOR_OLUSTUR);
		Klasor_Adi.append(P_BITIS);
		this->veriGonder((char*)Klasor_Adi.c_str(),Klasor_Adi.size());
		
		CevapAl();
		if(gVeri <= 0) return 0;
		Klasor_Adi.assign(gVeri,3);


		free(gVeri);
		if(!Klasor_Adi.compare(CVP_KLASOR_OLUSTUR)) // Eþit ise 0
		return 1;

	return 0;
	}
	public:
	int DosyaSil(string DosyaAdi){
		char* gVeri;
		DosyaAdi.insert(0,KMT_SIL);
		DosyaAdi.append(P_BITIS);
		this->veriGonder((char*)DosyaAdi.c_str(),DosyaAdi.size());
		CevapAl();
		if(gVeri <= 0) return 0;
		DosyaAdi = gVeri;
		int ilk = DosyaAdi.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = DosyaAdi.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",DosyaAdi,DosyaAdi,sonraki);
		DosyaAdi.erase(3);


		free(gVeri);
		if(!DosyaAdi.compare(CVP_SIL)) // Eþit ise 0
		return 1;

	return 0;
	}
public:
	// Pasif Mod & Önceden dosya boyutu alýnýp ona göre Byte oluþturulmalý.
	int Download(string DosyaAdi,Byte &dosya)
	{
		string Packet;
		char* gVeri;
			Packet.insert(0,KMT_TYPE_BINARY);
			Packet.append(P_BITIS);
			this->veriGonder((char*)Packet.c_str(),Packet.size());
			Sleep(100);
		CevapAl();
		Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);
if((Packet.compare(CVP_TYPE) == 0)){  // TYPE KOMUTU KABUL EDÝLDÝ
        Devam:  // Bazi Sunucular Þifre tekrarlama istiyor
        _KomutGonder(KMT_PASIF);
		Sleep(100);
		CevapAl();
		Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);
if((Packet.compare(CVP_PASIF)) == 0){ // CVP PASIF
         #pragma region Dosya protokolü için packet Olusturma
			
			Packet.assign(gVeri);
		
			size_t index_baslangic = Packet.rfind(")");
			
			if(index_baslangic == -1)
				return 0;

			int ilk_byte_son = Packet.rfind(",");
			if(ilk_byte_son == string::npos)
	         return 0;

			int Port =  atoi(Packet.substr((ilk_byte_son+1),(index_baslangic-ilk_byte_son)-1).c_str());

			size_t ikinci_byte_son =  Packet.rfind(",",ilk_byte_son-1);
			if(ikinci_byte_son == string::npos)
				return 0;
			index_baslangic = ilk_byte_son;
			Port =((atoi(Packet.substr((ikinci_byte_son+1),(index_baslangic-ikinci_byte_son)-1).c_str())) << 8) | Port;
			

	        
         #pragma endregion
		 Socket Socket2(inet_ntoa(this->struct_socketVeri.sin_addr),Port);
		 VekilParams params;
		 params.istemci = &Socket2;
		 params.veri = &dosya;
         params.Donus = 0; // 0 a Ayarla ilerde hata olursa -1 doner!
		 Thread t;
		 t.Baslat(&params,(int*)thread_Vekil_VeriAl);
		 //////////////////// DOWNLOAD KOMUTU GONDER //////////////
		 KomutGonder(KMT_DOWNLOAD,DosyaAdi);
		 //////////////////// DOWNLOAD KOMUTU GONDER //////////////
		
		 while(params.Donus == 0){ Sleep(100); } // Download Ýþlemini Bekle
		  CevapAl();
if(params.Donus > 0){  // Dosya Doðru inmiþ mi ?
		   t.Kaldir();
		   return 1;
}
else{
			 t.Kaldir();
			 return 0;
}
		
} // CVP PASIF
		
}// CVP TYPE
else if((Packet.compare(FTP_SIFRE_GEREKLI)) == 0){
			KomutGonder(KMT_SIFRE,Sifre_);
			Sleep(100);
		    CevapAl();
if(gVeri <= 0)
			return 0;

        Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);
		    if((Packet.compare(FTP_BAGLANDI)) == 0)
			goto Devam;
}
		return 0;
}

public:
	// Pasif Mod
int Upload(string DosyaAdi,Byte &dosya,char* TH_EK_PARAM)
	{
			string Packet;
		    char* gVeri;
			Packet.insert(0,KMT_TYPE_BINARY);
			Packet.append(P_BITIS);
			this->PaketTemizle();
			this->veriGonder((char*)Packet.c_str(),Packet.size());
		    CevapAl();
		Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);
if((Packet.compare(CVP_TYPE) == 0)){  // TYPE KOMUTU KABUL EDÝLDÝ
Devam:  // Bazi Sunucular Þifre tekrarlama istiyor
        
	    this->PaketTemizle();
	    _KomutGonder(KMT_PASIF);
		CevapAl();
		Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);

if((Packet.compare(CVP_PASIF)) == 0){ // CVP PASIF
			#pragma region Dosya protokolü için packet Olusturma
			
			Packet.assign(gVeri);
		
			size_t index_baslangic = Packet.rfind(")");
			
			if(index_baslangic == -1)
				return 0;

			int ilk_byte_son = Packet.rfind(",");
			if(ilk_byte_son == string::npos)
	         return 0;

			int Port =  atoi(Packet.substr((ilk_byte_son+1),(index_baslangic-ilk_byte_son)-1).c_str());

			size_t ikinci_byte_son =  Packet.rfind(",",ilk_byte_son-1);
			if(ikinci_byte_son == string::npos)
				return 0;
			index_baslangic = ilk_byte_son;
			Port =((atoi(Packet.substr((ikinci_byte_son+1),(index_baslangic-ikinci_byte_son)-1).c_str())) << 8) | Port;
			

	        
         #pragma endregion

			 Socket* Socket2;
             Socket2 = new Socket(inet_ntoa(this->struct_socketVeri.sin_addr),Port);
			 this->PaketTemizle();
			 KomutGonder(KMT_UPLOAD,DosyaAdi); // Veri gonderildi dosya adini belirt
			 CevapAl();
		    VekilParams* params;
			params = new VekilParams();
		    params->istemci = Socket2;
		    params->veri = &dosya;
			params->Veri_Gonderildi = Veri_Gonderildi;
			params->Aktarim_Tamamlandi = Aktarim_Tamamlandi;
			params->EK_PARAM = TH_EK_PARAM;
			params->DosyaAdi = DosyaAdi;
            params->Ptr = (int*)this;
		    Thread t;
			t.Baslat(params,(int*)thread_Vekil_VeriGonder);
			this->PaketTemizle();
					 

					 return 1;
		}
else if((Packet.compare(FTP_SIFRE_GEREKLI)) == 0){
			KomutGonder(KMT_SIFRE,Sifre_);
		    CevapAl();
		  if(gVeri <= 0)
			return 0;

		 Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);
		    if((Packet.compare(FTP_BAGLANDI)) == 0)
			goto Devam;
		}
		
	}
		return 0;
	}

inline
	tpKlasorBilgileri klasor_bilgileri_yorumla(string veri)
{
	tpKlasorBilgileri bilgiler;
	int index_ = 0;
	int index2 = 0;
	int son = veri.find_last_of("\r\n");
	if(son == -1)
		return bilgiler;
	while((index_ <= son) && (index_ != -1)) { 
		string Aralýk = "";
		index2 = KelimeArasi("","\r\n",veri,Aralýk,index_);
		int type_index = Aralýk.find("type=")+5;

		if(type_index == 4) // != (-1+Boyut) 
			return bilgiler;

		string Type = Aralýk.substr(type_index,Aralýk.find(";",type_index)-type_index);
		if(Type.compare("dir") == 0){
			int ad_index = Aralýk.rfind(";")+1;
			if(ad_index == 0)
				return bilgiler;

			bilgiler.Klasorler.push_back(Aralýk.substr(ad_index+1,Aralýk.length()));// ; Sonra 1 boþluk var
		}
		if(Type.compare("file") == 0){
			int ad_index = Aralýk.rfind(";")+1;
			if(ad_index == 0)
				return bilgiler;
			string Boyut = "";
			KelimeArasi("size=",";",Aralýk,Boyut);
			if(Boyut.compare("") != 0)
				bilgiler.DosyaBoyutu.push_back(atoi(Boyut.c_str()));
			bilgiler.Dosyalar.push_back(Aralýk.substr(ad_index+1,Aralýk.length())); // ; Sonra 1 boþluk var

		}
		index_=index2;
	}

	return bilgiler;
}
public:
	int KlasorDegistir(const char* _Klasor)
	{
		string Packet;
		char* gVeri;
		KomutGonder(KMT_KLASOR_DEGISTIR,_Klasor);
		Sleep(100);
		CevapAl();
		Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);
if((Packet.compare(CVP_KLASOR_DEGISTIR)) == 0 ) {
			Klasor = _Klasor;
			return 1;
}
		return 0;
	}
public:
	int KlasorBilgileri(tpKlasorBilgileri& Bilgiler)
	{
		string Packet;
		char* gVeri;
		Byte veri; // *
		_KomutGonder(KMT_PASIF);
		Sleep(100); // Server Bekle
		CevapAl();

		Packet = gVeri;
		int ilk = Packet.find("\r\n\"");
		if(ilk < 0)
		{veri.Kaldir(); return false;}
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);

if((Packet.compare(CVP_PASIF)) == 0){ // CVP PASIF
	    #pragma region Dosya protokolü için packet Olusturma
			
			Packet.assign(gVeri);
		
			size_t index_baslangic = Packet.rfind(")");
			
			if(index_baslangic == -1)
			{veri.Kaldir();return 0;}

			int ilk_byte_son = Packet.rfind(",");
			if(ilk_byte_son == string::npos)
			{veri.Kaldir();return 0;}

			int Port =  atoi(Packet.substr((ilk_byte_son+1),(index_baslangic-ilk_byte_son)-1).c_str());

			size_t ikinci_byte_son =  Packet.rfind(",",ilk_byte_son-1);
			if(ikinci_byte_son == string::npos)
			{veri.Kaldir();return 0;}
			index_baslangic = ilk_byte_son;
			Port =((atoi(Packet.substr((ikinci_byte_son+1),(index_baslangic-ikinci_byte_son)-1).c_str())) << 8) | Port;
			

	        
         #pragma endregion
				 Socket Socket2(inet_ntoa(this->struct_socketVeri.sin_addr),Port);
		 VekilParams params;
		 params.istemci = &Socket2;
		 params.veri = &veri;
         params.Donus = 0; // 0 a Ayarla ilerde hata olursa -2 doner!
		 Thread t;
		 t.Baslat(&params,(int*)thread_Vekil_rnVeriAl);
		 //////////////////// KLASOR BILGILERI KOMUTU //////////////
		 _KomutGonder(KMT_KLASORBILGILERI);
		 Sleep(100);
		 CevapAl();
		 //////////////////// KLASOR BILGILERI KOMUTU //////////////
		 
		 
		  
		 while(params.Donus == 0  ){ Sleep(100); } // Veriyi bekle
		  CevapAl();
if(params.Donus > 0){  // Veri Doðru inmiþ mi ?
	

	       Bilgiler = klasor_bilgileri_yorumla(veri.StringCevir());
	       veri.Kaldir();
		   t.Kaldir();
		   return 1;
}
else{
	         veri.Kaldir(); 
			 t.Kaldir();
			 return 0;
}
		

	}
   return 0;
	}

inline int klasor_ara(char* Klasor_Adi,tpKlasorBilgileri& Bilgiler){
         int Boyut = (Bilgiler.Klasorler).size();
         for(int i = 0; i < Boyut;i++){         
         if((Bilgiler.Klasorler[i].compare(Klasor_Adi)) == 0)
         return(i + 1);     
         }
         return 0; 
}
// index + 1 döner (bool) var - yok kondisyonu kazandirabilmek için,sonradan index kullanilacaksa dönüs - 1;
inline int dosya_boyut_al(int index,tpKlasorBilgileri& Bilgiler)
{
	return(Bilgiler.DosyaBoyutu[index-1]);

}

inline int dosya_ara(char* Dosya_Adi,tpKlasorBilgileri& Bilgiler){
         int Boyut = (Bilgiler.Dosyalar).size();
         for(int i = 0; i < Boyut;i++){         
         if((Bilgiler.Dosyalar[i].compare(Dosya_Adi)) == 0)
         return(i + 1);     
         }
         return 0; 
}
// index + 1 döner (bool) var - yok kondisyonu kazandirabilmek için,sonradan index kullanilacaksa dönüs - 1;
  bool DosyaKontrol(char* Dosya_Adi)
   {
	 tpKlasorBilgileri root_klasor;
    if(!KlasorBilgileri(root_klasor))
    return false;
    int index = -1;
    if(dosya_ara(Dosya_Adi,root_klasor))
     return true;
	
	return false;
   }
 bool DosyaIsimDegis(char* Eski,char* Yeni){
	string Packet;
		char* gVeri;
		KomutGonder(KMT_DOSYA_ISIM_DEGIS1,Eski);
		CevapAl();
		 Packet = gVeri;
		int ilk = Packet.rfind("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);
if((Packet.compare(CVP_DOSYA_ISIM_DEGIS1)) == 0 ) {
   KomutGonder(KMT_DOSYA_ISIM_DEGIS2,Yeni);
   CevapAl();
        Packet = gVeri;
		int ilk = Packet.rfind("\r\n\"");
		if(ilk < 0)
			return false;
		int sonraki = Packet.rfind("\r\n",ilk-1);
		if(sonraki > 0 )
		KelimeArasi("\r\n","\r\n\"",Packet,Packet,sonraki);
		Packet.erase(3);
if((Packet.compare(CVP_DOSYA_ISIM_DEGIS2)) == 0 ) {
                free(gVeri);
				return true;
 }

 }

return 0;
 }

};

#pragma comment(lib,"FtpProt.lib")
#endif