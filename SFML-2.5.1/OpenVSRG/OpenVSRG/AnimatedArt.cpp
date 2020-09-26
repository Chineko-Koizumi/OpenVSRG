#include "AnimatedArt.h"

#pragma region MenuArtRender

MenuArtRender::MenuArtRender(RenderWindow * Window_PTR, Color artColor) : Window_PTR(Window_PTR)
{

	triangleArray = new CircleShape[12];
	currentColor = artColor;
	currentColor.a = 125;

	for (int i = 0; i < 12; ++i)
	{
		triangleArray[i] = CircleShape(1.0f, 3);
		triangleArray[i].setFillColor(currentColor);
		triangleArray[i].setRadius(rand() % (int)(((float)Window_PTR->getSize().y / 2.0f) ) + (int)((float)Window_PTR->getSize().y / 4.0f));
		triangleArray[i].setOrigin(triangleArray[i].getRadius(), triangleArray[i].getRadius());
		triangleArray[i].setPosition(rand() % (Window_PTR->getSize().x + (int)triangleArray[i].getRadius()*2) - (int)(triangleArray[i].getRadius()), rand() % (Window_PTR->getSize().y + (int)triangleArray[i].getRadius()) - (int)(triangleArray[i].getRadius()/2.0f));
	}
}

MenuArtRender::~MenuArtRender()
{
}

void MenuArtRender::readrawAll()
{

	timeR += clock.restart();
	if (timeR.asMilliseconds() > 3)timeR = seconds(0);
	for (int i = 0; i < 12; ++i)
	{
		triangleArray[i].move(timeR.asSeconds() * 7.0f * (float)sqrt(i + 1), 0.0f);
		triangleArray[i].rotate(timeR.asSeconds() * (float)sqrt(i + 1));
		currentPosition = triangleArray[i].getPosition();

		if (currentPosition.x > Window_PTR->getSize().x + triangleArray[i].getRadius())
		{
			triangleArray[i].setPosition(-triangleArray[i].getRadius(), rand() % Window_PTR->getSize().y);
		}
		Window_PTR->draw(triangleArray[i]);
	}

}

void MenuArtRender::setColor(Color  artColor)
{
	currentColor = artColor;
	currentColor.a = 125;

	for (int i = 0; i < 12; ++i)
	{
		triangleArray[i].setFillColor(currentColor);
	}
}

#pragma endregion

#pragma region MenuLogoRender

MenuLogoRender::MenuLogoRender(RenderWindow * Window_PTR) : Window_PTR(Window_PTR)
{

	LogoLayersArray = new CircleShape[4];

	Texture **LogoLayersArray_T = new Texture*[4];

	for (int i = 0; i < 4; ++i)
	{
		LogoLayersArray_T[i] = new Texture;
	}

	LogoLayersArray_T[0]->loadFromFile("Textures\\Menu\\GameLogo\\Penta.png");
	LogoLayersArray_T[1]->loadFromFile("Textures\\Menu\\GameLogo\\Star.png");
	LogoLayersArray_T[2]->loadFromFile("Textures\\Menu\\GameLogo\\SmallStar.png");
	LogoLayersArray_T[3]->loadFromFile("Textures\\Menu\\GameLogo\\SmallerStar.png");

	for (int i = 0; i < 4; ++i)
	{
		LogoLayersArray[i] = CircleShape(Window_PTR->getSize().y / 8.0f);
		LogoLayersArray[i].setOrigin(LogoLayersArray[i].getRadius(), LogoLayersArray[i].getRadius());
		LogoLayersArray[i].setPosition(Window_PTR->getSize().x - LogoLayersArray[i].getRadius(), Window_PTR->getSize().y - LogoLayersArray[i].getRadius());
		LogoLayersArray_T[i]->setSmooth(true);
		LogoLayersArray[i].setTexture(LogoLayersArray_T[i]);
	}


}
MenuLogoRender::~MenuLogoRender()
{
}

