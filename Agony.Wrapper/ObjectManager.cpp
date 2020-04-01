#include "ObjectManager.h"
#include "../Agony/ObjectManager.h"
#include <iostream>

namespace Agony
{
	System::Collections::Generic::List<CGGameObject^>^ Agony::ObjectManager::GetGameObjectsVisible()
	{
		auto returnList = gcnew System::Collections::Generic::List<CGGameObject^>();
		auto visibleObjects = Agony::Native::ObjectManager::GetVisibleObjects();
		for (int i = 0; i < visibleObjects.size(); i++)
		{
			Agony::Native::CGObject* obj = visibleObjects[i];
			if (obj->GetType() == Agony::Native::WoWObjectType::GameObject)
			{
				returnList->Add(gcnew CGGameObject((Agony::Native::CGGameObject*)(obj)));
			}
		}
		return returnList;
	}

	System::Collections::Generic::List<CGGameObject^>^ ObjectManager::GetGameObjects()
	{
		auto returnList = gcnew System::Collections::Generic::List<CGGameObject^>();
		auto visibleObjects = Agony::Native::ObjectManager::GetObjects();
		for (int i = 0; i < visibleObjects.size(); i++)
		{
			Agony::Native::CGObject* obj = visibleObjects[i];
			if (obj->GetType() == Agony::Native::WoWObjectType::GameObject)
			{
				returnList->Add(gcnew CGGameObject((Agony::Native::CGGameObject*)(obj)));
			}
		}
		return returnList;
	}
}