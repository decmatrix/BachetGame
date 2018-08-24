#ifndef GAMEMECHANIC_H
#define GAMEMECHANIC_H

/* Библиотека которая занимается миханикой игры (алгоритмы сложности, цвет количества спичек и т.д.) */

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;

//функция которая возвращает количество взятых спичек компьютером
int chooseEnemy(int c, int border);
//функция которая меняет цвет количества в зависимости от количества
void setColorCount(int c, Text &text);
//функция которая задает случайное число для выбора компбютером
int random(int border);

#endif