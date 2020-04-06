#pragma once
#include "Macros.h"
#include <vector>
#include <Windows.h>
#include <iostream>

namespace Agony
{
	namespace Native
	{
		//Game

		typedef void(OnGamePreTick)();
		typedef void(OnGameTick)();
		typedef void(OnGamePostTick)();

		#define EVENT_TIMEOUT_EJECT 250

		// ReSharper disable once CppClassNeedsConstructorBecauseOfUninitializedMember
		template <typename T, typename ... TArgs> class DLLEXPORT EventHandler
		{
			std::vector<void*> m_EventCallbacks;
			DWORD t_RemovalTickCount = 0;
		public:

			void Add(void* callback)
			{
				if (callback != nullptr)
				{
					m_EventCallbacks.push_back(callback);
					//std::cout << "Added callback " << std::hex << callback << " inside : " << std::hex << &m_EventCallbacks << std::endl;
				}
				else
				{
					//std::cout << "Cannot add nullptr callback" << std::endl;
				}
			}

			void Remove(void* listener)
			{
				if (listener == nullptr)
				{
					//std::cout << "Cannot remove nullptr callback" << std::endl;
					return;
				}
				//std::cout << "Removed callback " << std::hex << listener << std::endl;
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

				for (auto ptr : m_EventCallbacks)
				{
					if (ptr != nullptr)
					{
						if (tickCount - t_RemovalTickCount > EVENT_TIMEOUT_EJECT)
						{
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
				//auto tickCount = GetTickCount();
				for (auto ptr : m_EventCallbacks)
				{
					if (ptr != nullptr)
					{
						//std::cout << "Called event on " << std::hex << ptr << std::endl;
						//if (tickCount - t_RemovalTickCount > EVENT_TIMEOUT_EJECT)
						{
							static_cast<T*>(ptr) (args...);
						}
					}
					else
					{
						//std::cout << "Cannot nullptr event" << std::endl;
					}
				}
				return true;
			}
		};
	}
}