#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"

class Bonus : public sf::Drawable, public sf::Transformable
{
public:
    Bonus(unsigned int x, unsigned int y, sf::Color defaultColor);

    void setPosition(unsigned int x, unsigned int y);
    sf::Vector2u getPosition();
protected:
    Bonus() = default;
    void updateVertices();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation de l'entit� -- on la combine avec celle qui a �t� pass�e par l'appelant
        states.transform *= getTransform(); // getTransform() est d�finie par sf::Transformable

        // on peut aussi surcharger states.shader ou states.blendMode si n�cessaire

        // on dessine le tableau de vertex
        target.draw(vertices, states);
    }

    sf::VertexArray vertices;
    sf::Vector2u position;
    sf::Color defaultColor;
};

