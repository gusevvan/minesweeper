#include <field.hpp>
#include <SFML/Graphics.hpp>
#include <game.hpp>

namespace msr {

    struct buttonParams {
        int length;
        int width;
        int bombs;
        std::string fieldInfo;
        std::string bombsInfo;
    };

    void Game::run() {
        sf::RenderWindow window(sf::VideoMode(_length * 50, _width * 50), "Minesweeper");
        Field field(_length, _width, _bombs);
        field.show(window);
        window.display();
        int step = 0;
        bool bombsNotOpen = true;
        while (window.isOpen())
        {
            window.clear();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    isOpen = false;
                    window.close();
                }
            }
            if (step < _length * _width - _bombs && bombsNotOpen) {
                if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x >= 0 && event.mouseButton.y >=0 &&
                                                                                        event.mouseButton.x <= 50 * _length && event.mouseButton.y <= 50 * _width) {
                            if (field.isBomb(event.mouseButton.x / 50, event.mouseButton.y / 50)) {
                                field.openBomb(event.mouseButton.x / 50, event.mouseButton.y / 50);
                                bombsNotOpen = false;
                            } else {
                                if (!field.isOpen(event.mouseButton.x / 50, event.mouseButton.y / 50)) {
                                    if (step == 0) {
                                        field.generate(event.mouseButton.x / 50, event.mouseButton.y / 50);
                                    }
                                    step += field.openCell(event.mouseButton.x / 50, event.mouseButton.y / 50);
                            }
                        }
                    }
                }
                field.show((window));
                window.display();
            } else {
                sf::RenderWindow result(sf::VideoMode(300, 100), "End!");
                sf::RectangleShape backGround(sf::Vector2f(300, 100));
                result.draw(backGround);
                sf::Font font;
                font.loadFromFile("bold.ttf");
                sf::Text text;
                text.setFont(font);
                text.setFillColor(sf::Color::Black);
                text.setCharacterSize(24);
                if (bombsNotOpen) {
                    field.openAllBombs();
                    field.show(window);
                    window.display();
                    text.setString("Win!");
                    text.setPosition(140, 30);
                } else {
                    text.setString("Loose!");
                    text.setPosition(115, 30);
                }
                result.draw(text);
                result.display();
                while (result.isOpen()) {
                    sf::Event event;
                    while (result.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            result.close();
                    }
                }
                break;
            }
        }
    }
    void Game::menu() {
        sf::RenderWindow window(sf::VideoMode(1000, 600), "Minesweeper");
        sf::RectangleShape backGroung(sf::Vector2f(1000, 600));
        backGroung.setFillColor(sf::Color(240, 240, 240));
        window.draw(backGroung);
        sf::Font font;
        font.loadFromFile("bold.ttf");
        sf::Text text;
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        sf::RectangleShape button(sf::Vector2f(298, 148));
        button.setOutlineThickness(1.f);
        button.setOutlineColor(sf::Color::Black);
        buttonParams params[2][2];
        params[0][0] = {8, 8, 18, " 8x8 ", " 18 bombs"};
        params[1][0] = {10, 12, 25, "10x12", " 25 bombs"};
        params[0][1] = {20, 15, 40, "20x15", " 40 bombs"};
        params[1][1] = {30, 20, 100, "30x20", "100 bombs"};
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                button.setPosition(120 + i * 420, 100 + j * 200);
                window.draw(button);
                text.setPosition(240 + i * 420, 140 + j * 200);
                text.setString(params[i][j].fieldInfo);
                window.draw(text);
                text.setPosition(210 + i * 420, 180 + j * 200);
                text.setString(params[i][j].bombsInfo);
                window.draw(text);
            }
        }
        window.display();
        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    isOpen = false;
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    bool flag = false;
                    for (int i = 0; i < 2; ++i) {
                        for (int j = 0; j < 2; ++j) {
                            if ((event.mouseButton.x >= (120 + i * 420)) && (event.mouseButton.x <= (420 + i * 420)) &&
                                                            (event.mouseButton.y >= (100 + j * 200)) && (event.mouseButton.y <= (250 + j * 200))) {
                                flag = true;
                                _length = params[i][j].length;
                                _width = params[i][j].width;
                                _bombs = params[i][j].bombs;
                            }
                        }
                    }
                    if (flag)
                    break;
                }
            }
        }
    }

}
