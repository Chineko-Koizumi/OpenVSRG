#define _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING 0
#include "SimFile.h"


#pragma region SimFile


SimFile::SimFile(String SimFile_name, String Dir_Path)
	:SimFile_name(SimFile_name),
	All_metadata_loaded(false),
	Number_of_levels(0),
	sample_start(0.0f),
	sample_lenth(10.0f),
	PoliBPM_F(false)
{
	std::string title		= "#TITLE:";
	std::string artist		= "#ARTIST:";
	std::string banner		= "#BANNER:";
	std::string background	= "#BACKGROUND:";
	std::string mapper		= "#CDTITLE:";
	std::string music_name	= "#MUSIC:";
	std::string samplestart = "#SAMPLESTART:";
	std::string samplelenth = "#SAMPLELENGTH:";
	std::string offset_str	= "#OFFSET:";
	std::string BPM_str		= "#BPMS:";
	std::string notes		= "#NOTES:";

	std::ifstream file(Dir_Path.toAnsiString());//œcie¿ka przychodzaca to œcie¿ka do pliku *.sm iten plik jest otwierany by uzyskaæ dostêp do banera 
	if (!file.is_open())
	{
		std::cout << "b³¹d, nie mozna za³adowaæ pliu sm SimFile.ccp 27 line\n";
	}
	else 
	{
		std::string File_line;
		String temp;
		SM_path = Dir_Path;
		Dir_Path.replace(Dir_Path.find(SimFile_name), SimFile_name.toAnsiString().length(), "");// tutaj œcie¿ka do pliku jest przerabiana na œcie¿kêdo folderu i przypisywana do pola obiektu
		this->Dir_Path = Dir_Path;

		while (std::getline(file,File_line))
		{
			if (!All_metadata_loaded) 
			{
				if (File_line.find(title) != std::string::npos)
				{
					Song_Title = getParameterFromSM(File_line);
					continue;
				}
				if (File_line.find(artist) != std::string::npos)
				{
					Song_Artist = getParameterFromSM(File_line);
					continue;
				}
				if (File_line.find(banner) != std::string::npos)
				{
					temp = getParameterFromSM(File_line);
					if (temp == "")
					{
						Banner_Path = "textures\\GUI\\DefaultNoBanner.png";
					}
					else
					{
						Banner_Path = Dir_Path + "\\" + getParameterFromSM(File_line); //maj¹c inforamcaje z pliku SM jak nazywa sie BG mo¿na je pobraæ sk³¹daj¹c jego œcie¿kê
					}
					continue;
				}
				if (File_line.find(background) != std::string::npos)
				{
					temp = getParameterFromSM(File_line);
					if (temp == "")
					{
						Background_Path = "textures\\GUI\\DefaultNoBackground.png";
					}
					else
					{
						Background_Path = Dir_Path + "\\" + getParameterFromSM(File_line);
					}
					continue;
				}
				if (File_line.find(mapper) != std::string::npos)
				{
					temp = getParameterFromSM(File_line);
					if (temp == "")
					{
						Mapper_Tag_Path = "textures\\GUI\\DefaultNoTag.png";
					}
					else
					{
						Mapper_Tag_Path = Dir_Path + "\\" + temp;
					}
					continue;
				}
				if (File_line.find(music_name) != std::string::npos)
				{
					Music_Path = Dir_Path + "\\" + getParameterFromSM(File_line);
					continue;
				}
				if (File_line.find(samplestart) != std::string::npos)
				{
					temp = getParameterFromSM(File_line);
					if (temp != "")
					{
						sample_start = atof(getParameterFromSM(File_line).c_str());
					}
					continue;
				}
				if (File_line.find(samplelenth) != std::string::npos)
				{
					temp = getParameterFromSM(File_line);
					if (temp != "")
					{
						sample_lenth = atof(getParameterFromSM(File_line).c_str());
					}
					continue;
				}
				if (File_line.find(offset_str) != std::string::npos)
				{
					temp = getParameterFromSM(File_line);
					if (temp != "")
					{
						offset = atof(getParameterFromSM(File_line).c_str());
					}
					continue;
				}
				if (File_line.find(BPM_str) != std::string::npos)
				{
					temp = getParameterFromSM(File_line);
					if (temp != "")
					{
						BPM = atof(getBPMParameterFromSM(File_line).c_str());
					}
					All_metadata_loaded = true;
					continue;
				}
			}
			if ((File_line.find(notes))!=std::string::npos)//#NOTES:
			{
				std::getline(file, File_line);					//dance - single:
				std::getline(file, File_line);					//Gpop:
				std::getline(file, File_line);					//Hard:

				levels[Number_of_levels] = getLevelParameterFromSM(File_line);
				++Number_of_levels;

			}
		}
	}
}

SimFile::~SimFile()
{
}

bool SimFile::isPoliBPM(std::string FileLine)
{
	if (FileLine.find(",")==std::string::npos) 
	{
		return false;
	}
	else true;
}

