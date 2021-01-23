#pragma once

#include "Entity.h"

class Emerald :public virtual Entity {
public:
	Emerald();
	Emerald(MAP& s_map, int x, int y, int lifes, std::string path, int dir);
	bool is_alive();
};