#include "stdafx.h"
#include "Receptor.h"


Receptor::Receptor(Texture *left, Texture *down, Texture *up, Texture *right, Texture *Tap_left, Texture *Tap_down, Texture *Tap_up, Texture *Tap_right,Input_Handler *input_handler, RenderWindow *window):left(left), down(down), up(up), right(right), Tap_left(left), Tap_down(down), Tap_up(up), Tap_right(right), input_handler(input_handler), window(window)
{
	left_S	= new Sprite;
	down_S	= new Sprite;
	up_S	= new Sprite;
	right_S = new Sprite;

	left_S->setTexture(*left);
	down_S->setTexture(*down);
	up_S->setTexture(*up);
	right_S->setTexture(*right);

	Tap_left_S	= new Sprite;
	Tap_down_S	= new Sprite;
	Tap_up_S	= new Sprite;
	Tap_right_S = new Sprite;

	Tap_left_S->setTexture(*Tap_left);
	Tap_down_S->setTexture(*Tap_down);
	Tap_up_S->setTexture(*Tap_up);
	Tap_right_S->setTexture(*Tap_right);

}


Receptor::~Receptor()
{
}

void Receptor::SetAllPositions(float start_pos_X, float start_pos_Y, float step)
{
	left_S	->setPosition(start_pos_X, start_pos_Y);
	down_S	->setPosition(start_pos_X + step, start_pos_Y);
	up_S	->setPosition(start_pos_X + step * 2, start_pos_Y);
	right_S	->setPosition(start_pos_X + step * 3, start_pos_Y);

	Tap_left_S->setPosition(start_pos_X, start_pos_Y);
	Tap_down_S->setPosition(start_pos_X + step, start_pos_Y);
	Tap_up_S->setPosition(start_pos_X + step * 2, start_pos_Y);
	Tap_right_S->setPosition(start_pos_X + step * 3, start_pos_Y);
}
void Receptor::Redraw_pattern()
{
	window->draw(*left_S, left);
	window->draw(*down_S, down);
	window->draw(*up_S, up);
	window->draw(*right_S, right);
}

void Receptor::Redraw_flash()
{
	if (input_handler->F_left)window->draw(*Tap_left_S, Tap_left);
	if (input_handler->F_down)window->draw(*Tap_down_S, Tap_down);
	if (input_handler->F_up)window->draw(*Tap_up_S, Tap_up);
	if (input_handler->F_right)window->draw(*Tap_right_S, Tap_right);
}

void Receptor::SetScale(float x, float y)
{
	left_S->setScale(x,y);
	down_S->setScale(x, y);
	up_S->setScale(x, y);
	right_S->setScale(x, y);

	Tap_left_S->setScale(x, y);
	Tap_down_S->setScale(x, y);
	Tap_up_S->setScale(x, y);
	Tap_right_S->setScale(x, y);
}

float Receptor::GetYPossition() const
{
	return left_S->getPosition().y;
}
