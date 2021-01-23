#include "Bag.h"
#include <iostream>
Bag::Bag() :distance(0), f_x(0), f_y(0) {}

Bag::Bag(MAP& s_map, int x, int y, int lifes, std::string path, int dir) : f_x(0), f_y(0), distance(0), Entity(s_map, x, y, lifes, path, dir) {}

void Bag::Move(MAP &s_map,float time,std::vector<Bag>&bag, std::vector<EasyEnemy>& ens, Digger& player) {
	el_time += time;
	time = 0;
	//Can our bag move left/right or not
	bool left_can_move = CanMoveLeft(s_map,bag,ens,player), right_can_move = CanMoveRight(s_map, bag, ens, player);
	if (!left_can_move && !way.empty() && way.top()==2) {
		while (!way.empty()) {
			way.pop();
		}
	}
	if (!right_can_move && !way.empty() && way.top() == 3) {
		while (!way.empty()) {
			way.pop();
		}
	}
	// stack_way is our way on map ( some entity can push bags )
	if (!way.empty() && el_time > 0.03) {
		is_moving = true;
		el_time = 0;
		switch (way.top()) {
		case 2:
			if (left_can_move) {
				for (int i = 0; i < ens.size(); i++) {
					for (int j = -3; j < 4; j++) {
						if (is_identical(m_x - 4, m_y + j, ens.at(i).GetPosX(), ens.at(i).GetPosY())) {
							ens.at(i).SetLifes(ens.at(i).GetLifes() - 1);
						}
					}
				}
				way.pop();
				if (m_x % 4 == 0 && !way.empty()) {
					f_x = (m_x - 1) * 4;
					f_y = m_y;
				}
				m_x--;
			}
			break;
		case 3:
			if (right_can_move) {
				for (int i = 0; i < ens.size(); i++) {
					for (int j = -3; j < 4; j++) {
						if (is_identical(m_x + 4, m_y + j, ens.at(i).GetPosX(), ens.at(i).GetPosY())) {
							ens.at(i).SetLifes(ens.at(i).GetLifes() - 1);
						}
					}
				}
				way.pop();
				if (m_x % 4 == 0 && !way.empty()) {
					f_x = (m_x + 1) * 4;
					f_y = m_y;
				}
				m_x++;
			}
			break;
		}
		if (way.empty()) {
			f_x = m_x;
			f_y = m_y;
			el_time = 2.f;
		}
	}
	int dy = (int)m_y % 4;
	int dx = (int)m_x % 4;
	int block = GetBlock(4, s_map, 4);
	if (el_time > 0.05) {
		if (el_time > 0.8 && block != 0 && block != 1 && !is_moving) {
			is_moving = true;
			el_time = 0;
		}
		//can be removed
		for (int i = 0; i < bag.size(); i++) {
			for (int j = -3; j < 4; j++) {
				if (is_identical(m_x + j, m_y + 4, bag.at(i).GetPosX(), bag.at(i).GetPosY()) || block !=17) {
					if (dy != 0) {
						is_moving = true;
						break;
					}
					el_time = 0;
					is_moving = false;
				}
			}
		}
		if (dx == 0) {
			if ((dy != 0 || block == 17)&& is_moving) {
				m_y++;
				el_time = 0;
				while (!way.empty()) {
					way.pop();
				}
				for (int i = 0; i < 4; i++) {
					s_map.map[m_y + 3][m_x + i] = 17;
				}
			}
		}
	}
	//after moving we have to show, that entity is moved
	f_x = m_x;
	f_y = m_y;
	setPosition(static_cast<float>(m_x) * 8.f, static_cast<float>(m_y) * 8.f + 32.f);
}

bool Bag::CanMoveLeft(MAP& s_map, std::vector<Bag>& bag, std::vector<EasyEnemy>& ens, Digger& player)  {
	for (int g = -3; g < 4; g++) {
		for (int j = 0; j < bag.size(); j++) {
			if (is_identical(m_x - 4, m_y + g, bag.at(j).GetPosX(), bag.at(j).GetPosY())) {
				return false;
			}
		}
	}
	for (int g = -3; g < 4; g++) {
		if (!way.empty() && m_x%4==0) {
			if (is_identical(m_x - 4, m_y + g, player.GetPosX(), player.GetPosY())) {
				return false;
			}
		}
	}
	for (int g = 4; g < 8; g++) {
		if (!way.empty() && m_x % 4 == 0) {
			if (is_identical(m_x - g, m_y, player.GetPosX(), player.GetPosY())) {
				return false;
			}
		}
	}
	if (GetBlock(2, s_map, 4) == 0) {
		return false;
	}
	return true;
}
bool Bag::CanMoveRight(MAP& s_map, std::vector<Bag>& bag, std::vector<EasyEnemy>& ens, Digger& player) {
	for (int g = -3; g < 4; g++) {
		for (int j = 0; j < bag.size(); j++) {
			if (is_identical(m_x + 4, m_y + g, bag.at(j).GetPosX(), bag.at(j).GetPosY())) {
				return false;
			}
		}
	}
	for (int g = -3; g < 4; g++) {
		if (!way.empty() && m_x % 4 == 0) {
			if (is_identical(m_x + 4, m_y + g, player.GetPosX(), player.GetPosY())) {
				return false;
			}
		}
	}
	for (int g = 4; g < 8; g++) {
		if (!way.empty() && m_x % 4 == 0) {
			if (is_identical(m_x + g, m_y, player.GetPosX(), player.GetPosY())) {
				return false;
			}
		}
	}
	if (GetBlock(3, s_map, 4) == 0) {
		return false;
	}
	return true;
}
int Bag::GetPosFX() { return f_x; }
int Bag::GetPosFY() { return f_y; }