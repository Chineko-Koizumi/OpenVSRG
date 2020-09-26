#include "stdafx.h"
#include "Score_Handler.h"


Score_Handler::Score_Handler( RenderWindow *game, String ArtistTitle)
	:combo(0),
	HP(500),
	Miss(0),
	Bad(0),
	Good(0),
	Great(0),
	Perfect(0),
	Flawless(0),
	miss_F(false),
	simfile_end_F(false),
	FullDP(0),
	DP(0),
	DP_percent(0.0f),
	hitsPerSec(0),
	itt(0),
	hitsArray{0,0,0},
	itt_CHT(0),
	Artist_Title_Str(ArtistTitle),
	game(game)
{
	HP_Bar_T	= new Texture;
	HP_Fill_T	= new Texture;

	HP_Bar_T->setSmooth(true);
	HP_Fill_T->setSmooth(true);

	HP_Bar_S	= new Sprite;
	HP_Fill_S	= new Sprite;

	hits_timing = new std::queue<float>;
	Score_calculating_Mutex = new Mutex();
	Redraw_Mutex = new Mutex();
}

Score_Handler::~Score_Handler()
{
	delete hits_timing;
	delete[] CoughtHitsTiming;
}

void Score_Handler::SetEndOfSimFilePTR(bool * ptr)
{
	external_simfile_end_F = ptr;
}

void Score_Handler::SetReceptorPossition(float receptorPos)
{
	Receptor_pos = receptorPos;
}

void Score_Handler::SetComboXYPossition(float comboposX, float comboposY)
{
	combo_text_pos_x = comboposX;
	combo_text_pos_y = comboposY;
	hit_type_pos_y = comboposY + combo_text.getCharacterSize();

	combo_text.setPosition(comboposX, comboposY);
	Hit_Type.setPosition(comboposX, hit_type_pos_y);
}

void Score_Handler::SetLifeBarOver(String barpath, String fillBarpath, float posX, float receptor_step)
{
	HPBar_possitionX = posX;
	Receptor_step = receptor_step;

	HP_Bar_T->loadFromFile(barpath);
	HP_Bar_S->setTexture(*HP_Bar_T, true);

	HP_Fill_T->loadFromFile(fillBarpath);
	HP_Fill_S->setTexture(*HP_Fill_T, true);

	float HP_scaling_factor_Y = game->getSize().y*0.10f / HP_Bar_T->getSize().y;
	float HP_scaling_factor_X = 4.0f*receptor_step/ HP_Bar_T->getSize().x;

	HP_Bar_S->setScale(HP_scaling_factor_X, HP_scaling_factor_Y);
	HP_Bar_S->setPosition(posX, Receptor_pos - HP_Bar_T->getSize().y*HP_scaling_factor_Y);

	HPBar_Fill_scaling_factor_Y = game->getSize().y*0.10f / HP_Fill_T->getSize().y;
	HPBar_Fill_scaling_factor_X = 4.0f*receptor_step / HP_Fill_T->getSize().x;

	HP_Fill_S->setScale(HP_scaling_factor_X, HPBar_Fill_scaling_factor_Y);
	HP_Fill_S->setPosition(posX, Receptor_pos - HP_Bar_T->getSize().y*HPBar_Fill_scaling_factor_Y);

	HPBar_possitionY = HP_Fill_S->getPosition().y;
}

void Score_Handler::SetCoughtPointerSize(int size)
{
	CoughtHitsTiming = new float[size];
}

