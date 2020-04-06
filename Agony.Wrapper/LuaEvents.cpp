#include "LuaEvents.h"

static Agony::WoWInternals::LuaEvents::LuaEvents()
{
	ATTACH_DOMAIN();
	System::Console::WriteLine("Binding Game Event:OnLuaEvent");
	ATTACH_EVENT(LuaEvent, Agony::Native::Game::Game::GetInstance()->OnLuaEvent, void(std::string, std::vector<std::any>));
}

void Agony::WoWInternals::LuaEvents::DomainUnloadEventHandler(System::Object^, System::EventArgs^)
{
	DETACH_EVENT(LuaEvent, Agony::Native::Game::Game::GetInstance()->OnLuaEvent, void(std::string, std::vector<std::any>));
}

void Agony::WoWInternals::LuaEvents::AttachEvent(System::String^ eventName, LuaEventHandlerDelegate^ handler)
{
	if (!RegisteredEvents->ContainsKey(eventName))
	{
		RegisteredEvents->Add(eventName, gcnew System::Collections::Generic::List<LuaEventHandlerDelegate^>);
		//TODO: Call unmanaged RegisterEvent
	}
	RegisteredEvents[eventName]->Add(handler);
}

void Agony::WoWInternals::LuaEvents::DetachEvent(System::String^ eventName, LuaEventHandlerDelegate^ handler)
{
	RegisteredEvents[eventName]->Remove(handler);
	if (RegisteredEvents[eventName]->Count == 0)
	{
		//TODO: Call unmanaged UnregisterEvent
	}
}

void Agony::WoWInternals::LuaEvents::OnLuaEventNative(std::string eventName, std::vector<std::any> results)
{
	START_TRACE
		auto eventNameManaged = gcnew System::String(eventName.c_str());
		if (Agony::WoWInternals::LuaEvents::RegisteredEvents->ContainsKey(eventNameManaged))
		{
			array<System::Object^>^ args = gcnew array<System::Object^>(results.size());
			int i = 0;
			for (auto arg : results)
			{
				if (arg.type() == typeid(std::string))
				{
					args[i] = gcnew System::String(std::any_cast<std::string>(arg).c_str());
				}
				else if (arg.type() == typeid(double))
				{
					args[i] = gcnew System::Double(std::any_cast<double>(arg));
				}
				else if (arg.type() == typeid(int))
				{
					args[i] = gcnew System::Int32(std::any_cast<int>(arg));
				}
				else if (arg.type() == typeid(bool))
				{
					args[i] = gcnew System::Boolean(std::any_cast<bool>(arg));
				}
				i++;
			}
			auto eventArgs = gcnew Agony::WoWInternals::LuaEventArgs(eventNameManaged, 0, args);
			for each (auto eventHandle in Agony::WoWInternals::LuaEvents::RegisteredEvents[eventArgs->EventName]->ToArray())
			{
				START_TRACE
					eventHandle(gcnew System::Object(), eventArgs);
				END_TRACE
			}
		}
	END_TRACE
}