void MenuLogoRender::readrawAll()
{

	timeR += clock.restart();

	if (timeR.asMilliseconds() > 3.0f)	timeR = seconds(0);
	for (int i = 0; i < 4; ++i)
	{
		LogoLayersArray[i].rotate(timeR.asSeconds() * (float)sqrt(i + i + 1));
		Window_PTR->draw(LogoLayersArray[i]);
	}

}


#pragma endregion

#pragma region SelectColorWheel

SelectColorWheel::SelectColorWheel(RenderWindow * Window_PTR, Font *def_font) : 
	Window_PTR(Window_PTR),
	cursor(0),
	back_cursor_value(0),
	timeR(seconds(0)),
	center_info_F(def_font)
{
	float character_size = Window_PTR->getSize().y / 10.0f;

	center_info_T.setFont(*def_font);
	center_info_T.setString("Select color from wheel");
	center_info_T.setCharacterSize(character_size);
	center_info_T.setPosition(Window_PTR->getSize().x/2.0f - center_info_T.getLocalBounds().width/2.0f, 0);

	Color_Array[0] = new Color(255, 0, 0, 255);
	Color_Array[1] = new Color(255, 64, 0, 25);
	Color_Array[2] = new Color(255, 128, 0, 25);
	Color_Array[3] = new Color(255, 191, 0, 25);
	Color_Array[4] = new Color(255, 255, 0, 25);
	Color_Array[5] = new Color(191, 255, 0, 25);
	Color_Array[6] = new Color(128, 255, 0, 25);
	Color_Array[7] = new Color(64, 255, 0, 25);
	Color_Array[8] = new Color(0, 255, 0, 25);
	Color_Array[9] = new Color(0, 255, 64, 25);
	Color_Array[10] = new  Color(0, 255, 128, 25);
	Color_Array[11] = new  Color(0, 255, 191, 25);
	Color_Array[12] = new  Color(0, 255, 255, 25);
	Color_Array[13] = new  Color(0, 191, 255, 25);
	Color_Array[14] = new  Color(0, 128, 255, 25);
	Color_Array[15] = new  Color(0, 64, 255, 25);
	Color_Array[16] = new  Color(0, 0, 255, 25);
	Color_Array[17] = new  Color(64, 0, 255, 25);
	Color_Array[18] = new  Color(128, 0, 255, 25);
	Color_Array[19] = new  Color(191, 0, 255, 25);
	Color_Array[20] = new  Color(255, 0, 255, 25);
	Color_Array[21] = new  Color(255, 0, 191, 25);
	Color_Array[22] = new  Color(255, 0, 128, 25);
	Color_Array[23] = new  Color(255, 0, 64, 25);

	SelectColorLayersArray = new CircleShape[colors_count];

	radius = Window_PTR->getSize().y;
	circumference_factor = 2.0f*M_PI / (float)colors_count;
	circle_rotation = (M_PI*8.0f) / 8.0f;

	for (int i = 0; i < colors_count; ++i)
	{
		SelectColorLayersArray[i] = CircleShape(Window_PTR->getSize().y / 3.0f, 3);
		SelectColorLayersArray[i].setFillColor(*Color_Array[i]);
		SelectColorLayersArray[i].setOrigin(SelectColorLayersArray[i].getRadius(), SelectColorLayersArray[i].getRadius());
		SelectColorLayersArray[i].setRotation(-(float)i*(360.0f / (float)colors_count));
		SelectColorLayersArray[i].setPosition(Window_PTR->getSize().x / 2.0f + radius * sin(circle_rotation + float(i)*circumference_factor), Window_PTR->getSize().y*1.5f + radius * cos(circle_rotation + float(i)*circumference_factor));
	}

}
SelectColorWheel::~SelectColorWheel()
{
}

