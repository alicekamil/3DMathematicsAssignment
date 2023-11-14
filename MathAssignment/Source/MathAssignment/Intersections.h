#pragma once

#include "CoreMinimal.h"

UENUM()
enum EIntersection
{
	Sphere,
	Plane,
	AABB,
	Triangle,
	Ray
};