// Dn.cpp : Defines the entry point for the console application.
//
/*
De�i�kenler: 


 stToplam = (s1 + s2)             stXor = (s1 XOR s2)            stOr = (s1 | s2)
 
 stxFark = (stToplam - stXor)   stxFark = (stXor - stOr)  
 stoFark = (stToplam - stOr)    stoFark = (stToplam - stOr)
 

[s1,s2]

X Fonksiyona giri� yaparsa ��kacak sonu� :  (stOr XOR X) + (stoFark XOR X)


*/
#pragma region ESK�LER
/*
	std::vector<int> dataList(int Adet)
  {
	  int node = stXor - 4;
	  std::vector<int> vk;
	  
	  for(int i = 0; i < Adet;i++)
	  {
		 
		     
                node = node + 4;
			if(i  == 8)
			   {node = (node + 32);}
			    vk.push_back(node);
				int d1 = ((node ^ stToplam) / 2);
				int d2 = ((node ^ stToplam) / 2) + 1;
				int d3 = d1 ^ stXor;
				int d4 = d2 ^ stXor;
				vk.push_back(d1); vk.push_back(d2); vk.push_back(d3); vk.push_back(d4);
	  }
	  return vk;
  }

*/

#pragma endregion

#include <vector>
#include <algorithm>
#include "Y�g�n.h"




class Node
{


	int stToplam;
	int stXor;
	std::vector<int> vKk;
public:
		Node(std::vector<int> vK)
	{
		stToplam = 0; stXor = 0;
		vKk = vK;
		for(int i = 0; i < vK.size();i++)
		{
			stXor ^= vK[i]; stToplam += vK[i];
		}
	}


  int NodeAl(int Say�)
	{
    int encrypt =0;
	for(int i = 0; i < 2;i++){ 
		encrypt += (vKk[i] ^ Say�);
	}
	return encrypt;
 };

	Y�g�n<int> dataList(int Adet){
	
	Y�g�n<int> Donus;

	for(int giris = 1; giris < Adet;giris++){
	int encrypt = 0;
	for(int i = 0; i < 2;i++){
	encrypt += (vKk[i] ^ giris);}
	
	int params[] = {0,encrypt};
	int s�ra = Donus.S�raAl(params,2);
	if(s�ra != -1)
			Donus.Yerle�tir(s�ra + 2,giris); 
	else{
		Donus.Ekle(0); Donus.Ekle(encrypt); Donus.Ekle(giris); Donus.Ekle(0);}
    }

    return Donus;
	};
};