void SelectColorWheel::readrawAll()
{
	RotateWheel();
	for (int i = colors_count - 1; i >= 0; --i)
	{
		Window_PTR->draw(SelectColorLayersArray[i]);
	}
	Window_PTR->draw(SelectColorLayersArray[cursor]);

	Window_PTR->draw(center_info_T);
}

int SelectColorWheel::getCursor()
{
	return cursor;
}

void SelectColorWheel::incrementCursor()
{
	if (cursor == colors_count - 1)
	{
		cursor = 0;
	}
	else
	{
		cursor++;
	}
}

void SelectColorWheel::decrementCursor()
{
	if (cursor == 0)
	{
		cursor = colors_count - 1;
	}
	else
	{
		cursor--;
	}
}

void SelectColorWheel::MoveLeft()
{
	back_cursor_value = cursor;

	NotSelected(cursor);
	incrementCursor();
	Selected(cursor);

	clock.restart();
}

void SelectColorWheel::MoveRight()
{
	back_cursor_value = cursor;

	NotSelected(cursor);
	decrementCursor();
	Selected(cursor);

	clock.restart();
}

void SelectColorWheel::RotateWheel()
{
	float move_step = cursor - back_cursor_value;
	if (0 == cursor && colors_count - 1 == back_cursor_value)
	{
		move_step = 1;
	}
	else if (colors_count - 1 == cursor && 0 == back_cursor_value)
	{
		move_step = -1;
	}

	timeR = clock.getElapsedTime();

	float time_move_step = (move_step - (move_step*timeR.asSeconds() / animation_time));
	if (timeR.asSeconds()>animation_time)
	{
		for (int i = 0; i < colors_count; ++i)
		{
			SelectColorLayersArray[i].setRotation(-(float)(i - cursor)*(360.0f / (float)colors_count));
			SelectColorLayersArray[i].setPosition(
				Window_PTR->getSize().x / 2.0f + radius * sin(circle_rotation + (float)(i - cursor)*circumference_factor), 
				Window_PTR->getSize().y * 1.5f + radius * cos(circle_rotation + (float)(i - cursor)*circumference_factor));
		}
	}
	else
	{
		for (int i = 0; i < colors_count; ++i)
		{
			SelectColorLayersArray[i].setRotation(-((float)i - (float)cursor + time_move_step)*(360.0f / (float)colors_count));
			SelectColorLayersArray[i].setPosition(
				Window_PTR->getSize().x / 2.0f + radius * sin(circle_rotation + (float)(i - cursor + time_move_step)*circumference_factor), 
				Window_PTR->getSize().y * 1.5f + radius * cos(circle_rotation + (float)(i - cursor + time_move_step)*circumference_factor));
		}

	}


}

void SelectColorWheel::NotSelected(int cur)
{
	temp_color = SelectColorLayersArray[cur].getFillColor();
	temp_color.a = 25;
	SelectColorLayersArray[cur].setFillColor(temp_color);
}

void SelectColorWheel::Selected(int cur)
{
	temp_color = SelectColorLayersArray[cur].getFillColor();
	temp_color.a = 255;
	SelectColorLayersArray[cur].setFillColor(temp_color);
}

Color SelectColorWheel::getSelectedColor()
{
	Color temp = *Color_Array[cursor];
	temp.a = 255;
	return temp;
}


#pragma endregion

#pragma region SongSelectSongsList

