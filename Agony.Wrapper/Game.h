#pragma once
#include "../Agony/Game.h"
using namespace Agony::Native;
using namespace System;
using namespace System::Text;

namespace Agony
{
	public ref class Game
	{
	public:
		static property bool IsInGame
		{
			bool get()
			{
				return Native::Game::IsInGame();
			}
		}

		static property String^ GameVersion
		{
			String^ get()
			{
				char* gameVersion = Native::Game::GetGameVersion();
				if (gameVersion != nullptr)
				{
					return gcnew System::String(Native::Game::GetGameVersion());
				}
				return "Unknown";
			}
		}
	};
}