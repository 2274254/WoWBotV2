#include "CGGameObject.h"
#include "LuaFunctions.h"

namespace Agony
{
	namespace Native
	{
		bool CGGameObject::Interact()
		{
			//auto m_currentObjectTrack = reinterpret_cast<ObjectGuid*>(Offsets::Base + Offsets::CGGameUI__m_currentObjectTrack);
			//m_currentObjectTrack = &this->GetGuid();
			//Agony::Native::LuaFunctions::Execute("InteractUnit('mouseover')");
			//return true;	
			auto x = this->GetGuid();
			//worth a test idont remember order thios
			return reinterpret_cast<bool(__fastcall*)(ObjectGuid*)>(Offsets::Base + Offsets::CGGameUI__OnSpriteRightClick)(&x);
			//std::cout << "This will call LUA..." << std::endl;
			//LuaFunctions::Call("InteractWith", {}, x.LoWord, x.HiWord);
			//return true;
			//return reinterpret_cast<bool(__fastcall*)(uint64_t*)>(Offsets::Base + Offsets::CGGameUI__OnSpriteRightClick)(&x.HiWord);
		}
	}
}