void Score_Handler::SetFont(Font *font_ex, int fontsize, Color color)
{
	font = font_ex;
	fontSize = fontsize;

	Artist_Title_Text				.setFont(*font);
	Early							.setFont(*font);
	Late							.setFont(*font);
	HitsTimingQuantized_Flawless	.setFont(*font);
	HitsTimingQuantized_Perfect_L	.setFont(*font);
	HitsTimingQuantized_Perfect_R	.setFont(*font);
	HitsTimingQuantized_Great_L		.setFont(*font);
	HitsTimingQuantized_Great_R		.setFont(*font);
	Score_Board_text				.setFont(*font);
	KPS_Text						.setFont(*font);
	DP_precent_text					.setFont(*font);
	Hit_Type						.setFont(*font);
	combo_text						.setFont(*font);
	HitError_text					.setFont(*font);
	RawDP_text						.setFont(*font);
	msMinus50						.setFont(*font);
	msPlus50						.setFont(*font);
	ms0								.setFont(*font);

	Artist_Title_Text				.setCharacterSize(fontsize / 4.0f);
	Early							.setCharacterSize(fontsize / 6.0f);
	Late							.setCharacterSize(fontsize / 6.0f);
	HitsTimingQuantized_Flawless	.setCharacterSize(fontsize / 6.0f);
	HitsTimingQuantized_Perfect_L	.setCharacterSize(fontsize / 6.0f);
	HitsTimingQuantized_Perfect_R	.setCharacterSize(fontsize / 6.0f);
	HitsTimingQuantized_Great_L		.setCharacterSize(fontsize / 6.0f);
	HitsTimingQuantized_Great_R		.setCharacterSize(fontsize / 6.0f);
	KPS_Text						.setCharacterSize(fontsize / 2.0f);
	DP_precent_text					.setCharacterSize(fontsize / 2.0f);
	Hit_Type						.setCharacterSize(fontsize / 2.0f);
	combo_text						.setCharacterSize(fontsize);
	HitError_text					.setCharacterSize(fontsize / 2.0f);
	Score_Board_text				.setCharacterSize(fontsize / 4.0f);
	RawDP_text						.setCharacterSize(fontsize / 2.0f);
	msMinus50						.setCharacterSize(fontsize / 6.0f);
	msPlus50						.setCharacterSize(fontsize / 6.0f);
	ms0								.setCharacterSize(fontsize / 6.0f);

	KPS_Text						.setFillColor(color);
	DP_precent_text					.setFillColor(color);
	Hit_Type						.setFillColor(color);
	combo_text						.setFillColor(color);
	HitError_text					.setFillColor(color);
	RawDP_text						.setFillColor(color);

	KPS_Text						.setStyle(Text::Bold);
	DP_precent_text					.setStyle(Text::Bold);
	Hit_Type						.setStyle(Text::Bold);
	combo_text						.setStyle(Text::Bold);
	HitError_text					.setStyle(Text::Bold);
	RawDP_text						.setStyle(Text::Bold);

	Artist_Title_Text.setString(Artist_Title_Str);

	KPS_Text.setString(String("00.0 HPS"));
	KPS_Text.setPosition(game->getSize().x - KPS_Text.getLocalBounds().width, 0);

	DP_precent_text.setString(String("00.00%"));
	DP_precent_text.setPosition(game->getSize().x - DP_precent_text.getLocalBounds().width, 0 + DP_precent_text.getLocalBounds().height*1.1f);

	Score_Board_text.setPosition(game->getSize().x*0.05f, game->getSize().y*0.05f);
}


void Score_Handler::initScores(float Flawless, float Perfect, float Great, float Good, float Bad)
{
	scores[0] = Bad + Receptor_pos;
	scores[1] = Good + Receptor_pos;
	scores[2] = Great + Receptor_pos;
	scores[3] = Perfect + Receptor_pos;
	scores[4] = Flawless + Receptor_pos;
	scores[5] = -Flawless + Receptor_pos;
	scores[6] = -Perfect + Receptor_pos;
	scores[7] = -Great + Receptor_pos;
	scores[8] = -Good + Receptor_pos;
	scores[9] = -Bad + Receptor_pos;
}

void Score_Handler::calculateTiming(float BPS, float NoteWayLength)
{
	this->BPS = BPS;
	this->NoteWayLength = NoteWayLength;

	initScores(BPS*NoteWayLength*Flawless_T*0.7352f, BPS*NoteWayLength*Perfect_T*0.7352f, BPS*NoteWayLength*Great_T*0.7352f, BPS*NoteWayLength*Good_T*0.7352f, BPS*NoteWayLength*Bad_T*0.7352f);
}

unsigned char Score_Handler::getQuantizedFloat(float x)
{
	return (unsigned char)(std::min(255, (int)(x * 256.0f)));
}

