#pragma once
#include "Macros.h"
#include "CGLocalPlayer.h"
#include "EventHandler.h"
#include "BuildInfo.h"
#include "LuaEvents.h"

namespace Agony
{
	namespace Native
	{
		typedef bool(OnWndProc)(HWND, UINT, WPARAM, LPARAM);

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
			EventHandler<OnWndProc, HWND, UINT, WPARAM, LPARAM> GameWndProc = EventHandler<OnWndProc, HWND, UINT, WPARAM, LPARAM>();
			EventHandler<void()> OnPreTick = EventHandler<void()>();
			EventHandler<void()> OnTick = EventHandler<void()>();
			EventHandler<void()> OnPostTick = EventHandler<void()>();

			//Lua Events
			LuaEvents::C_AchievementInfo AchievementInfoEvents = LuaEvents::C_AchievementInfo();
			LuaEvents::C_GossipInfo GossipInfoEvents = LuaEvents::C_GossipInfo();

			//
			bool ApplyHooks(void*);
			void ClearHooks(void* mainWindowHandle);
		};
	}
}