#include "Shape_OpenVSRG.h"
#include "SimFile.h"

using namespace sf;

#pragma region Shape_OpenVSRG

Shape_OpenVSRG::Shape_OpenVSRG(RenderWindow * window, int number)
{
	NumberOfShapes = number;
	Window = window;
	ItemsShape = new RectangleShape*[number];

	for (int i = 0; i < number; ++i)
	{
		ItemsShape[i] = new RectangleShape;
	}
}
Shape_OpenVSRG::~Shape_OpenVSRG()
{}

void Shape_OpenVSRG::SetSingleShapeSize(float x, float y, int shapenumber)
{
	if (shapenumber > -1 && shapenumber < NumberOfShapes)
	{
		ItemsShape[shapenumber]->setSize(Vector2f(x, y));
	}
}
void Shape_OpenVSRG::SetAllShapeSize(float x, float y)
{
	for (int i = 0; i <NumberOfShapes; ++i)
	{
		ItemsShape[i]->setSize(Vector2f(x,y));
	}
}
void Shape_OpenVSRG::SetSinglePosition(float x, float y, int shapenumber)
{
	if (shapenumber > -1 && shapenumber < NumberOfShapes)
	{
		ItemsShape[shapenumber]->setPosition(x, y);
	}	
}
void Shape_OpenVSRG::SetAllPosition(int x, int y, float x_bias, float y_bias, float x_multipler, float y_multipler) 
{
	for (int i = 0; i <NumberOfShapes; ++i)
	{
		ItemsShape[i]->setPosition(Vector2f((float)x+ i*x_multipler+x_bias, (float)y+i*y_multipler+y_bias));
	}
}
void Shape_OpenVSRG::RedrawAll() 
{
	for(int i=0;i<NumberOfShapes;++i)
	{
		Window->draw(*ItemsShape[i]);
	}
	
}
void Shape_OpenVSRG::RedrawSingle(int shapenumber) 
{
	if (shapenumber > -1 && shapenumber < NumberOfShapes) 
	{
		Window->draw(*ItemsShape[shapenumber]);
	}
}
void Shape_OpenVSRG::SetTexture(Texture * texture, int shapenumber)
{
	ItemsShape[shapenumber]->setTexture(texture);
}
int Shape_OpenVSRG::getNumberOfShapes()
{
	return NumberOfShapes;
}
RectangleShape ** Shape_OpenVSRG::GetWholePTR()
{
	return ItemsShape;
}

RenderWindow * Shape_OpenVSRG::getRenderWindow()
{
	return Window;
}


#pragma endregion

#pragma region Menu

Shape_Menu::Shape_Menu(RenderWindow* window, int elements_count, ...):Shape_OpenVSRG(window, elements_count)
{
	va_list v1;

	ScreenWidth = window->getSize().x;
	ScreenHeight = window->getSize().y;
	Texture_Colletion = new Texture*[elements_count];

	va_start(v1, elements_count);
	for (int i = 0; i < elements_count; ++i) 
	{
		Texture_Colletion[i] = new Texture;
		Texture_Colletion[i]->loadFromFile(va_arg(v1,String));
		Texture_Colletion[i]->setSmooth(true);
		SetTexture(Texture_Colletion[i], i);
		SetSingleShapeSize(Texture_Colletion[i]->getSize().x, Texture_Colletion[i]->getSize().y, i);
	}
	va_end(v1);

	SetAllPosition(0, 0, ScreenWidth*0.2f, ScreenHeight*0.2f, 0, ScreenHeight*0.10f);
}
Shape_Menu::~Shape_Menu() 
{}

#pragma endregion

#pragma region Song_Select

Song_Select::Song_Select(RenderWindow * window, Color Theme_Color):
	Shape_OpenVSRG(window,1),
	selected_diff(0),
	Current_Theme_Color(Theme_Color)
{
	ScreenWidth = window->getSize().x;
	ScreenHeight = window->getSize().y;

	Banner_S		= new Sprite;
	Artist_Tag_S	= new Sprite;

	Banner_T = new Texture;
		Banner_T->setRepeated(true);
	Artist_Tag_T = new Texture;

	Varsity.loadFromFile("Fonts\\varsity_regular.ttf");

	Artist_Title.setFont(Varsity);
	Artist_Title.setCharacterSize(25);
	Artist_Title.setFillColor(Theme_Color);

	for (int i = 0; i < 16; ++i) 
	{
		Difficulties[i].setFont(Varsity);
		Difficulties[i].setCharacterSize(25);
		Difficulties[i].setFillColor(Theme_Color);
	}
}

Song_Select::~Song_Select()
{
}

void Song_Select::setColor(Color color)
{
	color.a = 255;
	Current_Theme_Color = color;
	Artist_Title.setFillColor(color);
}

