#pragma once
#define _USE_MATH_DEFINES

#include <sfml\Graphics.hpp>
#include <cmath>

using namespace sf;

class MenuArtRender
{
private:
	RenderWindow * Window_PTR;
	CircleShape *triangleArray;
	Color currentColor;
	Clock clock;
	Time timeR;
	Vector2f currentPosition;

public:
	MenuArtRender(RenderWindow  *Window_PTR, Color artColor);
	~MenuArtRender();

	void readrawAll();
	void setColor(Color artColor);



};

class MenuLogoRender
{
public:
	MenuLogoRender(RenderWindow * Window_PTR);
	~MenuLogoRender();

	void readrawAll();

private:
	RenderWindow * Window_PTR;
	CircleShape *LogoLayersArray;

	Clock clock;

	Time timeR;
};

class SelectColorWheel
{
private:
	RenderWindow * Window_PTR;
	CircleShape *SelectColorLayersArray;
	Clock clock;
	Time timeR;

	Font *center_info_F;
	Text center_info_T;
	;
	const int colors_count = 24;
	Color *Color_Array[24];
	Color temp_color;

	int cursor;
	int back_cursor_value;

	const float animation_time = 0.333f;

	float radius;
	float circumference_factor;
	float circle_rotation;

public:
	SelectColorWheel(RenderWindow * Window_PTR, Font *def_font);
	~SelectColorWheel();

	void readrawAll();

	int getCursor();
	void incrementCursor();
	void decrementCursor();

	void MoveLeft();
	void MoveRight();
	void RotateWheel();

	void NotSelected(int cur);
	void Selected(int cur);

	Color getSelectedColor();
};

class SongSelectSongsList
{
private:
	struct item
	{
		RectangleShape Rectangle;
		Text item_T;
	};

	item items[13];
	float possition_Y_array[13];
	RenderWindow * WindowPTR;

	Font* font;
	Color default_color;

	Clock animation_clock;
	const Time animation_duration = seconds(0.25f);

	int moving_direction;

	int last, first, selected;

	float step_x;
	float step_y;
	float frame_thicc;
	float character_size;

public:
	const int RectangleCount = 13;

	SongSelectSongsList(RenderWindow *PTR, Font *font, Color default_color);

	void setCenterSong(String CenterText);
	void setString(int index, String Text);
	void setColor(Color color);

	void moveUp(String textUp, String textDown);
	void moveDown(String textUp, String textDown);

	void redrawAll();

	void decrementFirstLast();
	void incrementFirstLast();

};



