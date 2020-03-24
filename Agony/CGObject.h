#pragma once
#include "Macros.h"
#include "Offsets.h"
#include "StaticEnums.h"
#include "vector3.h"

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT CGObject
		{
		public:
			std::string GetName();
			WoWObjectType GetType();
			Vector3 GetPosition();
		};
	}
}
