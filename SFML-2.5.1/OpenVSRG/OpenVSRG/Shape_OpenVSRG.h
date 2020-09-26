#pragma once

#include <sfml\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <stdarg.h> 
#include <iostream>
#include "Animation.h"
#include "Config.h"

using namespace sf;

class SimFile;

class Shape_OpenVSRG
{
private:
	RectangleShape** ItemsShape;
	RenderWindow* Window;

public:
	int NumberOfShapes;

	Shape_OpenVSRG(RenderWindow * window, int numberofshapes);
	virtual	~Shape_OpenVSRG();
	void SetSingleShapeSize(float x, float y, int shapenumber);
	void SetAllShapeSize(float x, float y);
	void SetSinglePosition(float x, float y, int shapenumber);
	void SetAllPosition(int x, int y, float x_bias, float y_bias, float x_multipler, float y_multipler);
	void RedrawAll();
	void RedrawSingle(int shapenumber);
	void SetTexture(Texture * texture, int shapenumber);
	int getNumberOfShapes();
	RectangleShape** GetWholePTR();
	RenderWindow* getRenderWindow();
	
};

class Shape_Menu :public Shape_OpenVSRG
{
private:
	Texture** Texture_Colletion;

	int ScreenWidth, ScreenHeight;

public:
	Shape_Menu(RenderWindow * window, int elements_count, ...);
	~Shape_Menu();
};

class Song_Select :public Shape_OpenVSRG 
{

private:
	int ScreenWidth, ScreenHeight;

	Font Varsity;
	Text Artist_Title;
	Text Difficulties[16];

	Music music_preview;

	Texture* Banner_T;
	Texture* Artist_Tag_T;

	Sprite* Banner_S;
	Sprite* Artist_Tag_S;

	Color Current_Theme_Color;

	int selected_diff;
	int Diffculties_count;

public:
	Song_Select(RenderWindow * window, Color Theme_Color);
	~Song_Select();

	void setColor(Color color);
	void setSong(SimFile* Sim_File, int soundlevel);

	void RedrawAllWithTexts(SimFile * Sim_File);

	void StopMusicFromPreview();

	void INcrementDifficulty();
	void DEcrementDifficulty();

	String getArtistTitle();

	int getDiffculty();
};


class IN__DE_crementingText
{

private:
	int max, min, actual_value;
	Font Varsity;
	Text IN__DE_crementing_Text;
	RenderWindow *Display;
	Color Current_Theme_Color;
	RectangleShape background;

	String NonNumericValue;

public:
	IN__DE_crementingText(RenderWindow *Display, Color Theme_Color , int min, int max, int actual_value, float Text_Pos_X, float Text_Pos_Y);
	~IN__DE_crementingText();

	void setColor(Color color);
	void incrementTextValue();
	void decrementTextValue();
	int getActualValue();

	void redrawIText();
	void redrawAsNonNumericText();

	void setStringValue(String str);
	String convertIntToKey(int x);

};

class Text_menu_line
{
	std::vector<String> Menu_possitions;
	int Menu_possitions_count;
	
	float value;

public:
	Text_menu_line(int numberOfElements, ...);
	Text_menu_line();
	~Text_menu_line();

	int getTextCount();
	std::vector<String>* getMenuPossitionsArrayPTR();

	void setValue(float x);
	float getValue();
	void INcrementValue(float step);
	void DEcrementValue(float step);

private:

};

class Text_menu
{
	RenderWindow *game;

	Game_loop_config *loop_cofig;

	Color mainThemeColor;

	Font Varsity;
	Text_menu_line lines_colletion[11];
	Text **Visable_elements;

	int lines_count;

	int Text_menu_cursor_X;
	int Text_menu_cursor_Y;
public:
	void INcrementCursorY();
	void DEcrementCursorY();

	void INcrementCursorX();
	void DEcrementCursorX();

	void SetAllPossitions();
	void RedrawAllMenuElements();

	void SetColor(Color color);

	int getXcursor();
	int getYCursor();
	int getLinesCount();

	void DoSomething();

	Text_menu(RenderWindow *ptr, Game_loop_config *loop_cofig);
	~Text_menu();

private:

};

class Selected_Key_PopUp
{
	RenderWindow* menuWindow;
	RectangleShape Backgorund;

	Text Screen_Info1, Screen_Info2, Selected_key;
	Font *font;

	Keyboard::Key definedKey;
	int receptorNumber;

public:
	Selected_Key_PopUp(RenderWindow* game, Font *font, Color color);
	~Selected_Key_PopUp();

	void redrawAll();

	void setKey(Keyboard::Key x, int receptorN);
	void setColor(Color color);
	
	Keyboard::Key getKey();
	int getReceptorNumber();

};
class Main_Menu_Info
{
	RenderWindow* window;

	Texture *Senko_t;
	Texture *GameLogo_t;

	RectangleShape Senko_rect;
	RectangleShape GameLogo_rect;

public:
	Main_Menu_Info(RenderWindow* Window);
	~Main_Menu_Info();

	void redrawInfo();

private:

};



