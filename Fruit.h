#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"

class Fruit : public sf::Drawable, public sf::Transformable
{
public:
    Fruit(unsigned int x, unsigned int y);

    void setPosition(unsigned int x, unsigned int y);
    sf::Vector2u getPosition();
private:
    void updateVertices();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation de l'entité -- on la combine avec celle qui a été passée par l'appelant
        states.transform *= getTransform(); // getTransform() est définie par sf::Transformable

        // on peut aussi surcharger states.shader ou states.blendMode si nécessaire

        // on dessine le tableau de vertex
        target.draw(vertices, states);
    }

    sf::VertexArray vertices;
    sf::Vector2u position;
};

