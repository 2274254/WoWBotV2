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

	SharpDX::Vector3 CGObject::Position::get()
	{
		auto obj = this->GetPtr();
		if (obj != nullptr)
		{
			auto position = obj->GetPosition();
			return SharpDX::Vector3(position.x, position.y, position.z);
		}
		return SharpDX::Vector3(0, 0, 0);
	}
}