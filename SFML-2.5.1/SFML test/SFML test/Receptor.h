#pragma once
#include <sfml\Graphics.hpp>
#include "InputHandling.h"


using namespace sf;

class Receptor
{
	RenderWindow *window;

	Input_Handler *input_handler;

	Texture *left, *down, *up, *right;
	Sprite	*left_S, *down_S, *up_S, *right_S;

	Texture *Tap_left, *Tap_down, *Tap_up, *Tap_right;
	Sprite	*Tap_left_S, *Tap_down_S, *Tap_up_S, *Tap_right_S;


public:
	Receptor(Texture *left, Texture *down, Texture *up, Texture *right, Texture *Tap_left, Texture *Tap_down, Texture *Tap_up, Texture *Tap_right, Input_Handler *input_handler, RenderWindow *window);
	~Receptor();

	void SetAllPositions(float start_pos_X, float start_pos_Y, float step);
	void Redraw_pattern();
	void Redraw_flash();
	void SetScale(float x, float y);
	float GetYPossition()const;
};

