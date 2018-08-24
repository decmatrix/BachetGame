//игру сделал студент КПИ ФПМ КВ-73 Соколовский Б.
//1071 строка кода +-

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"

using namespace sf;

//точка запуска игры
int main(void)
{
	//получаем размеры экрана компьютера
	VideoMode mode = VideoMode::getDesktopMode();
	//создаем окно
	RenderWindow window(VideoMode(mode), "BACHET", Style::Fullscreen);
	//прячем курсор ОС
	window.setMouseCursorVisible(false);
	View fixed = window.getView();
	//создаем свой курсор
	Texture cursor;
	cursor.loadFromFile("resource/images/cursor.png");
	Sprite cursorSp(cursor);
	//звук
	bool v = true;

	while (window.isOpen())
	{		
		//вызываем глвное меню игры
		callMenu(window, cursorSp, &v);
		//выбираем сложность
		int diff = chDifficultyGame(window, cursorSp, &v);
		//запускаем игру
		if (diff != 0)
		{
			startGame(diff, window, cursorSp, &v);
		}
	}

	return 0;
}