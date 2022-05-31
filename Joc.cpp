#include "Joc.h"
#include "Bullet.h"
#include "SFML/Graphics.hpp"
#include <math.h>
#include <string>
#include <sstream>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
using namespace std;

using namespace sf;

void Joc::updateHighScore()
{
	if (this->points > highscore)
		highscore = this->points;

	ofstream myfile;
	myfile.open("highscore.txt", std::ofstream::out | std::ofstream::trunc);
	myfile << highscore;
	myfile.close();
}

void Joc::initHighscore()
{
	fstream myfile;
	myfile.open("highscore.txt");
	myfile >> highscore;
	std::cout << highscore;
}

void Joc::initPlayerSound()
{
	if (!shootingBuffer.loadFromFile("shooting.wav"))
		std::cout << "Eroare";

	sound.setBuffer(shootingBuffer);
	sound.setPitch(5);
	sound.setVolume(50);

	hitBuffer.loadFromFile("destroy.wav");
	soundHit.setBuffer(hitBuffer);
	soundHit.setVolume(50);

	damageTakenBuffer.loadFromFile("damage.wav");
	damageTaken.setBuffer(damageTakenBuffer);
	damageTaken.setVolume(50);

	themeMusic.openFromFile("theme.wav");
	themeMusic.play();

}

void Joc::updateBGSound()
{
	if (themeMusic.getStatus() == sf::SoundSource::Status::Stopped)
	{
		themeMusic.stop();
		themeMusic.play();
	}
}

void Joc::initSystems()
{
	this->points = 0;
}

Vector2f Joc::BulletDirection()
{
	Vector2f v;
	v.x = sin((float)atan2((float)(Mouse::getPosition(*fereastra).x - this->jucator->sprite.getPosition().x), Mouse::getPosition(*fereastra).y - this->jucator->sprite.getPosition().y)) * 180 / 3.14;
	v.y = cos((float)atan2((float)-(Mouse::getPosition(*fereastra).x - this->jucator->sprite.getPosition().x), Mouse::getPosition(*fereastra).y - this->jucator->sprite.getPosition().y)) * 180 / 3.14;
	return v;
}


using namespace sf;
void Joc::InitFereastra()
{
	this->fereastra = new RenderWindow(VideoMode(1920, 1080), "Space Shooter", Style::Close | Style::Fullscreen);
	this->fereastra->setFramerateLimit(120);
	this->fereastra->setVerticalSyncEnabled(false);
	sf::Cursor cursor;
	if (cursor.loadFromSystem(sf::Cursor::Cross))
		this->fereastra->setMouseCursor(cursor);
	this->welcomeT.loadFromFile("welcome.png");
	this->welcomeS.setTexture(welcomeT);

}

Joc::Joc()
{
	this->InitFereastra();
	this->textura.loadFromFile("bg.jpg");
	this->sprite.setTexture(this->textura);
	this->initScor();
	this->initTexturi();
	this->initSystems();
	this->initJucator();
	this->initInamici();
	this->jucator->setHp(10);
	this->initPlayerSound();
	this->initHighscore();


}

void Joc::initJucator()
{
	this->jucator = new Jucator;
}

Joc::~Joc()
{
	delete this->fereastra;
	delete this->jucator;

	for (auto& i : this->texturesM)
	{
		delete i.second;
	}

	for (auto* i : this->bullets)
	{
		delete i;
	}

	for (auto* i : this->inamici)
	{
		delete i;
	}

}

void Joc::updateGUI()
{

	std::stringstream ss;
	ss << "Points: " << this->points;
	this->scorText.setString(ss.str());

	std::stringstream stringHp;
	stringHp << this->jucator->gethp() * 10;
	this->hpText.setString(stringHp.str());
	this->hpText.setPosition(0, 57);

	std::stringstream stringLevel;
	stringLevel << "Level: " << level;
	this->textLevel.setString(stringLevel.str());
	this->textLevel.setPosition(0, 100);

	float hpPercent = static_cast<float>(this->jucator->gethp()) / this->jucator->gethpmax();
	this->playerHPBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHPBar.getSize().y));

	std::stringstream stringHS;
	stringHS << "Highscore: " << highscore;
	this->highScoreText.setString(stringHS.str());
	this->highScoreText.setPosition(0.f, 125.f);
}

void Joc::renderGUI()
{
	this->fereastra->draw(this->scorText);
	this->fereastra->draw(this->playerHPBarBack);
	this->fereastra->draw(this->playerHPBar);
	this->fereastra->draw(this->hpText);
	this->fereastra->draw(this->textLevel);
	this->fereastra->draw(this->highScoreText);

}


void Joc::initScor()
{
	if (!this->font.loadFromFile("scores2.ttf"))
		std::cout << "Eroare font";

	this->scorText.setFont(this->font);
	this->scorText.setCharacterSize(50);
	this->scorText.setFillColor(sf::Color::White);

	if (!this->fonthp.loadFromFile("scores2.ttf"))
		std::cout << "Eroare font";

	this->hpText.setFont(this->font);
	this->hpText.setCharacterSize(25);
	this->hpText.setFillColor(sf::Color::White);

	this->highscoreFont.loadFromFile("scores2.ttf");
	this->highScoreText.setFont(highscoreFont);
	this->highScoreText.setCharacterSize(30);
	this->highScoreText.setPosition(0.4, 150.f);


	this->textLevel.setFont(this->font);
	this->textLevel.setCharacterSize(30);
	this->textLevel.setFillColor(sf::Color::White);

	//init player GUI
	this->playerHPBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHPBar.setFillColor(sf::Color::Magenta);
	this->playerHPBar.setPosition(0.f, 60.f);
	this->playerHPBarBack = this->playerHPBar;
	this->playerHPBarBack.setFillColor(sf::Color::Black);



	//init level
}

