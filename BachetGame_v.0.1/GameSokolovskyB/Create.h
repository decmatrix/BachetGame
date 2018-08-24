#ifndef CREATE_H
#define CREATE_H

/* Библиотека в кторой создаются тексты, текстуры, фигуры и прочее */

#include <SFML/Graphics.hpp>
#include <string>

#define SIZE 100

using namespace std;
using namespace sf;

//функция которая создает текст и задает начальные параметры
void createText(Text &text, int pos_x, int pos_y, string strText, static const Color color);
//функция кторая создает текстуры для спрайтов
Texture createTexture(string way);
//функция которая создает фигуру в зависимости от перегруженой функции и задает начальные параметры
void createFigure(RectangleShape &figure, int pos_x, int pos_y, static const Color colorLine, static const Color colorFill, int thicknessLine);
//функции которая задает новую строку
void setNewString(int c, Text &text);
//функция которая устанавливает сложность игры
void setDiff(int diffic, int *border, string *borderStr, string *way, int *c, Text &textСount, Text &text, int *countAnim, float *timeAnim, Text &name);
//функция которая устанавливает врага в зависимости от сложности игры
void setEnemy(int diffic, Sprite &sprite);
//функция которая устанавливает анимацию врага в зависимости от сложности игры
void setAnimEnemy(int diffic, int animFrame, Sprite &sprite);

#endif