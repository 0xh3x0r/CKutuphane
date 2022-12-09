#pragma once

#ifndef PEBILGISI
#define PEBILGISI

#ifndef METIN_H
#include <metin.h>
#endif


#ifndef BYTE_H
#include <byte.h>
#endif






typedef struct imported_func {

	WORD hint;
	Metin funcname;
	int funcRVA;

	// offset of entry rel to import directory section
	int offset;

};

typedef struct imported_dll {
	Metin dllname;
	vector<imported_func> importedfuncs;

};



struct exported_name
{
	DWORD rva;
	WORD ordinal; // this is the index of function that named rva refers to

};


struct exported_func
{
	DWORD funcRva;
	DWORD Ordinal;
};

struct exportedfunc
{
	DWORD Ordinal;
	DWORD NameOrdinal;
	DWORD funcRVA;
	DWORD nameRVA;
	Metin funcname;

};


struct datadirs {


	IMAGE_DATA_DIRECTORY exportdir, importdir, resdir, exceptiondir, securitydir, basereloc, debug, architecture, globalptrdir, tlsdir, loadconfigdir, boundimportdir, iatdir, delayimportdir, comdescriptordir;
	int toplamaktif;

};

struct ozellikparser {

	bool executable;
	bool writeable;
	bool readable;
	bool shared;
	bool fardata;
	bool onaltibit;
	bool purgable;
	bool locked;
	bool preload;
	bool iscode;
	bool initializedata;
	bool uniniteddata;
	bool globalptr;
	bool islinkinfo;
	bool isreloc;
	bool linkother;
	bool linkremove;
	bool linkcomdat;


	ozellikparser(DWORD sectionozellikleri)

	{


		executable = (sectionozellikleri		& IMAGE_SCN_MEM_EXECUTE);
		writeable = (sectionozellikleri			& IMAGE_SCN_MEM_WRITE);
		readable = (sectionozellikleri			& IMAGE_SCN_MEM_READ);
		shared = (sectionozellikleri			& IMAGE_SCN_MEM_SHARED);
		locked = (sectionozellikleri			& IMAGE_SCN_MEM_LOCKED);

		fardata = (sectionozellikleri			& IMAGE_SCN_MEM_FARDATA);
		purgable = (sectionozellikleri			& IMAGE_SCN_MEM_16BIT);

		preload = (sectionozellikleri			& IMAGE_SCN_MEM_PRELOAD);

		iscode = (sectionozellikleri			& IMAGE_SCN_CNT_CODE);
		initializedata = (sectionozellikleri	& IMAGE_SCN_CNT_INITIALIZED_DATA);
		uniniteddata = (sectionozellikleri		& IMAGE_SCN_CNT_UNINITIALIZED_DATA);
		globalptr = (sectionozellikleri			& IMAGE_SCN_GPREL);
		islinkinfo = (sectionozellikleri		& IMAGE_SCN_LNK_INFO);
		isreloc = (sectionozellikleri			& IMAGE_SCN_LNK_NRELOC_OVFL);
		linkremove = (sectionozellikleri			& IMAGE_SCN_LNK_REMOVE);
		linkother = (sectionozellikleri			&IMAGE_SCN_LNK_OTHER);
		linkcomdat = (sectionozellikleri			&IMAGE_SCN_LNK_COMDAT);

	}