void Score_Handler::TranslateCoughtPossitionsToTimeSamples()
{
	float factor = BPS*NoteWayLength*0.7352f;
	for (int i = 0; i < itt_CHT; ++i) //Translacja pozycji na czasy trafieñ
	{
		CoughtHitsTiming[i] -= Receptor_pos;
		CoughtHitsTiming[i] /= factor;
	}

	HitsTimingLegendBackground.setPosition(game->getSize().x*0.05f - 4.0f, game->getSize().y*0.55f - 4.0f);
	HitsTimingLegendBackground.setSize(Vector2f(game->getSize().x*0.05f + 4.0f, game->getSize().y*0.4f + 4.0f));
	HitsTimingLegendBackground.setFillColor(Color(25, 41, 41, 255));

	HitsTimingBackgrounds.setPosition(game->getSize().x*0.1f - 4.0f, game->getSize().y*0.55f - 4.0f);
	HitsTimingBackgrounds.setSize(Vector2f(game->getSize().x*0.85f + 4.0f,game->getSize().y*0.4f + 4.0f));
	HitsTimingBackgrounds.setFillColor(Color(16,19,24,255));

	msMinus50.setString("+50ms");
	msMinus50.setPosition(Vector2f(game->getSize().x*0.05f - 4.0f, game->getSize().y*0.55f - msMinus50.getLocalBounds().height*0.5f));

	ms0.setString("0ms");
	ms0.setPosition(Vector2f(game->getSize().x*0.05f, game->getSize().y*0.55f + game->getSize().y*0.4f*0.5f - ms0.getLocalBounds().height*0.75f));

	msPlus50.setString("-50ms");
	msPlus50.setPosition(Vector2f(game->getSize().x*0.05f, game->getSize().y*0.55f + game->getSize().y*0.4f - msPlus50.getLocalBounds().height*1.5f));

	Artist_Title_Text.setPosition(HitsTimingBackgrounds.getPosition().x, HitsTimingBackgrounds.getPosition().y- Artist_Title_Text.getLocalBounds().height*1.5f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//-Rozrzut trafieñ wykres-//

	std::vector<unsigned char> QuantizedCoughtHitsTiming;
	QuantizedCoughtHitsTiming.push_back(125);

	HitsTimingQuantizedBackground.setSize(Vector2f(game->getSize().x*0.35, game->getSize().y*0.35));
	HitsTimingQuantizedBackground.setPosition(HitsTimingBackgrounds.getPosition().x + HitsTimingBackgrounds.getSize().x - HitsTimingQuantizedBackground.getSize().x , HitsTimingBackgrounds.getPosition().y- HitsTimingQuantizedBackground.getSize().y*1.5);
	HitsTimingQuantizedBackground.setFillColor(Color(16, 19, 24, 255));

	HitsTimingQuantizedBackgroundCenterLine.setSize(Vector2f(2.0f, HitsTimingQuantizedBackground.getSize().y));
	HitsTimingQuantizedBackgroundCenterLine.setPosition(HitsTimingQuantizedBackground.getPosition().x+ HitsTimingQuantizedBackground.getSize().x*0.5f, HitsTimingQuantizedBackground.getPosition().y);
	HitsTimingQuantizedBackgroundCenterLine.setFillColor(Color::White);

	HitsTimingQuantizedLegendBackground.setSize(Vector2f(HitsTimingQuantizedBackground.getSize().x, HitsTimingQuantizedBackground.getSize().y*0.20));
	HitsTimingQuantizedLegendBackground.setPosition(HitsTimingQuantizedBackground.getPosition().x, HitsTimingQuantizedBackground.getPosition().y + HitsTimingQuantizedBackground.getSize().y);
	HitsTimingQuantizedLegendBackground.setFillColor(Color(25, 41, 41, 255));

	Early							.setString("Early");
	Early							.setPosition(HitsTimingQuantizedBackground.getPosition().x + HitsTimingQuantizedBackground.getSize().x - Early.getLocalBounds().width, HitsTimingQuantizedBackground.getPosition().y);

	Late							.setString("Late");
	Late							.setPosition(HitsTimingQuantizedBackground.getPosition().x, HitsTimingQuantizedBackground.getPosition().y);


	HitsTimingQuantized_Flawless	.setString("Fl");
	HitsTimingQuantized_Flawless	.setPosition(HitsTimingQuantizedLegendBackground.getPosition().x + HitsTimingQuantizedLegendBackground.getSize().x*0.5f - HitsTimingQuantized_Flawless.getLocalBounds().width*0.5f, HitsTimingQuantizedLegendBackground.getPosition().y);
	
	HitsTimingQuantized_Perfect_R	.setString("Pe");
	HitsTimingQuantized_Perfect_L	.setString("Pe");
	HitsTimingQuantized_Perfect_L	.setPosition(HitsTimingQuantizedLegendBackground.getPosition().x + HitsTimingQuantizedLegendBackground.getSize().x*0.7352f -			HitsTimingQuantized_Perfect_L.getLocalBounds().width*0.5f, HitsTimingQuantizedLegendBackground.getPosition().y);
	HitsTimingQuantized_Perfect_R	.setPosition(HitsTimingQuantizedLegendBackground.getPosition().x + HitsTimingQuantizedLegendBackground.getSize().x*(1.0f - 0.7352) -	HitsTimingQuantized_Perfect_R.getLocalBounds().width*0.5f, HitsTimingQuantizedLegendBackground.getPosition().y);

	HitsTimingQuantized_Great_L		.setString("Gr");
	HitsTimingQuantized_Great_R		.setString("Gr");
	HitsTimingQuantized_Great_L		.setPosition(HitsTimingQuantizedLegendBackground.getPosition().x + HitsTimingQuantizedLegendBackground.getSize().x*0.89f -				HitsTimingQuantized_Great_L.getLocalBounds().width*0.5f, HitsTimingQuantizedLegendBackground.getPosition().y);
	HitsTimingQuantized_Great_R		.setPosition(HitsTimingQuantizedLegendBackground.getPosition().x + HitsTimingQuantizedLegendBackground.getSize().x*(1.0f - 0.89f) -	HitsTimingQuantized_Great_R.getLocalBounds().width*0.5f, HitsTimingQuantizedLegendBackground.getPosition().y);


	for (int i = 0; i < itt_CHT; ++i)
	{
		QuantizedCoughtHitsTiming.push_back((getQuantizedFloat((((CoughtHitsTiming[i] / 0.034f) + 1.0f)*0.5f))));
		//printf("%d-||%lf\n", QuantizedCoughtHitsTiming[i], CoughtHitsTiming[i] / 0.034f);
	}

	std::sort(QuantizedCoughtHitsTiming.begin(), QuantizedCoughtHitsTiming.end());

	int max = 0;
	int itt_Quant = 0;
	for (int i = 0; i < 256; ++i)
	{
		int offset = 0;
		while (1)
		{
			if (QuantizedCoughtHitsTiming.size() == itt_Quant)
			{
				if (offset > max)max = offset;
				break;
			}
			else if (i == QuantizedCoughtHitsTiming[itt_Quant])
			{
				offset++;
				itt_Quant++;
			}
			else
			{
				if (offset > max)max = offset;
				break;
			}
		}
		if (QuantizedCoughtHitsTiming.size() == itt_Quant)
		{
			break;
		}
	}

	itt_Quant = 0;
	Color currentSampleColor;

	for (int i = 0; i < 256; ++i)
	{
		int offset = 0;
		while (1)
		{
			if (QuantizedCoughtHitsTiming.size() == itt_Quant)
			{
				if (QuantizedCoughtHitsTiming[itt_Quant - 1] <= 248 && QuantizedCoughtHitsTiming[itt_Quant - 1] >= 240)
				{
					currentSampleColor = Color(153, 0, 204, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant - 1] <= 240 && QuantizedCoughtHitsTiming[itt_Quant - 1] >= 203)
				{
					currentSampleColor = Color(0, 153, 255, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant - 1] <= 203 && QuantizedCoughtHitsTiming[itt_Quant - 1] >= 165)
				{
					currentSampleColor = Color(102, 255, 51, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant - 1] <= 165 && QuantizedCoughtHitsTiming[itt_Quant - 1] >= 90)
				{
					currentSampleColor = Color(0, 204, 255, 255);/////<====
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant - 1] <= 90 && QuantizedCoughtHitsTiming[itt_Quant - 1] >= 52)
				{
					currentSampleColor = Color(102, 255, 51, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant - 1] <= 52 && QuantizedCoughtHitsTiming[itt_Quant - 1] >= 15)
				{
					currentSampleColor = Color(102, 255, 51, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant - 1] <= 15 && QuantizedCoughtHitsTiming[itt_Quant - 1] >= 7)
				{
					currentSampleColor = Color(0, 153, 255, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant - 1] <= 7)
				{
					currentSampleColor = Color(153, 0, 204, 255);
				}

				break;
			}
			else if (i == QuantizedCoughtHitsTiming[itt_Quant])
			{
				if (QuantizedCoughtHitsTiming[itt_Quant] > 248)
				{
					currentSampleColor = Color(153, 0, 204, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant] <= 248 && QuantizedCoughtHitsTiming[itt_Quant] >= 240)
				{
					currentSampleColor = Color(0, 153, 255, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant] <= 240 && QuantizedCoughtHitsTiming[itt_Quant] >= 203)
				{
					currentSampleColor = Color(102, 255, 51, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant] <= 203 && QuantizedCoughtHitsTiming[itt_Quant] >= 165)
				{
					currentSampleColor = Color(255, 204, 0, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant] <= 165 && QuantizedCoughtHitsTiming[itt_Quant] >= 90)
				{
					currentSampleColor = Color(0, 204, 255, 255);/////<====
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant] <= 90 && QuantizedCoughtHitsTiming[itt_Quant] >= 52)
				{
					currentSampleColor = Color(255, 204, 0, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant] <= 52 && QuantizedCoughtHitsTiming[itt_Quant] >= 15)
				{
					currentSampleColor = Color(102, 255, 51, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant] <= 15 && QuantizedCoughtHitsTiming[itt_Quant] >= 7)
				{
					currentSampleColor = Color(0, 153, 255, 255);
				}
				else if (QuantizedCoughtHitsTiming[itt_Quant] <= 7)
				{
					currentSampleColor = Color(153, 0, 204, 255);
				}
				offset++;
				itt_Quant++;
			}
			else
			{
				break;
			}
		}
		if (QuantizedCoughtHitsTiming.size() == itt_Quant)
		{
			HitsTimingQuantizedPoints[i] = Vertex(Vector2f(HitsTimingQuantizedBackground.getPosition().x + HitsTimingQuantizedBackground.getSize().x*((float)(i) / 256.0f), HitsTimingQuantizedBackground.getPosition().y + HitsTimingQuantizedBackground.getSize().y), currentSampleColor);
		}
		else
		{
			HitsTimingQuantizedPoints[i] = Vertex(Vector2f(HitsTimingQuantizedBackground.getPosition().x + HitsTimingQuantizedBackground.getSize().x*((float)(i) / 256.0f), HitsTimingQuantizedBackground.getPosition().y + HitsTimingQuantizedBackground.getSize().y*(1.0f - ((float)offset / (float)max)*0.75)), currentSampleColor);
		}

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	HitsTimingPoints = new RectangleShape[itt_CHT];

	float temp_factor=1.0f;
	for (int i = 0; i < itt_CHT; ++i) //nadanie kolorów punktom odpowiadaj¹cym próbkom czasowym oraz ich umiejscowienie na wykresie
	{
		if (Flawless_T >= abs(CoughtHitsTiming[i])) 
		{
			HitsTimingPoints[i].setFillColor(Color(0, 204, 255, 255));
		}
		else if (Perfect_T >= abs(CoughtHitsTiming[i])) 
		{
			HitsTimingPoints[i].setFillColor(Color(255, 204, 0, 255));
		}
		else if (Great_T >= abs(CoughtHitsTiming[i]))
		{
			HitsTimingPoints[i].setFillColor(Color(102, 255, 51, 255));
		}
		else if (Good_T >= abs(CoughtHitsTiming[i]))
		{
			HitsTimingPoints[i].setFillColor(Color(0, 153, 255, 255));
		}
		else 
		{
			HitsTimingPoints[i].setFillColor(Color(153, 0, 204, 255));
		}

		temp_factor = CoughtHitsTiming[i] *0.4f;
		temp_factor /= 0.068f;

		HitsTimingPoints[i].setSize(Vector2f(8.0f, 8.0f));
		HitsTimingPoints[i].setOrigin(4.0f, 4.0f);
		HitsTimingPoints[i].setPosition(game->getSize().x*0.1f + (((float)i/(float)itt_CHT)*game->getSize().x*0.85f), game->getSize().y*0.55f + game->getSize().y*0.4f*0.5f + (game->getSize().y*temp_factor));
	}

	float error=0;
	for (int i = 0; i < itt_CHT; ++i)//œredni b³¹d trafienia
	{
		error += abs(CoughtHitsTiming[i]);
	}
	error /= (float)itt_CHT;
	error *= 10000.0f;
	error = round(error);
	error /= 10.0f;

	String temp = "Flawless: " + std::to_string(Flawless) + "\r\n" +
		"Perfect: " + std::to_string(Perfect) + "\r\n" +
		"Great: " + std::to_string(Great) + "\r\n" +
		"Good: " + std::to_string(Good) + "\r\n" +
		"Bad: " + std::to_string(Bad) + "\r\n" +
		"Miss: " + std::to_string(Miss) + "\r\n" +
		"Raw DP: " + std::to_string(DP) + "\r\n";

	Score_Board_text.setString(temp);

	temp = std::to_string(error).substr(0,4) + "ms";
	HitError_text.setString(temp);

	DP_precent_text.setCharacterSize(fontSize * 1.2f);
	DP_precent_text.setString(DP_percent_str);
	DP_precent_text.setPosition(Vector2f(game->getSize().x*0.5 - DP_precent_text.getLocalBounds().width*0.8f, game->getSize().y*0.05f));

	HitError_text.setCharacterSize(fontSize / 2.0f);
	HitError_text.setPosition(Vector2f(DP_precent_text.getPosition().x + DP_precent_text.getLocalBounds().width*0.5f - HitError_text.getLocalBounds().width*0.5f, DP_precent_text.getPosition().y + DP_precent_text.getLocalBounds().height*1.40f));
	
}

