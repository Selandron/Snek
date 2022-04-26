#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <iostream>
#include "Snek.h"
#include "Direction.cpp"
#include "Fruit.h"
#include "Shrinker.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

sf::RenderWindow * buildMainWindow() {
    unsigned int width = constants::GRID_WIDTH * constants::BLOCK_SIZE + 250;
    unsigned int height = constants::GRID_HEIGHT * constants::BLOCK_SIZE;
    return new sf::RenderWindow(sf::VideoMode(width, height), "Snek");
}

void handleEvents(sf::Window* window, Snek* snek) {
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up && snek->getDirection() != Direction::DOWN) {
                snek->setDirection(Direction::UP);
            }
            else if (event.key.code == sf::Keyboard::Down && snek->getDirection() != Direction::UP) {
                snek->setDirection(Direction::DOWN);
            }
            else if (event.key.code == sf::Keyboard::Right && snek->getDirection() != Direction::LEFT) {
                snek->setDirection(Direction::RIGHT);
            }
            else if (event.key.code == sf::Keyboard::Left && snek->getDirection() != Direction::RIGHT) {
                snek->setDirection(Direction::LEFT);
            }
        }
    }
}

float getSpeed(int size) {
    return log(size + 1) / size + 0.1;
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow* window = buildMainWindow();

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Snek snek(5, sf::Vector2u(15, 15));

    Fruit fruit(rand() % 30, rand() % 30);
    Shrinker shrinker(rand() % 30, rand() % 30);

    sf::Clock clock;
    unsigned long score = 0;
    int multiplier = 1;
    sf::Text scoreText;
    sf::Font font;
    if (!font.loadFromFile("C:/WINDOWS/FONTS/ARIAL.TTF")) {
        return -1;
    }
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(constants::GRID_WIDTH * constants::BLOCK_SIZE, 0);
    scoreText.setString("Score: 0");
    scoreText.setFont(font);
    sf::Text multiplierText;
    multiplierText.setFont(font);
    multiplierText.setString("Multiplier: 1x");
    multiplierText.setPosition(constants::GRID_WIDTH * constants::BLOCK_SIZE, scoreText.getLocalBounds().height + 10);


    while (window->isOpen())
    {
        handleEvents(window, &snek);

        if (clock.getElapsedTime() > sf::seconds(getSpeed(snek.getSize()))) {
            snek.moveSnek();

            if (snek.headCollides()) {
                std::cout << "PERDU ! Score: " << score << std::endl;
                window->close();
            }

            if (snek.getSnekHeadPosition() == fruit.getPosition()) {
                snek.addRingAtEnd();
                snek.addRingAtEnd();
                multiplier += 2;
                multiplierText.setString("Multiplier: " + std::to_string(multiplier) + "x");
                score += 10 * multiplier;
                sf::Vector2u newPosition(rand() % 30, rand() % 30);
                while (snek.isInSnek(newPosition) || shrinker.getPosition() == fruit.getPosition()) {
                    newPosition = sf::Vector2u(rand() % 30, rand() % 30);
                }
                fruit.setPosition(newPosition.x, newPosition.y);
            }

            if (snek.getSnekHeadPosition() == shrinker.getPosition()) {
                snek.deleteRingAtEnd();
                score += 5 * multiplier;
                if (multiplier > 1) {
                    multiplier -= 1;
                    multiplierText.setString("Multiplier: " + std::to_string(multiplier) + "x");
                }
                sf::Vector2u newPosition(rand() % 30, rand() % 30);
                while (snek.isInSnek(newPosition) || shrinker.getPosition() == fruit.getPosition()) {
                    newPosition = sf::Vector2u(rand() % 30, rand() % 30);
                }
                shrinker.setPosition(newPosition.x, newPosition.y);
            }

            score += multiplier * 1;
            scoreText.setString("Score: " + std::to_string(score));
            clock.restart();
        }

        window->clear();
        window->draw(snek);
        window->draw(fruit);
        window->draw(shrinker);
        window->draw(scoreText);
        window->draw(multiplierText);
        window->display();
    }

    delete window;

    return 0;
}