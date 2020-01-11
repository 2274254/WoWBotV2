#pragma once
#include "stdafx.h"
#include "Startup.h"
#include <string>

typedef void(*DllFunc)();
//
HINSTANCE Startup::SharedLibrary = NULL;

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

DWORD Startup::Start()
{
	try
	{
		WCHAR DllPath[MAX_PATH] = { 0 };
		GetModuleFileNameW((HINSTANCE)&__ImageBase, DllPath, _countof(DllPath));
		std::wstring ws(DllPath);
		std::string pathAndFile(ws.begin(), ws.end());
		char* c = const_cast<char*>(pathAndFile.c_str());
		int strLength = strlen(c);
		int lastOccur = 0;
		for (int i = 0; i < strLength; i++)
		{
			if (c[i] == '\\') lastOccur = i;
		}
		std::string pathDoDll = pathAndFile.substr(0, lastOccur + 1);
		pathDoDll = pathDoDll.append("Sandbox.dll");

		SharedLibrary = LoadLibrary(pathDoDll.c_str());

		if (SharedLibrary == NULL)
		{
			std::cout << "Sandbox is missing (" << pathDoDll.c_str() << ")" << std::endl;
		}
		else
		{
			DllFunc bootsrap = (DllFunc)GetProcAddress(SharedLibrary, "Bootstrap");
			bootsrap();
		}
		FreeLibrary(SharedLibrary);
	}
	catch (const std::exception &exc)
	{
		// catch anything thrown within try block that derives from std::exception
		std::cerr << exc.what();
	}

	return 0;
}