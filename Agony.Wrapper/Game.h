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
		static property String^ GameVersion
		{
			String^ get()
			{
				return gcnew System::String(Native::Game::GetGameVersion().c_str());
			}
		}
	};
}