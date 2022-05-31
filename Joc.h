#pragma once
#include "Jucator.h"
#include "Bullet.h"
#include <map>
#include "Inamic.h"
#include "SFML/Audio.hpp"
using namespace sf;
class Joc
{
public:
	//fereastra
	RenderWindow* fereastra;

	//jucator
	Jucator* jucator;

	int highscore;
	void initHighscore();

	//systems
	int points;
	//scor
	sf::Font font;
	sf::Text scorText;

	sf::Font fonthp;
	sf::Text hpText;

	sf::Font fontLevel;
	sf::Text textLevel;
	void initScor();
	sf::RectangleShape playerHPBar;
	sf::RectangleShape playerHPBarBack;

	sf::Font highscoreFont;
	sf::Text highScoreText;

	void updateHighScore();

	//Inamici
	float spawnTimer;
	float spawnTimerMax;

	void initPlayerSound();
	//Resurse
	std::map<std::string, sf::Texture*> texturesM;
	std::vector<Bullet*>bullets;
	std::vector<Inamic*> inamici;

	Vector2f BulletDirection();

	sf::Sound sound;
	sf::SoundBuffer shootingBuffer;

	sf::Sound soundHit;
	sf::SoundBuffer hitBuffer;

	sf::Sound damageTaken;
	sf::SoundBuffer damageTakenBuffer;

	sf::Music themeMusic;

	int level;

	void initJucator();
	void InitFereastra();



	Joc();
	~Joc();
	Texture textura;
	Sprite sprite;

	Sprite welcomeS;
	Texture welcomeT;

	void initTexturi();
	void initInamici();

	void rulare();

	void update();
	void randare();
	void updateInput();
	void updatePollEvents();
	void updateInamici();
	void updateCombat();
	void updateGUI();
	void renderGUI();
	void initSystems();
	void updateBGSound();


	void updateBullets();
	bool Delete_bullets(Bullet* bullet);
};

