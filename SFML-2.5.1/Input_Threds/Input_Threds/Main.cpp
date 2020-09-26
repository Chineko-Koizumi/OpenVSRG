
#define _USE_MATH_DEFINES

#include <sfml\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML\Window\Joystick.hpp>

#include <iostream>
#include <string>
#include <cmath>


using namespace sf;

RenderWindow game(VideoMode(1600, 900), "SFML");

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

	SongSelectSongsList(RenderWindow *PTR, Font *font);

	void setString(int index, String Text);

	void moveUp(String textUp, String textDown);
	void moveDown(String textUp, String textDown);

	void redrawAll();

	void decrementFirstLast();
	void incrementFirstLast();

};

SongSelectSongsList::SongSelectSongsList(RenderWindow *PTR, Font *font):
	WindowPTR(PTR),
	font(font)
{
	step_x = WindowPTR->getSize().x / 2.0f;
	step_y = WindowPTR->getSize().y / 11.0f;
	frame_thicc = WindowPTR->getSize().y / 200.0f;
	character_size = WindowPTR->getSize().y / 25.0f;
	
	moving_direction = 0;

	first = 0;
	selected = 6;
	last = RectangleCount-1;

	for (int i = 0; i < RectangleCount; ++i)
	{
		items[i].Rectangle.setOutlineColor(Color::White);
		items[i].Rectangle.setFillColor(Color(0,0,0,0));
		items[i].Rectangle.setOutlineThickness(-frame_thicc);
		items[i].Rectangle.setSize(Vector2f(step_x, step_y));
		items[i].Rectangle.setPosition(step_x, step_y*i - step_y);

		possition_Y_array[i] = items[i].Rectangle.getPosition().y;

		items[i].item_T.setFont(*font);
		items[i].item_T.setCharacterSize(character_size);
		items[i].item_T.setString(std::to_string(i));
		items[i].item_T.setPosition(step_x + abs(frame_thicc), step_y*i - step_y);
	}

	items[selected].item_T.setFillColor(Color::Red);
}

void SongSelectSongsList::setString(int index, String Text)
{
	items[index].item_T.setString(Text);
}

void SongSelectSongsList::moveUp(String textUp, String textDown)
{
	items[selected].item_T.setFillColor(Color::White);

		incrementFirstLast();

	items[selected].item_T.setFillColor(Color::Red);

	items[first].item_T.setString(textUp);
	items[last].item_T.setString(textDown);

	moving_direction = 1;
	animation_clock.restart();
}

void SongSelectSongsList::moveDown(String textUp, String textDown)
{
	items[selected].item_T.setFillColor(Color::White);

		decrementFirstLast();

	items[selected].item_T.setFillColor(Color::Red);

	items[first].item_T.setString(textUp);
	items[last].item_T.setString(textDown);

	moving_direction = -1;
	animation_clock.restart();
}

void SongSelectSongsList::redrawAll()
{
	if (animation_clock.getElapsedTime() <= animation_duration) 
	{
		float shift = moving_direction *(step_y - step_y * (animation_clock.getElapsedTime().asSeconds() / animation_duration.asSeconds()));
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


int main()
{
	Font font;
	font.loadFromFile("Fonts/varsity_regular.ttf");
	SongSelectSongsList test(&game,&font);

	while (game.isOpen())
	{
	
		sf::Event event;

		// while there are pending events...
		while (game.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				game.close();
				break;

				// key pressed
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Right)
				{
					test.moveDown(String("dupaDown"), String("dupaDown"));
				}
				if (event.key.code == sf::Keyboard::Left)
				{
					test.moveUp(String("dupaUp"), String("dupaUp"));
				}
					break;

				// we don't process other types of events
			default:
				break;
			}
		}

		game.clear();
		
		test.redrawAll();

		game.display();
		
	}

	return 0;
}


