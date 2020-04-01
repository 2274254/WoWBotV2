#include "CGGameObject.h"
#include "LuaFunctions.h"

namespace Agony
{
	namespace Native
	{
		bool CGGameObject::Interact()
		{
			auto m_currentObjectTrack = reinterpret_cast<ObjectGuid*>(Offsets::Base + Offsets::CGGameUI__m_currentObjectTrack);
			m_currentObjectTrack = &this->GetGuid();
			Agony::Native::LuaFunctions::Execute("InteractUnit('mouseover')");
			return true;
			//return reinterpret_cast<bool(__fastcall*)(ObjectGuid*)>(Offsets::Base + Offsets::CGGameUI__OnSpriteRightClick)(&this->GetGuid());
		}
	}
}
