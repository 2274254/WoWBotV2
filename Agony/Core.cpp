#include "Core.h"
#include "Game.h"
#include "Console.h"
//#include "VMProtect/VMProtectSDK.h"
#include "EventHandler.h"
#include "Bootstrapper.h"
#include "D3dxHook.h"
#include <ctime>

namespace Agony
{
	namespace Native
	{
		uintptr_t Core::MainModule = 0;
		void* Core::MainWindowHandle = nullptr;
		void BootstrapAddons();

		bool Core::ApplyHooks() const
		{
			if (Agony::Native::Game::GetInstance()->ApplyHooks(Core::MainWindowHandle))
			{
				if (D3dxHook::ApplyHooks())
				{
					return true;
				}
				else
				{
					Agony::Native::Game::GetInstance()->ClearHooks(Core::MainWindowHandle);
				}
			}
			//VERIFY_HOOK(D3dxHook::ApplyHooks, "D3DXHook");
			return false;
		}

		Core::Core(HMODULE h_module)
		{
			//VMProtectBeginUltra(__FUNCTION__);
			this->hModule = h_module;
			//VMProtectEnd();
		}

		Core::~Core()
		{
		}

		bool Core::Initialize()
		{
			//VMProtectBeginUltra(__FUNCTION__);
			srand(time(nullptr));
			Console::PrintLn("Agony (%s - %s %s) loading... ", Game::GetGameVersion(), __TIME__, __DATE__);

			if (!this->ApplyHooks())
			{
				Console::PrintLn("3123911");
				return false;
			}
			else
			{
				this->CreateThreadBootstrapAddons();
				this->DisplayWelcomeMessage();
			}
			//VMProtectEnd();
			return true;
		}

		void Core::ClearHooks()
		{
			Agony::Native::Game::GetInstance()->ClearHooks(Core::MainWindowHandle);			
		}

		void Core::CreateThreadBootstrapAddons() const
		{
			CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(BootstrapAddons), nullptr, NULL, nullptr);
		}

		void Core::DisplayWelcomeMessage() const
		{
			EventHandler<1, OnWndProc, HWND, UINT, WPARAM, LPARAM>::GetInstance()->Add(nullptr);
			EventHandler<1, OnWndProc, HWND, UINT, WPARAM, LPARAM>::GetInstance()->Remove(nullptr);

			EventHandler<2, OnGamePreTick>::GetInstance()->Add(nullptr);
			EventHandler<2, OnGamePreTick>::GetInstance()->Remove(nullptr);

			EventHandler<3, OnGameTick>::GetInstance()->Add(nullptr);
			EventHandler<3, OnGameTick>::GetInstance()->Remove(nullptr);

			EventHandler<4, OnGamePostTick>::GetInstance()->Add(nullptr);
			EventHandler<4, OnGamePostTick>::GetInstance()->Remove(nullptr);
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
				Console::PrintLn("Bootstrap loaded.");
				Sleep(150u);
				/*if (ClientFacade::GetInstance()->GetGameState() == static_cast<uintptr_t>(GameMode::Running))
					EventHandler<3, OnGameStart>::GetInstance()->Trigger();

				if (ClientFacade::GetInstance()->GetGameState() == static_cast<uintptr_t>(GameMode::Connecting))
					EventHandler<26, OnGameLoad>::GetInstance()->Trigger();
				*/
			}
		}
	}
}