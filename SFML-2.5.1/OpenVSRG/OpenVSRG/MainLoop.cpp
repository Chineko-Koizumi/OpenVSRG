#define _SILENCE_TR2_SYS_NAMESPACE_DEPRECATION_WARNING 0

#include <sfml\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Shape_OpenVSRG.h"
#include "Animation.h"
#include "SimFile.h"
#include "Sound.h"
#include "Config.h"
#include "AnimatedArt.h"
#include <$(ProjectDir)\..\..\..\SFML test\SFML test\GameLoop.h>

#include <iostream>
#include <filesystem>

using namespace sf;

class GameWindow 
{
public:
	RenderWindow *Display;

	GameWindow(int x, int y) 
	{
		 Display = new RenderWindow(VideoMode(x, y), "SFML", Style::None);
		 Display->setMouseCursorVisible(false);
	}
	virtual  ~GameWindow()
	{}
	
};

class MainLoopCursor 
{
private:
	int LoopCursor;

public:
	MainLoopCursor() 
	{
		LoopCursor = 0;
	}
	~MainLoopCursor(){}

	int getLoopCursor() 
	{
		return LoopCursor;
	}
	void setLoopCursor(int x) 
	{
		LoopCursor = x;
	}
};

enum CursorEnum
{
	MAIN_MENU		= 0,
	OPTIONS			= 1,
	INFO			= 2,
	EXIT			= 3,
	COLOR_SELECT	= 4,

	SONG_SELECT		= 10,
	RESOLUTION		= 11,
	KEYS			= 12,
	KEYS_SELECT		= 13,

	SONG_MENU		= 100,

	GAME_LOOP		= 1000
};

