#pragma once
#pragma once

#include "Common.h"

class CTarget
{
public:
	Vec2 pos{ 0.0,0.0 };

	CTarget(const Vec2& p)
		: pos(p){}
};