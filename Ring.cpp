#pragma once
#include "SFML/Graphics.hpp"

struct Ring {
	Ring(sf::Vector2u pos, Ring* next) {
		this->pos = pos;
		this->next = next;
	}
	sf::Vector2u pos;
	Ring* next;
};