#include "Jucator.h"
#include <iostream>
using namespace sf;
using namespace std;
Jucator::Jucator()
{
	this->initTextura();
	this->initSprite();
	this->initVariabile();
	this->sprite.setOrigin(197.5f, 163.f);
	this->sprite.setPosition(1920 / 2, 1080 / 2);
}

void Jucator::updateAtac()
{
	if (this->vitezaAtac < this->vitezaAtacMaxima)
		this->vitezaAtac += 0.4f;
}

const bool Jucator::poateAtaca()
{
	if (this->vitezaAtac >= this->vitezaAtacMaxima)
	{
		this->vitezaAtac = 0.f;
		return true;
	}
	else return false;
}

void  Jucator::setHp( int value)
{
	hp = value;
}

const int& Jucator::gethp()const
{
	return this->hp;
}

const int& Jucator::gethpmax()const
{
	return this->hpMax;
}

void Jucator::initGUI()
{

}

void Jucator::initVariabile()
{
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->vitMiscare = 5.f;
	this->vitezaAtacMaxima = 15.f;
	this->vitezaAtac = this->vitezaAtacMaxima;
}

Jucator::~Jucator()
{
}

void Jucator::update()
{
	this->updateAtac();

}

void Jucator::randare(RenderTarget& target)
{
	target.draw(this->sprite);
}

void Jucator::initTextura()
{
	this->textura.loadFromFile("spaceship.png");
}

void Jucator::initSprite()
{
	this->sprite.setTexture(this->textura);
	this->sprite.scale(0.6f, 0.6f);
	this->sprite.setPosition(0, 0);
}

void Jucator::miscare(const float dirX, const float dirY)
{
	this->sprite.move(this->vitMiscare * dirX, this->vitMiscare * dirY);
}

const sf::Vector2f& Jucator::getPos() const
{
	return this->sprite.getPosition();
}