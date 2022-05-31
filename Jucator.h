#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;
class Jucator
{
public:
	Sprite sprite;
	Texture textura;

	float vitezaAtac;
	float vitezaAtacMaxima;
	float vitMiscare;

	int hp;
	int hpMax;

	const int& gethp()const;
	const int& gethpmax() const;
	void initSprite();
	void initTextura();
	void initVariabile();
	void initGUI();
public:
	Jucator();
	~Jucator();
	void setHp(const int hp);
	void looseHp(const int value);

	void update();
	void randare(RenderTarget&);
	void updateAtac();

	const bool poateAtaca();

	const sf::Vector2f& getPos() const;

	void miscare(const float dirX, const float dirY);
};
