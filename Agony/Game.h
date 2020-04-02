#pragma once
#include "Macros.h"
#include "CGLocalPlayer.h"
#include "EventHandler.h"
#include "BuildInfo.h"

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT Game
		{
			static BuildInfo BuildInfos;
		public:
			int InstanceCount = 0;
			static Game* GetInstance();
			static bool IsInGame();
			static const char* GetGameVersion();
			static uint64_t GetFrameMS();
			static CGLocalPlayer* Me();
			static Vector3 GetCorpseLocation();
			EventHandler<2, void()> OnPreTick = EventHandler<2, void()>();
			EventHandler<3, void()> OnTick = EventHandler<3, void()>();
			EventHandler<4, void()> OnPostTick = EventHandler<4, void()>();
			bool ApplyHooks(void*);
			void ClearHooks(void* mainWindowHandle);
		};
	}
}