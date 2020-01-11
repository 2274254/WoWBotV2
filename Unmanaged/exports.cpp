#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Injector.h"

#define INJECTION_API extern "C" __declspec(dllexport)

INJECTION_API bool Inject(int procId, const LPCWSTR dllPath)
{
	Injector injector = Injector("League of Legends.exe", false, false);
	injector.SetProcessInformation(procId);
	injector.SetManualMap(true);
	
	std::string path;	
	size_t origsize = wcslen(dllPath) + 1;
	size_t convertedChars = 0;
	char gszFile[100] = { 0 };
	wcstombs_s(&convertedChars, gszFile, origsize, dllPath, _TRUNCATE); //from wchar_t to char*
	path = (std::string) gszFile;
	
	return injector.ManualMap(path) == 0;
}