void Song_Select::setSong(SimFile * Sim_File, int soundlevel)
{
	Diffculties_count = Sim_File->getDifficultiesCount();

	if (Banner_T->loadFromFile(Sim_File->GetBannerPath()))
	{
		Banner_S->setTexture(*Banner_T, true);
	}
	else 
	{
		Sim_File->SetBannerpath(String("Textures\\GUI\\DefaultNoBanner.png"));
		Banner_T->loadFromFile("Textures\\GUI\\DefaultNoBanner.png");
		Banner_S->setTexture(*Banner_T, true);
	}

	if (Artist_Tag_T->loadFromFile(Sim_File->GetMapperTagPath())) 
	{
		Artist_Tag_S->setTexture(*Artist_Tag_T, true);
	}
	else 
	{
		Sim_File->SetArtistTagpath(String("Textures\\GUI\\DefaultNoTag.png"));
		Artist_Tag_T->loadFromFile("Textures\\GUI\\DefaultNoTag.png");
		Artist_Tag_S->setTexture(*Artist_Tag_T, true);
	}
	
	
	Artist_Title.setPosition(ScreenWidth*0.10f, ScreenHeight*0.10f);
	Banner_S->setPosition(Vector2f(ScreenWidth*0.10f, Artist_Title.getPosition().y+27));
	

	Artist_Tag_S->setPosition(Vector2f(ScreenWidth*0.10f, Artist_Title.getPosition().y + 27));

	float screen_factor_x = ScreenWidth*0.33f / Banner_T->getSize().x;
	float screen_factor_y = ScreenHeight * 0.25f / Banner_T->getSize().y;
	
	if (Banner_T->getSize().y*screen_factor_x >= ScreenHeight*0.25f) 
	{
		float shift_y = (Banner_T->getSize().y*screen_factor_x - ScreenHeight * 0.25f) / 2.0f;
		Banner_S->setTextureRect(IntRect(0.0f,shift_y/ screen_factor_x, ScreenWidth*0.33f/ screen_factor_x, ScreenHeight * 0.25f/ screen_factor_x));
		Banner_S->setScale(screen_factor_x, screen_factor_x);
	}
	else 
	{
		float shift_x = (Banner_T->getSize().x*screen_factor_y - ScreenWidth * 0.33f) / 2.0f;
		Banner_S->setTextureRect(IntRect(shift_x / screen_factor_y,0.0f, ScreenWidth*0.33f / screen_factor_y, ScreenHeight * 0.25f / screen_factor_y));
		Banner_S->setScale(screen_factor_y, screen_factor_y);
	}

	Artist_Title.setString(Sim_File->getSongArtist()+" - "+Sim_File->getSongTitle());

	String* Temp_ptr_S = Sim_File->getDifficulties();

	if (selected_diff >= Sim_File->getDifficultiesCount())selected_diff = Sim_File->getDifficultiesCount() - 1;

	for (int i = 0; i < Sim_File->getDifficultiesCount(); ++i) 
	{
		if (i == selected_diff)Difficulties[i].setFillColor(Color::White);
		Difficulties[i].setString(Temp_ptr_S[i]);
		Difficulties[i].setPosition(Banner_S->getPosition().x, (Banner_S->getPosition().y + ScreenHeight * 0.25f) + Difficulties[0].getCharacterSize()*i);
	}
	
	if (!music_preview.openFromFile(Sim_File->getMusicPath())) 
	{
		std::cout << "error loadding song previev Shape_OpenVSRG.cpp 204\n";
	}
	music_preview.play();
	music_preview.setVolume(soundlevel);
	music_preview.setLoop(true);

}

void Song_Select::RedrawAllWithTexts(SimFile * Sim_File)
{
	getRenderWindow()->draw(*Banner_S);
	getRenderWindow()->draw(*Artist_Tag_S, Artist_Tag_T);
	getRenderWindow()->draw(Artist_Title);

	for (int i = 0; i < Sim_File->getDifficultiesCount(); ++i) 
	{
		if (i == selected_diff)Difficulties[i].setFillColor(Current_Theme_Color);
		else Difficulties[i].setFillColor(Color::White);
		getRenderWindow()->draw(Difficulties[i]);
	}
}

void Song_Select::StopMusicFromPreview()
{
	music_preview.stop();
}

void Song_Select::INcrementDifficulty()
{
	selected_diff++;
	if (selected_diff >= Diffculties_count)selected_diff = Diffculties_count - 1;
}

void Song_Select::DEcrementDifficulty()
{
	selected_diff--;
	if (selected_diff <= 0)selected_diff = 0;
}

String Song_Select::getArtistTitle()
{
	return Artist_Title.getString();
}

int Song_Select::getDiffculty()
{
	return selected_diff;
}

#pragma endregion

#pragma region IN__DE_crementingText