void Score_Handler::calculateScore(float tap_pos)
{
	hitsPerSec++;

	CoughtHitsTiming[itt_CHT] = tap_pos;
	itt_CHT++;

	if (tap_pos > scores[1]) 
	{
		HP -= 20;
		Bad++;
		combo = 0;

		FullDP += 2;

		Hit_Type.setString("Bad");
		Hit_Type.setFillColor(Color(153, 0, 204, 255));
	}
	else if (scores[1] >= tap_pos && tap_pos > scores[2])
	{
		Good++;
		combo++;

		FullDP += 1;

		Hit_Type.setString("Good");
		Hit_Type.setFillColor(Color(0, 153, 255, 255));
	}
	else if (scores[2] >= tap_pos && tap_pos > scores[3])
	{
		HP += 1;
		Great++;
		combo++;

		DP += 1;
		FullDP += 1;

		Hit_Type.setString("Great");
		Hit_Type.setFillColor(Color(102, 255, 51, 255));
	}
	else if (scores[3] >= tap_pos && tap_pos > scores[4])
	{
		HP += 2;
		Perfect++;
		combo++;

		DP += 2;
		FullDP += 2;

		Hit_Type.setString("Perfect");
		Hit_Type.setFillColor(Color(255, 204, 0, 255));
	}
	else if (scores[4] >= tap_pos && tap_pos > scores[5])
	{
		HP += 5;
		Flawless++;
		combo++;

		DP += 3;
		FullDP += 3;

		Hit_Type.setString("Flawless");
		Hit_Type.setFillColor(Color(0, 204, 255, 255));
	}
	else if (scores[5] >= tap_pos && tap_pos > scores[6])
	{
		HP += 5;
		Perfect++;
		combo++;

		DP += 2;
		FullDP += 2;

		Hit_Type.setString("Perfect");
		Hit_Type.setFillColor(Color(255, 204, 0, 255));
	}
	else if (scores[6] >= tap_pos && tap_pos > scores[7])
	{
		HP += 2;
		Great++;
		combo++;

		DP += 1;
		FullDP += 1;

		Hit_Type.setString("Great");
		Hit_Type.setFillColor(Color(102, 255, 51, 255));
	}
	else if (scores[7] >= tap_pos && tap_pos > scores[8])
	{
		HP += 1;
		Good++;
		combo++;

		FullDP += 1;

		Hit_Type.setString("Good");
		Hit_Type.setFillColor(Color(0, 153, 255, 255));
	}
	else if (scores[8] >= tap_pos)
	{
		HP -= 20;
		Bad++;
		combo = 0;

		FullDP += 2;

		Hit_Type.setString("Bad");
		Hit_Type.setFillColor(Color(153, 0, 204, 255));
	}
	animation_clock.restart();
}

