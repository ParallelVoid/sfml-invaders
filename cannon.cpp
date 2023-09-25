#include "cannon.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "common.h"

Cannon::Cannon()
    :height(CELL)
    ,width(CELL*2)
    ,x(0)
    ,y(8*CELL) {

}

Cannon::~Cannon() {
    
}

void Cannon::Init() {
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setPosition(x,y);
    rectangle.setFillColor(sf::Color::Transparent);

    rectangle1.setSize(sf::Vector2f(width, height-CELL/3));
    rectangle1.setPosition(x,y+CELL/3);
    rectangle1.setFillColor(sf::Color::Green);

    rectangle2.setSize(sf::Vector2f(width/3, CELL/3));
    rectangle2.setPosition(x+2*CELL/3,y);
    rectangle2.setFillColor(sf::Color::Green);
}

void Cannon::Update() {
    // update the paddle
}

void Cannon::Draw(sf::RenderWindow& window) {
    window.draw(rectangle);
    window.draw(rectangle1);
    window.draw(rectangle2);
}

void Cannon::Reset() {
    //reset when game restarts
}

void Cannon::Move(int dir, sf::RenderWindow& window) {
    if (dir == RIGHT && (x + CELL) < CELL*(XCELLS - 1)) {
        x += CELL/3;
    }
    if (dir == LEFT && x >= NONE) {
        x -= CELL/3;
    }
    rectangle.setPosition(x,y);
    rectangle1.setPosition(x,y+CELL/3);
    rectangle2.setPosition(x+2*CELL/3,y);
}

int Cannon::GetX() {
    return x;
}

int Cannon::GetY() {
    return y;
}


bool Cannon::Hit(int x, int y) const{
    int bx = rectangle.getPosition().x;
    int by = rectangle.getPosition().y;
    if (bx <= x && bx + width >= x && by <= y && by + height >= y) {
        return true;
    }
    return false;
}
