#include "stdafx.h"
#include "GameLoop.h"

GameLoop::GameLoop(RenderWindow* game_ptr, OpenVSRG_Textures *Skins, Score_Handler* score_handler, std::string SimFilePath, String sim_music_path, String BackGround_Path, Font *font, String Artis_title,int key_left,int key_down, int key_up, int key_right, int SongVolume)
	:game(game_ptr),
	Skins(Skins),
	score_handler(score_handler),
	Simfile_Music_Path(sim_music_path),
	Background_Path(BackGround_Path),
	Song_ArtistTitle(Artis_title),
	font(font),
	key_left(key_left),
	key_down(key_down),
	key_up(key_up),
	key_right(key_right),
	SongVolume(SongVolume),
	Background_Dimm(0.0f),
	Song_pitch(1.0f),
	IterratorForBPMBLockCounting(0)
{
	Song_ArtistTitle_Text.setFont(*font);
	Song_ArtistTitle_Text.setString(Song_ArtistTitle);
	Song_ArtistTitle_Text.setCharacterSize(game->getSize().y / 25.0f);

	float ArtistTitle_X = game->getSize().x/2.0f - Song_ArtistTitle_Text.getGlobalBounds().width/2.0f;
	float ArtistTitle_Y = game->getSize().y - Song_ArtistTitle_Text.getGlobalBounds().height*2;

	Song_ArtistTitle_Text.setPosition(ArtistTitle_X, ArtistTitle_Y);

	NotePool_ = new NotePool(game_ptr, score_handler);

	int numLines = 0;
	int numlevels = 0;

	IterratorForBPMBLockCounting_flag_set = false;

	SimFileEnd = new bool;
	*SimFileEnd = false;

	Offset_flag_set = false;

	std::ifstream in(SimFilePath);
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "//")
		{
			++numLines;
			while (std::getline(in, line))
			{
				if (line.substr(0, 1) == ";")
				{
					++numlevels;
				}
				++numLines;
			}
		}
	}
	RawSimFileCount = numLines;
	LevelsCount = numlevels;

	in.clear();
	in.seekg(0, std::ios::beg);

	RawSimFile = new char*[numLines + 1];

	int iterrator = 0;
	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "//")
		{
			RawSimFile[iterrator] = new char[line.length() + 1];
			strcpy(RawSimFile[iterrator],line.c_str());
			iterrator++;

			while (std::getline(in, line))
			{
				RawSimFile[iterrator] = new char[line.length() + 1];
				strcpy(RawSimFile[iterrator], line.c_str());
				iterrator++;
			}
		}
	}
	in.close();
	//std::cout << RawSimFileCount<<"\n"<<LevelsCount<<"\n";
	

	if (Background_T.loadFromFile(BackGround_Path)) 
	{
		Background_S.setTexture(Background_T);
	}
	else 
	{
		Background_T.loadFromFile("Textures\\GUI\\DefaultNoBackground.png");
		Background_S.setTexture(Background_T);
	}

	float screen_game_X = game->getSize().x;
	float Texture_X = Background_T.getSize().x;

	Background_S.setScale(screen_game_X/Texture_X, screen_game_X/Texture_X);
	if (Background_T.getSize().y < game->getSize().y)
	{
		Background_S.move(0.0f, (game->getSize().y - (Background_T.getSize().y*(screen_game_X / Texture_X)))/2.0f);
	}
	else 
	{
		Background_S.setPosition(0.0f,0.0f);
	}
}

GameLoop::~GameLoop()
{
}

void GameLoop::SetMusicOffset(float SimFile_Offset)
{
	SimFile_Offset_from_file = SimFile_Offset;
}

void GameLoop::SetReceptorPosition(float receptor_pos)
{
	Receptor_Possition = receptor_pos;
}

void GameLoop::SetNoteReceptorStartingXPossition(float Note_starting_X)
{
	Note_receptor_starting_Xpos = Note_starting_X;
}

void GameLoop::SetNoteReceptorStartingXPossitionStep(float Note_receptor_starting_Xpos_s)
{
	Note_receptor_starting_Xpos_step = Note_receptor_starting_Xpos_s;
}

void GameLoop::SetNoteYWayLenth(float Note_Yway_l)
{
	Note_Yway_lenth = Note_Yway_l;
}

void GameLoop::SetStartBPM(float start_BPM)
{
	Song_BPM = start_BPM;
}

void GameLoop::SetLevelNumber(int level_num)
{
	Level_number = level_num;
}

void GameLoop::SetNoteScale(float mini_ratio)
{
	Note_Scale = mini_ratio;
}

void GameLoop::SetBackgroundDimm(float dimm_percent)
{
	Background_Dimm = dimm_percent;
	Background_S.setColor(Color(255,255,255,255*(dimm_percent/100.0f)));
}

void GameLoop::SetSongPitch(float pitch)
{
	Song_pitch = pitch;
}

