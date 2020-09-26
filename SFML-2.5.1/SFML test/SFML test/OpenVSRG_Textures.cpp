#include "stdafx.h"
#include "OpenVSRG_Textures.h"


OpenVSRG_Textures::OpenVSRG_Textures()
{
	{
		
		Left			= new Texture;
		Down			= new Texture;
		Up				= new Texture;
		Right			= new Texture;

		Receptor_left		= new Texture;
		Receptor_down		= new Texture;
		Receptor_up			= new Texture;
		Receptor_right		= new Texture;

		Tap_Receptor_left	= new Texture;
		Tap_Receptor_down	= new Texture;
		Tap_Receptor_up		= new Texture;
		Tap_Receptor_right	= new Texture;

		Left->loadFromFile("textures\\NotesSkins\\Pure White\\notes\\Left.png");
		Down->loadFromFile("textures\\NotesSkins\\Pure White\\notes\\Down.png");
		Up->loadFromFile("textures\\NotesSkins\\Pure White\\notes\\Up.png");
		Right->loadFromFile("textures\\NotesSkins\\Pure White\\notes\\Right.png");
		
		Receptor_left->loadFromFile("textures\\NotesSkins\\Pure White\\receptors\\Receptor0.png");
		Receptor_down->loadFromFile("textures\\NotesSkins\\Pure White\\receptors\\Receptor1.png");
		Receptor_up->loadFromFile("textures\\NotesSkins\\Pure White\\receptors\\Receptor2.png");
		Receptor_right->loadFromFile("textures\\NotesSkins\\Pure White\\receptors\\Receptor3.png");

		Tap_Receptor_left->loadFromFile("textures\\NotesSkins\\Pure White\\receptors\\Receptor0tap.png");
		Tap_Receptor_down->loadFromFile("textures\\NotesSkins\\Pure White\\receptors\\Receptor1tap.png");
		Tap_Receptor_up->loadFromFile("textures\\NotesSkins\\Pure White\\receptors\\Receptor2tap.png");
		Tap_Receptor_right->loadFromFile("textures\\NotesSkins\\Pure White\\receptors\\Receptor3tap.png");
	}
}


OpenVSRG_Textures::~OpenVSRG_Textures()
{
}
