#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <field.hpp>

namespace msr {
    void Field::generate(int startX, int startY) {
        srand(time(NULL));
        int freeCells = _length * _width, reservedCells = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if ((startX + i >= 0) && (startX + i < _length) && (startY + j >= 0) && (startY + j < _width)) {
                    ++reservedCells;
                }
            }
        }
        while (_bombs > _length * _width - freeCells) {
            int newBombPosition = rand() % (freeCells - reservedCells), freeBefore = 0;
            for (int i = 0; i < _length; ++i) {
                for (int j = 0; j < _width; ++j) {
                    if (_bombInfo[i][j] != 'B' && freeBefore == newBombPosition && (abs(i - startX) > 1 || abs(j - startY) > 1)) {
                        _bombInfo[i][j] = 'B';
                        ++freeBefore;
                    }
                    if (_bombInfo[i][j] != 'B' && (abs(i - startX) > 1 || abs(j - startY) > 1)) {
                        ++freeBefore;
                    }
                }
            }
            --freeCells;
        }
    }
    bool Field::isBomb(int posX, int posY) {
        return _bombInfo[posX][posY] == 'B';
    }
    bool Field::isOpen(int posX, int posY) {
        return _info[posX][posY] != 'X';
    }
    int Field::openCell(int posX, int posY) {
        int bombNeighbours = 0, newOpened = 1;
        _info[posX][posY] = '0';
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (((posX + i) >= 0) && ((posX + i) < _length) && ((posY + j) >= 0) && ((posY + j) < _width)) {
                    if (_bombInfo[posX + i][posY + j] == 'B') {
                        ++bombNeighbours;
                    }
                }
            }
        }
        if (bombNeighbours == 0) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (((posX + i) >= 0) && ((posX + i) < _length) && ((posY + j) >= 0) && ((posY + j) < _width)) {
                        if (_info[posX + i][posY + j] == 'X') {
                            newOpened += openCell(posX + i, posY + j);
                        }
                    }
                }
            }
        }
        _info[posX][posY] = bombNeighbours + '0';
        return newOpened;
    }
    void Field::openBomb(int posX, int posY) {
        _info[posX][posY] = 'B';
    }
    void Field::show(sf::RenderWindow& window) {
        sf::RectangleShape cell(sf::Vector2f(46.f, 46.f));
        cell.setOutlineThickness(2.f);
        cell.setOutlineColor(sf::Color::Black);
        sf::Text text;
        sf::Font font;
        font.loadFromFile("bold.ttf");
        text.setFont(font);
        text.setCharacterSize(36);
        sf::Texture texture;
        texture.loadFromFile("bomb.png");
        sf::Sprite bomb;
        bomb.setTexture(texture);
        for (int i = 0; i < _length; ++i) {
            for (int j = 0; j < _width; ++j) {
                cell.setPosition(i * 50 + 2, j * 50 + 2);
                if (_info[i][j] == 'X') {
                    cell.setFillColor(sf::Color(204, 204, 204));
                    window.draw(cell);
                } else {
                    cell.setFillColor(sf::Color::White);
                    window.draw(cell);
                    if (_info[i][j] != 'B') {
                        std::string cellValue;
                        cellValue += _info[i][j];
                        text.setString(cellValue);
                        text.setFillColor(sf::Color::Black);
                        text.setPosition(i * 50 + 15, j * 50 + 3);
                        window.draw(text);
                    } else {
                        bomb.setPosition(i * 50 + 2, j * 50 + 2);
                        bomb.setScale(sf::Vector2f(0.07f, 0.07f));
                        window.draw(bomb);
                    }
                }
            }
        }
    }
    void Field::openAllBombs() {
        for (int i = 0; i < _length; ++i) {
            for (int j = 0; j < _width; ++j) {
                if (_bombInfo[i][j] == 'B') {
                    _info[i][j] = 'B';
                }
            }
        }
    }
}
