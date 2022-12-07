#pragma once
#include<SFML/Graphics.hpp>

namespace msr {
    class Field {
        private:
            int _length = 0;
            int _width = 0;
            int _bombs = 0;
            char** _bombInfo = nullptr;
            char** _info = nullptr;
        public:
            Field(int length, int width, int bombs) {
                if (length <= 3 || width <= 3 || bombs >= (length * width - 9)) {
                    throw(0);
                }
                _length = length;
                _width = width;
                _bombs = bombs;
                _bombInfo = new char *[length];
                _info = new char *[length];
                for (int i = 0; i < length; ++i) {
                    _bombInfo[i] = new char[width];
                    _info[i] = new char[width];
                }
                for (int i = 0; i < length; ++i) {
                    for (int j = 0; j < width; ++j) {
                        _bombInfo[i][j] = '0';
                        _info[i][j] = 'X';
                    }
                }
            }
            void generate(int startX, int startY);
            bool isBomb(int posX, int posY);
            bool isOpen(int posX, int posY);
            int openCell(int posX, int posY);
            void openBomb(int posX, int posY);
            void show(sf::RenderWindow& window);
            void openAllBombs();
            ~Field() {
                for (int i = 0; i < _length; ++i) {
                    delete[] _bombInfo[i];
                    delete[] _info[i];
                }
                delete[] _bombInfo;
                delete[] _info;
            }
    };
}
