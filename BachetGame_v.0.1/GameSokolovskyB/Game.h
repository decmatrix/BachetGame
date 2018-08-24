#ifndef GMAE_H
#define GAME_H
/* Библиотека которая содержит функции самой иигры */

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Create.h"
#include "GameMechanic.h"
#include "EndGame.h"

using namespace sf;
using namespace std;

//функция запуска игры
void startGame(int diffic, RenderWindow &window, Sprite &cursor, bool *v);

#endif
