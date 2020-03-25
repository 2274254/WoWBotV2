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

	ObjectGuid^ CGObject::Guid::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return gcnew ObjectGuid(&unit->GetGuid());
		}
		return gcnew ObjectGuid();
	}

	WoWObjectType CGObject::Type::get()
	{
		auto obj = this->GetPtr();
		if (obj != nullptr)
		{
			return static_cast<WoWObjectType>(obj->GetType());
		}
		return Agony::WoWObjectType::Invalid;
	}

	System::String^ CGObject::Name::get()
	{
		auto obj = this->GetPtr();
		if (obj != nullptr)
		{
			return gcnew System::String(obj->GetName().c_str());
		}
		return gcnew System::String("Unknown");
	}
}