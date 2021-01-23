#pragma once

#include <SFML/Graphics.hpp>

class Cube {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	Cube() {}
	Cube(const std::string& path);
	void setPosition(float X, float Y);
};