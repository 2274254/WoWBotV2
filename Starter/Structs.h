#ifndef STRUCTS_H
#define STRUCTS_H
#include <string>
#include <d3d9.h>
#include <d3dx9math.h>

class SpellInfo
{
public:
	char pad_0x0000[10]; //0x0000
	int Level; //0x0010 
};

class GameObjectType
{
public:
	DWORD Int; //0x0000
	std::string String; //0x0004
};

class GameObject
{
public:
	DWORD VTable; //0x0000
	GameObjectType* Type; //0x0004
	char pad_0008[12]; //0x0008
	DWORD Team; //0x0014
	char pad_0018[8]; //0x0018
	std::string Name; //0x0020
	char pad_0038[24]; //0x0038
	D3DXVECTOR3 Position; //0x0050
	char pad_005C[72]; //0x005C
	DWORD State; //0x00A4
	char pad_00A8[72]; //0x00A8
	DWORD NetworkID; //0x00F0
	char pad_00F4[20]; //0x00F4
	bool IsDead; //0x0108
	char pad_0109[271]; //0x0109
	float Mana; //0x0218
	char pad_021C[12]; //0x021C
	float MaxMana; //0x0228
	char pad_022C[204]; //0x022C
	float Health; //0x02F8
	char pad_02FC[12]; //0x02FC
	float MaxHealth; //0x0308
	char pad_030C[2084]; //0x030C
	std::string CharName; //0x0B30
	char pad_0B34[496]; //0x0B48
	float AttackDamageMod; //0x0D38
	char pad_0D3C[108]; //0x0D3C
	float BaseAttackDamage; //0x0DA8
	char pad_0DAC[32]; //0x0DAC
	float Armor; //0x0DCC
	char pad_0DD0[4]; //0x0DD0
	float MagicResist; //0x0DD4
	char pad_0DD8[12]; //0x0DD8
	float MoveSpeed; //0x0DE4
	float Range; //0x0DE8
	char pad_0DEC[8132]; //0x0DEC
	SpellInfo* SpellSlot[64];// 0x2DB0
	std::string GetType() const {
		return this->Type->String;
	}
	bool IsValid() const
	{
		return this != nullptr;
	}
	bool IsMe() const;
	bool IsAlly() const;
	bool IsEnemy() const;
};

class DeviceHandler
{
public:
	char pad_0000[20]; //0x0000
	LPDIRECT3DDEVICE9 Direct3DDevice9; //0x0014
};

class Renderer
{
public:
	char pad_0000[16]; //0x0000
	DeviceHandler* DeviceHandler; //0x0010
	char pad_0014[12]; //0x0014
	int ScreenResolutionX; //0x0020
	int ScreenResolutionY; //0x0024
	char pad_0028[100]; //0x0028
	D3DXMATRIX ViewMatrix; //0x008C
	D3DXMATRIX ProjectionMatrix; //0x00CC
};

class BuffScriptBase
{
public:
	char pad_0x0000[0x8]; //0x0000
	char Name[32]; //0x0008 
};

class Buff
{
public:
	int Type; //0x0000 
	BuffScriptBase* BaseScript; //0x0004 
	float startTime; //0x0008 
	float endTime; //0x000C 
	char pad_0x0010[0x1C]; //0x0010
	char pad_0x002C[0x40]; //0x002C
	int Stacks; //0x006C 
	std::string GetName() const {
		return this->BaseScript->Name;
	}
};

class GameNotifyEventArgs
{
public:
	DWORD EventID; // 0x0000
	DWORD sourceNID; //0x0004
	DWORD targetNID; //0x0008
};

#endif