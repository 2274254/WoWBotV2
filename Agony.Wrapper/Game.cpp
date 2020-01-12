#include "Game.h"
#include "../Agony/EventHandler.h"

using namespace System::Collections::Generic;

namespace Agony
{
	static Game::Game()
	{
		ATTACH_DOMAIN();

		//ATTACH_EVENT(GameWndProc, 1, Native::OnWndProc, HWND, UINT, WPARAM, LPARAM);

		GameWndProcHandlers = gcnew List<GameWndProc^>();
		m_GameWndProcNativeDelegate = gcnew OnGameWndProcNativeDelegate(OnGameWndProcNative);
		m_GameWndProcNative = Marshal::GetFunctionPointerForDelegate(m_GameWndProcNativeDelegate);
		Agony::Native::EventHandler<1, Agony::Native::OnWndProc, HWND, UINT, WPARAM, LPARAM>::GetInstance()->Add(m_GameWndProcNative.ToPointer());

		printf("WE ATTACHED\n");
	}

	void Game::DomainUnloadEventHandler(Object^, System::EventArgs^)
	{
		DETACH_EVENT(GameWndProc, 1, Native::OnWndProc, HWND, UINT, WPARAM, LPARAM);
		printf("DOMAIN UNLOADED!?!?!?!\n");
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
}