IN__DE_crementingText::IN__DE_crementingText(RenderWindow *Display, Color Theme_Color, int min, int max, int actual_value, float Text_Pos_X, float Text_Pos_Y):
	Display(Display),
	Current_Theme_Color(Theme_Color),
	min(min),
	max(max),
	actual_value(actual_value),
	NonNumericValue(String("Not Defined"))
{
	Varsity.loadFromFile("Fonts\\varsity_regular.ttf");
	IN__DE_crementing_Text.setFont(Varsity);
	IN__DE_crementing_Text.setCharacterSize(72);
	IN__DE_crementing_Text.setFillColor(Current_Theme_Color);
	IN__DE_crementing_Text.setString((String)std::to_string(actual_value));
	IN__DE_crementing_Text.setPosition(Text_Pos_X, Text_Pos_Y);
}

IN__DE_crementingText::~IN__DE_crementingText()
{
}

void IN__DE_crementingText::setColor(Color  color)
{
	color.a = 255;
	Current_Theme_Color = color;
	IN__DE_crementing_Text.setFillColor(color);
}

void IN__DE_crementingText::incrementTextValue()
{

	if (actual_value >= max) {}
	else 
	{
		actual_value++;
	};
}

void IN__DE_crementingText::decrementTextValue()
{
	if (actual_value <= min) {}
	else
	{
		actual_value--;
	};
}

int IN__DE_crementingText::getActualValue()
{
	return actual_value;
}

void IN__DE_crementingText::redrawIText()
{
	IN__DE_crementing_Text.setString((String)std::to_string(actual_value));

	background.setPosition(IN__DE_crementing_Text.getPosition().x, IN__DE_crementing_Text.getPosition().y + IN__DE_crementing_Text.getLocalBounds().height*0.37f);
	background.setSize(Vector2f(IN__DE_crementing_Text.getLocalBounds().width*1.05f, IN__DE_crementing_Text.getLocalBounds().height*1.11f));
	background.setFillColor(Color::Black);

	Display->draw(background);
	Display->draw(IN__DE_crementing_Text);
}

void IN__DE_crementingText::redrawAsNonNumericText()
{
	IN__DE_crementing_Text.setString(NonNumericValue);

	background.setPosition(IN__DE_crementing_Text.getPosition().x, IN__DE_crementing_Text.getPosition().y + IN__DE_crementing_Text.getLocalBounds().height*0.37f);
	background.setSize(Vector2f(IN__DE_crementing_Text.getLocalBounds().width*1.05f, IN__DE_crementing_Text.getLocalBounds().height*1.11f));
	background.setFillColor(Color::Black);

	Display->draw(background);
	Display->draw(IN__DE_crementing_Text);
}

void IN__DE_crementingText::setStringValue(String str)
{
	NonNumericValue = str;
}

String IN__DE_crementingText::convertIntToKey(int x)
{

	switch (x)
	{
	case -1:{return String("Undefined"); break; }
	case 0: {return String("A"); break; }
	case 1: {return String("B"); break; }
	case 2: {return String("C"); break; }
	case 3: {return String("D"); break; }
	case 4: {return String("E"); break; }
	case 5: {return String("F"); break; }
	case 6: {return String("G"); break; }
	case 7: {return String("H"); break; }
	case 8: {return String("I"); break; }
	case 9: {return String("J"); break; }
	case 10:{return String("K"); break; }
	case 11:{return String("L"); break; }
	case 12:{return String("M"); break; }
	case 13:{return String("N"); break; }
	case 14:{return String("O"); break; }
	case 15:{return String("P"); break; }
	case 16:{return String("Q"); break; }
	case 17:{return String("R"); break; }
	case 18:{return String("S"); break; }
	case 19:{return String("T"); break; }
	case 20:{return String("U"); break; }
	case 21:{return String("V"); break; }
	case 22:{return String("W"); break; }
	case 23:{return String("X"); break; }
	case 24:{return String("Y"); break; }
	case 25:{return String("Z"); break; }
	case 26:{return String("Num0"); break; }
	case 27:{return String("Num1"); break; }
	case 28:{return String("Num2"); break; }
	case 29:{return String("Num3"); break; }
	case 30:{return String("Num4"); break; }
	case 31:{return String("Num5"); break; }
	case 32:{return String("Num6"); break; }
	case 33:{return String("Num7"); break; }
	case 34:{return String("Num8"); break; }
	case 35:{return String("Num9"); break; }
	case 36:{return String("Escape"); break; }
	case 37:{return String("LControl"); break; }
	case 38:{return String("LShift"); break; }
	case 39:{return String("LAlt"); break; }
	case 40:{return String("LSystem"); break; }
	case 41:{return String("RControl"); break; }
	case 42:{return String("RShift"); break; }
	case 43:{return String("RAlt"); break; }
	case 44:{return String("RSystem"); break; }
	case 45:{return String("Menu"); break; }
	case 46:{return String("LBracket"); break; }
	case 47:{return String("RBracket"); break; }
	case 48:{return String("Semicolon"); break; }
	case 49:{return String("Comma"); break; }
	case 50:{return String("Period"); break; }
	case 51:{return String("Quote"); break; }
	case 52:{return String("Slash"); break; }
	case 53:{return String("Backslash"); break; }
	case 54:{return String("Tilde"); break; }
	case 55:{return String("Equal"); break; }
	case 56:{return String("Hyphen"); break; }
	case 57:{return String("Space"); break; }
	case 58:{return String("Enter"); break; }
	case 59:{return String("Backspace"); break; }
	case 60:{return String("Tab	"); break; }
	case 61:{return String("PageUp"); break; }
	case 62:{return String("PageDown"); break; }
	case 63:{return String("End"); break; }
	case 64:{return String("Home"); break; }
	case 65:{return String("Insert"); break; }
	case 66:{return String("Delete"); break; }
	case 67:{return String("Add"); break; }
	case 68:{return String("Subtract"); break; }
	case 69:{return String("Multiply"); break; }
	case 70:{return String("Divide"); break; }
	case 71:{return String("Left"); break; }
	case 72:{return String("Right"); break; }
	case 73:{return String("Up"); break; }
	case 74:{return String("Down"); break; }
	case 75:{return String("Numpad0"); break; }
	case 76:{return String("Numpad1"); break; }
	case 77:{return String("Numpad2"); break; }
	case 78:{return String("Numpad3"); break; }
	case 79:{return String("Numpad4"); break; }
	case 80:{return String("Numpad5"); break; }
	case 81:{return String("Numpad6"); break; }
	case 82:{return String("Numpad7"); break; }
	case 83:{return String("Numpad8"); break; }
	case 84:{return String("Numpad9"); break; }
	case 85:{return String("F1"); break; }
	case 86:{return String("F2"); break; }
	case 87:{return String("F3"); break; }
	case 88:{return String("F4"); break; }
	case 89:{return String("F5"); break; }
	case 90:{return String("F6"); break; }
	case 91:{return String("F7"); break; }
	case 92:{return String("F8"); break; }
	case 93:{return String("F9"); break; }
	case 94:{return String("F10"); break; }
	case 95:{return String("F11"); break; }
	case 96:{return String("F12"); break; }
	case 97:{return String("F13"); break; }
	case 98:{return String("F14"); break; }
	case 99:{return String("F15"); break; }
	case 100: {return String("Pause"); break; }
	default: return String("Error");
	}
}

