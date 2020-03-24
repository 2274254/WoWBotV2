#include "Core.h"
#include "Game.h"
#include "Console.h"
#include "VMProtect/VMProtectSDK.h"
#include "EventHandler.h"
#include "Bootstrapper.h"
#include "D3dxHook.h"
#include <ctime>

namespace Agony
{
	namespace Native
	{
		int Core::MainModule = 0;
		void* Core::MainWindowHandle = nullptr;
		void BootstrapAddons();

		bool Core::ApplyHooks() const
		{
			Agony::Native::Game::GetInstance()->ApplyHooks(Core::MainWindowHandle);
			VERIFY_HOOK(D3dxHook::ApplyHooks, "D3DXHook");
			return true;
		}

		Core::Core(HMODULE h_module)
		{
			VMProtectBeginUltra(__FUNCTION__);

			this->hModule = h_module;

			srand(time(nullptr));

			Console::PrintLn("Agony (%s - %s %s) loading... ", Game::GetGameVersion(), __TIME__, __DATE__);

			if (!this->ApplyHooks())
			{
				Console::PrintLn("3123911");
			}
			else
			{
				//this->CreateThreadBootstrapAddons();
				//this->DisplayWelcomeMessage();
			}

			VMProtectEnd();
		}

		Core::~Core()
		{
		}

		void Core::CreateThreadBootstrapAddons() const
		{
			CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(BootstrapAddons), nullptr, NULL, nullptr);
		}

		void Core::DisplayWelcomeMessage() const
		{
			EventHandler<1, OnWndProc, HWND, UINT, WPARAM, LPARAM>::GetInstance()->Add(nullptr);
			EventHandler<1, OnWndProc, HWND, UINT, WPARAM, LPARAM>::GetInstance()->Remove(nullptr);
		}

		HMODULE Core::get_hModule() const
		{
			return this->hModule;
		}

		void Core::set_hModule(HMODULE h)
		{
			this->hModule = h;
		}

		void BootstrapAddons()
		{
			if (!Bootstrapper::GetInstance()->Initialize())
			{
				Console::PrintLn("[!] Failed to launch .NET addons in a safe environment.");
			}
			else
			{
				Sleep(150u);
				/*if (ClientFacade::GetInstance()->GetGameState() == static_cast<int>(GameMode::Running))
					EventHandler<3, OnGameStart>::GetInstance()->Trigger();

				if (ClientFacade::GetInstance()->GetGameState() == static_cast<int>(GameMode::Connecting))
					EventHandler<26, OnGameLoad>::GetInstance()->Trigger();
				*/
			}
		}
	}
}