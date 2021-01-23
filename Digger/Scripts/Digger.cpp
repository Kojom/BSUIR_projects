#include "Digger.h"
#include <iostream>

enum dirs { up = 0b0001, down = 0b0010, left = 0b0100, right = 0b1000, all = 0b1111 };

Digger::Digger():m_emerald_count(0) {}

Digger::Digger(MAP& s_map, int x, int y, int lifes, std::string path, int dir) :m_emerald_count(0), Entity(s_map, x, y, lifes, path, dir) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			s_map.map[m_y + i][m_x + j] = 17;
		}
	}
	setPosition(static_cast<float>(m_x) * 8.f, static_cast<float>(m_y) * 8.f + 32.f);
}

Digger::~Digger() {}

void Digger::Move(char dir, MAP& s_map, std::vector<Bag>& bag, std::vector<EasyEnemy>& ens) {
	bool border_ahead = false;
	if (dir == 0) return;
	toChar(dir);
	//Use recursion if player coordinates is not % 4
	if (el_time > 0.05) {
		int block = GetBlock(dir, s_map, 4);
		if (block == 0)
			border_ahead = true;
		switch (dir) {
		case 1:
			if (m_x % 4 != 0 || border_ahead) {
				Move(m_x % 4 == 1 ? dirs::left : m_x % 4 == 3 ? dirs::right : m_x % 4 == 2 ? m_prevdir : 0, s_map, bag, ens);
				m_x % 4 == 1 ? m_prevdir = dirs::up : m_x % 4 == 3 ? m_prevdir = dirs::up : m_prevdir = m_prevdir;
				return;
			}
			//Can not move into the bag
			for (int i = 0; i < bag.size(); i++) {
				if (is_identical(m_x, m_y - 4, bag.at(i).GetPosX(), bag.at(i).GetPosY())) {
					return;
				}
			}
			///////////////////////////////////////
			m_y--;
			for (int i = 0; i < 4; i++)
				s_map.map[m_y][m_x + i] = 17;
			break;
		case 2:
			if (m_y % 4 != 0 || border_ahead) {
				Move(m_y % 4 == 1 ? dirs::up : m_y % 4 == 3 ? dirs::down : m_y % 4 == 2 ? m_prevdir : 0, s_map, bag, ens);
				m_y % 4 == 1 ? m_prevdir = dirs::left : m_y % 4 == 3 ? m_prevdir = dirs::left : m_prevdir = m_prevdir;
				return;
			}
			//Can not move bag & our player, if after bag is another bag or easy_enemy
			for (int i = 0; i < bag.size(); i++) {
				for (int j = -3; j < 4; j++) {
					if (is_identical(m_x - 4, m_y + j, bag.at(i).GetPosX(), bag.at(i).GetPosY()) && bag.at(i).Moving()) {
						return;
					}
				}
				if (is_identical(m_x - 4, m_y, bag.at(i).GetPosX(), bag.at(i).GetPosY()) && !bag.at(i).Moving()) {
					if (bag.at(i).EmptyStack()) {
						bag.at(i).StepAdd(2, 4);
					}
					return;
				}
			}
			/////////////////////////////////////////////
			icon.sprite.setTextureRect(sf::IntRect(32, 0, -32, 32));
			m_x--;
			for (int i = 0; i < 4; i++)
				s_map.map[m_y + i][m_x] = 17;
			break;
		case 3:
			if (m_y % 4 != 0 || border_ahead) {
				Move(m_y % 4 == 1 ? dirs::up : m_y % 4 == 3 ? dirs::down : m_y % 4 == 2 ? m_prevdir : 0, s_map, bag, ens);
				m_y % 4 == 1 ? m_prevdir = dirs::right : m_y % 4 == 3 ? m_prevdir = dirs::right : m_prevdir = m_prevdir;
				return;
			}
			//Can not move bag & our player, if after bag is another bag or easy_enemy
			for (int i = 0; i < bag.size(); i++) {
				for (int j = -3; j < 4; j++) {
					if (is_identical(m_x + 4, m_y + j, bag.at(i).GetPosX(), bag.at(i).GetPosY()) && bag.at(i).Moving()) {
						return;
					}
				}
				if (is_identical(m_x + 4, m_y, bag.at(i).GetPosX(), bag.at(i).GetPosY()) && !bag.at(i).Moving()) {
					if (bag.at(i).EmptyStack()) {
						bag.at(i).StepAdd(3, 4);
					}
					return;
				}
			}
			///////////////////////////////////////////////////////
			icon.sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			m_x++;
			for (int i = 0; i < 4; i++)
				s_map.map[m_y + i][m_x + 3] = 17;
			break;
		case 4:
			if (m_x % 4 != 0 || border_ahead) {
				Move(m_x % 4 == 1 ? dirs::left : m_x % 4 == 3 ? dirs::right : m_x % 4 == 2 ? m_prevdir : 0, s_map, bag, ens);
				m_x % 4 == 1 ? m_prevdir = dirs::down : m_x % 4 == 3 ? m_prevdir = dirs::down : m_prevdir = m_prevdir;
				return;
			}
			//Can not move into the bag
			for (int i = 0; i < bag.size(); i++) {
				if (is_identical(m_x, m_y + 4, bag.at(i).GetPosX(), bag.at(i).GetPosY())) {
					return;
				}
			}
			////////////////////////////////
			m_y++;
			for (int i = 0; i < 4; i++)
				s_map.map[m_y + 3][m_x + i] = 17;
			break;
		}
		//Settint our previous direction 
		switch (dir) {
		case 1:
			m_prevdir = m_dir = dirs::up;
			break;
		case 2:
			m_prevdir = m_dir = dirs::left;
			break;
		case 3:
			m_prevdir = m_dir = dirs::right;
			break;
		case 4:
			m_prevdir = m_dir = dirs::down;
			break;
		}
		el_time = 0;
		setPosition(static_cast<float>(m_x) * 8.f, static_cast<float>(m_y) * 8.f + 32.f);
	}
}

