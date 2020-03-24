#pragma once
#include "Macros.h"
#include "WoWObject.h"

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
			static WoWObject* Me();
			bool ApplyHooks(void*);
			void ClearHooks(void* mainWindowHandle);
		};
	}
}