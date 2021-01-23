#include "Entity.h"

enum dirs { up = 0b0001, down = 0b0010, left = 0b0100, right = 0b1000, all = 0b1111 };

Entity::Entity(MAP& s_map,int x, int y, int lifes, std::string path, int dir) :m_x(x), m_y(y), m_prevdir(0), m_dir(dir), m_lifes(lifes), el_time(0),is_moving(0) {
	icon.texture.loadFromFile("images/" + path + ".png");
	icon.sprite.setTexture(icon.texture);
}
Entity::Entity() : m_x(0), m_y(0), m_prevdir(-1), m_dir(0), m_lifes(0), el_time(0),is_moving(0) {
	icon.texture.loadFromFile("images/Emerald.png");
	icon.sprite.setTexture(icon.texture);
}
Entity::~Entity() {}

int Entity::GetPosX() const { return m_x; }
int Entity::GetPosY() const { return m_y; }
int Entity::GetLifes() { return m_lifes; }
void Entity::SetLifes(int lifes) { m_lifes = lifes; }
void Entity::SetPosX(const int x) { m_x = x; }
void Entity::SetPosY(const int y) { m_y = y; }
void Entity::SetDir(const int dir) {
	m_dir = dir;
}
char Entity::GetDir() const {
	return m_dir;
}
void Entity::setPosition(float X, float Y) {
	icon.sprite.setPosition(X, Y);
}
void Entity::SetTime(const float time) {
	el_time = time;
}
float Entity::GetTime() { return el_time; }
void Entity::SetInfo(int x,int y,int lifes,std::string path,int dir) {
	m_x = x; m_y = y;
	m_lifes = lifes;
	icon.texture.loadFromFile("images/" + path + ".png");
	icon.sprite.setTexture(icon.texture);
	setPosition(static_cast<float>(m_x * 8), static_cast<float>(m_y * 8 + 32));
	m_dir = dir;
}
sf::Sprite Entity::sprite() {
	return icon.sprite;
}
int Entity::GetBlock(char dir, MAP& s_map, int hbx) const {
	int lim = 4;
	int bull = 0;
	if (hbx == 2) {
		lim = 3;
		bull = 2;
	}
	switch (dir) {
	case 1:
		for (int i = 4 - lim; i < lim; i++) {
			if (s_map.map[m_y - 1 + bull][m_x + i] > 0 && s_map.map[m_y - 1 + bull][m_x + i] < 17) {
				return 1;
			}
			if (s_map.map[m_y - 1 + bull][m_x + i] == 0) {
				return 0;
			}
		}
		return 17;
		break;
	case 2:
		for (int i = 4 - lim; i < lim; i++) {
			if (s_map.map[m_y + i][m_x - 1+bull] > 0 && s_map.map[m_y + i][m_x - 1 + bull] < 17) {
				return 1;
			}
			if (s_map.map[m_y + i][m_x - 1+bull] == 0) {
				return 0;
			}
		}
		return 17;
		break;
	case 3:
		for (int i = 4 - lim; i < lim; i++) {
			if (s_map.map[m_y + i][m_x + 4 -bull] > 0 && s_map.map[m_y + i][m_x + 4 - bull] < 17) {
				return 1;
			}
			if (s_map.map[m_y + i][m_x + 4-bull] == 0) {
				return 0;
			}
		}
		return 17;
		break;
	case 4:
		for (int i = 4 - lim; i < lim; i++) {
			if (s_map.map[m_y + 4-bull][m_x + i] > 0 && s_map.map[m_y + 4 - bull][m_x + i] < 17) {
				return 1;
			}
			if (s_map.map[m_y + 4-bull][m_x + i] == 0) {
				return 0;
			}
		}
		return 17;
		break;
	}
	return 0;
}
bool Entity::is_identical(int y1, int x1, int y2, int x2) {
	if (y1 == y2 && x1 == x2) { return 1; }
	return 0;
}
char Entity::toChar(char &dir) {
	if (dir & 0b0001) {
		dir = 1;
	}
	else if (dir & 0b0010) {
		dir = 4;
	}
	else if (dir & 0b0100) {
		dir = 2;
	}
	else if (dir & 0b1000) {
		dir = 3;
	}
	return dir;
}
void Entity::SetMoving(bool flag) { is_moving = flag; }
bool Entity::Moving() { return is_moving; }
void Entity::StepAdd(const int dir, const int steps) {
	for  (int i = 0; i < steps;  i++) {
		way.push(dir);
	}
}
bool Entity::EmptyStack() const{ return way.empty(); }