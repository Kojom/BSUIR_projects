#pragma once

#include "Entity.h"
#include "Bag.h"
class Bag;
class EasyEnemy : public virtual Entity {
protected:
	int Choose(MAP &map,std::vector<Bag>& bag);
public:
	EasyEnemy();
	EasyEnemy(MAP &s_map,int x, int y, int lifes, std::string path, int dir);
	~EasyEnemy();
	void Move(MAP& map, float time, std::vector<Bag>& bag, bool difficulty);
	void Respawn(int x, int y, float time);
};