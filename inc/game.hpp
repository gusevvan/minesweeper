#pragma once
#include <SFML/Graphics.hpp>
#include <field.hpp>

namespace msr {
    class Game {
        private:
            int _length, _width, _bombs;
        public:
            bool isOpen = true;
            void run();
            void menu();
    };

}
