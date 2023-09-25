#include "game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "common.h"

//#define DEBUG_TEST 1

Game::Game()
    :width(CELL*XCELLS)
    ,height(CELL*YCELLS)
    ,lvl(0)
    ,gameWon(false)
    ,speedCounter(60)
    ,resetSpeed(60)
    ,originalSpeed(60)
    ,score(0)
    ,highScore(0)
    ,dir(LEFT)
    ,gameOver(false) {
    
    }

Game::~Game() {
    for (int i = 0; i < enemies.size(); i++) {
        delete enemies[i];
    }
    for (int j = 0; j < barriers.size(); j++) {
        delete barriers[j];
    }
    for (int k = 0; k < bullets.size(); k++) {
        delete bullets[k];
    }
}

void Game::Init(sf::RenderWindow& window){
    if (!font.loadFromFile("font.ttf")) {
        std::cout<<"Font not loaded"<<std::endl;
    }
    if (!music1.openFromFile("siclone_death.ogg")) { // Death Sound
        std::cout<<"Sound not loaded"<<std::endl;
    }
    if (!music2.openFromFile("siclone_extra_life.ogg")) { // Win Sound
        std::cout<<"Sound not loaded"<<std::endl;
    }
    if (!music3.openFromFile("siclone_shoot.ogg")) { // Shoot Sound
        std::cout<<"Sound not loaded"<<std::endl;
    }
    if (!music4.openFromFile("siclone_shoot_enemy.ogg")) { // Enemy Shoot Sound
        std::cout<<"Sound not loaded"<<std::endl;
    }
    if (!music5.openFromFile("siclone_shoot_enemy.ogg")) { // Explosion Sound
        std::cout<<"Sound not loaded"<<std::endl;
    }
    if (!music6.openFromFile("siclone_shoot_enemy.ogg")) { // Small Explosion Sound
        std::cout<<"Sound not loaded"<<std::endl;
    }

    for (int xSpaces = 0; xSpaces < 2*XCELLS/3; xSpaces++) {
        for (int ySpaces = 0; ySpaces < 4; ySpaces++) {
            Enemy* enemy = new Enemy(CELL*(xSpaces + 1), CELL + ySpaces*CELL/2, 5 - ySpaces);
            enemies.push_back(enemy);
        }
    }
    cannon.Init();
    BuildLvl();
}

void Game::Update(int paddleDir, sf::RenderWindow& window) {
    if (gameOver || gameWon) {
        GameOverState();
        return;
    }
    resetSpeed--;
    if (resetSpeed%10 == 0) {
        for (auto bullet: bullets) {
            bullet->Move(UP);
        }
        for (auto bullet: eBullets) {
            bullet->Move(DOWN);
        } 
    }
    CheckCollision();
    CannonCollision();

    for (int b = 0; b < bullets.size(); b++) {
        if (bullets[b]->GetY() == 0) {
            DeleteBullet(b);
        }
    }

    for (int b = 0; b < eBullets.size(); b++) {
        if (eBullets[b]->GetY() == YCELLS*CELL) {
            DeleteEBullet(b);
        }

    }

    if (eBullets.empty()) {
        int maxY = 0;
        int maxX = enemies[enemies.size()/2] -> GetX();

        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i]->GetY() > maxY) {
                maxY = enemies[i]->GetY();
            }
        }

        Bullet* bullet = new Bullet(maxX, maxY, 1);
        eBullets.push_back(bullet);
        if (!gameOver and !gameWon) {
            music4.play();
        }
    }
    else {
        BarrierCollision();
    }

    if (resetSpeed == 0) {
        if (!enemies.empty()) {
            if (enemies[0]->GetX() == 0) {
                if (dir == LEFT) {
                    dir = DOWN;
                }
                else {
                    dir = RIGHT;
                }
            }

            else if (enemies[enemies.size() - 1]->GetX() == (XCELLS - 1)*CELL) {
                if (dir == RIGHT) {
                    dir = DOWN;
                }
                else {
                    dir = LEFT;
                }
            }
        }

        for (int i = 0; i < enemies.size(); i++) {
            enemies[i]->Move(dir);
            if (enemies[i]->GetY() >= CELL*YCELLS) {
                DeleteEnemy(i);
                gameOver = true;
            }
        }

        resetSpeed = speedCounter;
    }
    cannon.Move(paddleDir, window);
}