	DWORD asCharactericts()
	{
		DWORD characteristics = 0;
		if (executable)		characteristics = characteristics | IMAGE_SCN_MEM_EXECUTE;
		if (writeable)		characteristics = characteristics | IMAGE_SCN_MEM_WRITE;
		if (readable)		characteristics = characteristics | IMAGE_SCN_MEM_READ;
		if (shared)			characteristics = characteristics | IMAGE_SCN_MEM_SHARED;
		if (locked)			characteristics = characteristics | IMAGE_SCN_MEM_LOCKED;
		if (fardata)		characteristics = characteristics | IMAGE_SCN_MEM_FARDATA;
		if (purgable)		characteristics = characteristics | IMAGE_SCN_MEM_PURGEABLE;
		if (iscode)			characteristics = characteristics | IMAGE_SCN_CNT_CODE;
		if (initializedata)		characteristics = characteristics | IMAGE_SCN_CNT_INITIALIZED_DATA;
		if (uniniteddata)		characteristics = characteristics | IMAGE_SCN_CNT_UNINITIALIZED_DATA;
		if (globalptr)		characteristics = characteristics | IMAGE_SCN_GPREL;
		if (islinkinfo)		characteristics = characteristics | IMAGE_SCN_LNK_INFO;
		if (isreloc)		characteristics = characteristics | IMAGE_SCN_LNK_NRELOC_OVFL;
		if (linkremove)		characteristics = characteristics | IMAGE_SCN_LNK_REMOVE;
		if (linkother)		characteristics = characteristics | IMAGE_SCN_LNK_OTHER;
		if (linkcomdat)		characteristics = characteristics | IMAGE_SCN_LNK_COMDAT;


		return characteristics;
	}

};



class PEBilgisi
{

public:
	char* baseaddr;
	PIMAGE_DOS_HEADER dosheader;
	IMAGE_FILE_HEADER fileheader;
	IMAGE_OPTIONAL_HEADER32 peheader;



	vector<IMAGE_SECTION_HEADER> allsections;
	vector<IMAGE_SECTION_HEADER> executablesections;
	vector<IMAGE_SECTION_HEADER> datasections;

	// if detected these pointers points to raw data of relative section , its basicly baseaddr + section.PointerToRawData


	// pointer to opcodes & raw data of .code section
	char* ptrrawcode;



	// pointer to raw data of .data section
	char* ptrrawdata;

	IMAGE_SECTION_HEADER datasection;
	IMAGE_SECTION_HEADER codesection;
	IMAGE_SECTION_HEADER importsection;
	IMAGE_SECTION_HEADER resourcesection;

	// all imported functions and dlls are loaded in this vector. its sorted by dlls
	vector<imported_dll> importeddlls;

	// solely for readability it stores image entry directories (iat / import / bound import etc) some are not loaded
	datadirs imgdirs;



	int veriboyutu;

	int peboyutu;

	int sectionsayisi;

	PIMAGE_NT_HEADERS32 opthdr;

	PEBilgisi(Byte& veri)
	{
		baseaddr = veri.getdata();
		veriboyutu = veri.Boyut;


	}




	// Searches the allsections vector and gets the section that RVA points to | returns 0 if failed
	PIMAGE_SECTION_HEADER getSectionFromRVA(DWORD rva)
	{
		PIMAGE_SECTION_HEADER phdr = NULL;

		for (int i = 0; i < allsections.size(); i++)
		{
			DWORD sectionboundry = allsections[i].VirtualAddress + allsections[i].SizeOfRawData;
			if (rva <= sectionboundry)
			{
				phdr = &allsections[i];
				return phdr;
			}

		}

		return NULL;
	}





