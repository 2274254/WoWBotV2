#pragma once
#include "../Agony/Game.h"
#include "WndEventArgs.h"
#include "Macros.h"
#include "CGLocalPlayer.h"

//using namespace Agony::Native;

namespace Agony
{
	MAKE_EVENT_GLOBAL(GameWndProc, WndEventArgs^ args);
	MAKE_EVENT_GLOBAL(GamePreTick, EventArgs^ args);
	MAKE_EVENT_GLOBAL(GameTick, EventArgs^ args);
	MAKE_EVENT_GLOBAL(GamePostTick, EventArgs^ args);

	public ref class Game
	{
	internal:
		MAKE_EVENT_INTERNAL_PROCESS(GameWndProc, (HWND, UINT, WPARAM, LPARAM));
		MAKE_EVENT_INTERNAL(GamePreTick, ());
		MAKE_EVENT_INTERNAL(GameTick, ());
		MAKE_EVENT_INTERNAL(GamePostTick, ());
	public:
		static Game::Game();
		MAKE_EVENT_PUBLIC(OnWndProc, GameWndProc);
		MAKE_EVENT_PUBLIC(OnPreTick, GamePreTick);
		MAKE_EVENT_PUBLIC(OnTick, GameTick);
		MAKE_EVENT_PUBLIC(OnPostTick, GamePostTick);

		static void DomainUnloadEventHandler(Object^, EventArgs^);

		static property int InstanceCount
		{
			int get()
			{
				return Native::Game::GetInstance()->InstanceCount;
			}
		}

		static property Int64 FrameTimeMS
		{
			Int64 get()
			{
				return Native::Game::GetFrameMS();
			}
		}

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
				const char* gameVersion = Native::Game::GetGameVersion();
				if (gameVersion != nullptr)
				{
					return gcnew System::String(Native::Game::GetGameVersion());
				}
				return "Unknown";
			}
		}

		static property CGLocalPlayer^ Me
		{
			CGLocalPlayer^ get();
		}

	};
}