void Game::Render(sf::RenderWindow& window) {
    sf::Color colour1 (93, 74, 128);
    sf::Color colour2 (64, 47, 94);
    sf::Color colour3 (137, 129, 153);
    sf::Vertex backgroundgr[] =
        {
                sf::Vertex(sf::Vector2f(0, 0), colour2),
                sf::Vertex(sf::Vector2f(0, CELL*(YCELLS+1)), colour3),
                sf::Vertex(sf::Vector2f(CELL*XCELLS, CELL*(YCELLS+1)), colour3),
                sf::Vertex(sf::Vector2f(CELL*XCELLS, 0), colour2)
        };

    window.draw(backgroundgr, 4, sf::Quads);

    cannon.Draw(window);
    for (auto barrier: barriers) {
        barrier->Draw(window);
    }
    for (auto enemy: enemies) {
        enemy->Draw(window);
    }
    for (auto bullet: bullets) {
        bullet->Draw(window);
    }
    for (auto bullet: eBullets) {
        bullet->Draw(window);
    }

    if(gameWon) {
        if (resetSpeed == 10) {
        text.setFont(font); // font is a sf::Font
        text.setString("FINAL LEVEL COMPLETE!");
        text.setCharacterSize(40); // in pixels, not points!
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition(width/8 + CELL/4, height/3);
        window.draw(text);
        }
        else {
            text.setFont(font); // font is a sf::Font
            text.setString("LEVEL COMPLETE!");
            text.setCharacterSize(40); // in pixels, not points!
            text.setFillColor(sf::Color::Green);
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            text.setPosition(width/8 + CELL/4, height/3);
            window.draw(text);

            text.setString("Press SPACE to Continue");
            text.setCharacterSize(25); // in pixels, not points!
            text.setFillColor(sf::Color::Green);
            text.setPosition(width/8 + CELL/4, height/2 + 64);
            window.draw(text);
        }
    }

    else if (IsGameOver()) {
        text.setFont(font); // font is a sf::Font
        text.setString("GAME OVER");
        text.setCharacterSize(64); // in pixels, not points!
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition(width/6, height/3);
        window.draw(text);

        text.setString("Press SPACE to Play Again");
        text.setCharacterSize(25); // in pixels, not points!
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Underlined);
        text.setPosition(width/8 + CELL/4, height/2 + CELL);
        window.draw(text);

        std::string scoreString;
        std::string tempString;
        scoreString = "Your Score: ";
        tempString = std::to_string(score);
        scoreString = scoreString + tempString + "; High Score: ";
        tempString = std::to_string(highScore);
        scoreString = scoreString + tempString;

        text.setString(scoreString);
        text.setCharacterSize(12); // in pixels, not points!
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Underlined);
        text.setPosition(width/4, height/2 + 2*CELL);
        window.draw(text);
    }
}

void Game::NewBullet() {
    int bulletX = cannon.GetX() + 2*CELL/3 + 10;
    int bulletY = cannon.GetY() - CELL/4;
    Bullet* bullet = new Bullet(bulletX, bulletY, 0);
    bullets.push_back(bullet);
    if (!gameOver || !gameWon){
        music3.play();
    }
}

void Game::BuildLvl() {
#ifdef DEBUG_TEST
    for (int brickX = 0; brickX < 3; brickX++) {
        for (int brickY = 0; brickY < 1; brickY++) {
            brick.Init(CELL*brickX, CELL*brickY/2, brickY);
            bricks.push_back(brick);
        }
    }
    return;
#endif

    int barrierX = CELL;
    for (int i = 0; i < 6; i++) {
        Barrier* barrier = new Barrier(barrierX, CELL*7);
        barriers.push_back(barrier);
        barrierX = barrierX + 2*CELL;
    }
}

bool Game::IsGameOver() {
    return gameOver;
}

void Game::Reset(sf::RenderWindow& window) {
    if (gameWon) {
        speedCounter = speedCounter - 10;
        if (speedCounter == 0) {
            speedCounter = originalSpeed;
            score = 0;
        }
    }
    else {
        speedCounter = originalSpeed;
        score = 0;
    }
    gameOver = false;
    gameWon = false;
    dir = LEFT;
    barriers.clear();
    Init(window);
    resetSpeed = speedCounter;
}

void Game::CheckCollision() {
    for (int b = 0; b < bullets.size(); b++) {
        int bulletX = bullets[b]->GetX();
        int bulletY = bullets[b]->GetY();
        for (int e = 0; e < enemies.size(); e++) {
            int enemyX = enemies[e]->GetX();
            int enemyY = enemies[e]->GetY();
            if (((bulletX >= enemyX) and (bulletX <= (enemyX + CELL/2))) and ((bulletY >= enemyY) and (bulletY <= (enemyY + CELL/2)))) {
                score = score + enemies[e] -> GetPoints();
                if (!gameOver || !gameWon){
                    music6.play();
                }
                DeleteEnemy(e);
                DeleteBullet(b);
            }
        }

        if (enemies.empty()) {
            gameWon = true;
        }
    }
}

void Game::DeleteEnemy(int e) {
    delete enemies[e];
    enemies.erase(e + enemies.begin(), e + enemies.begin() + 1);
}

void Game::DeleteBullet(int b) {
    delete bullets[b];
    bullets.erase(b + bullets.begin(), b + bullets.begin() + 1);
}

void Game::DeleteEBullet(int b) {
    delete eBullets[b];
    eBullets.erase(b + eBullets.begin(), b + eBullets.begin() + 1);
}


void Game::DeleteBarrier(int b) {
    delete barriers[b];
    barriers.erase(b + barriers.begin(), b + barriers.begin() + 1);
}

void Game::BarrierCollision() {
    for (int e = 0; e < eBullets.size(); e++) {   
        int eBulX = eBullets[e] -> GetX();
        int eBulY = eBullets[e] -> GetY(); 

        for (int i = 0; i < barriers.size(); i++) {
            if (barriers[i] -> Hit(eBulX, eBulY)) {
                barriers[i] -> Damage();
                DeleteEBullet(e);
                if (barriers[i] -> GetHits() == 0) {
                    if (!gameOver || !gameWon){
                        music5.play();
                    }
                    DeleteBarrier(i);
                }
            }
        }
    }
}

void Game::CannonCollision() {
    for (int e = 0; e < eBullets.size(); e++) {   
        int eBulX = eBullets[e] -> GetX();
        int eBulY = eBullets[e] -> GetY(); 

        if (cannon.Hit(eBulX, eBulY)) {
            music1.play();
            gameOver = true;
        }
    }
}

void Game::GameOverState() {
    if (gameOver) {
        gameWon = false;
    }
    else {
        gameOver = false;
    }
    for (int i = 0; i < enemies.size(); i++) {
            DeleteEnemy(i);
        }
        for (int i = 0; i < bullets.size(); i++) {
            DeleteBullet(i);
        }
        for (int i = 0; i < eBullets.size(); i++) {
            DeleteEBullet(i);
        }
    if (score > highScore) {
        highScore = score;
    }
}
