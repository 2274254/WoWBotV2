#include "ObjectGuid.h"

namespace Agony
{
	Native::ObjectGuid* ObjectGuid::GetPtr()
	{
		return this->self;
	}

	ObjectGuid::ObjectGuid(Native::ObjectGuid* guid)
	{
		this->self = guid;
	}

	GuidType ObjectGuid::Type::get()
	{
		if (this->GetPtr() == nullptr) return GuidType::Invalid;
		return static_cast<GuidType>(this->GetPtr()->Type());
	}

	System::UInt16 ObjectGuid::RealmId::get()
	{
		if (this->GetPtr() == nullptr) return 0;
		return this->self->RealmId();
	}

	System::UInt16 ObjectGuid::ServerId::get()
	{
		if (this->GetPtr() == nullptr) return 0;
		return this->self->ServerId();
	}

	System::UInt16 ObjectGuid::MapId::get()
	{
		if (this->GetPtr() == nullptr) return 0;
		return this->self->MapId();
	}

	System::UInt32 ObjectGuid::Id::get()
	{
		if (this->GetPtr() == nullptr) return 0;
		return this->self->Id();
	}

	System::UInt64 ObjectGuid::CreationBits::get()
	{
		if (this->GetPtr() == nullptr) return 0;
		return this->self->CreationBits();
	}

	System::UInt64 ObjectGuid::LoWord::get()
	{
		if (this->GetPtr() == nullptr) return 0;
		return this->self->LoWord;
	}

	System::UInt64 ObjectGuid::HiWord::get()
	{
		if (this->GetPtr() == nullptr) return 0;
		return this->self->HiWord;
	}
}