int Digger::GetEmCount() { return m_emerald_count; }

void Digger::collision(Bullet& bullet, std::vector<EasyEnemy>& ens, std::vector<Emerald>& ems, std::vector<Bag>& bag, std::string type1, std::string type2, int& Score) {
	//Collisions & killing our entities
	if (type1 == "player" && type2 == "emerald") {
		for (int j = 0; j < ems.size(); j++) {
			if (ems.at(j).GetLifes() != 0) {
				if (is_identical(m_y - 2, m_x, ems.at(j).GetPosY(), ems.at(j).GetPosX()) ||
					is_identical(m_y, m_x - 2, ems.at(j).GetPosY(), ems.at(j).GetPosX()) ||
					is_identical(m_y, m_x + 2, ems.at(j).GetPosY(), ems.at(j).GetPosX()) ||
					is_identical(m_y + 2, m_x, ems.at(j).GetPosY(), ems.at(j).GetPosX())) {
					Score += 25;
					m_emerald_count++;
					ems.at(j).SetLifes(0);
					return;
				}
			}
		}
	}
	if (type1 == "player" && type2 == "enemy") {
		for (int j = 0; j < ens.size(); j++) {
			if(ens.at(j).GetLifes()){
				for (int i = -2; i < 3; i++) {
					for (int f = -2; f < 3; f++) {
						if (is_identical(m_y + i, m_x + f, ens.at(j).GetPosY(), ens.at(j).GetPosX()) && ens.at(j).GetLifes()) {
							m_lifes--;
							for (int h = 0; h < ens.size(); h++) {
								ens.at(h).SetLifes(0);
								ens.at(h).SetTime(0);
							}
							for (int h = 0; h < bag.size(); h++) {
								if (bag.at(h).Moving()) {
									bag.at(h).SetMoving(0);
									bag.at(h).SetLifes(0);
								}
							}
							return;
						}
					}
				}
			}
		}
	}
	if (type1 == "player" && type2 == "bag") {
		for (int j = 0; j < bag.size(); j++) {
			if (bag.at(j).GetLifes()>0) {
				for (int f = -3; f < 4; f++) {
					if (is_identical(m_y - 2, m_x + f, bag.at(j).GetPosY(), bag.at(j).GetPosX())) {
						m_lifes--;
						for (int h = 0; h < ens.size(); h++) {
							ens.at(h).SetLifes(0);
						}
						for (int h = 0; h < bag.size(); h++) {
							if (bag.at(h).Moving()) {
								bag.at(h).SetMoving(false);
								bag.at(h).SetLifes(0);
							}
						}
						return;
					}
				}
			}
		}
	}
	if (type1 == "enemy" && type2 == "bag") {
		for (int j = 0; j < bag.size(); j++) {
			for (int k = 0; k < ens.size(); k++) {
				for (int f = -(ens.at(k).GetPosX() % 4); f < 2; f++) {
					if (bag.at(j).GetLifes() > 0) {
						if (is_identical(ens.at(k).GetPosY() - 3, ens.at(k).GetPosX() + f, bag.at(j).GetPosY(), bag.at(j).GetPosX())) {
							if (ens.at(k).GetLifes()) {
								Score += 100;
							}
							ens.at(k).SetLifes(0);
							break;
						}
					}
				}
			}
		}
	}
	if (type1 == "enemy" && type2 == "bullet") {
		for (int j = 0; j < ens.size(); j++) {
			if (ens.at(j).GetLifes()) {
				for (int i = -2; i < 3; i++) {
					for (int f = -2; f < 3; f++) {
						if (is_identical(bullet.GetPosY() + i, bullet.GetPosX() + f, ens.at(j).GetPosY(), ens.at(j).GetPosX()) && bullet.GetLifes()) {
							if (ens.at(j).GetLifes()) {
								Score += 50;
							}
							bullet.SetLifes(0);
							ens.at(j).SetLifes(0);
							return;
						}
					}
				}
			}
		}
	}
	if (type1 == "bag" && type2 == "bullet") {
		for (int j = 0; j < bag.size(); j++) {
			if (bullet.GetLifes()) {
				for (int i = -2; i < 3; i++) {
					for (int f = -2; f < 3; f++) {
						if (is_identical(bullet.GetPosY() + i, bullet.GetPosX() + f, bag.at(j).GetPosY(), bag.at(j).GetPosX()) && bag.at(j).GetLifes()) {
							bullet.SetLifes(0);
							return;
						}
					}
				}
			}
		}
	}
}

void Digger::Entity_Collision(Bullet& bullet, std::vector<EasyEnemy>& ens, std::vector<Emerald>& ems, std::vector<Bag>& bag, int& Score) {
	collision(bullet, ens, ems, bag, "player", "emerald", Score);
	collision(bullet, ens, ems, bag, "player", "bag", Score);
	collision(bullet, ens, ems, bag, "player", "enemy", Score);
	collision(bullet, ens, ems, bag, "enemy", "bag", Score);
	collision(bullet, ens, ems, bag, "enemy", "bullet", Score);
	collision(bullet, ens, ems, bag, "bag", "bullet", Score);
}

void Digger::Respawn(int x, int y, float time) {
	//Delay our player after his dead
	el_time = time; m_x = y; m_y = x;
	setPosition(static_cast<float>(m_x) * 8.f, static_cast<float>(m_y) * 8.f + 32.f);
}

void Digger::SetEmCount(const int count) { m_emerald_count = count; }