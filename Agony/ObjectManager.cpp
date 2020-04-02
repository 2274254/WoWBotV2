#include "ObjectManager.h"
#include "Offsets.h"
#include "CGUnit.h"
#include "Game.h"
#include "Console.h"
#include <iostream>

namespace Agony
{
	namespace Native
	{
		std::vector<CGObject*> ObjectManager::GetVisibleObjects()
		{
			const CGObjectManager* m_CurObjectMgr = *reinterpret_cast<CGObjectManager**>(Offsets::Base + Offsets::ObjectMgr);
			/*
			auto player = reinterpret_cast<CGUnit*>(Agony::Native::Game::Me());
			std::cout << "Player name " << player->GetName() << std::endl;
			std::cout << "Player address 0x" << std::hex << player << std::endl;

			auto playerGuid = GetGUIDFromToken("player"); 
			std::cout << "Player guid1 address " << std::dec << player->GetGuid().LoWord << " " << std::dec << player->GetGuid().HiWord << std::endl;
			std::cout << "Player guid2 address " << std::dec << playerGuid.LoWord << " " << std::dec << playerGuid.HiWord << std::endl;
			std::cout << "Player guid3 address " << std::dec << m_CurObjectMgr->LocalGuid.LoWord << " " << std::dec << m_CurObjectMgr->LocalGuid.HiWord << std::endl;
			
			std::cout << "Player guid1 type " << std::dec << player->GetGuid().Type() << std::endl;
			std::cout << "Player guid2 type " << std::dec << playerGuid.Type() << std::endl;

			auto player2 = GetObjectFromGuid(&playerGuid);
			std::cout << "Player2 address 0x" << std::hex << player2 << std::endl;
			*/
			std::vector<CGObject*> returnList;
			for (auto i = *(uintptr_t*)(m_CurObjectMgr->VisibleObjects.Next); i != m_CurObjectMgr->VisibleObjects.Next; i = *(uintptr_t*)(i))
			{
				CGObject* wowObj = reinterpret_cast<CGObject*>(i - 0x18);
				/*if (wowObj->GetType() == WoWObjectType::Player)
				{
					CGUnit* unit = reinterpret_cast<CGUnit*>(wowObj);
					std::cout << "Obj player address 0x" << std::hex << unit << std::endl;
					std::cout << "Obj position = " << unit->GetPosition().x << ", " << unit->GetPosition().y << ", " << unit->GetPosition().z << std::endl;
					std::cout << "Obj race " << std::dec << (int)unit->GetRace() << std::endl;
					std::cout << "Obj class " << std::dec << (int)unit->GetClass() << std::endl;
					std::cout << "Obj HP " << std::dec << unit->GetCurrentHP() << "/" << std::dec << unit->GetMaxHP() << std::endl;
					std::cout << "Obj Mana " << std::dec << unit->GetCurrentMana() << "/" << std::dec << unit->GetMaxMana() << std::endl;
					//std::cout << "Obj name " << unit->GetName() << std::endl;
				}
				else
				{
					//std::cout << "Obj name " << wowObj->GetName() << std::endl;
				}*/
				if (wowObj->GetType() != WoWObjectType::Invalid)
				{
					if (wowObj->GetType() == WoWObjectType::Item)
					{
						std::cout << "Obj item address 0x" << std::hex << wowObj << std::endl;
					}
					returnList.push_back(wowObj);
				}
			}
			return returnList;
		}

		std::vector<CGObject*> ObjectManager::GetObjects()
		{
			std::vector<CGObject*> returnList;
			const CGObjectManager* m_CurObjectMgr = *reinterpret_cast<CGObjectManager**>(Offsets::Base + Offsets::ObjectMgr);
			for (uint64_t i = 0; i < m_CurObjectMgr->ActiveObjects.Capacity; i++)
			{
				CurMgr0x8Entry* entry = *reinterpret_cast<CurMgr0x8Entry**>(m_CurObjectMgr->ActiveObjects.Array + (8 * i));
				if (entry != nullptr && entry->ObjectBase->GetType() != WoWObjectType::Invalid)
				{
					returnList.push_back(entry->ObjectBase);
				}
			}
			return returnList;
		}

		CGObject* ObjectManager::GetBaseFromToken(std::string token)
		{
			return reinterpret_cast<CGObject * (__fastcall*)(const char*)>(Offsets::Base + Offsets::GetBaseFromToken)(token.c_str());
		}

		ObjectGuid ObjectManager::GetGUIDFromToken(std::string token)
		{
			ObjectGuid objectGUID{};
			reinterpret_cast<ObjectGuid* (__fastcall*)(ObjectGuid*, const char*, unsigned int)>(Offsets::Base + Offsets::Script_GetGUIDFromToken)(
				&objectGUID,
				token.c_str(),
				0
			);
			return objectGUID;
		}

		CGObject* ObjectManager::GetObjectFromGuid(ObjectGuid* guid)
		{
			/*return reinterpret_cast<CGObject* (__fastcall*)(ObjectGuid*, uint64_t, uint64_t, uint64_t)>(Offsets::Base + Offsets::ClntObjMgrObjectPtr)(
				guid,
				0x20,
				0,
				0x1A84
			);*/

			const CGObjectManager* m_CurObjectMgr = *reinterpret_cast<CGObjectManager**>(Offsets::Base + Offsets::ObjectMgr);
			for (uint64_t i = 0; i < m_CurObjectMgr->ActiveObjects.Capacity; i++)
			{
				CurMgr0x8Entry* entry = *reinterpret_cast<CurMgr0x8Entry**>(m_CurObjectMgr->ActiveObjects.Array + (8 * i));
				if(entry != nullptr && entry->ObjectBase->GetGuid().HiWord == guid->HiWord && entry->WowGuid.LoWord == guid->LoWord)
				{
					return entry->ObjectBase;
				}
			}
			/*
			uint64_t arrayIndex = (uint64_t)(m_CurObjectMgr->ActiveObjects.Capacity - 1) & (0xA2AA033B * guid->LoWord + 0xD6D018F5 * guid->HiWord);
			std::cout << "Array Index: " << std::hex << arrayIndex << std::endl;
			CurMgr0x8Entry* entry = *reinterpret_cast<CurMgr0x8Entry**>(m_CurObjectMgr->ActiveObjects.Array + (8 * arrayIndex));
			while (entry > 0)
			{
				std::cout << "Entry Index: " << std::hex << entry << std::endl;
				if (entry->ObjectBase->GetGuid().HiWord == guid->HiWord && entry->WowGuid.LoWord == guid->LoWord)
				{
					Console::PrintLn(entry->ObjectBase->GetName().c_str());
					return entry->ObjectBase;
				}
				entry = reinterpret_cast<CurMgr0x8Entry*>(entry->Next);
			}
			*/
			return nullptr;
		}

		bool ObjectManager::UnitExist(std::string token)
		{
			return GetBaseFromToken(token) != nullptr;
		}
	}
}