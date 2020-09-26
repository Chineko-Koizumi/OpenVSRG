#pragma once
#include <sfml\Graphics.hpp>

using namespace sf;

class OpenVSRG_Textures
{
public:
	
	Texture * Left;
	Texture * Down;
	Texture * Up;
	Texture * Right;
	
	Texture * Receptor_left;
	Texture * Receptor_down;
	Texture * Receptor_up;
	Texture * Receptor_right;

	Texture * Tap_Receptor_left;
	Texture * Tap_Receptor_down;
	Texture * Tap_Receptor_up;
	Texture * Tap_Receptor_right;

	OpenVSRG_Textures();
	~OpenVSRG_Textures();

private:

};


