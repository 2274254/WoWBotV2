#pragma once
#include "CGPlayer.h"

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT CGLocalPlayer : public CGPlayer
		{
		public:
			MAKE_GET(Money, int32_t, Offsets::GameObject::Money);
			MAKE_GET(CurrentXP, int32_t, Offsets::GameObject::CurrentXP);
			MAKE_GET(MaxXP, int32_t, Offsets::GameObject::MaxXP);
		};
	}
}