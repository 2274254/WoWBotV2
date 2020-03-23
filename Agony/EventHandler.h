#pragma once
#include "Macros.h"
#include <vector>
#include <Windows.h>

namespace Agony
{
	namespace Native
	{
		//Game
		typedef bool(OnWndProc)(HWND, UINT, WPARAM, LPARAM);
		#define EVENT_TIMEOUT_EJECT 250

		// ReSharper disable once CppClassNeedsConstructorBecauseOfUninitializedMember
		template <int uniqueEventNumber, typename T, typename ... TArgs>
		class DLLEXPORT EventHandler
		{
			std::vector<void*> m_EventCallbacks;
			DWORD t_RemovalTickCount;
			static EventHandler* instance;
		public:
			static EventHandler* GetInstance()
			{
				if (instance == nullptr)
				{
					instance = new EventHandler();
				}
				return instance;
			}

			void Add(void* callback)
			{
				if (callback != nullptr)
				{
					printf("ADDED CALLBACK\n");
					m_EventCallbacks.push_back(callback);
				}
				else
				{
					printf("CALLBACK WAS NULLPTR\n");
				}
			}

			void Remove(void* listener)
			{
				printf("CALLBACK REMOVED\n");
				if (listener == nullptr)
				{
					return;
				}

				auto eventPtr = find(m_EventCallbacks.begin(), m_EventCallbacks.end(), listener);
				if (eventPtr != m_EventCallbacks.end())
				{
					m_EventCallbacks.erase(find(m_EventCallbacks.begin(), m_EventCallbacks.end(), listener));
				}

				this->t_RemovalTickCount = GetTickCount();
			}

			bool __cdecl TriggerProcess(TArgs... args)
			{
				auto process = true;
				auto tickCount = GetTickCount();
				//printf("WE ARE HERE1\n");
				for (auto ptr : m_EventCallbacks)
				{
					printf("WE ARE HERE2\n");
					if (ptr != nullptr)
					{
						printf("WE ARE HERE3\n");
						if (tickCount - t_RemovalTickCount > EVENT_TIMEOUT_EJECT)
						{
							printf("WE ARE HERE4\n");
							if (!static_cast<T*>(ptr) (args...))
							{
								process = false;
							}
						}
					}
				}

				return process;
			}

			bool __cdecl Trigger(TArgs... args)
			{
				auto tickCount = GetTickCount();

				for (auto ptr : m_EventCallbacks)
				{
					if (ptr != nullptr)
					{
						if (tickCount - t_RemovalTickCount > EVENT_TIMEOUT_EJECT)
						{
							static_cast<T*>(ptr) (args...);
						}
					}
				}

				return true;
			}
		};

		template <int uniqueEventNumber, typename T, typename ... TArgs>
		EventHandler<uniqueEventNumber, T, TArgs...>* EventHandler<uniqueEventNumber, T, TArgs...>::instance = nullptr;
	}
}