void Score_Handler::ThreadScoreCalculating()// u¿ywaæ tylko w nowym w¹tku bo zablokuje program
{
	Color color_back = HP_Bar_S->getColor();
	bool setdefault_F= false;

	while (!simfile_end_F)
	{
		Score_calculating_Mutex->lock();
		if (!hits_timing->empty())
		{
			Redraw_Mutex->lock();
				calculateScore(hits_timing->front());
			Redraw_Mutex->unlock();

			hits_timing->pop();
		}
		Score_calculating_Mutex->unlock();

		if (HP > 1000)HP = 1000;
		else if (HP < 0)HP = 0;

		float HPBarWidth = 4.0f*Receptor_step*(HP / 1000.0f);
		float HPBarColor = HP/1000.0f;

		Redraw_Mutex->lock();
			HP_Fill_S->setColor(Color(255*(1.0f- HPBarColor),255* HPBarColor,0,255));
			HP_Fill_S->setTextureRect(IntRect(0, 0, HPBarWidth/ HPBar_Fill_scaling_factor_X, game->getSize().y*0.1f/ HPBar_Fill_scaling_factor_Y));
			if (HP == 1000)
			{ 
				HP_Bar_S->setColor(Color(255, 215, 0));
				setdefault_F = true;
			}
			else if(setdefault_F)
			{
				HP_Bar_S->setColor(color_back);
				setdefault_F = false;
			}
		Redraw_Mutex->unlock();

		sleep(milliseconds(4));
	}
}

