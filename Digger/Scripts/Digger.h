#pragma once

#include "Bag.h"
#include "EasyEnemy.h"
#include "Entity.h"
#include "Bullet.h"
#include "Emerald.h"
class Bag;
class EasyEnemy;
class Digger : public virtual Entity {
protected:
	int m_emerald_count;
public:
	Digger();
	Digger(MAP& s_map, int x, int y, int lifes, std::string path, int dir);
	~Digger();

	void Move(char dir, MAP& s_map, std::vector<Bag>& bag, std::vector<EasyEnemy>& ens);

	int GetEmCount();

	void collision(Bullet& bullet, std::vector<EasyEnemy>& ens, std::vector<Emerald>& ems, std::vector<Bag>& bag, std::string type1, std::string type2, int& Score);

	void Entity_Collision(Bullet& bullet, std::vector<EasyEnemy>& ens, std::vector<Emerald>& ems, std::vector<Bag>& bag, int& Score);

	void Respawn(int x, int y, float time);

	void SetEmCount(const int count);
};