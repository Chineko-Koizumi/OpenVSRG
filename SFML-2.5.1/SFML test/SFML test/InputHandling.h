#pragma once

#include <sfml\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "OpenVSRG_NotePool.h"
#include "Score_Handler.h"

class Input_Handler
{
	Score_Handler *Score;
	int left, down, up, right;

	NotePool *Notepool;

	std::queue<float>*hits_timing;

	float PosYforScoring;

public:

	bool F_left, F_down, F_up, F_right;
	bool F_Tapped_left, F_Tapped_down, F_Tapped_up, F_Tapped_right;
	bool *Sim_File_End_PTR;
	bool Sim_File_End;

	Input_Handler(int a, int b, int c, int d, bool* SimFileEnd_PTR, Score_Handler *score, NotePool * notepool);
	~Input_Handler();

	void KeysState();

private:

};