float Score_Handler::getKPS()
{
	if (animation_clock_KPS.getElapsedTime() > seconds(0.333f)) 
	{
		hitsArray[itt] = hitsPerSec;
		hitsPerSec = 0;

		switch (itt) 
		{
			case 2: 
			{
				itt = 0;
				break;
			}
			default: 
			{
				itt++;
			}
		}
		
		animation_clock_KPS.restart();
	}
	
	return (float(hitsArray[0]+ hitsArray[1]+ hitsArray[2]));
}



void Score_Handler::RedrawScoreAnimations()
{
	switch (FullDP)
	{
	case 0:
	{
		DP_percent = 0.0f;
		break;
	}
	default:
	{
		DP_percent = (float)DP / (float)FullDP;
		break;
	}
	}
	DP_percent_str = std::to_string(DP_percent * 100);
	DP_percent_str = DP_percent_str.substr(0, 5);
	
	KPS_str = std::to_string(getKPS());
	KPS_str = KPS_str.substr(0, 4);

	KPS_Text.setString(KPS_str + " HPS");
	DP_precent_text.setString(DP_percent_str + "%");

	if (combo>10)combo_text.setString(std::to_string(combo));
	else combo_text.setString("");

	timeR = animation_clock.getElapsedTime();

	float time_move_step = (timeR.asSeconds() / animation_time) / 2.0f + 1.0f / 2.0f;

	Redraw_Mutex->lock();
		if (miss_F) 
		{
			Hit_Type.setString("Miss");
			Hit_Type.setFillColor(Color(204, 0, 0, 255));
			miss_F = false;
			animation_clock.restart();
		}

		if (timeR.asSeconds()<animation_time)
		{
			Hit_Type.setScale(1, time_move_step);
		}
		
		game->draw(KPS_Text);
		game->draw(DP_precent_text);
		game->draw(Hit_Type);
		game->draw(combo_text);
		game->draw(*HP_Fill_S);
		game->draw(*HP_Bar_S);
	Redraw_Mutex->unlock();
}

