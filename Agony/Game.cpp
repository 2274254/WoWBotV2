#include "Game.h"
#include "Offsets.h"
#include "Macros.h"
#include "EventHandler.h"
#include "Bootstrapper.h"
#include "LuaFunctions.h"
#include "ObjectManager.h"
#include <iostream>

#pragma comment(lib, "User32.lib")

namespace Agony
{
	namespace Native
	{
		BuildInfo Game::BuildInfos = BuildInfo();
		Game* Game::GetInstance()
		{
			static auto inst = new Game();
			return inst;
		}

		WNDPROC m_wndProc;
		LRESULT WINAPI hkWndProc(HWND hwnd, UINT msg, WPARAM WParam, LPARAM LParam)
		{
			//printf("ON MESSAGE\n");
			auto process = Game::GetInstance()->GameWndProc.TriggerProcess(hwnd, msg, WParam, LParam);
			LRESULT returnValue;
			if (msg == WM_KEYUP)
			{
				/*if (WParam == VK_F5)
				{
					Bootstrapper::GetInstance()->Trigger(BootstrapEventType::Load);
				}*/
				if (WParam == VK_F8)
				{
					auto something = reinterpret_cast<uintptr_t**>(Offsets::Base + 0x27B3E80);
					//auto v10 = *(_OWORD*)(**off_27B3E80)[4]();

					reinterpret_cast<uintptr_t* (__fastcall * (**)[31])())()(something)
					((void(__fastcall*)(uintptr_t * (__fastcall * (**)[31])()))(**something)[4])(something);
					reinterpret_cast<uintptr_t* (__fastcall*)(uintptr_t**)[31]>(**something)[4](something);

					auto something2 = (uintptr_t*)(**something);
					auto something3 = something2[4];
					std::cout << "Something 3 = " << std::hex << (something3 - Offsets::Base) << std::endl;

					//v10 = *(int **)(*(_QWORD *)((char *)&dword_2A88F00 + v9 + 8) + 8 * localSpellIndex);
					auto spell = *(int**)(*(uintptr_t*)(Offsets::Base + 0x2A88F00 + 8) + 8 * 1);
					
					std::cout << "Spell id 1 = " << std::dec << spell[1] << std::endl;
					std::cout << "Spell id 2 = " << std::dec << spell[2] << std::endl;
					std::cout << "Spell id 3 = " << std::dec << spell[3] << std::endl;
					std::cout << "Spell id 4 = " << std::dec << spell[4] << std::endl;
					std::cout << "Spell id 5 = " << std::dec << spell[5] << std::endl;
					std::cout << "Spell id 6 = " << std::dec << spell[6] << std::endl;
					std::cout << "Spell id 7 = " << std::dec << spell[7] << std::endl;

					//auto spellOverride = reinterpret_cast<uintptr_t*(__fastcall*)(int32_t, uint32_t, int32_t)>(Offsets::Base + 0x11DEBE0)(262838, 0, 1);

					//uintptr_t result = 0;
					//reinterpret_cast<uintptr_t(__fastcall*)(uintptr_t*, uintptr_t*, int32_t, int32_t)>(Offsets::Base + 0xB83FC0)(spellOverride, &result, 0, 0);
				}
			}

			if (!process)
			{
				//m_blockInput = true;
				//m_lastInputBlock = GetTickCount();
			}
			else
			{
				/*if (GetTickCount() - m_lastInputBlock > 1000)
				{
					m_blockInput = false;
				}*/

				return CallWindowProc(m_wndProc, hwnd, msg, WParam, LParam);
			}
			return 1;
		}

		bool Game::IsInGame()
		{
			//return true;
			//IS_NULL_RETN(Offsets::Base, static_cast<unsigned __int16>(Offsets::InGame), false);
			const unsigned __int16 gameState = *reinterpret_cast<unsigned __int16*>(Offsets::Base + Offsets::InGame);
			return ((gameState >> 4) & 1);
		}

		const char* Game::GetGameVersion()
		{
			return BuildInfos.ToString().c_str();
			//auto returnValues = LuaFunctions::Call("GetBuildInfo", { 2, 2, 2, 1 }, NULL);
			//return (std::string(std::any_cast<const char*>(returnValues[0])) + std::string(std::any_cast<const char*>(returnValues[1]))).c_str();
		}

		uint64_t Game::GetFrameMS()
		{
			return reinterpret_cast<uint64_t(__fastcall*)()>(Offsets::Base + Offsets::FrameTime__GetCurTimeMs)();
		}

		CGLocalPlayer* Game::Me()
		{
			//const CGObjectManager* m_CurObjectMgr = *reinterpret_cast<CGObjectManager**>(Offsets::Base + Offsets::ObjectMgr);
			//ObjectGuid guid = m_CurObjectMgr->LocalGuid;
			//return (CGLocalPlayer*)ObjectManager::GetObjectFromGuid(&guid);
			return reinterpret_cast<CGLocalPlayer * (__fastcall*)(const char*)>(Offsets::Base + Offsets::GetBaseFromToken)("player");
		}

		Vector3 Game::GetCorpseLocation()
		{
			auto corpseBase = reinterpret_cast<CorpseBase*>(Offsets::Base + Offsets::CorpseBase);
			if (corpseBase != nullptr)
			{
				return corpseBase->pos;
			}
			return Vector3();
		}

		bool Game::ApplyHooks(void* mainWindowHandle)
		{
			m_wndProc = (WNDPROC)SetWindowLongPtr((HWND)mainWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hkWndProc));
			return true;
		}

		void Game::ClearHooks(void* mainWindowHandle)
		{
			SetWindowLongPtr((HWND)mainWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_wndProc));
		}
	}
}
