#pragma once
#include "Macros.h"

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT Game
		{
		public:
			static Game* GetInstance();
			static bool IsInGame();
			static char* GetGameVersion();
			bool ApplyHooks(void*);
		};
	}
}