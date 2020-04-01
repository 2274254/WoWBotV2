#include "Game.h"
#include "../Agony/EventHandler.h"

using namespace System::Collections::Generic;

namespace Agony
{
	static Game::Game()
	{
		ATTACH_DOMAIN();

		System::Console::WriteLine("Binding Game Event: GameWndProc");
		ATTACH_EVENT(GameWndProc,	1, Native::OnWndProc, HWND, UINT, WPARAM, LPARAM);

		System::Console::WriteLine("Binding Game Event: GamePreTick");
		//ATTACH_EVENT(GamePreTick,	2, Native::OnGamePreTick);
		GamePreTickHandlers  = gcnew List<GamePreTick^>();
		m_GamePreTickNativeDelegate = gcnew OnGamePreTickNativeDelegate(OnGamePreTickNative);
		m_GamePreTickNative = Marshal::GetFunctionPointerForDelegate(m_GamePreTickNativeDelegate);
		Agony::Native::Game::Game::GetInstance()->OnPreTick.Add(m_GamePreTickNative.ToPointer());

		System::Console::WriteLine("Binding Game Event: GameTick");
		//ATTACH_EVENT(GameTick,		3, Native::OnGameTick);
		GameTickHandlers = gcnew List<GameTick^>();
		m_GameTickNativeDelegate = gcnew OnGameTickNativeDelegate(OnGameTickNative);
		m_GameTickNative = Marshal::GetFunctionPointerForDelegate(m_GameTickNativeDelegate);
		Agony::Native::Game::Game::GetInstance()->OnTick.Add(m_GameTickNative.ToPointer());

		System::Console::WriteLine("Binding Game Event: GamePostTick");
		//ATTACH_EVENT(GamePostTick,	4, Native::OnGamePostTick);
		GamePostTickHandlers = gcnew List<GamePostTick^>();
		m_GamePostTickNativeDelegate = gcnew OnGamePostTickNativeDelegate(OnGamePostTickNative);
		m_GamePostTickNative = Marshal::GetFunctionPointerForDelegate(m_GamePostTickNativeDelegate);
		Agony::Native::Game::Game::GetInstance()->OnPostTick.Add(m_GamePostTickNative.ToPointer());


		/*GameWndProcHandlers			= gcnew List<GameWndProc^>();
		m_GameWndProcNativeDelegate = gcnew OnGameWndProcNativeDelegate(OnGameWndProcNative);
		m_GameWndProcNative			= Marshal::GetFunctionPointerForDelegate(m_GameWndProcNativeDelegate);
		Native::EventHandler<1, Native::OnWndProc, HWND, UINT, WPARAM, LPARAM>::GetInstance()->Add(m_GameWndProcNative.ToPointer());
		*/
		System::Console::WriteLine("Called static Game: " + Native::Game::GetInstance()->InstanceCount);
	}

	void Game::DomainUnloadEventHandler(Object^, System::EventArgs^)
	{
		DETACH_EVENT(GameWndProc,	1, Native::OnWndProc, HWND, UINT, WPARAM, LPARAM);
		DETACH_EVENT(GamePreTick,	2, Native::OnGamePreTick);
		DETACH_EVENT(GameTick,		3, Native::OnGameTick);
		DETACH_EVENT(GamePostTick,	4, Native::OnGamePostTick);
		System::Console::WriteLine("Domain Unloaded");
	}

	bool Game::OnGameWndProcNative(HWND HWnd, UINT message, WPARAM WParam, LPARAM LParam)
	{
		printf("WE GOT WNDPROC in WRAPPER\n");
		bool process = true;

		START_TRACE
		auto args = gcnew WndEventArgs(HWnd, message, WParam, LParam);
		for each (auto eventHandle in GameWndProcHandlers->ToArray())
		{
			START_TRACE
			eventHandle(args);
			END_TRACE
		}

		if (!args->Process)
			process = false;
		END_TRACE

		return process;
	}

	void Game::OnGamePreTickNative()
	{
		printf("OnPreTick in WRAPPER\n");
		System::Console::WriteLine("OnPreTick in Wrapper");
		START_TRACE
			for each (auto eventHandle in GamePreTickHandlers->ToArray())
			{
				START_TRACE
					eventHandle(EventArgs::Empty);
				END_TRACE
			}
		END_TRACE
	}

	void Game::OnGameTickNative()
	{
		System::Console::WriteLine("RECEIVED ONTICK INSIDE WRAPPER");
		START_TRACE
			for each (auto eventHandle in GameTickHandlers->ToArray())
			{
				START_TRACE
					eventHandle(EventArgs::Empty);
				END_TRACE
			}
		END_TRACE
	}

	void Game::OnGamePostTickNative()
	{
		START_TRACE
			for each (auto eventHandle in GamePostTickHandlers->ToArray())
			{
				START_TRACE
					eventHandle(EventArgs::Empty);
				END_TRACE
			}
		END_TRACE
	}

	CGLocalPlayer^ Game::Me::get()
	{
		return gcnew CGLocalPlayer(Native::Game::Me());
	}
}