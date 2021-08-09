/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2015
*/

#pragma once

#include <windows.h>

typedef DWORD Void;
typedef DWORD Any;
typedef DWORD uint;
typedef DWORD Hash;
typedef int EntityHandle;
typedef int PlayerHandle;
typedef int FireId;
typedef int PedHandle;
typedef int VehicleHandle;
typedef int CamHandle;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int PickupHandle;
typedef int ObjectHandle;
typedef int WeaponHandle;
typedef int InteriorHandle;
typedef int BlipHandle;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int CameraHandle;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;

/*#pragma pack(push, 1)
typedef struct
{
	float x;
	DWORD _paddingx;
	float y;
	DWORD _paddingy;
	float z;
	DWORD _paddingz;
} Vector3;
#pragma pack(pop)*/

#define ALIGN8 __declspec(align(8))

struct Vector2
{
	ALIGN8 float x;
	ALIGN8 float y;

	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2(const float x, const float y)
	{
		this->x = x;
		this->y = y;
	}
};

static_assert(sizeof(Vector2) == 16, "");