#include "stdafx.h"

#include "OpenVSRG_Note.h"

#pragma region Note

Note::Note()
{
	sprite = new Sprite();
	in_Queue_F = false;
	destroyed_F = false;
	In_Use = false;
}

Note::~Note()
{
}

void Note::SetConstPointers(RenderWindow * g_window, Mutex* M0, Mutex* M1, Mutex* M2, Mutex* M3, Score_Handler *score_handlerPTR, std::queue<Note*> *queue_receptor_0, std::queue<Note*> *queue_receptor_1, std::queue<Note*> *queue_receptor_2, std::queue<Note*> *queue_receptor_3)
{
	window = g_window;

	score_handler = score_handlerPTR;

	q_receptor_0 = queue_receptor_0;
	q_receptor_1 = queue_receptor_1;
	q_receptor_2 = queue_receptor_2;
	q_receptor_3 = queue_receptor_3;

	Receptor0_Mutex = M0;
	Receptor1_Mutex = M1;
	Receptor2_Mutex = M2;
	Receptor3_Mutex = M3;
}

void Note::initNote(Texture * texptr, float X, float Y, float DestroyOnY, int receptor_number, float receptor_scale)
{
	sprite->setPosition(X, Y);

	DestroyOnY_Axis = DestroyOnY;

	Receptor_number = receptor_number;

	sprite->setTexture(*texptr, true);

	sprite->setScale(receptor_scale, receptor_scale);

	in_Queue_F = false;
	destroyed_F = false;
	In_Use = true;
}

Note * Note::getNext()
{
	return next;
}

void Note::setNext(Note * Next)
{
	next = Next;
}

void Note::RedrawArrow()
{
	if (!In_Use)return;
	window->draw(*sprite);
}

bool Note::AnimateNote(float a, float tappable_dist)
{
	if (!In_Use)return false;

	sprite->move(0.0f, a);

	if (!in_Queue_F)
	{
		if (sprite->getPosition().y <= tappable_dist)
		{
			switch (Receptor_number)
			{
			case 0:
			{
				Receptor0_Mutex->lock();
				q_receptor_0->push(this);//Gdy zda¿y siê losowy b³¹d z Deque zajrzyj tutaj i dodaj 4 mutexy 
				Receptor0_Mutex->unlock();

				in_Queue_F = true;
			}break;

			case 1:
			{
				Receptor1_Mutex->lock();
				q_receptor_1->push(this);
				Receptor1_Mutex->unlock();

				in_Queue_F = true;
			}break;
			case 2:
			{
				Receptor2_Mutex->lock();
				q_receptor_2->push(this);
				Receptor2_Mutex->unlock();

				in_Queue_F = true;
			}break;
			case 3:
			{
				Receptor3_Mutex->lock();
				q_receptor_3->push(this);
				Receptor3_Mutex->unlock();

				in_Queue_F = true;
			}break;
			}
		}
	}
	if (destroyed_F) 
	{
		In_Use = false;
		destroyed_F = false;
		return true;
	}
	else if (DestroyOnY_Axis >= sprite->getPosition().y) 
	{
		In_Use = false;
			score_handler->Miss++;
			score_handler->HP -= 50;
			score_handler->combo = 0;
			score_handler->FullDP += 10;
			score_handler->miss_F = true;

		return true;
	}
	else 
	{
		return false;
	}
}

#pragma endregion



