#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "common.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(XCELLS*CELL, WINDOW_HEIGHT), "Space Invaders");
    Game game;
    game.Init(window);
    int dir = NONE;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && game.gameWon == true) {
                    dir = NONE;
                    game.lvl++;
                    game.Reset(window);
                }
                else if (event.key.code == sf::Keyboard::Space && game.IsGameOver()) {
                    if (event.key.code == sf::Keyboard::Space) {
                        dir = NONE;
                        game.lvl = 0;
                        game.Reset(window);
                    }
                }
                if (event.key.code == sf::Keyboard::Space) {
                    game.NewBullet();

                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                   dir = RIGHT;
                }
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
                   dir = LEFT;
                }
            }
        }
        
        game.Update(dir, window);
        window.clear();
        game.Render(window);
        window.display();

        dir = NONE;
    }

    return 0;
}