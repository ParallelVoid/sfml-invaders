#ifndef CANNON_H
#define CANNON_H

#include <SFML/Graphics.hpp>

class Cannon{
public:
    Cannon();
    ~Cannon();

    void Init();
    void Update();
    void Draw(sf::RenderWindow& window);
    void Reset();
    void Move(int dir, sf::RenderWindow& window);
    int GetX();
    int GetY();
    bool Hit(int x, int y) const;

private:
    const unsigned int height;
    const unsigned int width;
    int x;
    int y;

    sf::RectangleShape rectangle;
    sf::RectangleShape rectangle1;
    sf::RectangleShape rectangle2;
};

#endif
