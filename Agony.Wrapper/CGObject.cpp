#include "CGObject.h"

namespace Agony
{
	Native::CGObject* CGObject::GetPtr()
	{
		return this->self;
	}

	CGObject::CGObject(Native::CGObject* obj)
	{
		this->self = obj;
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