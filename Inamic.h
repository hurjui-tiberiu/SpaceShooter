#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Inamic
{
public:
	unsigned pointCount;
	sf::Sprite sprite;
	sf::Texture textura;
	int hp;
	int hpMax;
	int damage;
	int speed;
	int points;

	void initVariables();
	void initShape();
public:
	const sf::FloatRect getBounds() const;
	Inamic(float pos_x, float pos_y, int level);
	virtual ~Inamic();

	void update();
	void render(sf::RenderTarget* target);
};

