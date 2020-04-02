#pragma once
#include "CGUnit.h"

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT CGPlayer : public CGUnit
		{
		public:
			CGObject* GetItemBySlot(int slot);
		};
	}
}