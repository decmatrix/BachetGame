#ifndef ENDGAME_H
#define ENDGAME_H

/* Библиотека в кторой вызывает функция в зависимости от концовки игры (проиграл или выиграл) */

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Create.h"

using namespace sf;

//функция которая вызывает окно проиграша
void callLose(Font &font, RenderWindow &window, bool *v);
//функция которая вызывает окно выиграша
void callWin(Font &font, RenderWindow &window, bool *v);

#endif
