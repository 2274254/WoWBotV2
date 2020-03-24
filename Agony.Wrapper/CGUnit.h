#pragma once
#include "../Agony/CGUnit.h"
#include "CGObject.h"
using namespace SharpDX;

namespace Agony
{
	public ref class CGUnit : public CGObject
	{
		Native::CGUnit* GetPtr();
	public:
		CGUnit(Native::CGObject* obj) : CGObject(obj) {}

		property SharpDX::Vector3 Position
		{
			SharpDX::Vector3 get();
		}

		property UnitRaceId Race
		{
			UnitRaceId get();
		}

		property UnitClassId Class
		{
			UnitClassId get();
		}
	};
}
