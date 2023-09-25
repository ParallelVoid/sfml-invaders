#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "coord.h"
#include "common.h"

class Bullet {
public:
    Bullet();
    Bullet(int newX, int newY, int colour);
    ~Bullet();

    void Update();
    void Draw(sf::RenderWindow& window);
    void Move(int dir);
    int GetX();
    int GetY();

private:
    unsigned int radius;
    unsigned int y;
    unsigned int x;

    sf::CircleShape circle;
};

#endif
