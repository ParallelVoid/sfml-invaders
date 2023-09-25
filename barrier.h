#ifndef BARRIER_H
#define BARRIER_H

#include <SFML/Graphics.hpp>
#include "coord.h"

class Barrier {
public:
    Barrier(int x, int y);
    ~Barrier();

    void Update();
    void Draw(sf::RenderWindow& window);
    bool Hit(int x, int y) const;
    int GetHits() const;
    void Damage();

private:

    unsigned int hits;
    unsigned int height;
    unsigned int width;

    sf::RectangleShape rectangle;
    sf::RectangleShape rectangle1;
    sf::RectangleShape rectangle2;
    sf::RectangleShape rectangle3;
};

#endif