void Joc::updateInamici()
{
	//spawn
	this->spawnTimer += 0.2;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->inamici.push_back(new Inamic(rand() % 1880, -200.f, level));
		this->spawnTimer = 0.f;
	}
	//update
	unsigned counter = 0;
	for (auto* inamic : this->inamici)
	{
		inamic->update();

		if (inamic->getBounds().top > this->fereastra->getSize().y)
		{
			delete this->inamici.at(counter);
			this->inamici.erase(this->inamici.begin() + counter);
			--counter;

			if (this->points < 1)
				this->points = 0;
			else --(this->points);
		}
		else if (inamic->getBounds().intersects(this->jucator->sprite.getGlobalBounds()))
		{
			damageTaken.play();
			delete this->inamici.at(counter);
			this->inamici.erase(this->inamici.begin() + counter);
			if (this->jucator->gethp() < 2)
			{
				this->jucator->setHp(0);
				this->points = 0;
				this->jucator->setHp(10);
				level = 0;
			}
			else
			{
				this->jucator->setHp(this->jucator->gethp() - 1);
			}

		}

		++counter;
	}
}


void Joc::updateCombat()
{
	for (int i = 0; i < this->inamici.size(); i++)
	{
		bool enemy_deleted = false;
		for (int k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->inamici[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				soundHit.play();
				this->points++;
				if (this->points % 10 == 0)
					level++;
				delete this->inamici[i];
				this->inamici.erase(this->inamici.begin() + i);
				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;

			}
		}
	}

}


void  Joc::initInamici()
{
	this->spawnTimerMax = 15.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Joc::updatePollEvents()
{
	Event e;
	while (this->fereastra->pollEvent(e))
	{
		if (e.Event::type == Event::Closed)
			this->fereastra->close();
		if (e.Event::type == Event::KeyPressed)
			if (e.Event::key.code == Keyboard::Escape)
				this->fereastra->close();
		this->jucator->sprite.setRotation((float)atan2((float)-(Mouse::getPosition(*fereastra).x - this->jucator->sprite.getPosition().x), Mouse::getPosition(*fereastra).y - this->jucator->sprite.getPosition().y) * 180 / 3.14 + 180);





	}
}

void Joc::updateInput()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->jucator->miscare(-1.f, 0.f);
		if (this->jucator->getPos().x < 0)
			this->jucator->sprite.setPosition(0.f, this->jucator->getPos().y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->jucator->miscare(1.f, 0.f);
		if (this->jucator->getPos().x > 1920)
			this->jucator->sprite.setPosition(1920.f, this->jucator->getPos().y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->jucator->miscare(0.f, -1.f);
		if (this->jucator->getPos().y < 0)
			this->jucator->sprite.setPosition(this->jucator->getPos().x, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->jucator->miscare(0.f, 1.f);
		if (this->jucator->getPos().y > 1080)
			this->jucator->sprite.setPosition(this->jucator->getPos().x, 1080.f);
	}

	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && this->jucator->poateAtaca())
	{


		this->bullets.push_back(new Bullet(this->texturesM["BULLET"], this->jucator->getPos().x, this->jucator->getPos().y, this->BulletDirection().x, this->BulletDirection().y, 0.4f, atan2((float)-(Mouse::getPosition(*fereastra).x - this->jucator->sprite.getPosition().x), Mouse::getPosition(*fereastra).y - this->jucator->sprite.getPosition().y) * 180 / 3.14));
		sound.play();
	}

}



void Joc::update()
{
	this->updatePollEvents();
	this->updateInput();

	this->jucator->update();
	this->updateBullets();
	this->welcomeS.move(0, -2);
	this->updateInamici();
	this->updateCombat();
	this->updateGUI();
	this->updateBGSound();
	this->updateHighScore();
}

void Joc::randare()
{
	this->fereastra->clear();
	this->fereastra->draw(sprite);
	this->fereastra->draw(welcomeS);
	this->jucator->randare(*this->fereastra);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->fereastra);
	}

	for (auto* inamic : this->inamici)
	{
		inamic->render(this->fereastra);
	}

	this->renderGUI();
	this->fereastra->display();
}

void Joc::rulare()
{
	while (this->fereastra->isOpen())
	{
		this->update();
		this->randare();
	}
}

void Joc::initTexturi()
{
	this->texturesM["BULLET"] = new sf::Texture();
	this->texturesM["BULLET"]->loadFromFile("bullet.png");
}

void Joc::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		if (Delete_bullets(bullet))
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}

		++counter;
	}
}

bool Joc::Delete_bullets(Bullet* bullet)
{
	if (bullet->getBounds().top + bullet->getBounds().height < 0)
		return true;
	if (bullet->getBounds().left + bullet->getBounds().width < 0)
		return true;
	if (bullet->getBounds().left > 1920)
		return true;
	if (bullet->getBounds().top > 1080)
		return true;

	return false;
}