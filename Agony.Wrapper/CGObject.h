#pragma once
#include "../Agony/CGObject.h"
#include "StaticEnums.h"

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

		property WoWObjectType Type
		{
			WoWObjectType get();
		}
	};
}