#pragma endregion

#pragma region Text_menu_line

Text_menu_line::Text_menu_line(int numberOfElements, ...)
{
	va_list v1;
	Menu_possitions_count = numberOfElements;

	va_start(v1, numberOfElements);
	for (int i = 0; i < numberOfElements; ++i)
	{
		Menu_possitions.push_back( va_arg(v1, String));
	}
	va_end(v1);
}

Text_menu_line::Text_menu_line()
{
}

Text_menu_line::~Text_menu_line()
{
}

int Text_menu_line::getTextCount()
{
	return Menu_possitions_count;
}

std::vector<String>* Text_menu_line::getMenuPossitionsArrayPTR()
{
	return &Menu_possitions;
}

void Text_menu_line::setValue(float x)
{
	value = x;
}

float Text_menu_line::getValue()
{
	return value;
}

void Text_menu_line::INcrementValue(float step)
{
	value += step;
}

void Text_menu_line::DEcrementValue(float step)
{
	value -= step;
}

#pragma endregion

#pragma region Text_menu

int Text_menu::getXcursor()
{
	return Text_menu_cursor_X;
}

int Text_menu::getYCursor()
{
	return Text_menu_cursor_Y;
}

int Text_menu::getLinesCount()
{
	return lines_count;
}

void Text_menu::DoSomething()
{
	switch (Text_menu_cursor_Y)
	{
	case 0: 
	{
		switch (Text_menu_cursor_X)
		{
		case 2:
		{
			loop_cofig->Player_Offset += 1.0f;
		}break;
		case 3:
		{
			loop_cofig->Player_Offset -= 1.0f;
		}break;
		case 4:
		{
			loop_cofig->Player_Offset += 0.10f;
		}break;
		case 5:
		{
			loop_cofig->Player_Offset -= 0.10f;
		}break;
		case 6:
		{
			loop_cofig->Player_Offset += 0.010f;
		}break;
		case 7:
		{
			loop_cofig->Player_Offset -= 0.010f;
		}break;


		default:break;
		}
	}break;
	case 1:
	{
		switch (Text_menu_cursor_X)
		{
		case 2:
		{
			loop_cofig->BPM_speed_multiplicator += 1.0f;
		}break;
		case 3:
		{
			loop_cofig->BPM_speed_multiplicator -= 1.0f;
		}break;
		case 4:
		{
			loop_cofig->BPM_speed_multiplicator += 0.10f;
		}break;
		case 5:
		{
			loop_cofig->BPM_speed_multiplicator -= 0.10f;
		}break;
		case 6:
		{
			loop_cofig->BPM_speed_multiplicator += 0.010f;
		}break;
		case 7:
		{
			loop_cofig->BPM_speed_multiplicator -= 0.010f;
		}break;


		default:break;
		}
	}break;
	case 2:
	{
		switch (Text_menu_cursor_X)
		{
		case 2:
		{
			loop_cofig->Note_Scale += 1.0f;
		}break;
		case 3:
		{
			loop_cofig->Note_Scale -= 1.0f;
		}break;
		case 4:
		{
			loop_cofig->Note_Scale += 0.10f;
		}break;
		case 5:
		{
			loop_cofig->Note_Scale -= 0.10f;
		}break;
		case 6:
		{
			loop_cofig->Note_Scale += 0.010f;
		}break;
		case 7:
		{
			loop_cofig->Note_Scale -= 0.010f;
		}break;


		default:break;
		}
	}break;
	case 3:
	{
		switch (Text_menu_cursor_X)
		{
		case 2:
		{
			loop_cofig->Background_Dimm = 0.0f;
		}break;
		case 3:
		{
			loop_cofig->Background_Dimm = 20.0f;
		}break;
		case 4:
		{
			loop_cofig->Background_Dimm = 40.0f;
		}break;
		case 5:
		{
			loop_cofig->Background_Dimm = 60.0f;
		}break;
		case 6:
		{
			loop_cofig->Background_Dimm = 80.0f;
		}break;
		case 7:
		{
			loop_cofig->Background_Dimm = 100.0f;
		}break;


		default:break;
		}
	}break;
	case 4:
	{
		switch (Text_menu_cursor_X)
		{
		case 2:
		{
			loop_cofig->Game_Speed += 1.0f;
		}break;
		case 3:
		{
			if (loop_cofig->Game_Speed <= 1.1f) 
			{
				loop_cofig->Game_Speed = 0.1f;
			}
			else loop_cofig->Game_Speed -= 1.0f;
		}break;
		case 4:
		{
			loop_cofig->Game_Speed += 0.10f;
		}break;
		case 5:
		{
			if (loop_cofig->Game_Speed <= 0.2f)
			{
				loop_cofig->Game_Speed = 0.1f;
			}
			else loop_cofig->Game_Speed -= 0.10f;
		}break;
		case 6:
		{
			loop_cofig->Game_Speed += 0.010f;
		}break;
		case 7:
		{
			if (loop_cofig->Game_Speed <= 0.11f)
			{
				loop_cofig->Game_Speed = 0.1f;
			}
			else loop_cofig->Game_Speed -= 0.01f;
		}break;


		default:break;
		}
	}break;

	default:break;
	}

}

