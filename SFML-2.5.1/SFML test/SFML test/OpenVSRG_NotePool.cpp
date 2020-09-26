#include "stdafx.h"

#include "OpenVSRG_NotePool.h"

#pragma region NotePool

NotePool::NotePool(RenderWindow * g_window, Score_Handler* score_handler)
{
	queue_receptor_0 = new std::queue<Note*>;
	queue_receptor_1 = new std::queue<Note*>;
	queue_receptor_2 = new std::queue<Note*>;
	queue_receptor_3 = new std::queue<Note*>;

	mutex0 = new Mutex();
	mutex1 = new Mutex();
	mutex2 = new Mutex();
	mutex3 = new Mutex();

	for (int i = 0; i < POOL_SIZE; i++)
	{
		Notes_[i] = new Note;	
	}
	
	FirstAvailable_ = Notes_[0];
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		Notes_[i]->SetConstPointers(g_window, mutex0, mutex1, mutex2, mutex3, score_handler, queue_receptor_0,queue_receptor_1, queue_receptor_2, queue_receptor_3);
		Notes_[i]->setNext(Notes_[i + 1]);
	}
	Notes_[POOL_SIZE - 1]->SetConstPointers(g_window, mutex0, mutex1, mutex2, mutex3, score_handler, queue_receptor_0, queue_receptor_1, queue_receptor_2, queue_receptor_3);
	Notes_[POOL_SIZE - 1]->setNext(NULL);
}

NotePool::~NotePool()
{

	while (!queue_receptor_0->empty())
	{
		queue_receptor_0->pop();
	}
	while (!queue_receptor_1->empty())
	{
		queue_receptor_1->pop();
	}
	while (!queue_receptor_2->empty())
	{
		queue_receptor_2->pop();
	}
	while (!queue_receptor_3->empty())
	{
		queue_receptor_3->pop();
	}

	delete queue_receptor_0;
	delete queue_receptor_1;
	delete queue_receptor_2;
	delete queue_receptor_3;

	for (int i = 0; i < POOL_SIZE; i++)
	{
		delete Notes_[i] ;
	}
	delete[]Notes_;
}

void NotePool::create(Texture * texptr, float X, float Y, float DestroyOnX, int Receptor_number, float receptor_scale)
{
	assert(FirstAvailable_ != NULL);
		Note* newNote = FirstAvailable_;
		FirstAvailable_ = newNote->getNext();
		newNote->initNote(texptr, X, Y, DestroyOnX, Receptor_number, receptor_scale);
}

void NotePool::animate(float a, float tappable_dist)
{
	
	for (int i = 0; i < POOL_SIZE; i++)
	{

		if (Notes_[i]->AnimateNote(a, tappable_dist))
		{
			// Add this particle to the front of the list.
			switch (Notes_[i]->Receptor_number)
			{
				case 0:
				{
					mutex0->lock();

					queue_receptor_0->pop();
					Notes_[i]->in_Queue_F = false;

					mutex0->unlock();
				}break;

				case 1:
				{
					mutex1->lock();

					queue_receptor_1->pop();
					Notes_[i]->in_Queue_F = false;

					mutex1->unlock();
				}break;

				case 2:
				{
					mutex2->lock();

					queue_receptor_2->pop();
					Notes_[i]->in_Queue_F = false;

					mutex2->unlock();
				}break;

				case 3:
				{
					mutex3->lock();

					queue_receptor_3->pop();
					Notes_[i]->in_Queue_F = false;

					mutex3->unlock();
				}break;
			}
			Notes_[i]->setNext(FirstAvailable_);
			FirstAvailable_ = Notes_[i];
		}
	}
	
}

void NotePool::RedrawNotes()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (Notes_[i]->In_Use)
		{
			Notes_[i]->RedrawArrow();
		}
	}
}

#pragma endregion





