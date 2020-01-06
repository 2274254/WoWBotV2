#pragma once
#include <windows.h>
#include "Vector2.h"
#include "vector3.h"
#include "imgui.h"
#include <d3d11.h>
#include "WoWObject.h"

class BigVector2
{
public:
	double x, y;

	BigVector2()
	{
	}

	BigVector2(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
};

class BigVector3
{
public:
	double x, y, z;

	BigVector3()
	{
	}

	BigVector3(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class Drawings
{
	
public:

	static ID3D11Device* pDevice;
	static ID3D11DeviceContext* pDeviceContext;
	static ID3D11RenderTargetView* RenderTargetView;
	static ID3D11RenderTargetView* NormalTargetView;
	static Vector3* Waypoints;
	static int WaypointsLenght;
	static int CurrentWaypoint;
	
	static BigVector2 WorldToScreen(Vector3 unitPosition);
	static void DrawLine(Vector2 from, Vector2 to);
	static void DrawLine(Vector3 from, Vector3 to);
};

