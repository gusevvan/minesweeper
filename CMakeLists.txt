cmake_minimum_required(VERSION 3.15) # Проверка версии CMake.
									 # Если версия установленой программы
									 # старее указаной, произайдёт аварийный выход.

set(PROJECT_NAME mineswipper)	 # имя проекта
project("${PROJECT_NAME}")


set(CMAKE_CXX_STANDARD 17)			 # устанавливаем 17 стандарт языка
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("./inc/")


add_executable("${PROJECT_NAME}" main.cpp
                                        ./inc/game.hpp
                                        ./src/game.cpp
                                        ./inc/field.hpp
                                        ./src/field.cpp)

target_link_libraries("${PROJECT_NAME}" sfml-graphics
                                                        sfml-window
                                                        sfml-system)

file(COPY "assets/bold.ttf" DESTINATION ".")
file(COPY "assets/bomb.png" DESTINATION ".")
