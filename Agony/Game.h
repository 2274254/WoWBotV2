#pragma once
#include "Macros.h"
#include <string>

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT Game
		{
		public:
			static std::string GetGameVersion();
		};
	}
}