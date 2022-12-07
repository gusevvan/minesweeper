#include <field.hpp>
#include <game.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    msr::Game game;
    while (game.isOpen) {
        game.menu();
        if (game.isOpen) {
            game.run();
        }
    }
}

