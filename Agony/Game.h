#pragma once
#include "Macros.h"
#include "CGLocalPlayer.h"
#include "EventHandler.h"

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT Game
		{
		public:
			int InstanceCount = 0;
			static Game* GetInstance();
			static bool IsInGame();
			static char* GetGameVersion();
			static CGLocalPlayer* Me();
			EventHandler<2, void()> OnPreTick = EventHandler<2, void()>();
			EventHandler<3, void()> OnTick = EventHandler<3, void()>();
			EventHandler<4, void()> OnPostTick = EventHandler<4, void()>();
			bool ApplyHooks(void*);
			void ClearHooks(void* mainWindowHandle);
		};
	}
}