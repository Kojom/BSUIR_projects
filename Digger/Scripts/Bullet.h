#pragma once
#include "Entity.h"

class Bullet :public virtual Entity {
public:
	Bullet();
	void Move(MAP& s_map);
};