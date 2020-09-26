#pragma once

#include <SFML\Graphics.hpp>
using namespace sf;
class Shape_Menu;

class Animation
{
private:
	
public:
	Clock clock;
	float delta_time;
	
	virtual void Update(RectangleShape * rect)=0;
	virtual void Reset(RectangleShape * rect)=0;

};

class Menu_Animation : public Animation
{
private:
	int R, G, B;
	bool RF, GF, BF;

public:
	Menu_Animation();
	Menu_Animation(float x);
	virtual ~Menu_Animation();
	void Update(RectangleShape * rect) override;
	void Reset(RectangleShape * rect) override;
};
class Menu_Colletion_Animation: public Menu_Animation
{
private:
	Shape_Menu* Menu_Colletion;
	Menu_Animation* Animation;
	int cursor;
	int cursor_limit;

public:
	Menu_Colletion_Animation(Shape_Menu* Menu_Colletion);
	virtual ~Menu_Colletion_Animation();

	void setCursor(int x);
	int getCursor();
	void setCursorLimit(int x);
	int getCursorLimit();
	void AnimateAll();
	void IncrementCursor();
	void DecrementCursor();
	Shape_Menu* getMenu_colletionPTR();
};





