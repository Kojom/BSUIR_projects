#include "Cube.h"

Cube::Cube(const std::string& path) {
	texture.loadFromFile("images/" + path + ".png");
	sprite.setTexture(texture);
}
void Cube::setPosition(float X, float Y) {
	sprite.setPosition(X, Y);
}