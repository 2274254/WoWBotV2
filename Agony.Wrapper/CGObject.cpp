#include "CGObject.h"

namespace Agony
{
	Native::CGObject* CGObject::GetPtr()
	{
		return nullptr;
	}

	WoWObjectType CGObject::Type::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return static_cast<WoWObjectType>(unit->GetType());
		}
		return Agony::WoWObjectType::Invalid;
	}
}