#include "Config.h"


#pragma region Config
Config::Config()
{
	main_theme_color = Color(255, 255, 0);

	default_font = new Font;
	default_font->loadFromFile("Fonts\\varsity_regular.ttf");

	key_left  = Keyboard::Left;
	key_down  = Keyboard::Down;
	key_up	  = Keyboard::Up;
	key_right = Keyboard::Right;
	
	std::string Screen_Height = "Screen_Height:";
	std::string Screen_Width = "Screen_Width:";
	std::string HitSound = "HitSound:";
	std::string Sound = "Sound:";

	std::ifstream file("Config.ini");

	if (!file.is_open())
	{
	}
	else
	{

		std::string File_line;
		while (std::getline(file, File_line))
		{
			if (File_line.find(Screen_Height) != std::string::npos)
			{
				this->Screen_Height = std::stoi(getParameterFromConfig(File_line));
			}
			if (File_line.find(Screen_Width) != std::string::npos)
			{
				this->Screen_Width = std::stoi(getParameterFromConfig(File_line));
			}
			if (File_line.find(HitSound) != std::string::npos)
			{
				this->HitSounds_Level = std::stoi(getParameterFromConfig(File_line));
			}
			if (File_line.find(Sound) != std::string::npos)
			{
				this->Sounds_Level = std::stoi(getParameterFromConfig(File_line));
			}
		}
	}
	file.close();
}
Config::~Config()
{
}

std::string Config::getParameterFromConfig(std::string FileLine)
{
	int pos1, pos2;
	pos1 = FileLine.find(":");
	pos2 = FileLine.find(";");

	return FileLine.substr(pos1 + 1, pos2 - pos1 - 1);
}
Color  Config::getThemeColor()
{
	return main_theme_color;
}
void Config::setThemeColor(Color color)
{
	main_theme_color = color;
}
void Config::setThemeColor(int x, int y, int z)
{
	main_theme_color = Color(x,y,z);
}
int Config::getKey(int receptor_number_0_3)
{
	switch (receptor_number_0_3) 
	{
		case 0: 
		{
			return key_left;

			break;
		}

		case 1:
		{
			return key_down;

			break;
		}

		case 2:
		{
			return key_up;

			break;
		}

		case 3:
		{
			return key_right;

			break;
		}

		default: 
		{
			return 0;
		}
	}
}
int Config::getScreenHeight()
{
	return Screen_Height;
}
int Config::getScreenWidth()
{
	return Screen_Width;
}
int Config::HitSoundsLevel()
{
	return HitSounds_Level;
}
int Config::SoundsLevel()
{
	return Sounds_Level;
}

void Config::setScreenHeightAndWidth(int x, int y)
{
	std::ofstream fileOut("Config.ini", std::ios_base::out);
	fileOut << "Screen_Height:" << y << ";\nScreen_Width:" << x << ";\nHitSound:" << HitSounds_Level << ";\nSound:" << Sounds_Level << ";";
	Screen_Height = y;
	Screen_Width = x;
	fileOut.close();
}
void Config::setHitSoundLevel(int x)
{
	std::ofstream fileOut("Config.ini", std::ios_base::out);
	fileOut << "Screen_Height:" << Screen_Height << ";\nScreen_Width:" << Screen_Width << ";\nHitSound:" << x << ";\nSound:" << Sounds_Level << ";";
	HitSounds_Level = x;
	fileOut.close();
}
void Config::setSoundLevel(int x)
{
	std::ofstream fileOut("Config.ini", std::ios_base::out);
	fileOut << "Screen_Height:" << Screen_Height << ";\nScreen_Width:" << Screen_Width << ";\nHitSound:" << HitSounds_Level << ";\nSound:" << x << ";";
	Sounds_Level = x;
	fileOut.close();
}

void Config::setKey(Keyboard::Key x, int receptor_number_0_3)
{
	switch (receptor_number_0_3)
	{
		case 0:
		{
			key_left = x;
			break;
		}

		case 1:
		{
			key_down = x;
			break;
		}

		case 2:
		{
			key_up = x;
			break;
		}

		case 3:
		{
			key_right = x;
			break;
		}

		default:
		{
			return;
		}
	}
}

Font *Config::getFont()
{
	return default_font;
}

#pragma endregion


#pragma region Game_loop_config

Game_loop_config::Game_loop_config()
{
	BPM_speed_multiplicator = 1.0f;
	Music_Offset = 0.0f;
	Player_Offset = -0.09f;
	Note_Receptor_Starting_XPossition = 0.0f;
	Note_Receptor_Starting_XPossition_step = 150.0f;
	Receptor_Position = 100.0f;
	Note_YWay_Lenth = 1000.0f;
	Start_BPM = 100.0f;
	Note_Scale = 1.7f;
	Background_Dimm = 50.0f;
	Game_Speed = 1.0f;
	Combo_XY_Possition = 0.0f;
 
}

Game_loop_config::~Game_loop_config()
{
}

#pragma endregion



