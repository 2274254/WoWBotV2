#pragma once
#include "ObjectGuid.h"

namespace Agony
{
	
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

		property System::String^ Name
		{
			System::String^ get();
		}

		property SharpDX::Vector3 Position
		{
			SharpDX::Vector3 get();
		}
	};
}
