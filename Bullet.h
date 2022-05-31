#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;

class Bullet
{
public:
	Vector2f directie;
	float viteza;
	Sprite forma;
	Texture* textura;
public:
	Bullet();
	Bullet(Texture* _textura, float pos_x, float pos_y, float dir_X, float dir_Y, float _viteza, float angle);
	virtual ~Bullet();


	const FloatRect getBounds() const;

	void initSprite();
	void update();
	void render(RenderTarget* target);
};

#endif 
