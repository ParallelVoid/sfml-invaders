#include "barrier.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "common.h"

Barrier::Barrier(int x, int y)
    :hits(3)
    ,height(CELL/2)
    ,width(CELL) {
    sf::Color colour(5, 161, 46);

    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setPosition(x,y);
    rectangle.setFillColor(sf::Color::Transparent);

    rectangle1.setSize(sf::Vector2f(width, height - height/3));
    rectangle1.setPosition(x,y);
    rectangle1.setFillColor(colour);
    rectangle2.setSize(sf::Vector2f(width/4, height));
    rectangle2.setPosition(x,y);
    rectangle2.setFillColor(colour);
    rectangle3.setSize(sf::Vector2f(width/4, height));
    rectangle3.setPosition(x + width*3/4,y);
    rectangle3.setFillColor(colour);
}

Barrier::~Barrier() {

}


void Barrier::Update() {

}

void Barrier::Draw(sf::RenderWindow& window) {
    window.draw(rectangle);
    window.draw(rectangle1);
    window.draw(rectangle2);
    window.draw(rectangle3);
}

bool Barrier::Hit(int x, int y) const {
    int bx = rectangle.getPosition().x;
    int by = rectangle.getPosition().y;
    if (bx <= x && bx + width >= x && by <= y && by + height >= y) {
        return true;
    }
    return false;
}

int Barrier::GetHits() const {
    return hits;
}

void Barrier::Damage() {
    hits = hits - 1;
}
