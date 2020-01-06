#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <vector>
#include <string>
#include "vector3.h"

class Navigation
{
public:
	static Navigation* GetInstance();
	void Initialize(unsigned int mapId);
	void Release();
	Vector3* CalculatePath(unsigned int mapId, Vector3 start, Vector3 end, bool straightPath, int* length, bool allowSwimming);
	void FreePathArr(Vector3* length);
    std::string GetMmapsPath();

private:
	static Navigation* s_singletonInstance;
	Vector3* currentPath;
};

#endif