std::string SimFile::getParameterFromSM(std::string FileLine)
{
	int pos1, pos2;
	pos1 = FileLine.find(":");
	pos2 = FileLine.find(";");
	

	return FileLine.substr(pos1 + 1, pos2 - pos1 - 1);
}

std::string SimFile::getBPMParameterFromSM(std::string FileLine)
{
	int pos1, pos2;
	pos1 = FileLine.find("=");
	pos2 = FileLine.find(";");

	return FileLine.substr(pos1 + 1, pos2 - pos1 - 1);
}

std::string SimFile::getLevelParameterFromSM(std::string FileLine)
{
	int pos2;

	pos2 = FileLine.find(":");
	return FileLine.substr(0, pos2);
}

String SimFile::GetBannerPath()
{
	return Banner_Path;
}

String SimFile::GetBackgroundPath()
{
	return Background_Path;
}

String SimFile::GetMapperTagPath()
{
	return Mapper_Tag_Path;
}

String SimFile::getSongArtist()
{
	return Song_Artist;
}

String SimFile::getSongTitle()
{
	return Song_Title;
}

String SimFile::getMusicPath()
{
	return Music_Path;
}

String SimFile::getSMPath()
{
	return SM_path;
}

String* SimFile::getDifficulties()
{
	return levels;
}

void SimFile::SetBannerpath(String path)
{
	Banner_Path = path;
}

void SimFile::SetArtistTagpath(String path)
{
	Mapper_Tag_Path = path;
}

int SimFile::getDifficultiesCount()
{
	return Number_of_levels;
}

float SimFile::getSampleStart()
{
	return sample_start;
}

float SimFile::getSampleLenth()
{
	return sample_lenth;
}

#pragma endregion

#pragma region Load_SimFileColletion

SimFiles_Colletion_Load::SimFiles_Colletion_Load()
{
	cursor = 0;
}

SimFiles_Colletion_Load::~SimFiles_Colletion_Load()
{
}

void SimFiles_Colletion_Load::LoadSimFiles()
{
	for (std::tr2::sys::recursive_directory_iterator i("Songs"), end; i != end; ++i)//pêtla iteruje po folderach w Songs i wy³apuje wszystkie pliki z *.sm wczytuj¹c ich œcie¿ki do kostruktora
	{
		if (!is_directory(i->path()))
		{
			if (String::InvalidPos != (((String)i->path().filename().c_str()).find(".sm", 0)))
			{
				int checkSM = 0;

				String temp1, temp2;
				temp1 = (String)i->path().filename().c_str();
				temp2 = (String)i->path().c_str();

				checkSM = temp1.toAnsiString().length() - 3;

				if (String::InvalidPos != (((String)i->path().filename().c_str()).find(".sm", checkSM)))
				{
					SimFiles_Colletion.push_back(new SimFile(temp1, temp2));
					std::cout << "File loaded: " << temp2.toAnsiString() << "\n";
				}

			}
		}
	}
	//std::sort(SimFiles_Colletion.begin(), SimFiles_Colletion.end()); napisz funkcjê komparuj¹c¹
}

std::vector<SimFile*> SimFiles_Colletion_Load::getSimFilesColletion()
{
	return SimFiles_Colletion;
}

void SimFiles_Colletion_Load::NextSong()
{
	if (cursor == SimFiles_Colletion.size()-1) 
	{
		cursor = 0;
	}
	else 
	{
		cursor++;
	}
}

void SimFiles_Colletion_Load::PreviousSong()
{
	if (cursor == 0) 
	{
		cursor = SimFiles_Colletion.size()-1;
	}
	else 
	{
		 cursor--;
	}
}

String SimFiles_Colletion_Load::getNextSongBynumber(int number)
{
	if ((cursor + number) >= SimFiles_Colletion.size()) 
	{
		int temp_index = number - (SimFiles_Colletion.size() - cursor);
		return SimFiles_Colletion[temp_index]->getSongArtist() + " - " + SimFiles_Colletion[temp_index]->getSongTitle();
	}
	else 
	{
		return SimFiles_Colletion[cursor + number]->getSongArtist() + " - " + SimFiles_Colletion[cursor + number]->getSongTitle();
	}
}

String SimFiles_Colletion_Load::getPreviousSongBynumber(int number)
{
	if ( (cursor - number) < 0 )
	{
		int temp_index = SimFiles_Colletion.size() - (number - cursor) ;
		return SimFiles_Colletion[temp_index]->getSongArtist() + " - " + SimFiles_Colletion[temp_index]->getSongTitle();
	}
	else
	{
		return SimFiles_Colletion[cursor - number]->getSongArtist() + " - " + SimFiles_Colletion[cursor - number]->getSongTitle();
	}
}

SimFile* SimFiles_Colletion_Load::getCurrentSongByCursor()
{
	return SimFiles_Colletion[cursor];
}

#pragma endregion


