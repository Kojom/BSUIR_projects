#include "EasyEnemy.h"
#include <iostream>
EasyEnemy::~EasyEnemy() {}

EasyEnemy::EasyEnemy() {}

EasyEnemy::EasyEnemy(MAP& s_map, int x, int y, int lifes, std::string path, int dir) : Entity(s_map, x, y, lifes, path, dir) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			s_map.map[m_y + i][m_x + j] = 17;
		}
	}
}

int EasyEnemy::Choose(MAP &s_map,std::vector<Bag> &bag) {
	//Can not move in some direction if here is bag / block ( up / down )
	//Can not move in some direction if here is bag / block ( left / right ) but can move bag
	int dir[4]{ 1,2,3,4 };
	int j = 4;
	if (m_x % 4 != 0) {
		dir[0] = dir[3] = 0;
	}
	if (m_y % 4 != 0) {
		dir[1] = dir[2] = 0;
	}
	for (int i = 0; i < 4; i++) {
		int block = GetBlock(dir[i], s_map, 4);
		if ((block == 0 || block == 1) ) {
			dir[i] = 0;
		}
	}
	for (int f = 0; f < bag.size(); f++) {
			if (is_identical(m_x , m_y + 4, bag.at(f).GetPosX(), bag.at(f).GetPosY())) {
				dir[3] = 0;
			}
			if (is_identical(m_x , m_y - 4, bag.at(f).GetPosX(), bag.at(f).GetPosY())) {
				dir[0] = 0;
			}
	}
	for (int i = 0; i < 4; i++) {
		if (dir[i] == 0) {
			j--;
		}
	}
	if (j > 1) {
		for (int i = 0; i < 4; i++) {
			if (dir[i] == m_prevdir) {
				dir[i] = 0;
				j--;
			}
		}
	}
	if (j <= 0) { return 0; }
	int* possdir = new int[j];
	int i = 0;
	for (int f = 0; f < 4; f++) {
		if (dir[f] != 0) {
			possdir[i] = dir[f];
			i++;
		}
	}
	return possdir[rand() % j];
}

void EasyEnemy::Move(MAP& s_map, float time, std::vector<Bag>& bag, bool difficulty) {
	el_time += time;
	int dif = 0;
	difficulty ? dif = 0 : dif = 1;
	if (el_time > 0.04f - (dif*0.02)) {
		int dir = Choose(s_map, bag);
		switch (dir) {
		case 1: m_y--; break;
		case 2:
			for (int i = 0; i < bag.size(); i++) {
				for (int j = -3; j < 4; j++) {
					if (is_identical(m_x - 4, m_y + j, bag.at(i).GetPosX(), bag.at(i).GetPosY()) && bag.at(i).Moving()) {
						m_prevdir = 2;
						return;
					}
				}
				if (is_identical(m_x - 4, m_y, bag.at(i).GetPosX(), bag.at(i).GetPosY()) && !bag.at(i).Moving()) {
					if (bag.at(i).EmptyStack()) {
						bag.at(i).StepAdd(2, 4);
					}
					m_prevdir = 2;
					return;
				}
			}
			m_x--;
			break;
		case 3:
			for (int i = 0; i < bag.size(); i++) {
				for (int j = -3; j < 4; j++) {
					if (is_identical(m_x + 4, m_y + j, bag.at(i).GetPosX(), bag.at(i).GetPosY()) && bag.at(i).Moving()) {
						m_prevdir = 2;
						return;
					}
				}
				if (is_identical(m_x + 4, m_y, bag.at(i).GetPosX(), bag.at(i).GetPosY()) && !bag.at(i).Moving()) {
					if (bag.at(i).EmptyStack()) {
						bag.at(i).StepAdd(3, 4);
					}
					m_prevdir = 3;
					return;
				}
			}
			m_x++;
			break;
		case 4: m_y++; break;
		}
		el_time = 0;
		m_prevdir = 4 - (dir % 4 - 1) - (dir / 4) * 4;
		setPosition(static_cast<float>(m_x) * 8.f, static_cast<float>(m_y) * 8.f + 32.f);
	}
}

void EasyEnemy::Respawn(int x,int y, float time) {
	el_time += time;
	time = 0;
	if (el_time > 3) {
		m_x = y; m_y = x;
		setPosition(static_cast<float>(m_x) * 8.f, static_cast<float>(m_y) * 8.f + 32.f);
		m_lifes = 1;
	}
}