#pragma once
#include "singletonBase.h"
class CollisionManager : public singletonBase<CollisionManager>
{
public:
	CollisionManager() {}
	~CollisionManager() {}
};