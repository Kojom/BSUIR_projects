#pragma once

#include "MAP.h"
#include "Cube.h"
#include <stack>

class Entity {
protected:
	int m_x, m_y;
	int m_prevdir;
	char m_dir;
	int m_lifes;
	float el_time;
	bool is_moving;
	std::stack<int> way;
	Cube icon;
public:
	Entity(MAP &s_map,int x, int y,int lifes,std::string path,int dir);
	Entity();
	~Entity();

	int GetPosX() const;
	int GetPosY() const;

	void SetPosX(const int x);
	void SetPosY(const int y);
	void SetDir(const int dir);
	void SetLifes(int lifes);
	void SetTime(const float time);
	void SetInfo(int x, int y, int lifes, std::string path, int dir);
	void setPosition(float X, float Y);
	char GetDir() const;
	int GetLifes();
	float GetTime();
	sf::Sprite sprite();
	int GetBlock(char dir, MAP &s_map,int hbx) const;
	bool is_identical(int y1, int x1, int y2, int x2);
	char toChar(char& dir);
	void SetMoving(bool flag);
	bool Moving();
	void StepAdd(const int dir, const int steps);
	bool EmptyStack()const;
};