#pragma once

#include "Entity.h"
#include "Digger.h"
#include "EasyEnemy.h"
class Digger;
class Bag : public virtual Entity {
protected:
	int f_x;
	int f_y;
	int distance;
public:
	Bag(MAP& s_map, int x, int y, int lifes, std::string path, int dir);
	Bag();
	void Move(MAP& map, float time, std::vector<Bag>& bag, std::vector<EasyEnemy>& ens, Digger& player);
	bool CanMoveLeft(MAP& s_map, std::vector<Bag>& bag, std::vector<EasyEnemy>& ens, Digger& player) ;
	bool CanMoveRight(MAP& s_map, std::vector<Bag>& bag, std::vector<EasyEnemy>& ens, Digger& player) ;
	int GetPosFX();
	int GetPosFY();
};
