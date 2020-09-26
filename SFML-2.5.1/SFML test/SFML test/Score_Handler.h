#pragma once
#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <queue> 

using namespace sf;

class Score_Handler
{
	RenderWindow *game;

	Font *font;
	int fontSize;

	Text combo_text;
	Text Hit_Type;
	Text DP_precent_text;
	Text KPS_Text;
	Text HitError_text;
	Text Score_Board_text;
	Text RawDP_text;

	std::string DP_percent_str;
	std::string KPS_str;

	Texture* HP_Bar_T;
	Texture* HP_Fill_T;

	Sprite* HP_Bar_S;
	Sprite* HP_Fill_S;

	Clock animation_clock;
	const float animation_time = 0.2f;
	Time timeR;

	Clock animation_clock_KPS;
	const float animation_time_KPS = 0.2f;

	int hitsPerSec;
	int itt;
	int hitsArray[3];

	float combo_text_pos_y;
	float combo_text_pos_x;
	float hit_type_pos_y;

	const float Flawless_T	= 0.010000f;
	const float Perfect_T	= 0.020000f;
	const float Great_T		= 0.030000f;
	const float Good_T		= 0.032000f;
	const float Bad_T		= 0.034000f;

	RectangleShape HitsTimingQuantizedBackground;
	RectangleShape HitsTimingQuantizedLegendBackground;
	RectangleShape HitsTimingQuantizedBackgroundCenterLine;
	Vertex HitsTimingQuantizedPoints[256];

	Text HitsTimingQuantized_Flawless;
	Text HitsTimingQuantized_Perfect_L;
	Text HitsTimingQuantized_Perfect_R;
	Text HitsTimingQuantized_Great_L;
	Text HitsTimingQuantized_Great_R;
	Text Early;
	Text Late;

	Text Artist_Title_Text;
	String  Artist_Title_Str;

	RectangleShape HitsTimingLegendBackground;
	RectangleShape HitsTimingBackgrounds;
	RectangleShape *HitsTimingPoints;

	Text msMinus50;
	Text msPlus50;
	Text ms0;

	float *CoughtHitsTiming;
	int itt_CHT;

	float BPS;
	float NoteWayLength;

public:
	std::queue<float> *hits_timing;
	Mutex* Score_calculating_Mutex;
	Mutex* Redraw_Mutex;

	int Flawless;
	int Perfect;
	int Great;
	int Good;
	int Bad;
	int Miss;
	int DP;
	int FullDP;
	float DP_percent;

	bool *external_simfile_end_F;
	bool simfile_end_F;

	bool miss_F;

	int HP;
	int combo;

	float scores[10];

	float Receptor_pos;
	float Receptor_step;
	float HPBar_possitionX;
	float HPBar_possitionY;
	float HPBar_Fill_scaling_factor_Y;
	float HPBar_Fill_scaling_factor_X;

	Score_Handler(RenderWindow *game, String ArtistTitle);
	~Score_Handler();

	void SetEndOfSimFilePTR(bool*ptr);
	void SetReceptorPossition(float receptorPos);
	void SetFont(Font *font, int setsize, Color color);
	void SetComboXYPossition(float comboposX, float comboposY);
	void SetLifeBarOver(String barpath, String fillBarpath, float posX, float receptor_step);
	void SetCoughtPointerSize(int size);

	void initScores(float Flawless, float  Perfect, float Great, float Good, float Bad);
	void calculateTiming(float BPS,float NoteWayLength);
	void calculateScore(float tap_pos);
	void ThreadScoreCalculating();
	void CalculateDP();
	void TranslateCoughtPossitionsToTimeSamples();

	void RedrawScoreAnimations();
	void DrawScoreBoard();

	float getKPS();
	unsigned char getQuantizedFloat(float x);
};

