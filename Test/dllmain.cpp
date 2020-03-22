// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>

DWORD __stdcall Initialize(LPVOID param)
{
    AllocConsole();
    FILE* f1;
    FILE* f2;
    FILE* f3;
    freopen_s(&f1, "CONOUT$", "wb", stdout);
    freopen_s(&f2, "CONOUT$", "wb", stderr);
    freopen_s(&f3, "CONIN$", "rb", stdin);

    std::cout << "It works!" << std::endl;

    while (1 & !GetAsyncKeyState(VK_F4))
        Sleep(1);

    const auto conHandle = GetConsoleWindow();
    FreeConsole();
    PostMessage(conHandle, WM_CLOSE, 0, 0);
    FreeLibraryAndExitThread(static_cast<HMODULE>(param), NULL);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Initialize), nullptr, NULL, nullptr);
        }
        break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

