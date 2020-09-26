#pragma once

#include <queue>
#include <sfml\Graphics.hpp>
#include <assert.h>
#include "OpenVSRG_Note.h"

class NotePool
{
private:
	static const int POOL_SIZE = 256;

	Note *Notes_[POOL_SIZE];
	Note * FirstAvailable_;

public:

	Mutex * mutex0;
	Mutex * mutex1;
	Mutex * mutex2;
	Mutex * mutex3;

	std::queue<Note*> *queue_receptor_0;
	std::queue<Note*> *queue_receptor_1;
	std::queue<Note*> *queue_receptor_2;
	std::queue<Note*> *queue_receptor_3;

	NotePool(RenderWindow * g_window, Score_Handler* score_handler);
	~NotePool();

	void create(Texture * texptr, float X, float Y, float DestroyOnX, int Receptor_number, float receptor_scale);
	void animate(float a, float tappable_dist);
	void RedrawNotes();
private:

};






