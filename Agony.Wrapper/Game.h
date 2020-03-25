#pragma once
#include "../Agony/Game.h"
#include "WndEventArgs.h"
#include "Macros.h"
#include "CGUnit.h"

//using namespace Agony::Native;

namespace Agony
{
	MAKE_EVENT_GLOBAL(GameWndProc, WndEventArgs^ args);

	public ref class Game
	{
	internal:
		MAKE_EVENT_INTERNAL_PROCESS(GameWndProc, (HWND, UINT, WPARAM, LPARAM));
	public:
		static Game::Game();
		MAKE_EVENT_PUBLIC(OnWndProc, GameWndProc);

		static void DomainUnloadEventHandler(Object^, EventArgs^);

		static property bool IsInGame
		{
			bool get()
			{
				return Native::Game::IsInGame();
			}
		}

		static property System::String^ GameVersion
		{
			System::String^ get()
			{
				char* gameVersion = Native::Game::GetGameVersion();
				if (gameVersion != nullptr)
				{
					return gcnew System::String(Native::Game::GetGameVersion());
				}
				return "Unknown";
			}
		}

		static property CGUnit^ Me
		{
			CGUnit^ get();
		}

	};
}