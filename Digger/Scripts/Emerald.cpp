#include "Emerald.h"

Emerald::Emerald() {}
Emerald::Emerald(MAP& s_map, int x, int y, int lifes, std::string path, int dir) : Entity(s_map, x, y, lifes, path, dir) {}
bool Emerald::is_alive() { 
	if (m_lifes <= 0) {
		return false;
	}
	return true;
}
