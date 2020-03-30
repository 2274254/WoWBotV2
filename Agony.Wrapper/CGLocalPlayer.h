#pragma once
#include "../Agony/CGLocalPlayer.h"
#include "CGPlayer.h"

namespace Agony
{
	public ref class CGLocalPlayer : public CGPlayer
	{
		Native::CGLocalPlayer* GetPtr();
	public:
		CGLocalPlayer(Native::CGLocalPlayer* obj) : CGPlayer(obj) {}

		property Int32 Money
		{
			Int32 get();
		}

		property Int32 CurrentXP
		{
			Int32 get();
		}

		property Int32 MaxXP
		{
			Int32 get();
		}
	};
}
