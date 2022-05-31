#include "Bullet.h"
using namespace sf;


void Bullet::initSprite()
{
	this->forma.setOrigin(68.f, 76.5f);
	this->forma.scale(0.5f, 0.5f);
}


Bullet::Bullet(Texture* _textura, float pos_x, float pos_y, float dir_X, float dir_Y, float _viteza, float angle)
{
	this->forma.setTexture(*_textura);
	this->directie.x = dir_X;
	this->directie.y = dir_Y;
	this->viteza = _viteza;
	this->forma.setPosition(pos_x, pos_y);
	this->initSprite();
	this->forma.setRotation(angle);
	this->forma.rotate(180);

}

void Bullet::update()
{
	this->forma.move(this->viteza * this->directie);
}

void Bullet::render(RenderTarget* target)
{
	target->draw(this->forma);
}

Bullet::~Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
	return this->forma.getGlobalBounds();
}