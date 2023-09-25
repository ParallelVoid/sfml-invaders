#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Enemy::Enemy(int newX, int newY, int dif)
    :side_length(CELL/4),
    sides(CELL/8) {
    x = newX;
    y = newY;
    points = dif*5;

    octagon.setRadius(side_length);
    octagon.setPointCount(sides);
    octagon.setPosition(x,y);
    octagon.setFillColor(sf::Color::Blue);
    rectagle.setSize(sf::Vector2f(side_length*2, side_length/2));
    rectagle.setPosition(x,y + side_length*3/2);
    rectagle.setFillColor(sf::Color::Blue);
    }

Enemy::~Enemy() {

}


void Enemy::Update() {
}

void Enemy::Draw(sf::RenderWindow& window) {
    window.draw(octagon);
    window.draw(rectagle);
}

void Enemy::Move(int dir) {
    if (dir == LEFT) {
        x = x - 2;
    }
    else if (dir == RIGHT) {
        x = x + 2;
    }
    else if (dir == DOWN) {
        y = y + CELL/4;
    }
    octagon.setPosition(x,y);
    rectagle.setPosition(x,y + side_length*3/2);
}

int Enemy::GetY() {
    return y;
}

int Enemy::GetX() {
    return x;
}

int Enemy::GetPoints() {
    return points;
}
