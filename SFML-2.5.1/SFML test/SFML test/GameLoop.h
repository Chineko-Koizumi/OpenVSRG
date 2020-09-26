#pragma once
#include <sfml\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <fstream>
#include <iostream>

#include "OpenVSRG_Textures.h"
#include "OpenVSRG_NotePool.h"
#include "InputHandling.h"
#include "Receptor.h"

using namespace sf;

class GameLoop
{
	RenderWindow* game;

	OpenVSRG_Textures *Skins;
	NotePool * NotePool_;
	Score_Handler * score_handler;

	char** RawSimFile;
	char** Level;

	int key_left, key_down, key_up, key_right;

	int SongVolume;

	String Simfile_Music_Path;
	String Background_Path;

	String Song_ArtistTitle;
	Text Song_ArtistTitle_Text;
	Font *font;

	Clock clockl;

	Time Global_elapsed;
	Time SimFile_offset_temp;
	Time Next_Block_Generate;
	Time ZERO = sf::seconds(0);
	Time EndOfGamePlay = sf::seconds(0);

	int Level_number;
	int RawSimFileCount;
	int LevelLinesCount;
	int LevelsCount;
	int IterratorForBPMBLockCounting;//pocz¹tek mapy sima zaraz po informacjach o BPM itp (0000)

	float Song_BPM;
	float Song_BPS;
	float Beat_Time;
	float Beat_Block_Time;
	float SimFile_Offset_from_file; 

	float Receptor_Possition;
	float Note_receptor_starting_Xpos;
	float Note_receptor_starting_Xpos_step;
	float Note_Yway_lenth;
	float Note_Scale;
	float Background_Dimm;
	float Song_pitch;
	 
	bool *SimFileEnd;
	bool IterratorForBPMBLockCounting_flag_set;
	bool Offset_flag_set;

public:
	
	GameLoop(RenderWindow* game_ptr, OpenVSRG_Textures *Skins, Score_Handler* score_handler, std::string SimFilePath, String sim_music_path, String BackGround_Path, Font *font,String Artis_title, int key_left, int key_down, int key_up, int key_right, int SongVolume);
	~GameLoop();

	void SetMusicOffset(float SimFile_Offset);
	void SetReceptorPosition(float receptor_pos);
	void SetNoteReceptorStartingXPossition(float Note_receptor_starting_Xpos);
	void SetNoteReceptorStartingXPossitionStep(float Note_receptor_starting_Xpos_step);
	void SetNoteYWayLenth(float Note_Yway_lenth);
	void SetStartBPM(float start_BPM);
	void SetLevelNumber(int level_num);
	void SetNoteScale(float mini_ratio);
	void SetBackgroundDimm(float dimm_percent);
	void SetSongPitch(float pitch);

	void GenereteLevel(int lvl);
	void CalllSimFileNextBPMBLockGenerate(float receptor_pos, float DestroyXPos);
	void RunGame();
	void CalculateBPMVariables(float BPM);

	Sprite Background_S;
	Texture Background_T;

private:

};