	// load important data entry sections to imgdirs variable
	void loadentries()
	{

		// some important data entries can be

		imgdirs.toplamaktif = 0;


		for (size_t i = 0; i < 15; i++)
		{
			if (opthdr->OptionalHeader.DataDirectory[i].Size > 0) imgdirs.toplamaktif++;

		}

		imgdirs.exportdir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
		imgdirs.importdir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
		imgdirs.delayimportdir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT];
		imgdirs.boundimportdir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT];
		imgdirs.iatdir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT];
		imgdirs.resdir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE];



		imgdirs.architecture = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE];



		imgdirs.exceptiondir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION];
		imgdirs.debug = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG];

		imgdirs.tlsdir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS];
		imgdirs.globalptrdir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR];
		imgdirs.basereloc = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
		imgdirs.loadconfigdir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG];
		imgdirs.comdescriptordir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR];


		imgdirs.securitydir = opthdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY];




	}




	bool peoku()
	{

		dosheader = (PIMAGE_DOS_HEADER)baseaddr;

		// check validity of the data
		if (dosheader->e_magic == IMAGE_DOS_SIGNATURE)
		{
			int opthdroffset = dosheader->e_lfanew;
			opthdr = (PIMAGE_NT_HEADERS32)(baseaddr + opthdroffset);

			if (opthdr->Signature == IMAGE_NT_SIGNATURE) // PE / PE32 signature check
			{

				veriTasi(&fileheader, &opthdr->FileHeader, sizeof(IMAGE_FILE_HEADER));
				veriTasi(&peheader, &opthdr->OptionalHeader, sizeof(IMAGE_OPTIONAL_HEADER32));

				sectionsayisi = opthdr->FileHeader.NumberOfSections;
				int offsetsectiontable = opthdroffset + sizeof(IMAGE_NT_HEADERS32);
				int sectiontabloboyut = sectionsayisi * sizeof(IMAGE_SECTION_HEADER);

				// base address  + opt header + sectiontablesize = PE header size  
				peboyutu = opthdroffset + sizeof(IMAGE_NT_HEADERS32) + sectiontabloboyut;
				// look for dis later IMAGE_ROM_HEADERS && IMAGE_ROM_OPTIONAL_HEADERS

				// !!! LOAD IMPORT IMGDIRS !!!!
				loadentries();

				PIMAGE_SECTION_HEADER psection = (PIMAGE_SECTION_HEADER)(baseaddr + offsetsectiontable);

				// section bilgilerini yukle
				for (int i = 0; i < sectionsayisi; i++)
				{
					IMAGE_SECTION_HEADER sect = (IMAGE_SECTION_HEADER)(*psection);

					int sectionozellikleri = sect.Characteristics;



					allsections.push_back(sect);

					ozellikparser ozellikler = sect.Characteristics;

					Metin sectionadi = (char*)sect.Name;


					// executable olan sectionlari ekle eger codesectioniysa codesectiona ata
					if (ozellikler.iscode || ozellikler.executable)
					{
						executablesections.push_back(sect);

						if (ozellikler.iscode) codesection = sect;
						ptrrawcode = baseaddr + sect.PointerToRawData;

					}
					// importtable & importsection ekle
					else if (sect.VirtualAddress == imgdirs.importdir.VirtualAddress)
					{

						importsection = sect;
					}
					// resource section
					else if (sect.VirtualAddress == imgdirs.resdir.VirtualAddress)
					{
						resourcesection = sect;


					}
					else if (sectionadi == ".data")
					{
						datasection = sect;
						ptrrawdata = baseaddr + sect.PointerToRawData;
					}
					// eger onemli bir veya tanimli olmayan bir data sectioni degilse datasections listesine ekle
					else if (ozellikler.readable || ozellikler.initializedata || ozellikler.uniniteddata)
					{
						datasections.push_back(sect);

					}




					psection++;

				}


				return true;
			}

			return false;
		}

		return false;

	}




	bool exporttableoku()
	{

		PIMAGE_EXPORT_DIRECTORY pexpdir;


		// if export dir exists.
		if (imgdirs.exportdir.VirtualAddress != 0)
		{

			int rva = imgdirs.exportdir.VirtualAddress;
			PIMAGE_SECTION_HEADER exportsection = getSectionFromRVA(rva);
			if (exportsection == 0) return false; // export section cant b found


			int offexport = imgdirs.exportdir.VirtualAddress - exportsection->VirtualAddress;

			char* ptrexport = baseaddr + exportsection->PointerToRawData + offexport;
			pexpdir = (PIMAGE_EXPORT_DIRECTORY)ptrexport;

			int offsetfuncs = pexpdir->AddressOfFunctions - rva;
			int offsetnames = pexpdir->AddressOfNames - rva;
			int offsetordinals = pexpdir->AddressOfNameOrdinals - rva;


			char* ptrfuncs = ptrexport + offsetfuncs;
			char* ptrNames = ptrexport + offsetnames;
			char* ptrOrdinals = ptrexport + offsetordinals;

			// !! IMPORTANT !! Load known functions with names
			int nfuncnames = pexpdir->NumberOfNames;
			int nfuncs = pexpdir->NumberOfFunctions;

			int ordinalBase = pexpdir->Base; // starting ordinal for exports in module 




											 // ptr to function rva table
			int* pfuncrva = (int*)ptrfuncs;

			// ptr to function name rva table
			int* pnamerva = (int*)ptrNames;

			WORD* pordinaltable = (WORD*)ptrOrdinals;

			char* ptrtoname = (char*)pnamerva;



			vector<exported_name> fnames;

			vector<exportedfunc> funcs;


			for (int i = 0; i < nfuncs; i++)
			{

				exportedfunc fnc;

				fnc.funcRVA = *(pfuncrva + i);
				fnc.Ordinal = ordinalBase + i;
				funcs.push_back(fnc);
			}


			for (int i = 0; i < nfuncnames; i++)
			{
				exported_name fname;


				fname.rva = *(pnamerva + i);
				fname.ordinal = *(pordinaltable + i); // name ordinal refers to index of function rva

				if (fname.ordinal > funcs.size())
					return false; // fatal error func name index is bigger than function list!

				int offs = fname.rva - rva;
				char* ptrname = ptrexport + offs;

				// set the name of function that name refers to
				exportedfunc* pfnc = &funcs[fname.ordinal];
				pfnc->funcname = ptrname;
				pfnc->nameRVA = fname.rva;
				pfnc->NameOrdinal = i; // index of name rva


			}



			return true;
		}




		return false;
	}

	bool importtableoku()
	{


		if (imgdirs.importdir.VirtualAddress == 0) return false; // import dir doesnt exist or we couldnt find it


		PIMAGE_SECTION_HEADER pimportsection = getSectionFromRVA(imgdirs.importdir.VirtualAddress);

		int rva = pimportsection->VirtualAddress;
		char* psectionbase = (char*)baseaddr + pimportsection->PointerToRawData;



		PIMAGE_IMPORT_DESCRIPTOR pimpdesc;


		int offimport = imgdirs.importdir.VirtualAddress - rva;

		int boyut = imgdirs.importdir.Size;


		int descadet = boyut / 4;  // real import count = importdirsize / 4 / 2 because it also holds name rvas
		descadet /= 2;


		pimpdesc = (PIMAGE_IMPORT_DESCRIPTOR)((PIMAGE_IMPORT_DESCRIPTOR)(psectionbase + offimport));





		do
		{

			char* dllname = psectionbase + (pimpdesc->Name - rva);
			imported_dll dll;
			dll.dllname = dllname;


			int* pnameoffsets = (int*)(psectionbase + (pimpdesc->OriginalFirstThunk - rva));
			int* pfuncaddroffsets = (int*)(psectionbase + (pimpdesc->FirstThunk - rva));





			do {

				imported_func fnc;
				int nameoffset = (*pnameoffsets - rva);
				int funcoffset = (*pfuncaddroffsets - rva);

				char* str = psectionbase + nameoffset;
				int realaddr = (*pfuncaddroffsets);


				PIMAGE_IMPORT_BY_NAME pimpfunc = (PIMAGE_IMPORT_BY_NAME)str;



				fnc.funcname = pimpfunc->Name;
				fnc.hint = pimpfunc->Hint;
				fnc.funcRVA = realaddr;
				fnc.offset = funcoffset;


				dll.importedfuncs.push_back(fnc);

				pnameoffsets++;
				pfuncaddroffsets++;

			} while (*pnameoffsets != 0);


			importeddlls.push_back(dll);
			pimpdesc++;
		} while (pimpdesc->FirstThunk != 0);



		return true;

	}


};




#endif