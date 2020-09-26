#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Shape_OpenVSRG.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace sf;

class SimFile
{
private:
	String Dir_Path;
	String SM_path;
	String Music_Path;
	String Banner_Path;
	String Background_Path;
	String Mapper_Tag_Path;

	String SimFile_name;
	String Song_Title;
	String Song_Artist;
	
	float sample_start;
	float sample_lenth;

	bool All_metadata_loaded;

	int Number_of_levels;

	String levels[16];

public:

	SimFile(String SimFile_name, String Dir_Path);
	~SimFile();

	std::string getParameterFromSM(std::string FileLine);
	std::string getBPMParameterFromSM(std::string FileLine);
	std::string getLevelParameterFromSM(std::string FileLine);

	bool isPoliBPM(std::string FileLine);

	String GetBannerPath();
	String GetBackgroundPath();
	String GetMapperTagPath();
	String getSongArtist();
	String getSongTitle();
	String getMusicPath();
	String getSMPath();
	String* getDifficulties();

	void SetBannerpath(String path);
	void SetArtistTagpath(String path);

	int getDifficultiesCount();

	float getSampleStart();
	float getSampleLenth();

	float offset;
	float BPM;

	bool PoliBPM_F;
};

class SimFiles_Colletion_Load
{
private:
	int cursor;

	std::vector<SimFile*>SimFiles_Colletion;
	Shape_OpenVSRG* Song_Select_Items;

public:
	SimFiles_Colletion_Load();
	~SimFiles_Colletion_Load();

	void LoadSimFiles();
	std::vector<SimFile*> getSimFilesColletion();
	void NextSong();
	void PreviousSong();

	
	String getNextSongBynumber(int number);
	String getPreviousSongBynumber(int number);

	SimFile* getCurrentSongByCursor();
	
private:

};


