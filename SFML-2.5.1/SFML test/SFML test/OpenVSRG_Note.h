#pragma once

#include <sfml\Graphics.hpp>
#include <queue>
#include "Score_Handler.h"

using namespace sf;

enum SM_VALUES
{
	NO_NOTE = 0 + 48,
	NOTE = 1 + 48,
	HOLD_HEAD = 2 + 48,
	HOLD__ROLL_BODY = 100,
	HOLD__ROLL_TAIL = 3 + 48,
	ROLL_HEAD = 4 + 48,
	MINE = 77
};

class Note
{


private:
	RenderWindow * window;
	Score_Handler * score_handler;

	Note* next;

	Mutex* Receptor0_Mutex;
	Mutex* Receptor1_Mutex;
	Mutex* Receptor2_Mutex;
	Mutex* Receptor3_Mutex;

	float DestroyOnY_Axis;

public:
	Sprite * sprite;

	bool in_Queue_F;
	bool destroyed_F;
	bool In_Use;
	int Receptor_number;

	std::queue<Note*> *q_receptor_0;
	std::queue<Note*> *q_receptor_1;
	std::queue<Note*> *q_receptor_2;
	std::queue<Note*> *q_receptor_3;

	Note();
	~Note();

	void SetConstPointers(RenderWindow *g_window, Mutex* M0, Mutex* M1, Mutex* M2, Mutex* M3, Score_Handler *score_handler, std::queue<Note*> *queue_receptor_0, std::queue<Note*> *queue_receptor_1, std::queue<Note*> *queue_receptor_2, std::queue<Note*> *queue_receptor_3);
	void initNote(Texture * texptr, float X, float Y, float DestroyOnX, int Receptor_number, float receptor_scale);
	Note* getNext();
	void setNext(Note* next);
	void RedrawArrow();
	bool AnimateNote(float a, float tappable_dist);
};


