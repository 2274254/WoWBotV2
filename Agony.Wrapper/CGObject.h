#pragma once
#include "../Agony/CGObject.h"
#include "StaticEnums.h"

namespace Agony
{
	public ref class CGObject
	{
		Native::CGObject* GetPtr();
	public:
		property WoWObjectType Type
		{
			WoWObjectType get();
		}
	};
}
