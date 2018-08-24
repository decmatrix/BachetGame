#include "GameMechanic.h"

//функция которая возвращает количество взятых спичек компьютером
int chooseEnemy(int c, int border)
{
	int choose;
	if (c > 1 && c < border + 2) choose = c - 1;
	else if (c > border * 7 && c - border <= 7 * border) choose = c - border * 7;
	else if (c > border * 5 + 2 && c - border <= 5 * border + 2) choose = c - border * 5 - 2;
	else if (c > border * 4 + 1 && c - border <= 4 * border + 1) choose = c - border * 4 - 1;
	else if (c > 3 * border && c - border <= 3 * border) choose = c - 3 * border;
	else if (c != border + 2 && c - border <= border + 2) choose = c - border - 2;
	else 
	//генератор выбора спичек компьютером
	do{
		choose = (random(border) % border) + 1;
	} while (c - choose < 1);

	return choose;
}

//функция которая меняет цвет количества в зависимости от количества
void setColorCount(int c, Text &text)
{
	if (c <= 100 && c > 80)
	{
		text.setColor(Color::Green);
	}
	if (c <= 80 && c > 50)
	{
		text.setColor(Color::Yellow);
	}
	if (c <= 50 && c > 30)
	{
		text.setColor(Color(247, 139, 209));
	}
	if (c <= 30 && c >= 0)
	{
		text.setColor(Color::Red);
	}
}

//функция которая задает случайное число для выбора компбютером
int random(int border)
{
	int random;
	random = (rand() % (border - 1 + 1) + 1);
	return random;
}