#include "CGPlayer.h"

namespace Agony
{
	Native::CGPlayer* CGPlayer::GetPtr()
	{
		return static_cast<Native::CGPlayer*>(this->self);
	}
}