Text_menu::Text_menu(RenderWindow *ptr, Game_loop_config *loop_cofig)
	:game(ptr),
	loop_cofig(loop_cofig)
{
	Text_menu_cursor_X = 2;
	Text_menu_cursor_Y = 0;

	mainThemeColor - Color::Yellow;

	Varsity.loadFromFile("Fonts\\varsity_regular.ttf");

	lines_count = 6;

	lines_colletion[0] = Text_menu_line(8, (String)"Offset:                   ", (String)"          ",(String)"+1", (String)"-1", (String)"+0.1", (String)"-0.1", (String)"+0.01", (String)"-0.01");
	lines_colletion[1] = Text_menu_line(8, (String)"Xmode:                    ", (String)"          ",(String)"+1", (String)"-1", (String)"+0.1", (String)"-0.1", (String)"+0.01", (String)"-0.01");
	//lines_colletion[2] = Text_menu_line(8, (String)"Set Receptor X Possition: ", (String)"          ",(String)"default", (String)"center", (String)"+10", (String)"-10", (String)"+100", (String)"-100");
	//lines_colletion[3] = Text_menu_line(6, (String)"Set Receptor Step:        ", (String)"          ",(String)"+10", (String)"-10", (String)"+100", (String)"-100");
	//lines_colletion[4] = Text_menu_line(7, (String)"Set Receptor Y Possition: ", (String)"          ",(String)"default", (String)"+10", (String)"-10", (String)"+100", (String)"-100");
	//lines_colletion[5] = Text_menu_line(8, (String)"Set Receptor Possition:   ", (String)"          ",(String)"default", (String)"center", (String)"+10", (String)"-10", (String)"+100", (String)"-100");
	//lines_colletion[6] = Text_menu_line(8, (String)"Set Receptor X Possition: ", (String)"          ",(String)"default", (String)"center", (String)"+10", (String)"-10", (String)"+100", (String)"-100");
	lines_colletion[2] = Text_menu_line(8, (String)"Notescale:                ", (String)"          ",(String)"+1", (String)"-1", (String)"+0.1", (String)"-0.1", (String)"+0.01", (String)"-0.01");
	lines_colletion[3] = Text_menu_line(8, (String)"Bg brightness:            ",(String)"          ", (String)"0%", (String)"20%", (String)"40%", (String)"60%", (String)"80%", (String)"100%");
	lines_colletion[4] = Text_menu_line(8, (String)"Speed mode:               ", (String)"          ",(String)"+1", (String)"-1", (String)"+0.1", (String)"-0.1", (String)"+0.01", (String)"-0.01");
	//lines_colletion[5] = Text_menu_line(9, (String)"Combo Possition:         ", (String)"          ",(String)"default", (String)"hidden", (String)"+10", (String)"-110", (String)"-0.1", (String)"+100", (String)"-100");
	lines_colletion[5] = Text_menu_line(3, (String)"", (String)"",(String)"GO!!");

}

