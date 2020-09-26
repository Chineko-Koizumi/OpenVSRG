#include "stdafx.h"

#include "InputHandling.h"

Input_Handler::Input_Handler(int a, int b, int c, int d, bool* SimFileEnd_PTR, Score_Handler *score, NotePool * notepool)
	:left(a),
	down(b), 
	up(c), 
	right(d),
	Sim_File_End_PTR(SimFileEnd_PTR),
	Score(score), 
	Notepool(notepool)
{
	F_left			= false;
	F_down			= false;
	F_up			= false;
	F_right			= false;

	F_Tapped_left	= false;
	F_Tapped_down	= false;
	F_Tapped_up		= false;
	F_Tapped_right	= false;

	Sim_File_End = false;

	hits_timing = score->hits_timing;
}

Input_Handler::~Input_Handler()
{
}

void Input_Handler::KeysState()// uzywac tylko w osobnym watku inaczej zablokuje caly program!!!
{
	while (!Sim_File_End)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(left))) 
		{
			F_left = true; 

			if(!F_Tapped_left)
			{
				Notepool->mutex0->lock();

				if (!Notepool->queue_receptor_0->empty())
				{
					Score->Score_calculating_Mutex->lock();
					hits_timing->push(Notepool->queue_receptor_0->front()->sprite->getPosition().y);
					Score->Score_calculating_Mutex->unlock();


					Notepool->queue_receptor_0->front()->destroyed_F = true;
				}

				F_Tapped_left = true;
				Notepool->mutex0->unlock();
			}
		}
		else 
		{ 
			F_left = false; 
			F_Tapped_left = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(down)))
		{
			F_down = true;

			if (!F_Tapped_down)
			{
				Notepool->mutex1->lock();

				if (!Notepool->queue_receptor_1->empty())
				{
					Score->Score_calculating_Mutex->lock();
					hits_timing->push(Notepool->queue_receptor_1->front()->sprite->getPosition().y);
					Score->Score_calculating_Mutex->unlock();

					Notepool->queue_receptor_1->front()->destroyed_F = true;
				}
				F_Tapped_down = true;
				
				Notepool->mutex1->unlock();
			}
		}
		else 
		{ 
			F_down = false;
			F_Tapped_down = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(up)))
		{
			F_up = true;

			if (!F_Tapped_up)
			{
				Notepool->mutex2->lock();

				if (!Notepool->queue_receptor_2->empty())
				{
					Score->Score_calculating_Mutex->lock();
					hits_timing->push(Notepool->queue_receptor_2->front()->sprite->getPosition().y);
					Score->Score_calculating_Mutex->unlock();

					Notepool->queue_receptor_2->front()->destroyed_F = true;
				}
				F_Tapped_up = true;

				Notepool->mutex2->unlock();
			}
		}
		else
		{
			F_up = false;
			F_Tapped_up = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(right)))
		{
			F_right = true;

			if (!F_Tapped_right)
			{
				Notepool->mutex3->lock();

				if (!Notepool->queue_receptor_3->empty())
				{
					Score->Score_calculating_Mutex->lock();
					hits_timing->push(Notepool->queue_receptor_3->front()->sprite->getPosition().y);
					Score->Score_calculating_Mutex->unlock();

					Notepool->queue_receptor_3->front()->destroyed_F = true;
				}
				F_Tapped_right = true;

				Notepool->mutex3->unlock();
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			*Sim_File_End_PTR = true;
		}
		else
		{
			F_right = false;
			F_Tapped_right = false;
		}
	}
}

