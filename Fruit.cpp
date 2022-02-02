#include "Fruit.h"

Fruit::Fruit(unsigned int x, unsigned int y)
{
	this->position.x = x;
	this->position.y = y;

	this->updateVertices();
}

void Fruit::setPosition(unsigned int x, unsigned int y)
{
	this->position.x = x;
	this->position.y = y;
	this->updateVertices();
}

sf::Vector2u Fruit::getPosition()
{
	return this->position;
}

void Fruit::updateVertices()
{
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(4);

	vertices[0].position = sf::Vector2f(this->position.x * constants::BLOCK_SIZE, this->position.y * constants::BLOCK_SIZE);
	vertices[1].position = sf::Vector2f((this->position.x + 1) * constants::BLOCK_SIZE, this->position.y * constants::BLOCK_SIZE);
	vertices[2].position = sf::Vector2f((this->position.x + 1) * constants::BLOCK_SIZE, (this->position.y + 1) * constants::BLOCK_SIZE);
	vertices[3].position = sf::Vector2f(this->position.x * constants::BLOCK_SIZE, (this->position.y + 1) * constants::BLOCK_SIZE);

	vertices[0].color = sf::Color::Red;
	vertices[1].color = sf::Color::Red;
	vertices[2].color = sf::Color::Red;
	vertices[3].color = sf::Color::Red;
}