Text_menu::~Text_menu()
{
}

void Text_menu::INcrementCursorY()
{
	Text_menu_cursor_Y++;
	if (Text_menu_cursor_Y >= lines_count)Text_menu_cursor_Y = 0;
	if (lines_colletion[Text_menu_cursor_Y].getTextCount() <= Text_menu_cursor_X)Text_menu_cursor_X = lines_colletion[Text_menu_cursor_Y].getTextCount() - 1;
}

void Text_menu::DEcrementCursorY()
{
	Text_menu_cursor_Y--;
	if (Text_menu_cursor_Y < 0)Text_menu_cursor_Y = lines_count - 1;
	if (lines_colletion[Text_menu_cursor_Y].getTextCount() <= Text_menu_cursor_X)Text_menu_cursor_X = lines_colletion[Text_menu_cursor_Y].getTextCount() - 1;
}

void Text_menu::INcrementCursorX()
{
	Text_menu_cursor_X++;
	if (Text_menu_cursor_X >= lines_colletion[Text_menu_cursor_Y].getTextCount())Text_menu_cursor_X = 2;
}

void Text_menu::DEcrementCursorX()
{
	Text_menu_cursor_X--;
	if (Text_menu_cursor_X < 2)Text_menu_cursor_X = lines_colletion[Text_menu_cursor_Y].getTextCount() - 1;
}


void Text_menu::SetAllPossitions()
{
	float character_size = 0.03f*game->getSize().y;

	Visable_elements = new Text*[lines_count];
	for (int i = 0; i<lines_count; ++i)
	{
		Visable_elements[i] = new Text[lines_colletion[i].getTextCount()];
	}

	for (int i = 0; i < lines_count; ++i)
	{
		for (int j = 0; j < lines_colletion[i].getTextCount(); ++j)
		{

			Visable_elements[i][j].setFont(Varsity);
			Visable_elements[i][j].setCharacterSize(character_size);
			Visable_elements[i][j].setString(lines_colletion[i].getMenuPossitionsArrayPTR()->operator[](j));

			if (j == 0)Visable_elements[i][j].setPosition(0.0f, ((float)i / lines_count)*(game->getSize().y*0.8f));
			else Visable_elements[i][j].setPosition(Visable_elements[i][0].getCharacterSize()*10 +((float)j-1)/ lines_colletion[i].getTextCount()*(game->getSize().x*0.9f), ((float)i / lines_count)*(game->getSize().y*0.8f));
	
		}
	}
}

void Text_menu::RedrawAllMenuElements()
{
	std::string temp;

	temp = std::to_string(loop_cofig->Player_Offset);
	temp = temp.substr(0, 6);
	Visable_elements[0][1].setString(temp);

	temp = std::to_string(loop_cofig->Start_BPM*loop_cofig->BPM_speed_multiplicator);
	temp = temp.substr(0,6);
	Visable_elements[1][1].setString(temp);

	temp = std::to_string(loop_cofig->Note_Scale);
	temp = temp.substr(0, 4);
	Visable_elements[2][1].setString(temp);

	temp = std::to_string((int)loop_cofig->Background_Dimm);
	Visable_elements[3][1].setString(temp + "%");

	temp = std::to_string(loop_cofig->Game_Speed);
	temp = temp.substr(0, 4);
	Visable_elements[4][1].setString(temp);

	for (int i = 0; i < lines_count; ++i)
	{
		for (int j = 0; j < lines_colletion[i].getTextCount(); ++j)
		{
			
			if(Text_menu_cursor_X==j&&Text_menu_cursor_Y==i)Visable_elements[i][j].setFillColor(mainThemeColor);
			else  Visable_elements[i][j].setFillColor(Color::White); 


			game->draw(Visable_elements[i][j]);
		}
	}
}

void Text_menu::SetColor(Color color)
{
	mainThemeColor = color;
}


#pragma endregion

#pragma region Selected_Key_PopUp

