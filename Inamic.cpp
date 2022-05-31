#include "Inamic.h"

void Inamic::initShape()
{
	this->textura.loadFromFile("enemy.png");
	this->sprite.setTexture(textura);
	float randum = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + 0.4;
	this->sprite.setScale(randum, randum);
}

Inamic::Inamic(float pos_x, float pos_y, int level)
{
	this->initVariables();
	this->initShape();
	this->sprite.setPosition(pos_x, pos_y);
	this->sprite.scale(0.6, 0.6);
	this->speed = level;
}

void Inamic::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->hp = 0;
	this->speed = 3.4f;
	this->hpMax = 10;
	this->damage = 1;
	this->points = 5;
}


void Inamic::update()
{

	this->sprite.move(0.f, 3 * (this->sprite.getScale().x * 2 + speed / 3));
}

void Inamic::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

const sf::FloatRect Inamic::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

Inamic::~Inamic()
{

}