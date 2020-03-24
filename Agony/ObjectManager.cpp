#include "ObjectManager.h"
#include "Offsets.h"
#include "CGUnit.h"
#include <iostream>

namespace Agony
{
	namespace Native
	{
		std::vector<WoWObject*> ObjectManager::GetVisibleObjects()
		{
			std::vector<WoWObject*> returnList;
			const CGObjectManager* m_CurObjectMgr = *reinterpret_cast<CGObjectManager**>(Offsets::Base + Offsets::ObjectMgr);
			for (auto i = *(uintptr_t*)(m_CurObjectMgr->VisibleObjects.Next); i != m_CurObjectMgr->VisibleObjects.Next; i = *(uintptr_t*)(i))
			{
				WoWObject* wowObj = reinterpret_cast<WoWObject*>(i - 0x18);
				if (wowObj->Type == WoWObjectType::Player)
				{
					CGUnit* unit = (CGUnit*)wowObj;
					unit->GetType();
					std::cout << "Obj player address 0x" << std::hex << unit << std::endl;
					std::cout << "Obj Pos = " << unit->GetPosition().x << ", " << unit->GetPosition().y << ", " << unit->GetPosition().z << std::endl;
					//std::cout << "Obj name " << unit->GetName() << std::endl;
				}
				returnList.push_back(wowObj);
			}
			return returnList;
		}

		WoWObject* ObjectManager::GetBaseFromToken(std::string token)
		{
			return reinterpret_cast<WoWObject* (__fastcall*)(const char*)>(Offsets::Base + Offsets::GetBaseFromToken)(token.c_str());
		}

		bool ObjectManager::UnitExist(std::string token)
		{
			return GetBaseFromToken(token) != nullptr;
		}
	}
}