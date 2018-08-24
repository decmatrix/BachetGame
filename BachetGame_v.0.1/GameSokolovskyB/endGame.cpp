#include "EndGame.h"

//функция которая вызывает окно проиграша
void callLose(Font &font, RenderWindow &window, bool *v)
{
	//делает цикл окна пока мы не закроем его кнопкой esc
	int isEnd = 1;

	//массивы символов для текста
	char pressEsc[SIZE];

	//загружаем текстуры
	Text lose("", font, 200); createText(lose, 450, 480, "YOU LOSE", Color::Red);
	Text prEsc("", font, 50); createText(prEsc, 340, 780, "Don't worry, keep calm and press space...", Color::White);
	

	//загруаем музыку
	Music music;
	music.openFromFile("resource/sounds/end/lose.ogg");
	//воспроизводим музыку
	if (*v == true)
	{
		music.play();
	}

	//цикл окна
	while (isEnd)
	{
		//очищает окно
		window.clear();

		//октрыто окно пока не нажмем кнопку  esc 
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			isEnd = 0;
		}

		//вкл/выкл музыку
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::EventType::KeyPressed)
			{
				if (event.key.code == Keyboard::Key::M)
				{
					if (music.getStatus() == music.Paused || music.getStatus() == music.Stopped)
					{
						*v = true;
						music.play();
					}
					else if (music.getStatus() == music.Playing)
					{
						*v = false;
						music.pause();
					}
				}
			}
		}

		//рисуем текст
		window.draw(lose);
		window.draw(prEsc);

		//выводим на экран
		window.display();
	}
}

//функция которая вызывает окно выиграша
void callWin(Font &font, RenderWindow &window, bool *v)
{
	//делает цикл окна пока мы не закроем его кнопкой esc
	int isEnd = 1;

	//загружаем тестуры
	Text win("", font, 200); createText(win, 500, 450, "YOU WIN", Color::Green);
	Text prEsc("", font, 50); createText(prEsc, 740, 780, "Press space...", Color::White);

	//загружаем музыку
	Music music;
	music.openFromFile("resource/sounds/end/win.ogg");
	//воспроизводим музыку
	if (*v == true)
	{
		music.play();
	}

	//цикл окна
	while (isEnd)
	{
		//очищаем окно
		window.clear();

		//октрыто окно пока не нажмем кнопку  esc 
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			isEnd = 0;
		}

		//вкл/выкл музыку
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::EventType::KeyPressed)
			{
				if (event.key.code == Keyboard::Key::M)
				{
					if (music.getStatus() == music.Paused || music.getStatus() == music.Stopped)
					{
						*v = true;
						music.play();
					}
					else if (music.getStatus() == music.Playing)
					{
						*v = false;
						music.pause();
					}
				}
			}
		}

		//рисуем текст
		window.draw(win);
		window.draw(prEsc);

		//выводим на экран
		window.display();
	}
}