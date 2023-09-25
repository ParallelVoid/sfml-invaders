#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "cannon.h"
#include "barrier.h"
#include "bullet.h"
#include "enemy.h"

class Game {
public:
    Game();
    ~Game();

    void Init(sf::RenderWindow& window);
    void Update(int paddleDir, sf::RenderWindow& window); // update AI
    void Render(sf::RenderWindow& window); // draw
    void NewBullet();
    bool IsGameOver();
    void Reset(sf::RenderWindow& window);

private:
    void BuildLvl();
    void Generate();
    void CheckCollision();
    void DeleteEnemy(int e);
    void DeleteBullet(int b);
    void DeleteEBullet(int b);
    void DeleteBarrier(int b);
    void BarrierCollision();
    void CannonCollision();
    void GameOverState();

public:
    const unsigned int width;
    const unsigned int height;
    unsigned int lvl;
    bool gameWon;

private:
    Cannon cannon;
    std::vector <Barrier*> barriers;
    std::vector <Enemy*> enemies;
    std::vector <Bullet*> bullets;
    std::vector <Bullet*> eBullets;
    sf::Font font;
    sf::Text text;
    sf::Music music1;
    sf::Music music2;
    sf::Music music3;
    sf::Music music4;
    sf::Music music5;
    sf::Music music6;
    unsigned int speedCounter;
    unsigned int resetSpeed;
    unsigned int originalSpeed;
    unsigned int score;
    unsigned int highScore;
    int dir;
    bool gameOver;
};

#endif