int main()
{
	Config Configuration_details;

	Game_loop_config game_loop_config;
	OpenVSRG_Textures Skins;

	SimFiles_Colletion_Load Loaded_simfile_coletion;
	Loaded_simfile_coletion.LoadSimFiles();

	GameWindow *Game;
	Game = new GameWindow(Configuration_details.getScreenWidth(), Configuration_details.getScreenHeight());

	SelectColorWheel select_main_color(Game->Display, Configuration_details.getFont());
	MenuArtRender Main_menu_splashart(Game->Display, Configuration_details.getThemeColor());
	//MenuLogoRender Info_menu_logo(Game->Display); tutaj dodaj nekosia, narazie tylko siê krêci.
	
	MainLoopCursor LoopCursor;

	Shape_Menu Menu(Game->Display, 4, (String)"textures\\GUI\\Menu\\Start.png", (String)"textures\\GUI\\Menu\\Options.png", (String)"textures\\GUI\\Menu\\Info.png", (String)"textures\\GUI\\Menu\\Exit.png");
	Menu_Colletion_Animation Menu_M(&Menu);

	Shape_Menu Options(Game->Display, 5, (String)"textures\\GUI\\Options\\Resolution.png", (String)"textures\\GUI\\Options\\Hitsound.png", (String)"textures\\GUI\\Options\\Sound.png", (String)"textures\\GUI\\Options\\Keys.png", (String)"textures\\GUI\\Options\\Back.png");
	Menu_Colletion_Animation Menu_O(&Options);

		Shape_Menu Resolution(Game->Display, 6, (String)"textures\\GUI\\Resolutions\\1024_576.png", (String)"textures\\GUI\\Resolutions\\1280_720.png", (String)"textures\\GUI\\Resolutions\\1366_768.png", (String)"textures\\GUI\\Resolutions\\1600_900.png", (String)"textures\\GUI\\Resolutions\\1920_1080.png", (String)"textures\\GUI\\Resolutions\\Back.png");
		Menu_Colletion_Animation Menu_R(&Resolution);

		Shape_Menu Select_Keys(Game->Display, 5, (String)"textures\\GUI\\Keys\\Left.png", (String)"textures\\GUI\\Keys\\Down.png", (String)"textures\\GUI\\Keys\\Up.png", (String)"textures\\GUI\\Keys\\Right.png", (String)"textures\\GUI\\Resolutions\\Back.png");
		Menu_Colletion_Animation Menu_SK(&Select_Keys);
		Selected_Key_PopUp Select_keys_popup(Game->Display, Configuration_details.getFont(), Configuration_details.getThemeColor());

		IN__DE_crementingText	HitSound_Value_Text(Game->Display, Configuration_details.getThemeColor(), 0, 100, Configuration_details.HitSoundsLevel(), Options.GetWholePTR()[1]->getPosition().x + Options.GetWholePTR()[1]->getSize().x, Options.GetWholePTR()[1]->getPosition().y),
								Sound_Value_Text(Game->Display, Configuration_details.getThemeColor(), 0, 100, Configuration_details.SoundsLevel(), Options.GetWholePTR()[2]->getPosition().x + Options.GetWholePTR()[2]->getSize().x, Options.GetWholePTR()[2]->getPosition().y),
								Left_Selected_Key	(Game->Display, Configuration_details.getThemeColor(), 0, 0, 0, Select_Keys.GetWholePTR()[0]->getPosition().x + Select_Keys.GetWholePTR()[1]->getSize().x, Select_Keys.GetWholePTR()[0]->getPosition().y),
								Down_Selected_Key	(Game->Display, Configuration_details.getThemeColor(), 0, 0, 0, Select_Keys.GetWholePTR()[1]->getPosition().x + Select_Keys.GetWholePTR()[1]->getSize().x, Select_Keys.GetWholePTR()[1]->getPosition().y),
								Up_Selected_Key		(Game->Display, Configuration_details.getThemeColor(), 0, 0, 0, Select_Keys.GetWholePTR()[2]->getPosition().x + Select_Keys.GetWholePTR()[1]->getSize().x, Select_Keys.GetWholePTR()[2]->getPosition().y),
								Right_Selected_Key	(Game->Display, Configuration_details.getThemeColor(), 0, 0, 0, Select_Keys.GetWholePTR()[3]->getPosition().x + Select_Keys.GetWholePTR()[1]->getSize().x, Select_Keys.GetWholePTR()[3]->getPosition().y);

	Main_Menu_Info manimenuinfo(Game->Display);

	Text_menu	song_modificators_menu(Game->Display, &game_loop_config);
				song_modificators_menu.SetAllPossitions();

	

	HitSound	Menu_Hitsound("Sounds\\_common change.ogg"), 
				Menu_ChangeSection_Hitsound("Sounds\\Common start.ogg"), 
				Menu_Back_HitSound("Sounds\\Common back.ogg"), 
				Menu_Sound_Loop("Sounds\\_common menu music (loop).ogg");

				Menu_Sound_Loop.GetSOUND()->setVolume((float)Configuration_details.SoundsLevel());
				Menu_Hitsound.GetSOUND()->setVolume((float)Configuration_details.HitSoundsLevel());
				Menu_ChangeSection_Hitsound.GetSOUND()->setVolume((float)Configuration_details.HitSoundsLevel());
				Menu_Back_HitSound.GetSOUND()->setVolume((float)Configuration_details.HitSoundsLevel());

	Song_Select Song(Game->Display, Configuration_details.getThemeColor());
	SongSelectSongsList SongsList(Game->Display,Configuration_details.getFont(), Configuration_details.getThemeColor());

				for (int i = 0; i < 7; ++i) //wype³nia pola "not loaded" w menu wybioru piosenki tytu³ami
				{
					Song.setSong(Loaded_simfile_coletion.getCurrentSongByCursor(), Configuration_details.SoundsLevel());
					SongsList.setCenterSong(Song.getArtistTitle());
					Loaded_simfile_coletion.NextSong();
					SongsList.moveDown(Loaded_simfile_coletion.getNextSongBynumber(6), Loaded_simfile_coletion.getPreviousSongBynumber(6));
					Song.StopMusicFromPreview();
				}

	Event evt;

	LoopCursor.setLoopCursor(COLOR_SELECT);
	while (Game->Display->isOpen())
	{
		Game->Display->clear();

		//updates
		switch (LoopCursor.getLoopCursor()) 
		{
			case COLOR_SELECT:
			{
				while (Game->Display->pollEvent(evt))
				{
					switch (evt.type)
					{
					case Event::KeyPressed:
					{
						if (Keyboard::isKeyPressed(Keyboard::Key::Left))
						{
							select_main_color.MoveLeft();
							Menu_Hitsound.TriggerHitSound();
						}
						if (Keyboard::isKeyPressed(Keyboard::Key::Right))
						{
							select_main_color.MoveRight();
							Menu_Hitsound.TriggerHitSound();
						}
						if (Keyboard::isKeyPressed(Keyboard::Key::Up))
						{
							select_main_color.MoveLeft();
							Menu_Hitsound.TriggerHitSound();
						}
						if (Keyboard::isKeyPressed(Keyboard::Key::Down))
						{
							select_main_color.MoveRight();
							Menu_Hitsound.TriggerHitSound();
						}
						if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
						{
							Game->Display->close();
							Game->~GameWindow();
							return 0;
						}
						if (Keyboard::isKeyPressed(Keyboard::Key::Return))
						{
							Configuration_details.setThemeColor(select_main_color.getSelectedColor());

							Main_menu_splashart.setColor(Configuration_details.getThemeColor());
							HitSound_Value_Text.setColor(Configuration_details.getThemeColor());
							Sound_Value_Text.setColor(Configuration_details.getThemeColor());
							Song.setColor(Configuration_details.getThemeColor());
							SongsList.setColor(Configuration_details.getThemeColor());
							song_modificators_menu.SetColor(Configuration_details.getThemeColor());

							Select_keys_popup.setColor(Configuration_details.getThemeColor());
							
							Left_Selected_Key.setColor(Configuration_details.getThemeColor());
							Left_Selected_Key.setStringValue(Left_Selected_Key.convertIntToKey(Configuration_details.getKey(0)));

							Down_Selected_Key.setColor(Configuration_details.getThemeColor());
							Down_Selected_Key.setStringValue(Down_Selected_Key.convertIntToKey(Configuration_details.getKey(1)));

							Up_Selected_Key.setColor(Configuration_details.getThemeColor());
							Up_Selected_Key.setStringValue(Up_Selected_Key.convertIntToKey(Configuration_details.getKey(2)));

							Right_Selected_Key.setColor(Configuration_details.getThemeColor());
							Right_Selected_Key.setStringValue(Right_Selected_Key.convertIntToKey(Configuration_details.getKey(3)));

							LoopCursor.setLoopCursor(MAIN_MENU);
						}
						break;
					}
					}
				}
				select_main_color.readrawAll();
			}
			break;

			case MAIN_MENU:
			{
				if (Menu_Sound_Loop.GetSOUND()->getStatus()!=SoundSource::Status::Playing) 
				{
					Menu_Sound_Loop.TriggerHitSound();
				}
				while (Game->Display->pollEvent(evt))
				{
					switch (evt.type)
					{
						case Event::KeyPressed:
						{
							if (Keyboard::isKeyPressed(Keyboard::Key::Up))
							{
								Menu_Hitsound.TriggerHitSound();
								Menu_M.DecrementCursor();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Down))
							{
								Menu_Hitsound.TriggerHitSound();
								Menu_M.IncrementCursor();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Return))
							{

								if (Menu_M.getCursor() == 0) 
								{
									Menu_ChangeSection_Hitsound.TriggerHitSound();
									LoopCursor.setLoopCursor(SONG_SELECT);
									Song.setSong(Loaded_simfile_coletion.getCurrentSongByCursor(),Configuration_details.SoundsLevel());
								}
								if (Menu_M.getCursor() == 1)
								{
									Menu_ChangeSection_Hitsound.TriggerHitSound();
									LoopCursor.setLoopCursor(OPTIONS);
								}
								if (Menu_M.getCursor() == 2)
								{
									Menu_ChangeSection_Hitsound.TriggerHitSound();
									LoopCursor.setLoopCursor(INFO);
								}
								if (Menu_M.getCursor() == Menu_M.getCursorLimit())
								{
									Menu_ChangeSection_Hitsound.TriggerHitSound();
									LoopCursor.setLoopCursor(EXIT);
								}
								
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
							{
								Menu_ChangeSection_Hitsound.TriggerHitSound();
								Game->Display->close();
								Game->~GameWindow();
								return 0;
							}
							break;
						}
					}
				}
				Main_menu_splashart.readrawAll();
				Menu_M.AnimateAll();
				Menu_M.getMenu_colletionPTR()->RedrawAll();
			}
			break;

			case SONG_SELECT:
			{
				Menu_Sound_Loop.GetSOUND()->pause();
				
				while (Game->Display->pollEvent(evt)) 
				{
					switch (evt.type)
					{
						case Event::KeyPressed:
						{
							if (Keyboard::isKeyPressed(Keyboard::Key::Left))
							{
								Song.INcrementDifficulty();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Right))
							{
								Song.DEcrementDifficulty();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Up))
							{
								Loaded_simfile_coletion.PreviousSong();
								Song.setSong(Loaded_simfile_coletion.getCurrentSongByCursor(), Configuration_details.SoundsLevel());
								
								SongsList.moveUp(Loaded_simfile_coletion.getNextSongBynumber(6), Loaded_simfile_coletion.getPreviousSongBynumber(6));
								SongsList.setCenterSong(Song.getArtistTitle());
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Down))
							{
								Loaded_simfile_coletion.NextSong();
								Song.setSong(Loaded_simfile_coletion.getCurrentSongByCursor(), Configuration_details.SoundsLevel());

								SongsList.moveDown(Loaded_simfile_coletion.getNextSongBynumber(6), Loaded_simfile_coletion.getPreviousSongBynumber(6));
								SongsList.setCenterSong(Song.getArtistTitle());
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
							{
								Menu_Back_HitSound.TriggerHitSound();
								LoopCursor.setLoopCursor(MAIN_MENU);
								Song.StopMusicFromPreview();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Return))
							{
								game_loop_config.Music_Offset = Loaded_simfile_coletion.getCurrentSongByCursor()->offset;
								game_loop_config.Start_BPM = Loaded_simfile_coletion.getCurrentSongByCursor()->BPM;
								game_loop_config.level_number = Song.getDiffculty();
								Song.StopMusicFromPreview();
								LoopCursor.setLoopCursor(SONG_MENU);
							}
							break;
						}
					}
				}
				Song.RedrawAllWithTexts(Loaded_simfile_coletion.getCurrentSongByCursor());
				SongsList.redrawAll();
			}
			break;

			case SONG_MENU:
			{
				while (Game->Display->pollEvent(evt))
				{
					switch (evt.type)
					{
						case Event::KeyPressed:
						{
							if (Keyboard::isKeyPressed(Keyboard::Key::Left))
							{
								song_modificators_menu.DEcrementCursorX();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Right))
							{
								song_modificators_menu.INcrementCursorX();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Up))
							{
								song_modificators_menu.DEcrementCursorY();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Down))
							{
								song_modificators_menu.INcrementCursorY();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
							{
								LoopCursor.setLoopCursor(SONG_SELECT);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Return))
							{
								if (song_modificators_menu.getYCursor() == song_modificators_menu.getLinesCount()-1) 
								{
									LoopCursor.setLoopCursor(GAME_LOOP);
								}
								else 
								{
									song_modificators_menu.DoSomething();
								}
								
							}
							break;
						}
					}
				}
				song_modificators_menu.RedrawAllMenuElements();
			}
			break;

			case GAME_LOOP:
			{

				float BPM_speed_multiplicator = game_loop_config.BPM_speed_multiplicator;
				String ArtistTitle_temp = Loaded_simfile_coletion.getCurrentSongByCursor()->getSongArtist() + " - " + Loaded_simfile_coletion.getCurrentSongByCursor()->getSongTitle();

				Score_Handler score(Game->Display, ArtistTitle_temp);
				score.SetFont(Configuration_details.getFont(), int(Game->Display->getSize().y/6.0f), Configuration_details.getThemeColor());

				GameLoop Current_Simfile(Game->Display, &Skins, &score, Loaded_simfile_coletion.getCurrentSongByCursor()->getSMPath(), Loaded_simfile_coletion.getCurrentSongByCursor()->getMusicPath(), Loaded_simfile_coletion.getCurrentSongByCursor()->GetBackgroundPath(),Configuration_details.getFont() ,ArtistTitle_temp, Configuration_details.getKey(0), Configuration_details.getKey(1), Configuration_details.getKey(2), Configuration_details.getKey(3), Configuration_details.SoundsLevel());
				
				Current_Simfile.SetMusicOffset(game_loop_config.Music_Offset + game_loop_config.Player_Offset);
				Current_Simfile.SetNoteReceptorStartingXPossition(Game->Display->getSize().x*0.5f-2.0f* game_loop_config.Note_Receptor_Starting_XPossition_step);
				Current_Simfile.SetNoteReceptorStartingXPossitionStep(game_loop_config.Note_Receptor_Starting_XPossition_step);
				Current_Simfile.SetReceptorPosition(game_loop_config.Receptor_Position);
				Current_Simfile.SetNoteYWayLenth(Game->Display->getSize().y*BPM_speed_multiplicator);
				Current_Simfile.SetStartBPM(game_loop_config.Start_BPM);
				Current_Simfile.SetLevelNumber(game_loop_config.level_number);
				Current_Simfile.SetNoteScale(game_loop_config.Note_Scale);
				Current_Simfile.SetBackgroundDimm(game_loop_config.Background_Dimm);
				Current_Simfile.SetSongPitch(game_loop_config.Game_Speed);

				score.SetReceptorPossition(game_loop_config.Receptor_Position);
				score.SetComboXYPossition(Game->Display->getSize().x*0.5f + 2.0f * game_loop_config.Note_Receptor_Starting_XPossition_step, Game->Display->getSize().y *0.1f);
				score.SetLifeBarOver("textures\\Gui\\OverLifeBar.png", "textures\\Gui\\HPBar.png", Game->Display->getSize().x*0.5f - 2.0f * game_loop_config.Note_Receptor_Starting_XPossition_step, game_loop_config.Note_Receptor_Starting_XPossition_step);
				
				Current_Simfile.RunGame();

				score.TranslateCoughtPossitionsToTimeSamples();
				while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
				{

					Game->Display->clear();

					Game->Display->draw(Current_Simfile.Background_S, &Current_Simfile.Background_T);
					score.DrawScoreBoard();

					Game->Display->display();

					sf::sleep(seconds(0.02f));
				}

				sf::sleep(seconds(0.2f));
				LoopCursor.setLoopCursor(SONG_SELECT);
			}
			break;

			case OPTIONS:
			{
				if (Menu_Sound_Loop.GetSOUND()->getStatus() != SoundSource::Status::Playing)
				{
					Menu_Sound_Loop.TriggerHitSound();
				}
				while (Game->Display->pollEvent(evt))
				{
					switch (evt.type)
					{
						case Event::KeyPressed:
						{
							if (Keyboard::isKeyPressed(Keyboard::Key::Up))
							{
								Menu_Hitsound.TriggerHitSound();
								Menu_O.DecrementCursor();
							}

							if(Keyboard::isKeyPressed(Keyboard::Key::Down))
							{
								Menu_Hitsound.TriggerHitSound();
								Menu_O.IncrementCursor();
							}

							if (Keyboard::isKeyPressed(Keyboard::Key::Left))
							{
								if (Menu_O.getCursor() == 1)
								{
									HitSound_Value_Text.decrementTextValue();

									Menu_Hitsound.GetSOUND()->setVolume((float)HitSound_Value_Text.getActualValue());
									Menu_ChangeSection_Hitsound.GetSOUND()->setVolume((float)HitSound_Value_Text.getActualValue());
									Menu_Back_HitSound.GetSOUND()->setVolume((float)HitSound_Value_Text.getActualValue());
										
								}
								else if(Menu_O.getCursor() == 2)
								{
									Sound_Value_Text.decrementTextValue();
									Menu_Sound_Loop.GetSOUND()->setVolume((float)Sound_Value_Text.getActualValue());
								}
								
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Right))
							{
								if (Menu_O.getCursor() == 1)
								{
									HitSound_Value_Text.incrementTextValue();


									Menu_Hitsound.GetSOUND()->setVolume((float)HitSound_Value_Text.getActualValue());
									Menu_ChangeSection_Hitsound.GetSOUND()->setVolume((float)HitSound_Value_Text.getActualValue());
									Menu_Back_HitSound.GetSOUND()->setVolume((float)HitSound_Value_Text.getActualValue());
								}
								else if (Menu_O.getCursor() == 2)
								{
									Sound_Value_Text.incrementTextValue();
									Menu_Sound_Loop.GetSOUND()->setVolume((float)Sound_Value_Text.getActualValue());
								}
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
							{
								Menu_Back_HitSound.TriggerHitSound();
								LoopCursor.setLoopCursor(MAIN_MENU);

								Configuration_details.setHitSoundLevel(HitSound_Value_Text.getActualValue());
								Configuration_details.setSoundLevel(Sound_Value_Text.getActualValue());
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Return))
							{
								if (Menu_O.getCursor() == 0)
								{
									Menu_ChangeSection_Hitsound.TriggerHitSound();
									LoopCursor.setLoopCursor(RESOLUTION);
								}
								else if (Menu_O.getCursor() == 3) 
								{
									Menu_ChangeSection_Hitsound.TriggerHitSound();
									LoopCursor.setLoopCursor(KEYS);
								}
								else if (Menu_O.getCursor() == Menu_O.getCursorLimit())
								{
									Menu_ChangeSection_Hitsound.TriggerHitSound();
									LoopCursor.setLoopCursor(MAIN_MENU);

									Configuration_details.setHitSoundLevel(HitSound_Value_Text.getActualValue());
									Configuration_details.setSoundLevel(Sound_Value_Text.getActualValue());
								}
							}
						}
						break;
					}
				}
				Main_menu_splashart.readrawAll();
				Menu_O.AnimateAll();
				Menu_O.getMenu_colletionPTR()->RedrawAll();

				Sound_Value_Text.redrawIText();
				HitSound_Value_Text.redrawIText();
			}
			break;

			case RESOLUTION:
			{
				if (Menu_Sound_Loop.GetSOUND()->getStatus() != SoundSource::Status::Playing)
				{
					Menu_Sound_Loop.TriggerHitSound();
				}
				while (Game->Display->pollEvent(evt))
				{
					switch (evt.type)
					{
						case Event::KeyPressed:
						{
							if (Keyboard::isKeyPressed(Keyboard::Key::Up))
							{
								Menu_R.DecrementCursor();
								Menu_Hitsound.TriggerHitSound();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Down))
							{
								Menu_R.IncrementCursor();
								Menu_Hitsound.TriggerHitSound();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
							{
								Menu_Back_HitSound.TriggerHitSound();
								LoopCursor.setLoopCursor(OPTIONS);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Return))
							{
								if (Menu_R.getCursor() == Menu_R.getCursorLimit())
								{
									Menu_ChangeSection_Hitsound.TriggerHitSound();
									LoopCursor.setLoopCursor(OPTIONS);
								}
								if (Menu_R.getCursor() == 0)
								{
									Configuration_details.setScreenHeightAndWidth(1024, 576);
									Game->Display->close();
									Game->~GameWindow();
									return 0;
								}
								if (Menu_R.getCursor() == 1)
								{
									Configuration_details.setScreenHeightAndWidth(1280, 720);
									Game->Display->close();
									Game->~GameWindow();
									return 0;
									
								}
								if (Menu_R.getCursor() == 2)
								{
									Configuration_details.setScreenHeightAndWidth(1366, 768);
									Game->Display->close();
									Game->~GameWindow();
									return 0;
							
								}
								if (Menu_R.getCursor() == 3)
								{
									Configuration_details.setScreenHeightAndWidth(1600, 900);
									Game->Display->close();
									Game->~GameWindow();
									return 0;
						
								}
								if (Menu_R.getCursor() == 4)
								{
									Configuration_details.setScreenHeightAndWidth(1920, 1080);
									Game->Display->close();
									Game->~GameWindow();
									return 0;
								}
							}
						}
						break;
					}
				}
				Main_menu_splashart.readrawAll();
				Menu_R.AnimateAll();
				Menu_R.getMenu_colletionPTR()->RedrawAll();
			}
			break;

			case KEYS:
			{
				if (Menu_Sound_Loop.GetSOUND()->getStatus() != SoundSource::Status::Playing)
				{
					Menu_Sound_Loop.TriggerHitSound();
				}

				while (Game->Display->pollEvent(evt))
				{
					switch (evt.type)
					{
						case Event::KeyPressed:
						{
				
							if (Keyboard::isKeyPressed(Keyboard::Key::Up))
							{
								Menu_Hitsound.TriggerHitSound();
								Menu_SK.DecrementCursor();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Down))
							{
								Menu_Hitsound.TriggerHitSound();
								Menu_SK.IncrementCursor();
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
							{
								LoopCursor.setLoopCursor(OPTIONS);
							}
							if (Keyboard::isKeyPressed(Keyboard::Key::Return))
							{
								if (Menu_SK.getCursor() == 0) 
								{
									Select_keys_popup.setKey(Keyboard::Key(Configuration_details.getKey(0)), 0);
									LoopCursor.setLoopCursor(KEYS_SELECT);
								}
								else if(Menu_SK.getCursor() == 1)
								{
									Select_keys_popup.setKey(Keyboard::Key(Configuration_details.getKey(1)), 1);
									LoopCursor.setLoopCursor(KEYS_SELECT);
								}
								else if (Menu_SK.getCursor() == 2)
								{
									Select_keys_popup.setKey(Keyboard::Key(Configuration_details.getKey(2)), 2);
									LoopCursor.setLoopCursor(KEYS_SELECT);
								}
								else if (Menu_SK.getCursor() == 3)
								{
									Select_keys_popup.setKey(Keyboard::Key(Configuration_details.getKey(3)), 3);
									LoopCursor.setLoopCursor(KEYS_SELECT);
								}

								if (Menu_SK.getCursor() == Menu_SK.getCursorLimit())
								{
									Menu_ChangeSection_Hitsound.TriggerHitSound();
									LoopCursor.setLoopCursor(OPTIONS);
								}
							}
							break;
						}
					}
				}
				Main_menu_splashart.readrawAll();

				Menu_SK.AnimateAll();
				Menu_SK.getMenu_colletionPTR()->RedrawAll();

				Left_Selected_Key.redrawAsNonNumericText();
				Down_Selected_Key.redrawAsNonNumericText();
				Up_Selected_Key.redrawAsNonNumericText();
				Right_Selected_Key.redrawAsNonNumericText();
			}
			break;

			case KEYS_SELECT:
			{
				if (Menu_Sound_Loop.GetSOUND()->getStatus() != SoundSource::Status::Playing)
				{
					Menu_Sound_Loop.TriggerHitSound();
				}

				while (Game->Display->pollEvent(evt))
				{
					switch (evt.type)
					{
						case Event::KeyPressed:
						{
							
							if (Keyboard::isKeyPressed(Keyboard::Key::Return))
							{
								Configuration_details.setKey(Select_keys_popup.getKey(), Select_keys_popup.getReceptorNumber());

								Left_Selected_Key.setStringValue(Left_Selected_Key.convertIntToKey(Configuration_details.getKey(0)));
								Down_Selected_Key.setStringValue(Down_Selected_Key.convertIntToKey(Configuration_details.getKey(1)));
								Up_Selected_Key.setStringValue(Up_Selected_Key.convertIntToKey(Configuration_details.getKey(2)));
								Right_Selected_Key.setStringValue(Right_Selected_Key.convertIntToKey(Configuration_details.getKey(3)));

								LoopCursor.setLoopCursor(KEYS);
							}
							else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
							{
								LoopCursor.setLoopCursor(KEYS);
							}
							else 
							{
								Select_keys_popup.setKey(evt.key.code, Select_keys_popup.getReceptorNumber());
							}
							
							break;
						}
					}
				}
				Main_menu_splashart.readrawAll();
				Menu_SK.AnimateAll();
				Menu_SK.getMenu_colletionPTR()->RedrawAll();

				Select_keys_popup.redrawAll();

			}
			break;

			case INFO:
			{
				if (Menu_Sound_Loop.GetSOUND()->getStatus() != SoundSource::Status::Playing)
				{
					Menu_Sound_Loop.TriggerHitSound();
				}

				while (Game->Display->pollEvent(evt))
				{
					switch (evt.type)
					{
					case Event::KeyPressed:
					{
					
						if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
						{
							LoopCursor.setLoopCursor(MAIN_MENU);
						}
						break;
					}
					}
				}
				Main_menu_splashart.readrawAll();
				manimenuinfo.redrawInfo();
			}
			break;

			case EXIT:
			{
				Game->Display->close();
				Game->~GameWindow();
				return 0;
			}
			break;
		}
		
		Game->Display->display();
	}
	return 0;
}