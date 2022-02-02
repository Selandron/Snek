#pragma once
#include "Ring.cpp"
#include "Direction.cpp"
#include "Constants.h"

class Snek : public sf::Drawable, public sf::Transformable
{
public:
	Snek(unsigned int baseSize, sf::Vector2u headPosition);
	void addRingAtEnd();
	void moveHeadInDirection(Direction direction);
    bool headCollides();
    bool isInSnek(sf::Vector2u position);

    sf::Vector2u getSnekHeadPosition();
private:
	Ring* findLastRing();
    void updateVertices();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
        states.transform *= getTransform(); // getTransform() est définie par sf::Transformable

        // on peut aussi surcharger states.shader ou states.blendMode si nécessaire

        // on dessine le tableau de vertex
        target.draw(vertices, states);
    }

	unsigned int size;
	Ring* head;
	sf::VertexArray vertices;
};

