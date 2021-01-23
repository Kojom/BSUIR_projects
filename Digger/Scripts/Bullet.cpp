#include "Bullet.h"

enum dirs { up = 0b0001, down = 0b0010, left = 0b0100, right = 0b1000, all = 0b1111 };

Bullet::Bullet() {}

void Bullet::Move(MAP& s_map) {
	switch (m_dir) {
	case dirs::up:
		if (el_time > 0.025 && GetBlock(1, s_map, 2) == 17) {
			m_y--;
		}
		else if (GetBlock(1, s_map, 2) != 17) { m_lifes = 0; }
		break;
	case dirs::left:
		if (el_time > 0.025 && GetBlock(2, s_map, 2) == 17) {
			m_x--;
		}
		else if (GetBlock(2, s_map, 2) != 17) { m_lifes = 0; }
		break;
	case dirs::right:
		if (el_time > 0.025 && GetBlock(3, s_map, 2) == 17) {
			m_x++;
		}
		else if (GetBlock(3, s_map, 2) != 17) { m_lifes = 0; }
		break;
	case dirs::down:
		if (el_time > 0.025 && GetBlock(4, s_map, 2) == 17) {
			m_y++;
		}
		else if (GetBlock(4, s_map, 2) != 17) { m_lifes = 0; }
		break;
	}
	if (el_time > 0.025) {
		el_time = 0;
		setPosition(static_cast<float>(m_x) * 8.f, static_cast<float>(m_y) * 8.f + 32.f);
	}
}