Selected_Key_PopUp::Selected_Key_PopUp(RenderWindow* game, Font *font, Color color):
	menuWindow(game),
	font(font),
	definedKey(Keyboard::Key::Unknown),
	receptorNumber(0)
{
	Backgorund.setSize(Vector2f(menuWindow->getSize().x, menuWindow->getSize().y));
	Backgorund.setPosition(0.0f, 0.0f);
	Backgorund.setFillColor(Color(0, 0, 0, 240));

	float character_size = menuWindow->getSize().y / 10.0f;

	Screen_Info1.setFont(*font);
	Screen_Info1.setString(String("Select key"));
	Screen_Info1.setFillColor(color);
	Screen_Info1.setCharacterSize(character_size);
	Screen_Info1.setPosition(menuWindow->getSize().x / 2.0f - Screen_Info1.getLocalBounds().width / 2.0f, 0);

	Screen_Info2.setFont(*font);
	Screen_Info2.setString(String("Press Enter to accept or ESC to cancel"));
	Screen_Info2.setFillColor(color);
	Screen_Info2.setCharacterSize(character_size/3.0f);
	Screen_Info2.setPosition(menuWindow->getSize().x / 2.0f - Screen_Info2.getLocalBounds().width / 2.0f, menuWindow->getSize().y-Screen_Info2.getLocalBounds().height*2.0f);

	Selected_key.setFont(*font);
	Selected_key.setString(String("Press Enter to accept or ESC to cancel"));
	Selected_key.setCharacterSize(character_size );
	Selected_key.setFillColor(color);
	Selected_key.setPosition(menuWindow->getSize().x / 2.0f - Screen_Info2.getLocalBounds().width /4.0f, menuWindow->getSize().y/2.0f - Screen_Info2.getLocalBounds().height*2.0f);
}

Selected_Key_PopUp::~Selected_Key_PopUp()
{
}

void Selected_Key_PopUp::redrawAll()
{
	menuWindow->draw(Backgorund);
	menuWindow->draw(Screen_Info1);
	menuWindow->draw(Screen_Info2);
	menuWindow->draw(Selected_key);
}

void Selected_Key_PopUp::setKey(Keyboard::Key x, int receptorN)
{
	definedKey = x;
	receptorNumber = receptorN;

	switch (x) 
	{
		case -1: {Selected_key.setString("Undefined	"); break; }
		case 0 : {Selected_key.setString("A			");break;}
		case 1 : {Selected_key.setString("B			"); break; }
		case 2 : {Selected_key.setString("C			"); break; }
		case 3 : {Selected_key.setString("D			"); break; }
		case 4 : {Selected_key.setString("E			"); break; }
		case 5 : {Selected_key.setString("F			"); break; }
		case 6 : {Selected_key.setString("G			"); break; }
		case 7 : {Selected_key.setString("H			"); break; }
		case 8 : {Selected_key.setString("I			"); break; }
		case 9 : {Selected_key.setString("J			"); break; }
		case 10 : {Selected_key.setString("K		"); break; }
		case 11 : {Selected_key.setString("L		"); break; }
		case 12 : {Selected_key.setString("M		"); break; }
		case 13 : {Selected_key.setString("N		"); break; }
		case 14 : {Selected_key.setString("O		"); break; }
		case 15 : {Selected_key.setString("P		"); break; }
		case 16 : {Selected_key.setString("Q		"); break; }
		case 17 : {Selected_key.setString("R		"); break; }
		case 18 : {Selected_key.setString("S		"); break; }
		case 19 : {Selected_key.setString("T		"); break; }
		case 20 : {Selected_key.setString("U		"); break; }
		case 21 : {Selected_key.setString("V		"); break; }
		case 22 : {Selected_key.setString("W		"); break; }
		case 23 : {Selected_key.setString("X		"); break; }
		case 24 : {Selected_key.setString("Y		"); break; }
		case 25 : {Selected_key.setString("Z		"); break; }
		case 26 : {Selected_key.setString("Num0		"); break; }
		case 27 : {Selected_key.setString("Num1		"); break; }
		case 28 : {Selected_key.setString("Num2		"); break; }
		case 29 : {Selected_key.setString("Num3		"); break; }
		case 30 : {Selected_key.setString("Num4		"); break; }
		case 31 : {Selected_key.setString("Num5		"); break; }
		case 32 : {Selected_key.setString("Num6		"); break; }
		case 33 : {Selected_key.setString("Num7		"); break; }
		case 34 : {Selected_key.setString("Num8		"); break; }
		case 35 : {Selected_key.setString("Num9		"); break; }
		case 36 : {Selected_key.setString("Escape		"); break; }
		case 37 : {Selected_key.setString("LControl	"); break; }
		case 38 : {Selected_key.setString("LShift		"); break; }
		case 39 : {Selected_key.setString("LAlt		"); break; }
		case 40 : {Selected_key.setString("LSystem		"); break; }
		case 41 : {Selected_key.setString("RControl	"); break; }
		case 42 : {Selected_key.setString("RShift		"); break; }
		case 43 : {Selected_key.setString("RAlt		"); break; }
		case 44 : {Selected_key.setString("RSystem		"); break; }
		case 45 : {Selected_key.setString("Menu		"); break; }
		case 46 : {Selected_key.setString("LBracket	"); break; }
		case 47 : {Selected_key.setString("RBracket	"); break; }
		case 48 : {Selected_key.setString("Semicolon	"); break; }
		case 49 : {Selected_key.setString("Comma		"); break; }
		case 50 : {Selected_key.setString("Period		"); break; }
		case 51 : {Selected_key.setString("Quote		"); break; }
		case 52 : {Selected_key.setString("Slash		"); break; }
		case 53 : {Selected_key.setString("Backslash	"); break; }
		case 54 : {Selected_key.setString("Tilde		"); break; }
		case 55 : {Selected_key.setString("Equal		"); break; }
		case 56 : {Selected_key.setString("Hyphen		"); break; }
		case 57 : {Selected_key.setString("Space		"); break; }
		case 58 : {Selected_key.setString("Enter		"); break; }
		case 59 : {Selected_key.setString("Backspace	"); break; }
		case 60 : {Selected_key.setString("Tab			"); break; }
		case 61 : {Selected_key.setString("PageUp		"); break; }
		case 62 : {Selected_key.setString("PageDown	"); break; }
		case 63 : {Selected_key.setString("End			"); break; }
		case 64 : {Selected_key.setString("Home		"); break; }
		case 65 : {Selected_key.setString("Insert		"); break; }
		case 66 : {Selected_key.setString("Delete		"); break; }
		case 67 : {Selected_key.setString("Add			"); break; }
		case 68 : {Selected_key.setString("Subtract	"); break; }
		case 69 : {Selected_key.setString("Multiply	"); break; }
		case 70 : {Selected_key.setString("Divide		"); break; }
		case 71 : {Selected_key.setString("Left		"); break; }
		case 72 : {Selected_key.setString("Right		"); break; }
		case 73 : {Selected_key.setString("Up			"); break; }
		case 74 : {Selected_key.setString("Down		"); break; }
		case 75 : {Selected_key.setString("Numpad0		"); break; }
		case 76 : {Selected_key.setString("Numpad1		"); break; }
		case 77 : {Selected_key.setString("Numpad2		"); break; }
		case 78 : {Selected_key.setString("Numpad3		"); break; }
		case 79 : {Selected_key.setString("Numpad4		"); break; }
		case 80 : {Selected_key.setString("Numpad5		"); break; }
		case 81 : {Selected_key.setString("Numpad6		"); break; }
		case 82 : {Selected_key.setString("Numpad7		"); break; }
		case 83 : {Selected_key.setString("Numpad8		"); break; }
		case 84 : {Selected_key.setString("Numpad9		"); break; }
		case 85 : {Selected_key.setString("F1			"); break; }
		case 86 : {Selected_key.setString("F2			"); break; }
		case 87 : {Selected_key.setString("F3			"); break; }
		case 88 : {Selected_key.setString("F4			"); break; }
		case 89 : {Selected_key.setString("F5			"); break; }
		case 90 : {Selected_key.setString("F6			"); break; }
		case 91 : {Selected_key.setString("F7			"); break; }
		case 92 : {Selected_key.setString("F8			"); break; }
		case 93 : {Selected_key.setString("F9			"); break; }
		case 94 : {Selected_key.setString("F10			"); break; }
		case 95 : {Selected_key.setString("F11			"); break; }
		case 96 : {Selected_key.setString("F12			"); break; }
		case 97 : {Selected_key.setString("F13			"); break; }
		case 98 : {Selected_key.setString("F14			"); break; }
		case 99 : {Selected_key.setString("F15			"); break; }
		case 100 : {Selected_key.setString("Pause		"); break; }
	}
}

