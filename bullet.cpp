#include "bullet.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Bullet::Bullet()
    :radius(CELL/8) {

    }

Bullet::Bullet(int newX, int newY, int colour) {
    x = newX;
    y = newY;
    radius = CELL/8;
    circle.setRadius(radius);
    circle.setPosition(x,y);
    if (colour == 0) {
        circle.setFillColor(sf::Color::White);
    }
    else if (colour == 1) {
        circle.setFillColor(sf::Color::Red);
    }
}

Bullet::~Bullet() {

}


void Bullet::Update() {

}

void Bullet::Draw(sf::RenderWindow& window) {
    window.draw(circle);
}

void Bullet::Move(int dir) {
    y = y - 2*dir;
    circle.setPosition(x,y);
}

int Bullet::GetX() {
    return x;
}

int Bullet::GetY() {
    return y;
}
