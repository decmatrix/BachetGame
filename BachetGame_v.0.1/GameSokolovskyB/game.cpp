#include "Game.h"

#include <iostream>
using namespace std;


void startGame(int diffic, RenderWindow &window, Sprite &cursor, bool *v)
{
	//получаем позицию курсора
	cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));

	//путь к фоновой музыке
	string wayMusic = "resource/sounds/game/dif1.ogg";
	//буфер ввода текста
	string s;
	//количество спичек
	int count = 100;
	//количество спичек которое берет враг и игрок
	int takeEnemy = 1;
	int takePlayer = 1;
	//количество возможных взятий спичек
	int borderTake = 10; string borderTakeStr = "10"; char btStr[SIZE];
	//переменные для работы со временем
	Clock clock;
	Time elapsedTime;
	//количество кадров анимации
	int numFramesEnemy = 4;
	int numFramesPlayer = 23;
	int numFramesMatch = 4;
	//время анимации одного кадра
	float animationDurationPlayer = 2;
	float animationDurationEnemy = 1;
	float animationDurationMatch = 1;

	//переменные для работы с логикой игры
	//цикл игры
	int isGame = 1;
	//проверка на возможность ввода
	int enter = 0;
	//проверка на неправильный ввод
	int badVal = 0;
	//проверка на взятия спичек врагом
	int enemyTaken = 0;

	//загружаем шрифты
	Font fontGame;
	fontGame.loadFromFile("resource/fonts/game/fontGame.ttf");

	//создаем текст и задаем начальные параметры
	Text barCountT("", fontGame, 30); createText(barCountT, 12, 45, "Count matches: ", Color::White);
	Text barEnemyT("", fontGame, 30); createText(barEnemyT, 1402, 45, "Enemy take:", Color::White);
	Text barPlayerT("", fontGame, 30); createText(barPlayerT, 702, 990, "Player take:", Color::White);

	Text question("", fontGame, 30); createText(question, 12, 320, "> Enter count matches [1 .. " + borderTakeStr + "]:", Color::White);
	Text answ("", fontGame, 30); createText(answ, 610, 320, "0", Color::Blue);
	Text badValue("", fontGame, 30); createText(badValue, 12, 350, "> You entered bad valume! -_-", Color::Red);
	Text consoleGame("", fontGame, 30); createText(consoleGame, 12, 265, "Bash game console v. 1.0: ", Color::Magenta);
	Text enemyTakeT("", fontGame, 30); createText(enemyTakeT, 12, 350, "> Enemy take!", Color::Cyan);

	Text countT("", fontGame, 30); createText(countT, 350, 45, "100", Color::Green);
	Text enemyT("", fontGame, 30); createText(enemyT, 1702, 45, "0", Color::Red);
	Text playerT("", fontGame, 30); createText(playerT, 1002, 990, "0", Color::Blue);

	Text exit("", fontGame, 30); createText(exit, 1815, 790, "EXIT", Color::Green);

	Text bossName("", fontGame, 30); createText(bossName, 1815, 810, "IMMORTAL KOSTY", Color::Red);

	//создаем спрайты и устанавливаем начальные параметры
	Texture enemy = createTexture("resource/images/game/enemy.png");
	Sprite enemySp(enemy, IntRect(0, 0, 300, 580)); enemySp.setPosition(1075, 20);


	if (diffic == 1)
	{
		enemy = createTexture("resource/images/game/enemy1.png");
		enemySp.setTexture(enemy);
		setEnemy(diffic, enemySp);
	}
	else if (diffic == 2)
	{
		enemy = createTexture("resource/images/game/enemy2.png");
		enemySp.setTexture(enemy);
		setEnemy(diffic, enemySp);
	}
	else if (diffic == 3)
	{
		enemy = createTexture("resource/images/game/enemy3.png");
		enemySp.setTexture(enemy);
		setEnemy(diffic, enemySp);
	}

	Texture player = createTexture("resource/images/game/player.png");
	Sprite playerSp(player, IntRect(0, 0, 500, 440)); playerSp.setPosition(100, 660);

	Texture match = createTexture("resource/images/game/match.png");
	Sprite matchSp(match, IntRect(0, 0, 200, 220)); matchSp.setPosition(570, 25);

	Texture exitGame = createTexture("resource/images/game/exitGame.png");
	Sprite exitGameSp(exitGame); exitGameSp.setPosition(1745, 855);

	Texture voice = createTexture("resource/images/voice.png");

	if (*v == false)
	{
		voice = createTexture("resource/images/noVoice.png");
	}

	Sprite voiceSp(voice); voiceSp.setPosition(0, 1000);



	//установка сложности игры
	setDiff(diffic, &borderTake, &borderTakeStr, &wayMusic, &count, countT, question, &numFramesEnemy, &animationDurationEnemy, bossName);

	//создаем фигуры
	RectangleShape barCount(Vector2f(500, 100));
	createFigure(barCount, 10, 10, Color::Yellow, Color::Black, 15);

	RectangleShape barEnemy(Vector2f(500, 100));
	createFigure(barEnemy, 1400, 10, Color::Yellow, Color::Black, 15);

	RectangleShape barPlayer(Vector2f(500, 100));
	createFigure(barPlayer, 700, 960, Color::Yellow, Color::Black, 15);

	//загружаем музыку и звуковые эффекты
	Music music;
	music.openFromFile(wayMusic);

	SoundBuffer bufferBoom;
	bufferBoom.loadFromFile("resource/sounds/game/boom.ogg");
	Sound boom(bufferBoom);

	SoundBuffer bufferTake;
	bufferTake.loadFromFile("resource/sounds/game/take.ogg");
	Sound take(bufferTake);

	SoundBuffer bufferError;
	bufferError.loadFromFile("resource/sounds/game/error.ogg");
	Sound error(bufferError);


	//воспроизводим музыку и звуки	
	if (*v == true)
	{
		music.play();
	}


	music.setLoop(true);

	boom.play();

	while (isGame)
	{
		//специально для режима 3
		if (diffic == 3)
		{
			srand((unsigned)time(NULL));
			bossName.setColor(Color(rand() % 200, rand() % 200, rand() % 200));
		}

		//устанавливаем позицию курсора
		cursor.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));

		enter = 0;

		if (borderTake >= count)
		{
			borderTake -= 1;

			_itoa(borderTake, btStr, 10);
			borderTakeStr = btStr;
			question.setString("> Enter count matches (1 .. " + borderTakeStr + "):");
		}

		//получаем время
		Time deltaTime = clock.restart();
		elapsedTime += deltaTime;
		//переводим в секунды
		float timeAsSecond = elapsedTime.asSeconds();
		//время на которое умножается кадр анимации
		int animFrameEnemy = static_cast<int>((timeAsSecond / animationDurationEnemy) * numFramesEnemy) % numFramesEnemy;
		int animFramePlayer = static_cast<int>((timeAsSecond / animationDurationPlayer) * numFramesPlayer) % numFramesPlayer;
		int animFrameMatch = static_cast<int>((timeAsSecond / animationDurationMatch) * numFramesMatch) % numFramesMatch;

		//countT.setString(countStr);
		countT.setColor(Color::Green);

		//нажатие кнопки выхода из игры
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//окно выхода
			if (IntRect(1745, 855, 230, 230).contains(Mouse::getPosition(window)))
			{
				//выхход из цикла
				isGame = 0;
				//остановить фоновую музыку
				music.stop();
			}
		}

		//цикл событий
		Event event;
		while (window.pollEvent(event))
		{
			//событие ввода текста
			if (event.type == Event::EventType::TextEntered && enter == 0)
			{
				//вывод
				if (event.KeyPressed == Keyboard::BackSpace && s.size() != 0) 
				{ 
					//буфер вывода
					s.pop_back();  
				}
				//ввод
				else if (event.text.unicode >= 48 && event.text.unicode <= 57)
				{
					//буфер ввода
					s.push_back((char)event.text.unicode);
				}

			}
			if (event.type == Event::EventType::KeyPressed)
			{
				//очистить ввод после нажатия BackSpace
				if (event.key.code == Keyboard::BackSpace)
				{
					//очистка буффера ввода
					s.clear();
				}
			}

			//прекращение ввода (количества спичек)
			if (event.type == Event::EventType::KeyPressed)
			{
				//вкл/выкл музыку
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

				//прекратить ввод после нажатия Enter
				if (event.key.code == Keyboard::Key::Return)
				{
					//следующий ввод разреген
					enter = 1;
					//проверка на ввод
					badVal = 0;
					//установка и очищение буфера ввода
					takePlayer = atoi(s.c_str());
					s.clear();

					//проверка на ввод
					if (takePlayer <= 0 || takePlayer > borderTake)
					{
						error.play();
						badVal = 1;
					}

					//ход сделан
					if (badVal != 1)
					{
						take.play();
					}

					//ход в случае правильного ввода
					if (badVal == 0)
					{
						//ход игрока
						count -= takePlayer;

						//переустонавливаем значения
						setNewString(count, countT);
						setNewString(takePlayer, playerT);

						if (count == 1)
						{
							//игрок победил
							music.stop();
							callWin(fontGame, window, v);
							return;
						}
						else
						{
							//ход врага
							takeEnemy = chooseEnemy(count, borderTake);
							count -= takeEnemy;

							//переустонавливаем значения
							setNewString(count, countT);
							setNewString(takeEnemy, enemyT);

							//враг похожил
							enemyTaken = 1;

							if (count == 1)
							{
								//врга выиграл
								music.stop();
								callLose(fontGame, window, v);
								return;
							}
						}
					}
				}
			}
		}

		//окно можно так же закрыть нажав esc
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			isGame = 0;
		}

		//проверяем количество спичек и меняем цвет в зависимости от количества
		setColorCount(count, countT);

		//анимируем персонажей
		setAnimEnemy(diffic, animFrameEnemy, enemySp);
		playerSp.setTextureRect(IntRect(500 * animFramePlayer, 0, 500, 440));
		matchSp.setTextureRect(IntRect(200 * animFrameMatch, 0, 200, 220));

		//очищаем окно
		window.clear();

		//рисуем фигуры
		window.draw(barCount);
		window.draw(barEnemy);
		window.draw(barPlayer);

		//рисуем текст
		window.draw(barEnemyT);
		window.draw(barPlayerT);
		window.draw(barCountT);

		window.draw(countT);
		window.draw(enemyT);
		window.draw(playerT);

		window.draw(question);

		window.draw(exit);

		answ.setString(s);
		window.draw(answ);

		window.draw(consoleGame);

		window.draw(bossName);

		if (badVal == 1)
		{
			window.draw(badValue);
		}
		else
		{
			if (enemyTaken == 1)
			{
				window.draw(enemyTakeT);
			}
		}

		//рисуем персонажей (спрайты)
		window.draw(enemySp); 
		window.draw(playerSp);

		//рисуем анимированые изображения
		window.draw(matchSp);

		//рисуем обычные изоброжения (спрайты)
		window.draw(exitGameSp);
		window.draw(voiceSp);

		//рисуем курсор
		window.draw(cursor);

		//выводим все на экран
		window.display();
	}
}