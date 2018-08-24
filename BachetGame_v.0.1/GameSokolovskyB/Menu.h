#ifndef MENU_H
#define MENU_H

/* Библиотека в которой находится меню игры */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Create.h"

using namespace sf;

//функция которая вызывает главное меню игры
void callMenu(RenderWindow &window, Sprite &cursor, bool *v);
//функция в кторой вызывается 
int chDifficultyGame(RenderWindow &window, Sprite &cursor, bool *v);

#endif