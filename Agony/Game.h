#pragma once
#include "Macros.h"
#include <string>

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT Game
		{
		public:
			static bool IsInGame();
			static char* GetGameVersion();
		};
	}
}