void Selected_Key_PopUp::setColor(Color cr)
{
	Screen_Info1.setFillColor(cr);
	Screen_Info2.setFillColor(cr);
	Selected_key.setFillColor(cr);
}

Keyboard::Key Selected_Key_PopUp::getKey()
{
	return definedKey;
}

int Selected_Key_PopUp::getReceptorNumber()
{
	return receptorNumber;
}


#pragma endregion

#pragma region Main_Menu_Info

Main_Menu_Info::Main_Menu_Info(RenderWindow* window):
	window(window)
{
	Senko_t = new Texture;
	Senko_t->loadFromFile("Textures\\GUI\\CreatorNick.png");
	Senko_t->setSmooth(true);

	GameLogo_t = new Texture;
	GameLogo_t->loadFromFile("Textures\\GUI\\GameLogo.png");
	GameLogo_t->setSmooth(true);

	Senko_rect.setSize(Vector2f(window->getSize().y*0.6f*0.9285f, window->getSize().y*0.6f));
	Senko_rect.setTexture(Senko_t);
	Senko_rect.setPosition(window->getSize().x*0.5f - Senko_rect.getSize().x*0.5f, window->getSize().y - Senko_rect.getSize().y + 10.0f);

	GameLogo_rect.setSize(Vector2f(window->getSize().y*0.59f, window->getSize().y*0.59f*0.4915f));
	GameLogo_rect.setTexture(GameLogo_t);
	GameLogo_rect.setPosition(window->getSize().x*0.5f - GameLogo_rect.getSize().x*0.5f, window->getSize().y*0.1f);
}

Main_Menu_Info::~Main_Menu_Info()
{
}

void Main_Menu_Info::redrawInfo()
{
	window->draw(Senko_rect);
	window->draw(GameLogo_rect);
}

#pragma endregion


