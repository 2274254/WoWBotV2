#pragma once
#include "vector3.h"

class CorpseBase
{
public:
    char pad_0000[40]; //0x0000
    Vector3 pos; //0x0028
}; //Size: 0x0034

class WoWObject
{
public:
    char pad_0000[272]; //0x0000
    Vector3 pos; //0x0110
    char pad_011C[4]; //0x011C
    float fAngle; //0x0120
}; //Size: 0x124
