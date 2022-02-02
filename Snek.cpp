#include "Snek.h"

Snek::Snek(unsigned int baseSize, sf::Vector2u headPosition)
{
	this->head = new Ring(headPosition, nullptr);
	this->size = 1;
	for (size_t i = 1; i < baseSize; i++) {
		this->addRingAtEnd();
	}
}

void Snek::addRingAtEnd()
{
	Ring* last = this->findLastRing();
	Ring* newRing = new Ring(last->pos, nullptr);
	last->next = newRing;
	this->size++;
	updateVertices();
}

void Snek::moveHeadInDirection(Direction direction)
{
	sf::Vector2u previousPosition = this->head->pos;

	// Compute new head position
	if (direction == Direction::UP) {
		int y = this->head->pos.y - 1;
		if (y < 0) {
			y += constants::GRID_HEIGHT;
		}
		this->head->pos.y = y;
	}
	if (direction == Direction::DOWN) {
		this->head->pos.y = (this->head->pos.y + 1) % constants::GRID_HEIGHT;
	}
	if (direction == Direction::RIGHT) {
		this->head->pos.x = (this->head->pos.x + 1) % constants::GRID_WIDTH;
	}
	if (direction == Direction::LEFT) {
		int x = this->head->pos.x - 1;
		if (x < 0) {
			x += constants::GRID_WIDTH;
		}
		this->head->pos.x = x;
	}

	// Update queue of snek
	Ring* head = this->head->next;
	while (head != nullptr) {
		sf::Vector2u currentPosition = head->pos;
		head->pos = previousPosition;
		previousPosition = currentPosition;
		head = head->next;
	}
	this->updateVertices();
}

bool Snek::headCollides()
{
	Ring* head = this->head->next;
	if (head == nullptr) {
		return false;
	}
	while (head != nullptr) {
		if (head->pos == this->head->pos) {
			return true;
		}
		head = head->next;
	}
	return false;
}

bool Snek::isInSnek(sf::Vector2u position)
{
	Ring* head = this->head->next;
	if (head == nullptr) {
		return false;
	}
	while (head != nullptr) {
		if (head->pos == position) {
			return true;
		}
		head = head->next;
	}
	return false;
}

sf::Vector2u Snek::getSnekHeadPosition()
{
	return this->head->pos;
}

Ring* Snek::findLastRing()
{
	Ring* last = this->head;
	while (last->next != nullptr) {
		last = last->next;
	}
	return last;
}

void Snek::updateVertices()
{
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(this->size * 4);
	
	Ring* head = this->head;
	unsigned int count = 0;

	sf::Vertex* quad = &vertices[count * 4];
	quad[0].position = sf::Vector2f(head->pos.x * constants::BLOCK_SIZE, head->pos.y * constants::BLOCK_SIZE);
	quad[1].position = sf::Vector2f((head->pos.x + 1) * constants::BLOCK_SIZE, head->pos.y * constants::BLOCK_SIZE);
	quad[2].position = sf::Vector2f((head->pos.x + 1) * constants::BLOCK_SIZE, (head->pos.y + 1) * constants::BLOCK_SIZE);
	quad[3].position = sf::Vector2f(head->pos.x * constants::BLOCK_SIZE, (head->pos.y + 1) * constants::BLOCK_SIZE);

	quad[0].color = sf::Color::Yellow;
	quad[1].color = sf::Color::Yellow;
	quad[2].color = sf::Color::Yellow;
	quad[3].color = sf::Color::Yellow;
	head = head->next;
	count++;

	while (head != nullptr) {
		sf::Vertex* quad = &vertices[count * 4];

		quad[0].position = sf::Vector2f(head->pos.x * constants::BLOCK_SIZE, head->pos.y * constants::BLOCK_SIZE);
		quad[1].position = sf::Vector2f((head->pos.x + 1) * constants::BLOCK_SIZE, head->pos.y * constants::BLOCK_SIZE);
		quad[2].position = sf::Vector2f((head->pos.x + 1) * constants::BLOCK_SIZE, (head->pos.y + 1) * constants::BLOCK_SIZE);
		quad[3].position = sf::Vector2f(head->pos.x * constants::BLOCK_SIZE, (head->pos.y + 1) * constants::BLOCK_SIZE);

		quad[0].color = sf::Color::Green;
		quad[1].color = sf::Color::Green;
		quad[2].color = sf::Color::Green;
		quad[3].color = sf::Color::Green;
		head = head->next;
		count++;
	}
}
