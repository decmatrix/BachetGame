#include "Menu.h"

void callMenu(RenderWindow &window, Sprite &cursor, bool *v)
{
	// загружаем шрифты
	Font fontGame;
	fontGame.loadFromFile("resource/fonts/game/fontGame.ttf");

	//загружаем музыку и звуковые эффекты
	SoundBuffer buffer;
	buffer.loadFromFile("resource/sounds/menu/select.ogg");
	Sound select(buffer);

	Music music;
	music.openFromFile("resource/sounds/menu/bgMenuMusic.ogg");
	
	if (*v == true)
	{
		music.play();
	}
	
	music.setLoop(true);

	//создаем текст
	Text newGame("", fontGame, 50); createText(newGame, 780, 300, "NEW GAME", Color::Black);
	Text aboutGame("", fontGame, 50); createText(aboutGame, 740, 450, "ABOUT GAME", Color::Black);
	Text rulesGame("", fontGame, 50); createText(rulesGame, 740, 600, "GAME RULES", Color::Black);
	Text exitGame("", fontGame, 50); createText(exitGame, 855, 750, "EXIT", Color::Black);

	Text nameGame("", fontGame, 80); createText(nameGame, 745, 70, "BACHET", Color::Blue);

	//загружаем текстуры и спрайты
	Texture bgMenu = createTexture("resource/images/menu/bgMenu.png");
	Sprite bgMenuSp(bgMenu); bgMenuSp.setPosition(0, 0);
	Texture about = createTexture("resource/images/menu/about.png");
	Sprite aboutSp(about);
	Texture rules = createTexture("resource/images/menu/rules.png");
	Sprite rulesSp(rules);
	
	Texture voice = createTexture("resource/images/voice.png");

	if (*v == false)
	{
		voice = createTexture("resource/images/noVoice.png");
	}

	Sprite voiceSp(voice); voiceSp.setPosition(0, 0);

	//получаем номер выбора сложности
	int chooseDiff = 1;

	//переменные для управления логикой меню
	int isMenu = 1;
	int choose = 0;

	//цикл меню
	while (isMenu)
	{
		//устанавливаем позицию курсора
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));

		//обнуляем выбор
		choose = 0; 

		//очищаем экран
		window.clear();

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
						voice = createTexture("resource/images/voice.png");
						music.play();
					}
					else if (music.getStatus() == music.Playing)
					{
						*v = false;
						voice = createTexture("resource/images/noVoice.png");
						music.pause();
					}
				}
			}
		}


		//запоминаем позицию мышки
		if (IntRect(780, 300, 275, 55).contains(Mouse::getPosition(window))) choose = 1;
		if (IntRect(740, 450, 350, 55).contains(Mouse::getPosition(window))) choose = 2;
		if (IntRect(740, 600, 350, 55).contains(Mouse::getPosition(window))) choose = 3;
		if (IntRect(855, 750, 125, 55).contains(Mouse::getPosition(window))) choose = 4;

		//обрабатываем событие нажатие мышки
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (choose == 1) 
			{ 
				select.play();
				music.stop();
				isMenu = 0;
			}
			if (choose == 2) 
			{ 
				select.play(); 
				window.draw(aboutSp);
				window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (choose == 3) 
			{
				select.play(); 
				window.draw(rulesSp); 
				window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (choose == 4)
			{ 
				music.stop();   
				window.close();
				exit(EXIT_SUCCESS); 
			}
		}

		//рисуем части меню
		window.draw(bgMenuSp);
		window.draw(newGame);
		window.draw(aboutGame);
		window.draw(rulesGame);
		window.draw(exitGame);

		window.draw(nameGame);

		window.draw(voiceSp);

		//рисуем курсор
		window.draw(cursor);

		//выводим на экран
		window.display();
	}
}

//функция в кторой вызывается 
int chDifficultyGame(RenderWindow &window, Sprite &cursor, bool *v)
{
	// загружаем шрифты
	Font fontGame;
	fontGame.loadFromFile("resource/fonts/game/fontGame.ttf");

	//загружаем текстуры и спрайты
	Texture bgMenu = createTexture("resource/images/menu/bgMenu.png");
	Sprite bgMenuSp(bgMenu); bgMenuSp.setPosition(0, 0);

	Texture voice = createTexture("resource/images/voice.png");

	if (*v == false)
	{
		voice = createTexture("resource/images/noVoice.png");
	}

	Sprite voiceSp(voice); voiceSp.setPosition(0, 0);

	//создаем текст
	Text chooseDiff("", fontGame, 100); createText(chooseDiff, 420, 70, "CHOOSE DIFFICULTY", Color::Blue);

	Text chEasy("", fontGame, 50); createText(chEasy, 100, 300, "EASY", Color::Green);
	Text easyInf("", fontGame, 30); createText(easyInf, 380, 320, "(100 matches, you may take 1..10 matches)", Color::Black);
	Text chNormal("", fontGame, 50); createText(chNormal, 100, 500, "NORMAL", Color::Yellow);
	Text normalInf("", fontGame, 30); createText(normalInf, 380, 520, "(30 matches, you may take 1..5 matches)", Color::Black);
	Text chHard("", fontGame, 50); createText(chHard, 100, 700, "H.A.R.D.", Color::Red);
	Text hardInf("", fontGame, 30); createText(hardInf, 380, 720, "(25 matches, you may take 1..3 matches. IT'S VERY HARD MODE)", Color::Black);

	//загружаем музыку и звуковые эффекты
	SoundBuffer buffer;
	buffer.loadFromFile("resource/sounds/menu/select.ogg");
	Sound select(buffer);

	Music music;
	music.openFromFile("resource/sounds/menu/bgMenuMusic.ogg");

	if (*v == true)
	{
		music.play();
	}
	music.setLoop(true);

	//пока не выбрали сложность
	int isChoose = 1;

	//возвращаем номер выбора сложности
	int choose = 0;

	//цикл пока не выбрали сложность
	while (isChoose)
	{
		//специально для Кости Н.
		srand((unsigned)time(NULL));
		chHard.setColor(Color(rand() % 200, rand() % 200, rand() % 200));

		//устанавливаем позицию курсора
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));

		//очищаем экран
		window.clear();

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
						voice = createTexture("resource/images/voice.png");
						music.play();
					}
					else if (music.getStatus() == music.Playing)
					{
						*v = false;
						voice = createTexture("resource/images/noVoice.png");
						music.pause();
					}
				}
			}
		}


		//запоминаем позицию мышки
		if (IntRect(100, 300, 140, 55).contains(Mouse::getPosition(window))) choose = 1;
		if (IntRect(100, 500, 180, 55).contains(Mouse::getPosition(window))) choose = 2;
		if (IntRect(100, 700, 177, 55).contains(Mouse::getPosition(window))) choose = 3;

		//обрабатываем событие нажатие мышки
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (choose != 0)
			{
				select.play();
				isChoose = 0;
			}
		}

		//октрыто окно пока не нажмем кнопку  esc 
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			choose = 0;
			isChoose = 0;
		}

		//рисуем
		window.draw(bgMenuSp);
		window.draw(chEasy);
		window.draw(chNormal);
		window.draw(chHard);

		window.draw(easyInf);
		window.draw(normalInf);
		window.draw(hardInf);

		window.draw(chooseDiff);

		window.draw(voiceSp);

		//рисуем курсор
		window.draw(cursor);

		//выводим на экран
		window.display();
	}

	music.stop();
	return  choose;
}