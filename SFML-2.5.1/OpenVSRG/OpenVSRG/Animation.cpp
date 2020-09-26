#include "Shape_OpenVSRG.h"
#include "Animation.h"
#include <sfml\Graphics.hpp>
using namespace sf;



#pragma region Menu_Animation

Menu_Animation::Menu_Animation()
{
	delta_time = 0.0f;

	R = 0;
	G = 0;
	B = 0;

	RF = true;
	GF = true;
	BF = true;
}
Menu_Animation::Menu_Animation(float x)
{
	delta_time = x;


	R = 0;
	G = 0;
	B = 0;

	RF = true;
	GF = true;
	BF = true;
}
Menu_Animation::~Menu_Animation()
{
}
void Menu_Animation::Update(RectangleShape * rect)
{
	delta_time += clock.restart().asSeconds();
	if (delta_time >= 0.005f) 
	{
			if (R >= 254)RF = false;
			else if (R == 0)RF = true;

			if (G >= 253)GF = false;
			else if (G == 0)GF = true;

			if (B >= 255)BF = false;
			else if (B == 0)BF = true;

			if (RF)R+=2;
			else R--;

			if (GF)G+=3;
			else G--;
	
			if (BF)B++;
			else B--;
	
			rect->setFillColor(Color(R, G, B));

			//printf(" %f %d %d %d \n", delta_time,R,G,B);

		delta_time = 0;
	}
}
void Menu_Animation::Reset(RectangleShape * rect)
{
	rect->setFillColor(Color(255, 255, 255));
}

#pragma endregion


#pragma region Menu_Colletion_Animation

Menu_Colletion_Animation::Menu_Colletion_Animation(Shape_Menu * Menu_Colletion)
	:Menu_Colletion(Menu_Colletion), 
	Animation(Animation), 
	cursor_limit(Menu_Colletion->getNumberOfShapes()-1),
	cursor(0)
{}
Menu_Colletion_Animation::~Menu_Colletion_Animation()
{
}
void Menu_Colletion_Animation::setCursor(int x)
{
	if(cursor_limit>=x)cursor = x;
}
void Menu_Colletion_Animation::setCursorLimit(int x)
{
	cursor_limit = x;
}
int Menu_Colletion_Animation::getCursorLimit()
{
	return cursor_limit;
}
int Menu_Colletion_Animation::getCursor()
{
	return cursor;
}
void Menu_Colletion_Animation::AnimateAll()
{
	Update(Menu_Colletion->GetWholePTR()[cursor]);
	for (int i = 0; i <=cursor_limit; ++i) 
	{
		if (cursor != i)Reset(Menu_Colletion->GetWholePTR()[i]);
	}
}
void Menu_Colletion_Animation::IncrementCursor()
{
	if (cursor == cursor_limit)cursor = 0;
	else cursor++;
}
void Menu_Colletion_Animation::DecrementCursor()
{
	if (cursor == 0)cursor = cursor_limit;
	else cursor--;
}
Shape_Menu * Menu_Colletion_Animation::getMenu_colletionPTR()
{
	return Menu_Colletion;
}
#pragma endregion