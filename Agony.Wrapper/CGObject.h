#pragma once
#include "../Agony/CGObject.h"
#include "StaticEnums.h"

namespace Agony
{
	public ref class ObjectGuid
	{
	internal:
		Native::ObjectGuid* GetPtr();
	protected:
		Native::ObjectGuid* self;
	public:
		ObjectGuid(Native::ObjectGuid* guid);
		ObjectGuid() {};

		property GuidType Type
		{
			GuidType get();
		}

		property System::UInt16 RealmId
		{
			System::UInt16 get();
		}

		property System::UInt16 ServerId
		{
			System::UInt16 get();
		}

		property System::UInt16 MapId
		{
			System::UInt16 get();
		}

		property System::UInt32 Id
		{
			System::UInt32 get();
		}

		property System::UInt64 CreationBits
		{
			System::UInt64 get();
		}

		property System::UInt64 LoWord
		{
			System::UInt64 get();
		}

		property System::UInt64 HiWord
		{
			System::UInt64 get();
		}
	};

	public ref class CGObject
	{
	internal:
		Native::CGObject* GetPtr();
	protected:
		Native::CGObject* self;
	public:
		CGObject(Native::CGObject* obj);
		CGObject() {};

		property ObjectGuid^ Guid
		{
			ObjectGuid^ get();
		}

		property WoWObjectType Type
		{
			WoWObjectType get();
		}
	};
}
