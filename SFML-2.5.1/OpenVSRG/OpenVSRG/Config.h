#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Config
{
	int Screen_Height, Screen_Width;
	int HitSounds_Level, Sounds_Level;
	int key_left, key_down, key_up, key_right;

	Color main_theme_color;
	Font *default_font;

public:
	Config();
	~Config();

	std::string getParameterFromConfig(std::string FileLine);

	Color getThemeColor();
	void   setThemeColor(Color color);
	void   setThemeColor(int x, int y, int z);

	int getKey(int receptor_number_0_3);
	int getScreenHeight();
	int getScreenWidth();
	int HitSoundsLevel();
	int SoundsLevel();

	void setScreenHeightAndWidth(int x, int y);
	void setHitSoundLevel(int x);
	void setSoundLevel(int x);
	void setKey(Keyboard::Key x, int receptor_number_0_3);

	Font* getFont();
};

class Game_loop_config
{
public:

	float BPM_speed_multiplicator;
	float Music_Offset;
	float Player_Offset;
	float Note_Receptor_Starting_XPossition;
	float Note_Receptor_Starting_XPossition_step;
	float Receptor_Position;
	float Note_YWay_Lenth;
	float Start_BPM;
	float Note_Scale;
	float Background_Dimm;
	float Game_Speed;
	float Combo_XY_Possition;

	int level_number;

	Game_loop_config();
	~Game_loop_config();

private:

};


