#include "Bonus.h"

Bonus::Bonus(unsigned int x, unsigned int y, sf::Color defaultColor)
{
	this->position.x = x;
	this->position.y = y;
	this->defaultColor = defaultColor;
	this->updateVertices();
}

void Bonus::setPosition(unsigned int x, unsigned int y)
{
	this->position.x = x;
	this->position.y = y;
	this->updateVertices();
}

sf::Vector2u Bonus::getPosition()
{
	return this->position;
}

void Bonus::updateVertices()
{
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(4);

	vertices[0].position = sf::Vector2f(this->position.x * constants::BLOCK_SIZE, this->position.y * constants::BLOCK_SIZE);
	vertices[1].position = sf::Vector2f((this->position.x + 1) * constants::BLOCK_SIZE, this->position.y * constants::BLOCK_SIZE);
	vertices[2].position = sf::Vector2f((this->position.x + 1) * constants::BLOCK_SIZE, (this->position.y + 1) * constants::BLOCK_SIZE);
	vertices[3].position = sf::Vector2f(this->position.x * constants::BLOCK_SIZE, (this->position.y + 1) * constants::BLOCK_SIZE);

	vertices[0].color = this->defaultColor;
	vertices[1].color = this->defaultColor;
	vertices[2].color = this->defaultColor;
	vertices[3].color = this->defaultColor;
}

