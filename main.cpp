#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <iostream>
#include "Snek.h"
#include "Direction.cpp"
#include "Fruit.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

sf::RenderWindow * buildMainWindow() {
    unsigned int width = constants::GRID_WIDTH * constants::BLOCK_SIZE;
    unsigned int height = constants::GRID_HEIGHT * constants::BLOCK_SIZE;
    return new sf::RenderWindow(sf::VideoMode(width, height), "Snek");
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow* window = buildMainWindow();

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Snek snek(5, sf::Vector2u(15, 15));

    Fruit fruit(rand() % 30, rand() % 30);

    Direction direction = Direction::UP;
    sf::Clock clock;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && direction != Direction::DOWN) {
                    direction = Direction::UP;
                }
                if (event.key.code == sf::Keyboard::Down && direction != Direction::UP) {
                    direction = Direction::DOWN;
                }
                if (event.key.code == sf::Keyboard::Right && direction != Direction::LEFT) {
                    direction = Direction::RIGHT;
                }
                if (event.key.code == sf::Keyboard::Left && direction != Direction::RIGHT) {
                    direction = Direction::LEFT;
                }
            }
        }

        if (clock.getElapsedTime() > sf::seconds(0.1)) {
            clock.restart();
            snek.moveHeadInDirection(direction);
            if (snek.headCollides()) {
                std::cout << "PERDU !" << std::endl;
                window->close();
            }
            if (snek.getSnekHeadPosition() == fruit.getPosition()) {
                snek.addRingAtEnd();
                snek.addRingAtEnd();
                sf::Vector2u newPosition(rand() % 30, rand() % 30);
                while (snek.isInSnek(newPosition)) {
                    newPosition = sf::Vector2u(rand() % 30, rand() % 30);
                }
                fruit.setPosition(newPosition.x, newPosition.y);
            }
        }

        window->clear();
        window->draw(snek);
        window->draw(fruit);
        window->display();
    }

    delete window;

    return 0;
}