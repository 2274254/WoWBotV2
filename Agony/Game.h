#pragma once
#include "Macros.h"
#include "CGLocalPlayer.h"
#include "EventHandler.h"
#include "BuildInfo.h"
#include <any>

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
			EventHandler<void()> EnterInGame = EventHandler<void()>();
			EventHandler<void()> ExitInGame = EventHandler<void()>();
			EventHandler<void(std::string, std::vector<std::any>), std::string, std::vector<std::any>> OnLuaEvent = EventHandler<void(std::string, std::vector<std::any>), std::string, std::vector<std::any>>();

			bool ApplyHooks(void*);
			void ClearHooks(void* mainWindowHandle);
		};
	}
}