SongSelectSongsList::SongSelectSongsList(RenderWindow *PTR, Font *font, Color default_color) :
	WindowPTR(PTR),
	font(font),
	default_color(default_color)
{
	step_x = WindowPTR->getSize().x / 2.0f;
	step_y = WindowPTR->getSize().y / 11.0f;
	frame_thicc = WindowPTR->getSize().y / 200.0f;
	character_size = WindowPTR->getSize().y / 25.0f;

	moving_direction = 0;

	first = 0;
	selected = 6;
	last = RectangleCount - 1;

	for (int i = 0; i < RectangleCount; ++i)
	{
		items[i].Rectangle.setOutlineColor(Color::White);
		items[i].Rectangle.setFillColor(Color(0, 0, 0, 0));
		items[i].Rectangle.setOutlineThickness(-frame_thicc);
		items[i].Rectangle.setSize(Vector2f(step_x, step_y));
		items[i].Rectangle.setPosition(step_x, step_y*i - step_y);

		possition_Y_array[i] = items[i].Rectangle.getPosition().y;

		items[i].item_T.setFont(*font);
		items[i].item_T.setCharacterSize(character_size);
		items[i].item_T.setString("not loaded yet");
		items[i].item_T.setPosition(step_x + abs(frame_thicc), step_y*i - step_y);
	}

	items[selected].item_T.setFillColor(default_color);
}

void SongSelectSongsList::setCenterSong(String CenterText)
{
	items[selected].item_T.setString(CenterText);
}

void SongSelectSongsList::setString(int index, String Text)
{
	items[index].item_T.setString(Text);
}

void SongSelectSongsList::setColor(Color color)
{
	default_color = color;
	items[selected].item_T.setFillColor(default_color);
}

void SongSelectSongsList::moveUp(String textUp, String textDown)
{
	items[selected].item_T.setFillColor(Color::White);

	incrementFirstLast();

	items[selected].item_T.setFillColor(default_color);

	items[first].item_T.setString(textUp);
	items[last].item_T.setString(textDown);

	moving_direction = 1;
	animation_clock.restart();
}

void SongSelectSongsList::moveDown(String textUp, String textDown)
{
	items[selected].item_T.setFillColor(Color::White);

	decrementFirstLast();

	items[selected].item_T.setFillColor(default_color);

	items[first].item_T.setString(textUp);
	items[last].item_T.setString(textDown);

	moving_direction = -1;
	animation_clock.restart();
}

void SongSelectSongsList::redrawAll()
{
	if (animation_clock.getElapsedTime() <= animation_duration)
	{
		float shift = moving_direction * (step_y - step_y * (animation_clock.getElapsedTime().asSeconds() / animation_duration.asSeconds()));
		int cursor = first;
		for (int i = 0; i < RectangleCount; ++i)
		{
			if (cursor == RectangleCount) cursor = 0;

			items[cursor].Rectangle.setPosition(step_x, possition_Y_array[i] + shift);
			items[cursor].item_T.setPosition(step_x + abs(frame_thicc), possition_Y_array[i] + shift);
			cursor++;
		}
	}
	else
	{
		int cursor = first;
		for (int i = 0; i < RectangleCount; ++i)
		{
			if (cursor == RectangleCount) cursor = 0;

			items[cursor].Rectangle.setPosition(step_x, possition_Y_array[i]);
			items[cursor].item_T.setPosition(step_x + abs(frame_thicc), possition_Y_array[i]);
			cursor++;
		}
	}

	for (int i = 0; i < RectangleCount; ++i)
	{
		WindowPTR->draw(items[i].Rectangle);
		WindowPTR->draw(items[i].item_T);
	}
}

void SongSelectSongsList::decrementFirstLast()
{
	if (first == 0)
	{
		first = RectangleCount - 1;
		last--;
		selected--;
	}
	else if (last == 0)
	{
		last = RectangleCount - 1;
		first--;
		selected--;
	}
	else if (selected == 0)
	{
		selected = RectangleCount - 1;
		last--;
		first--;
	}
	else
	{
		last--;
		first--;
		selected--;
	}
}

void SongSelectSongsList::incrementFirstLast()
{

	if (first == RectangleCount - 1)
	{
		first = 0;
		last++;
		selected++;
	}
	else if (last == RectangleCount - 1)
	{
		last = 0;
		first++;
		selected++;
	}
	else if (selected == RectangleCount - 1)
	{
		selected = 0;
		last++;
		first++;
	}
	else
	{
		last++;
		first++;
		selected++;
	}
}

#pragma endregion


