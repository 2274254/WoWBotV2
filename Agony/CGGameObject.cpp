#include "CGGameObject.h"

namespace Agony
{
	namespace Native
	{
		bool CGGameObject::Interact()
		{
			return reinterpret_cast<bool(__fastcall*)(ObjectGuid*)>(Offsets::Base + Offsets::CGGameUI__OnSpriteRightClick)(&this->GetGuid());
		}
	}
}