void GameLoop::GenereteLevel(int lvl)
{
	int counter = 0;
	int iterrator = 0;
	int alloc_iterrator = 0;
	int back_value = 0;

	while (1)
	{
		if (lvl == iterrator)
		{
			if (strstr(RawSimFile[counter], ";") != nullptr)
			{
				++counter;
				++alloc_iterrator;

				Level = new char*[alloc_iterrator];
				LevelLinesCount = alloc_iterrator;
				break;
			}
			else
			{
				++alloc_iterrator;
				++counter;
			}

		}
		else if (strstr(RawSimFile[counter], ";") != nullptr)
		{
			++counter;
			++iterrator;
			back_value = counter + 1;
		}
		else
		{
			++counter;
		}

	}

	alloc_iterrator = 0;
	counter = back_value;

	while (1)
	{
		
			if (strstr(RawSimFile[counter], ";") != nullptr)
			{
				Level[alloc_iterrator] = new char[strlen(RawSimFile[counter]) + 1];
				LevelLinesCount = alloc_iterrator;
				break;
			}
			else
			{
				Level[alloc_iterrator] = new char[strlen(RawSimFile[counter]) + 1];
				++alloc_iterrator;
				++counter;
			}

	}

	alloc_iterrator = 0;
	counter = back_value;

	while (1)
	{

		if (strstr(RawSimFile[counter], ";") != nullptr)
		{
			strcpy(Level[alloc_iterrator], RawSimFile[counter]);
			counter = 0;

			break;
		}
		else
		{
			strcpy(Level[alloc_iterrator], RawSimFile[counter]);
			//std::cout << "[" << iterrator << "]" << Level[alloc_iterrator]<< "\n";
			++counter;
			++alloc_iterrator;
		}
	}
}
void GameLoop::CalllSimFileNextBPMBLockGenerate(float receptor_pos, float DestroyXPos)
{

	int iterratorBackValue = 0;
	int SimFileBPMBlockCounter = 0;
	float Note0_Xpos, Note1_Xpos, Note2_Xpos, Note3_Xpos;
	float Note_Ypos, Note_Ypos_for_j;

	Note_Ypos = Receptor_Possition + Note_Yway_lenth;
	

	Note0_Xpos = Note_receptor_starting_Xpos;
	Note1_Xpos = Note_receptor_starting_Xpos + Note_receptor_starting_Xpos_step;
	Note2_Xpos = Note_receptor_starting_Xpos + Note_receptor_starting_Xpos_step * 2;
	Note3_Xpos = Note_receptor_starting_Xpos + Note_receptor_starting_Xpos_step * 3;

	if (*SimFileEnd)return;

	if (!IterratorForBPMBLockCounting_flag_set)
	{
		while (1)
		{
			if (strlen( Level[IterratorForBPMBLockCounting]) == 4)
			{
				iterratorBackValue = IterratorForBPMBLockCounting;
				IterratorForBPMBLockCounting_flag_set = true;
				break;
			}
			++IterratorForBPMBLockCounting;
		}
	}
	else
	{
		iterratorBackValue = IterratorForBPMBLockCounting;
	}

	while (1)
	{
		if (strstr(Level[IterratorForBPMBLockCounting], ",") != nullptr || strstr(Level[IterratorForBPMBLockCounting], ";") != nullptr)
		{
			if (strstr(Level[IterratorForBPMBLockCounting], ";") != nullptr)

			{
				*SimFileEnd = true;
			}

			SimFileBPMBlockCounter = IterratorForBPMBLockCounting - iterratorBackValue; //jakiej d³ugoœci jest blok BPM 
			++IterratorForBPMBLockCounting;

			Note_Ypos_for_j = (Note_Yway_lenth / SimFileBPMBlockCounter);

			break;
		}
		++IterratorForBPMBLockCounting;
	}

	for (int j = 0; j < SimFileBPMBlockCounter; ++j)
	{
		//std::cout << Level[iterratorBackValue + j].toAnsiString() <<": " << j+1 << "\n";
		for (int i = 0; i < 4; ++i)
		{
			switch (i)
			{
			case 0:
			{
				switch (Level[iterratorBackValue + j][i])//lewa
				{
					case NOTE:
					{

						NotePool_->create(Skins->Left, Note0_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					case HOLD_HEAD:
					{
						NotePool_->create(Skins->Left, Note0_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					case ROLL_HEAD:
					{
						NotePool_->create(Skins->Left, Note0_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					default: break;
				}
			} break;
			case 1:
			{
				switch (Level[iterratorBackValue + j][i])//dó³
				{
					case NOTE:
					{
						NotePool_->create(Skins->Down, Note1_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					case HOLD_HEAD:
					{
						NotePool_->create(Skins->Down, Note1_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					case ROLL_HEAD:
					{
						NotePool_->create(Skins->Down, Note1_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					default: break;
				}
			} break;
			case 2:
			{

				switch (Level[iterratorBackValue + j][i])//góra
				{
					case NOTE:
					{
						NotePool_->create(Skins->Up, Note2_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					case HOLD_HEAD:
					{

						NotePool_->create(Skins->Up, Note2_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					case ROLL_HEAD:
					{

						NotePool_->create(Skins->Up, Note2_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					default: break;
				}
			} break;
			case 3:
			{
				switch (Level[iterratorBackValue + j][i])//prawa
				{
					case NOTE:
					{
						NotePool_->create(Skins->Right, Note3_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					case HOLD_HEAD:
					{

						NotePool_->create(Skins->Right, Note3_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					case ROLL_HEAD:
					{

						NotePool_->create(Skins->Right, Note3_Xpos, Note_Ypos   + Note_Ypos_for_j*j, DestroyXPos, i, Note_Scale);

					}break;

					default: break;
				}
				} break;

				default: break;
			}
		}
	}
	if (*SimFileEnd)IterratorForBPMBLockCounting = 0;
	//std::cout<<"------" << "\n";
}
void GameLoop::CalculateBPMVariables(float BPM)
{
	Song_BPM = BPM;
	Song_BPS = Song_BPM / 60.0f;
	Beat_Time = 1.0f / Song_BPS;
	Beat_Block_Time = Beat_Time * 4.0f;
}

void GameLoop::RunGame()
{
	sf::Music *music;
	music = new Music();
	music->setPitch(Song_pitch);
	music->setVolume(SongVolume);

	CalculateBPMVariables(Song_BPM*Song_pitch);

	score_handler->SetEndOfSimFilePTR(SimFileEnd);
	score_handler->calculateTiming(Song_BPS, Note_Yway_lenth);

	Input_Handler input_handler(key_left, key_down, key_up, key_right, SimFileEnd ,score_handler, NotePool_);

	Receptor receptor(Skins->Receptor_left, Skins->Receptor_down, Skins->Receptor_up, Skins->Receptor_right, Skins->Tap_Receptor_left, Skins->Tap_Receptor_down, Skins->Tap_Receptor_up, Skins->Tap_Receptor_right, &input_handler, game);
	receptor.SetAllPositions(Note_receptor_starting_Xpos, score_handler->Receptor_pos, Note_receptor_starting_Xpos_step);
	receptor.SetScale(Note_Scale, Note_Scale);

	Thread Input_Handler_thread(&Input_Handler::KeysState, &input_handler);
	Input_Handler_thread.launch();

	Thread Score_Handler_thread(&Score_Handler::ThreadScoreCalculating, score_handler);
	Score_Handler_thread.launch();

	GenereteLevel(Level_number);
	score_handler->SetCoughtPointerSize(LevelLinesCount*4);

	clockl.restart();
	
	if (!music->openFromFile(Simfile_Music_Path))
	{ 
		std::cout << "music load error gameloop.cpp 401" << "\n";
		return;
	}
	
	while (1)
	{
		Global_elapsed = clockl.restart();

		NotePool_->animate(-((Note_Yway_lenth  )*(Global_elapsed.asSeconds() / Beat_Block_Time)), score_handler->scores[0]);

		Next_Block_Generate += Global_elapsed;
		
		//#OFFSET
		if (Offset_flag_set) 
		{
			if (Next_Block_Generate.asSeconds() >= Beat_Block_Time)
			{
				CalllSimFileNextBPMBLockGenerate(receptor.GetYPossition(), score_handler->scores[9]);
				Next_Block_Generate = ZERO;
			}
		}
		else 
		{
			SimFile_offset_temp += Global_elapsed;
			if (-SimFile_Offset_from_file/Song_pitch <= 2*Beat_Block_Time)
			{
				if (SimFile_offset_temp.asSeconds() >= (2*Beat_Block_Time + SimFile_Offset_from_file/ Song_pitch))
				{
					if (music->getStatus() == 0)music->play();
					Offset_flag_set = true;
				}
				if (Next_Block_Generate.asSeconds() >= Beat_Block_Time)
				{
					CalllSimFileNextBPMBLockGenerate(receptor.GetYPossition(), score_handler->scores[9]);
					Next_Block_Generate = ZERO;
				}
			}
			else
			{
				if (music->getStatus() == 0)music->play();
				if (SimFile_offset_temp.asSeconds() >= (-SimFile_Offset_from_file/ Song_pitch - Beat_Block_Time))
				{
					CalllSimFileNextBPMBLockGenerate(receptor.GetYPossition(), score_handler->scores[9]);
					Next_Block_Generate = ZERO;
					Offset_flag_set = true;
				}
			}
		}

		game->clear();

		game->draw(Background_S,&Background_T);
		
		score_handler->RedrawScoreAnimations();
		receptor.Redraw_pattern();
		NotePool_->RedrawNotes();
		receptor.Redraw_flash();

		game->draw(Song_ArtistTitle_Text);

		game->display();

		if (*SimFileEnd)
		{
			EndOfGamePlay += Global_elapsed;
			if ((EndOfGamePlay.asSeconds() >Beat_Block_Time*3.0f))
			{
				input_handler.Sim_File_End = true;
				score_handler->simfile_end_F = true;

				score_handler->CalculateDP();

				NotePool_->~NotePool();

				for (int i = 0; i < RawSimFileCount;++i) 
				{
					delete[] RawSimFile[i];
				}
				for (int i = 0; i < LevelLinesCount; ++i)
				{
					delete[] Level[i];
				}

				delete[] RawSimFile;
				delete[] Level;

				delete SimFileEnd;
				delete music;

				return;
			}
		}
	}

	
}

