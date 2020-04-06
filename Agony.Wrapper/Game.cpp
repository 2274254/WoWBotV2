#include "Game.h"
#include "../Agony/EventHandler.h"

using namespace System::Collections::Generic;

namespace Agony
{
	static Game::Game()
	{
		ATTACH_DOMAIN();

		System::Console::WriteLine("Binding Game Event: GameWndProc");
		ATTACH_EVENT(GameWndProc, Agony::Native::Game::Game::GetInstance()->GameWndProc,  Native::OnWndProc, HWND, UINT, WPARAM, LPARAM);
		
		System::Console::WriteLine("Binding Game Event: GamePreTick");
		ATTACH_EVENT(GamePreTick, Agony::Native::Game::Game::GetInstance()->OnPreTick, Native::OnGamePreTick);

		System::Console::WriteLine("Binding Game Event: GameTick");
		ATTACH_EVENT(GameTick, Agony::Native::Game::Game::GetInstance()->OnTick, Native::OnGameTick);

		System::Console::WriteLine("Binding Game Event: GamePostTick");
		ATTACH_EVENT(GamePostTick, Agony::Native::Game::Game::GetInstance()->OnPostTick, Native::OnGamePostTick);
	}

	void Game::DomainUnloadEventHandler(Object^, System::EventArgs^)
	{
		DETACH_EVENT(GameWndProc, Agony::Native::Game::Game::GetInstance()->GameWndProc, Native::OnWndProc, HWND, UINT, WPARAM, LPARAM);
		DETACH_EVENT(GamePreTick, Agony::Native::Game::Game::GetInstance()->OnPreTick, Native::OnGamePreTick);
		DETACH_EVENT(GameTick, Agony::Native::Game::Game::GetInstance()->OnTick, Native::OnGameTick);
		DETACH_EVENT(GamePostTick, Agony::Native::Game::Game::GetInstance()->OnPostTick, Native::OnGamePostTick);
		System::Console::WriteLine("Domain Unloaded");
	}

	bool Game::OnGameWndProcNative(HWND HWnd, UINT message, WPARAM WParam, LPARAM LParam)
	{
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

	SharpDX::Vector3 Game::CorpseLocation::get()
	{
		auto corpseLocation = Native::Game::GetCorpseLocation();
		return SharpDX::Vector3(corpseLocation.x, corpseLocation.y, corpseLocation.z);
	}
}