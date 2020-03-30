#pragma once
#include "../Agony/CGPlayer.h"
#include "CGUnit.h"

namespace Agony
{
	public ref class CGPlayer : public CGUnit
	{
		Native::CGPlayer* GetPtr();
	public:
		CGPlayer(Native::CGPlayer* obj) : CGUnit(obj) {}
	};
}