void Score_Handler::CalculateDP()
{
	DP = Flawless * 3 + Perfect * 2 + Great;
	FullDP = Flawless * 3 + Perfect * 3 + Great * 3 + Good + Bad * 2 + Miss * 10;
	DP_percent = (float)DP / (float)FullDP;
}

void Score_Handler::DrawScoreBoard()
{
	DP_percent_str = std::to_string(DP_percent * 100);
	DP_percent_str = DP_percent_str.substr(0, 5);

	game->draw(DP_precent_text);
	game->draw(HitError_text);
	game->draw(RawDP_text);

	game->draw(HitsTimingLegendBackground);
	game->draw(msMinus50);
	game->draw(ms0);
	game->draw(msPlus50);
	game->draw(Artist_Title_Text);
	
	game->draw(HitsTimingBackgrounds);

	for (int i = 0; i < itt_CHT; ++i)
	{
		game->draw(HitsTimingPoints[i]);
	}

	game->draw(HitsTimingQuantizedBackground);
	game->draw(HitsTimingQuantizedBackgroundCenterLine);
	game->draw(HitsTimingQuantizedPoints, 256, TrianglesStrip);
	game->draw(HitsTimingQuantizedLegendBackground);

	game->draw(Late);
	game->draw(Early);
	game->draw(HitsTimingQuantized_Flawless);
	game->draw(HitsTimingQuantized_Perfect_L);
	game->draw(HitsTimingQuantized_Perfect_R);
	game->draw(HitsTimingQuantized_Great_L);
	game->draw(HitsTimingQuantized_Great_R);

	game->draw(Score_Board_text);
}


