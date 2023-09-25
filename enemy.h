#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "coord.h"
#include "common.h"

class Enemy{
public:
    Enemy(int newX, int newY, int dif);
    ~Enemy();

    void Update();
    void Draw(sf::RenderWindow& window);
    void Move(int dir);
    int GetY();
    int GetX();
    int GetPoints();

private:
    const unsigned int side_length;
    const unsigned int sides;
    unsigned int y;
    unsigned int x;
    unsigned int points;

    sf::CircleShape octagon;
    sf::RectangleShape rectagle;
};

#endif
