#include "CGObject.h"
#include "Console.h"

namespace Agony::Native
{
	WoWObjectType CGObject::GetType()
	{
		__try
		{
			if (this == nullptr) return WoWObjectType::Invalid;
			auto unitType = *reinterpret_cast<WoWObjectType**>(this + static_cast<int>(Offsets::GameObject::Type));
			if (unitType != nullptr)
			{
				return *static_cast<WoWObjectType*>(unitType);
			}
		}
		__except (1)
		{
			Console::PrintLn("Native Exception thrown at: const Native::GameObject::GetType() &");
		}
		return WoWObjectType::Invalid;
	}
}
