#include "StageSelect.h"
#include "XAudio2.h"
#include "Input.h"
#include <stdio.h>
StageSelect::StageSelect()
{
	//ステージ背景
	mBackGround[STAGE_MEADOW] = new Image("assets/StageSelect/BackGround.png", { 0,0,0 }, { 7.1,4,1 });
	mBackGround[STAGE_ICE] = new Image("assets/StageSelect/BackGround.png", { 0,0,0 }, { 7.1,4,1 });
	mBackGround[STAGE_VOLCANO] = new Image("assets/StageSelect/BackGround.png", { 0,0,0 }, { 7.1,4,1 });
	mBackGround[STAGE_CEMETERY] = new Image("assets/StageSelect/BackGround.png", { 0,0,0 }, { 7.1,4,1 });
	mBackGround[STAGE_DEMONCASTLE] = new Image("assets/StageSelect/BackGround.png", { 0,0,0 }, { 7.1,4,1 });
	mBackGround[STAGE_CASTLE] = new Image("assets/StageSelect/BackGround.png", { 0,0,0 }, { 7.1,4,1 });
	//ステージイメージ
	mStageImage[STAGE_MEADOW] = new Image("assets/StageSelect/Back_Image01.png", { 0, -0.05, 0 }, { 2,2,1 });
	mStageImage[STAGE_ICE] = new Image("assets/StageSelect/Back_Image02.png", { 0, -0.05, 0 }, { 2,2,1 });
	mStageImage[STAGE_CASTLE] = new Image("assets/StageSelect/Back_Image03.png", { 0, -0.08, 0 }, { 3,3,1 });
	mStageImage[STAGE_VOLCANO] = new Image("assets/StageSelect/Back_Image04.png", { 0, -0.05, 0 }, { 2,2,1 });
	mStageImage[STAGE_CEMETERY] = new Image("assets/StageSelect/Back_Image05.png", { 0, -0.05, 0 }, { 2,2,1 });
	mStageImage[STAGE_DEMONCASTLE] = new Image("assets/StageSelect/Back_Image06.png", { 0, -0.1, 0 }, { 3,3,1 });
	//ステージ番号(1-1など)
	mStageNum[STAGE_1_1] = new Image("assets/StageSelect/Num1-1.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	mStageNum[STAGE_1_2] = new Image("assets/StageSelect/Num1-2.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	mStageNum[STAGE_2_1] = new Image("assets/StageSelect/Num2-1.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	mStageNum[STAGE_2_2] = new Image("assets/StageSelect/Num2-2.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	mStageNum[STAGE_MINIBOSS] = new Image("assets/StageSelect/Num3-1.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	mStageNum[STAGE_3_1] = new Image("assets/StageSelect/Num4-1.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	mStageNum[STAGE_3_2] = new Image("assets/StageSelect/Num4-2.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	mStageNum[STAGE_4_1] = new Image("assets/StageSelect/Num5-1.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	mStageNum[STAGE_4_2] = new Image("assets/StageSelect/Num5-2.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	mStageNum[STAGE_BIGBOSS] = new Image("assets/StageSelect/Num6-1.png", { -2, 0.25, 0 }, { 1.5,1.5,1 });
	//ランク
	mRank[RANK_NULL] = new Image("assets/StageSelect/Stare_Nulls.png", { 2, 0.25, 0 }, { 1.5,1.5,1.5 });
	mRank[RANK_B] = new Image("assets/StageSelect/Stare_B.png", { 2, 0.25, 0 }, { 1.5,1.5,1.5 });
	mRank[RANK_A] = new Image("assets/StageSelect/Stare_A.png", { 2, 0.25, 0 }, { 1.5,1.5,1.5 });
	mRank[RANK_S] = new Image("assets/StageSelect/Stare_S.png", { 2, 0.25, 0 }, { 1.5,1.5,1.5 });
	mRank[RANK_SS] = new Image("assets/StageSelect/Stare_SS.png", { 2, 0.25, 0 }, { 1.5,1.5,1.5 });
	//ステージ手前の変なの
	mFrontImage[STAGE_MEADOW] = new Image("assets/StageSelect/Stage01.jpg", { 0,-3.4f,0 }, { 7, 4, 1 });
	mFrontImage[STAGE_ICE] = new Image("assets/StageSelect/Stage02.png", { 0,-3.4f,0 }, { 7, 4, 1 });
	mFrontImage[STAGE_CASTLE] = new Image("assets/StageSelect/Stage05.png", { 0,-1.35f,0 }, { 7, 4, 1 });
	mFrontImage[STAGE_VOLCANO] = new Image("assets/StageSelect/Stage03.png", { 0,-3.4f,0 }, { 7, 4, 1 });
	mFrontImage[STAGE_CEMETERY] = new Image("assets/StageSelect/Stage04.png", { 0,-3.4f,0 }, { 7, 4, 1 });
	mFrontImage[STAGE_DEMONCASTLE] = new Image("assets/StageSelect/Stage06.png", { 0,-1.35f,0 }, { 7, 4, 1 });
	//その他
	for (int i = 0; i < 3; i++)
		mStageRoute_main[i] = new Image("assets/StageSelect/Load.png", { 0, -1.5f, 0 }, { 3.75,0.3,1 }, { 1,1,1 }, 0);
	mOverall_Map = new Image("assets/StageSelect/Map.png", { 0, 1.5, 0 }, { 4,0.3,1 });
	mOverall_Map_point = new Image("assets/StageSelect/All_Point.png", { 0,1.5,0 }, { 0.5,0.5,1 }, { 0,0,5,1 });
	for (int i = 0; i < 5; i++)
		mStanding_Position[i] = new Image("assets/StageSelect/Scaffold.png", { -1.5,-1.5,0 }, { 1,1,1 });
	mSister = new Image("assets/StageSelect/Sister.png", { -1.5,-1.1,0 }, { 0.5,1,1 }, { 0,0,5,4 });
	mBoss = new Image("assets/StageSelect/Boss.png", { 0,0.8,0 }, { 1,1,1 }, { 0,0,6,2 });
	mFence = new Image("assets/StageSelect/Fence.png", { 0,0.1,0 }, { 3,3,1 });
	//ランク(debug)
	/*max_rank[STAGE_1_1] = RANK_SS;
	max_rank[STAGE_1_2] = RANK_A;*/

	//初期化
	now_stage = STAGE_1_1;
	now_sound = SOUND_LABEL_STAGE_MEADOW_BGM;

	max_stage = STAGE_BIGBOSS;

	//アニメーション初期化
	this->ObjectInitialize();
	Update();
}

void StageSelect::Initialize()
{
	if (now_event == EVENT_NULL) {
		FILE* fp = NULL;
		fopen_s(&fp, "assets/oni.dat", "r");
		if (fp != NULL) {
			for (int i = 0; i < 10; i++)
				fscanf_s(fp, "%d", &max_rank[i]);
		}
		fclose(fp);
		max_stage = STAGE_1_1;
		if (max_rank[STAGE_1_1] != RANK_NULL)
			max_stage = STAGE_1_2;
		if (max_rank[STAGE_1_2] != RANK_NULL)
			max_stage = STAGE_2_1;
		if (max_rank[STAGE_2_1] != RANK_NULL)
			max_stage = STAGE_MINIBOSS;
		if (max_rank[STAGE_MINIBOSS] != RANK_NULL)
			max_stage = STAGE_3_1;
		if (max_rank[STAGE_3_1] != RANK_NULL)
			max_stage = STAGE_4_1;
		if (max_rank[STAGE_4_1] != RANK_NULL)
			max_stage = STAGE_BIGBOSS;
	}
	//初期化フラグOFF
	this->Initialize_flag = false;
	//終了フラグOFF
	this->Finish_flag = false;
	Sound::instance().Play(now_sound);
	Next_scene = SCENE_STAGESELECT;
	LoadText_flag = true;

	Texture();
	for (auto a : mSelectObject)
		a->Update();
}

void StageSelect::Update()
{
	//やること
	//・ステージ背景を条件に合わせて変更
	//・ステージ移動時画面隠す
	//・決定ボタンでそのステージの情報を格納
	if (Next_scene == SCENE_OPTION)
		Next_scene = SCENE_STAGESELECT;
	ImageUpanddown();
	SisterAnim();
	if (now_stage == STAGE_MINIBOSS || now_stage == STAGE_BIGBOSS)
		BossAnim();
	if (StageMovement_flag)
		StageMove();
	if (PointMovement_flag)
		PointMove();
	if (LoadText_flag)
		Texture();
	for (auto a : mSelectObject)
		a->Update();
}

void StageSelect::Draw()
{
	for (GameObject* obj : mSelectObject)
		obj->Draw();
}

void StageSelect::Release()
{
	//for (GameObject* obj : mSelectObject) {
	//	delete obj;
	//}
	mSelectObject.clear();
	mSelectObject.shrink_to_fit();
}

void StageSelect::ObjectInitialize()
{
	int num = mSelectObject.size();
	for (auto a : mSelectObject) {
		a->Initialize();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void StageSelect::Input_Update()
{
	if (now_state == STATE_WAITING) {
		if (Input::instance().GetKeyboardPress('D') || Input::instance().GetButtonPress(XINPUT_RIGHT)) {//右
			if (now_stage < max_stage) {
				switch (now_stage)
				{
				case STAGE_1_1:
				case STAGE_2_1:
				case STAGE_3_1:
				case STAGE_4_1:
					Sound::instance().Play(SOUND_LABEL_STAGE_WALK_SE);
					this->PointMovement_flag = true;
					now_state = STATE_MOVERIGHT;
					break;
				case STAGE_1_2:
				case STAGE_2_2:
				case STAGE_3_2:
				case STAGE_4_2:
				case STAGE_MINIBOSS:
					Sound::instance().Play(SOUND_LABEL_STAGE_WALK_SE);
					this->StageMovement_flag = true;
					StageSound();
					Sound::instance().Stop(now_sound);
					now_state = STATE_MOVERIGHT;
					break;
				case STAGE_BIGBOSS://これ以上右には行けない
					now_state = STATE_WAITING;
					break;
				default:
					break;
				}
			}
		}
		else if (Input::instance().GetKeyboardPress('A') || Input::instance().GetButtonPress(XINPUT_LEFT)) {//左
			switch (now_stage)
			{
			case STAGE_2_1:
			case STAGE_3_1:
			case STAGE_4_1:
			case STAGE_BIGBOSS:
			case STAGE_MINIBOSS:
				Sound::instance().Play(SOUND_LABEL_STAGE_WALK_SE);
				this->StageMovement_flag = true;
				StageSound();
				Sound::instance().Stop(now_sound);
				now_state = STATE_MOVELEFT;
				break;
			case STAGE_1_2:
			case STAGE_2_2:
			case STAGE_3_2:
			case STAGE_4_2:
				Sound::instance().Play(SOUND_LABEL_STAGE_WALK_SE);
				this->PointMovement_flag = true;
				now_state = STATE_MOVELEFT;
				break;
			case STAGE_1_1://これ以上左には行けない
				now_state = STATE_WAITING;
				break;
			default:
				break;
			}
		}
		else if (Input::instance().GetKeyboardTrigger(VK_RETURN) || Input::instance().GetButtonPress_Once(XINPUT_B)) {//ゲーム画面へ
			this->Finish_flag = true;
			this->Fade_flag = true;
			this->Next_scene = SCENE_GAMESCENE;
			StageSound();
			SOUND sound = (SOUND)(SOUND_LABEL_INGAMESTAGE1_SE + rand() % 5);
			Sound::instance().Play(sound);
			Sound::instance().Stop(now_sound);
		}
		else if (Input::instance().GetKeyboardTrigger(VK_TAB) || Input::instance().GetButtonPress_Once(XINPUT_START)) {//オプション画面へ
			this->Finish_flag = true;
			this->Fade_flag = true;
			this->Next_scene = SCENE_OPTION;
			StageSound();
		}
	}
}
void StageSelect::Texture()//画像更新
{
	mSelectObject.clear();
	StagePoint();
	switch (now_stage)
	{
	case STAGE_1_1:
		//背景位置調整
		mBackGround[STAGE_MEADOW]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_ICE]->SetPosition({ 7,0,0 });//Next Stage
		mFrontImage[STAGE_MEADOW]->SetPosition({ 0,mFrontImage[STAGE_MEADOW]->Get_Position()->y,0 });
		//立ち位置調整
		mStanding_Position[0]->SetPosition({ -1.5f,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ 1.5f,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ 0,-1.55f,0 });
		mStageRoute_main[1]->SetPosition({ 3,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ 0,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 3,0.3,1 });
		mStageRoute_main[1]->SetSize({ 3.75,0.3,1 });
		mStageRoute_main[2]->SetSize({ 3,0.3,1 });
		switch (max_stage)
		{
		case STAGE_1_1:
			mStageRoute_main[0]->Set_Color({ 1,1,1,0 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,0 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			break;
		case STAGE_1_2:
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,0 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			break;
		default:
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			break;
		}
		mSister->SetPosition({ -1.5,-1.1,0 });//妹位置初期化
		mSelectObject.emplace_back(mBackGround[STAGE_ICE]);
		mSelectObject.emplace_back(mBackGround[STAGE_MEADOW]);
		mSelectObject.emplace_back(mFrontImage[STAGE_MEADOW]);
		mSelectObject.emplace_back(mStageImage[STAGE_MEADOW]);
		mSelectObject.emplace_back(mStageNum[STAGE_1_1]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		mSelectObject.emplace_back(mSister);
		break;
	case STAGE_1_2:
		//背景位置調整
		mBackGround[STAGE_MEADOW]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_ICE]->SetPosition({ 7,0,-1 });//Next Stage
		mFrontImage[STAGE_MEADOW]->SetPosition({ 0,mFrontImage[STAGE_MEADOW]->Get_Position()->y,0 });
		mFrontImage[STAGE_ICE]->SetPosition({ 7,mFrontImage[STAGE_ICE]->Get_Position()->y,0 });
		//立ち位置調整
		mStanding_Position[0]->SetPosition({ -1.5f,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ 1.5f,-1.5f,0 });
		mStanding_Position[2]->SetPosition({ 5.5f,-1.5f,0 });
		mStanding_Position[3]->SetPosition({ 8.5f,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ 0,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ 0,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 3,0.3,1 });
		mStageRoute_main[2]->SetSize({ 3,0.3,1 });
		switch (max_stage)
		{
		case STAGE_1_2://未クリア
			mStageRoute_main[1]->SetPosition({ 3,-1.55f,0 });
			mStageRoute_main[1]->SetSize({ 3.75,0.3,1 });
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,0 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			break;
		case STAGE_2_1:
			mStageRoute_main[1]->SetPosition({ 3.5,-1.55f,0 });
			mStageRoute_main[1]->SetSize({ 4,0.3,1 });
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,1 });
			break;
		default://クリア済み
			mStageRoute_main[1]->SetPosition({ 6,-1.55f,0 });
			mStageRoute_main[1]->SetSize({ 10,0.3,1 });
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,1 });
			break;
		}
		mSelectObject.emplace_back(mBackGround[STAGE_ICE]);
		mSelectObject.emplace_back(mBackGround[STAGE_MEADOW]);
		mSelectObject.emplace_back(mFrontImage[STAGE_MEADOW]);
		mSelectObject.emplace_back(mFrontImage[STAGE_ICE]);
		mSelectObject.emplace_back(mStageImage[STAGE_MEADOW]);
		mSelectObject.emplace_back(mStageNum[STAGE_1_2]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mStanding_Position[2]);
		mSelectObject.emplace_back(mStanding_Position[3]);

		mSelectObject.emplace_back(mSister);
		break;
	case STAGE_2_1:
		mBackGround[STAGE_ICE]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_VOLCANO]->SetPosition({ 7,0,0 });//Next Stage
		mBackGround[STAGE_MEADOW]->SetPosition({ -7,0,0 });//Before Stage
		mFrontImage[STAGE_MEADOW]->SetPosition({ -7,mFrontImage[STAGE_MEADOW]->Get_Position()->y,0 });
		mFrontImage[STAGE_ICE]->SetPosition({ 0,mFrontImage[STAGE_ICE]->Get_Position()->y,0 });
		//立ち位置調整
		mStanding_Position[0]->SetPosition({ -1.5f,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ 1.5f,-1.5f,0 });
		mStanding_Position[2]->SetPosition({ -5.5f,-1.5f,0 });
		mStanding_Position[3]->SetPosition({ -8.5f,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ -4.75,-1.55f,0 });
		mStageRoute_main[1]->SetPosition({ 4.75,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ 0,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 7,0.3,1 });
		mStageRoute_main[1]->SetSize({ 7,0.3,1 });
		mStageRoute_main[2]->SetSize({ 3,0.3,1 });
		switch (max_stage)
		{
		case STAGE_2_1://未クリア
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,0 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			break;
		default://クリア済み

			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,1 });
			break;
		}
		mSelectObject.emplace_back(mBackGround[STAGE_ICE]);
		mSelectObject.emplace_back(mBackGround[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mBackGround[STAGE_MEADOW]);
		mSelectObject.emplace_back(mFrontImage[STAGE_MEADOW]);
		mSelectObject.emplace_back(mFrontImage[STAGE_ICE]);
		mSelectObject.emplace_back(mStageImage[STAGE_ICE]);
		mSelectObject.emplace_back(mStageNum[STAGE_2_1]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mStanding_Position[2]);
		mSelectObject.emplace_back(mStanding_Position[3]);
		mSelectObject.emplace_back(mSister);
		break;
	case STAGE_2_2:
		mBackGround[STAGE_ICE]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_CASTLE]->SetPosition({ 7,0,0 });//Next Stage
		mBackGround[STAGE_MEADOW]->SetPosition({ -7,0,0 });//Before Stage
		mFrontImage[STAGE_CASTLE]->SetPosition({ 7,mFrontImage[STAGE_CASTLE]->Get_Position()->y,0 });
		mFrontImage[STAGE_ICE]->SetPosition({ 0,mFrontImage[STAGE_ICE]->Get_Position()->y,0 });
		//立ち位置調整
		mStanding_Position[0]->SetPosition({ -1.5f,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ 1.5f,-1.5f,0 });
		mStanding_Position[2]->SetPosition({ 7,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ -3,-1.55f,0 });
		mStageRoute_main[1]->SetPosition({ 2.75,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ 9,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 3,0.3,1 });
		mStageRoute_main[1]->SetSize({ 8.5,0.3,1 });
		mStageRoute_main[2]->SetSize({ 3.75,0.3,1 });
		switch (max_stage)
		{
		case STAGE_MINIBOSS:
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			break;
		default://クリア済み
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,1 });
			break;
		}
		mSelectObject.emplace_back(mBackGround[STAGE_ICE]);
		mSelectObject.emplace_back(mBackGround[STAGE_CASTLE]);
		mSelectObject.emplace_back(mBackGround[STAGE_MEADOW]);
		mSelectObject.emplace_back(mFrontImage[STAGE_ICE]);
		mSelectObject.emplace_back(mFrontImage[STAGE_CASTLE]);
		mSelectObject.emplace_back(mStageImage[STAGE_ICE]);
		mSelectObject.emplace_back(mStageNum[STAGE_2_2]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mStanding_Position[2]);
		mSelectObject.emplace_back(mSister);
		break;
	case STAGE_MINIBOSS:
		mBackGround[STAGE_CASTLE]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_VOLCANO]->SetPosition({ 7,0,0 });//Next Stage
		mBackGround[STAGE_ICE]->SetPosition({ -7,0,0 });//Before Stage
		mFrontImage[STAGE_CASTLE]->SetPosition({ 0,mFrontImage[STAGE_CASTLE]->Get_Position()->y,0 });
		mFrontImage[STAGE_ICE]->SetPosition({ -7,mFrontImage[STAGE_ICE]->Get_Position()->y,0 });
		mFrontImage[STAGE_VOLCANO]->SetPosition({ 7,mFrontImage[STAGE_VOLCANO]->Get_Position()->y,0 });
		mStanding_Position[0]->SetPosition({ 0,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ -5.5f,-1.5f,0 });
		mStanding_Position[2]->SetPosition({ -8.5f,-1.5f,0 });
		mStanding_Position[3]->SetPosition({ 5.5f,-1.5f,0 });
		mStanding_Position[4]->SetPosition({ 8.5f,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ -6,-1.55f,0 });
		mStageRoute_main[1]->SetPosition({ 6,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ -7.5,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 12,0.3,1 });
		mStageRoute_main[1]->SetSize({ 12.5,0.3,1 });
		mStageRoute_main[2]->SetSize({ 3.75,0.3,1 });
		switch (max_stage)
		{
		case STAGE_MINIBOSS:
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,0 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			break;
		case STAGE_3_1:
			mStageRoute_main[1]->SetSize({ 5.5, 0.3, 1 });
			mStageRoute_main[1]->SetPosition({ 2.5,-1.55f,0 });
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			mBoss->Set_Color({ 1,1,1,0 });
			break;
		default://クリア済み
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			mBoss->Set_Color({ 1,1,1,0 });
			break;
		}
		mBoss->SetPosition({ 0,0.8,0 });
		mSelectObject.emplace_back(mBackGround[STAGE_CASTLE]);
		mSelectObject.emplace_back(mBackGround[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mBackGround[STAGE_ICE]);
		mSelectObject.emplace_back(mFrontImage[STAGE_CASTLE]);
		mSelectObject.emplace_back(mFrontImage[STAGE_ICE]);
		mSelectObject.emplace_back(mFrontImage[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mBoss);
		mSelectObject.emplace_back(mStageImage[STAGE_CASTLE]);
		mSelectObject.emplace_back(mStageNum[STAGE_MINIBOSS]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mStanding_Position[2]);
		mSelectObject.emplace_back(mStanding_Position[3]);
		mSelectObject.emplace_back(mStanding_Position[4]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		mSelectObject.emplace_back(mSister);
		break;
	case STAGE_3_1:
		mBackGround[STAGE_VOLCANO]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_CEMETERY]->SetPosition({ 7,0,0 });//Next Stage
		mBackGround[STAGE_CASTLE]->SetPosition({ -7,0,0 });//Before Stage
		mFrontImage[STAGE_CASTLE]->SetPosition({ -7,mFrontImage[STAGE_CASTLE]->Get_Position()->y,0 });
		mFrontImage[STAGE_VOLCANO]->SetPosition({ 0,mFrontImage[STAGE_VOLCANO]->Get_Position()->y,0 });
		//立ち位置調整
		mStanding_Position[0]->SetPosition({ -1.5f,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ 1.5f,-1.5f,0 });
		mStanding_Position[2]->SetPosition({ 5.5f,-1.5f,0 });
		mStanding_Position[3]->SetPosition({ 8.5f,-1.5f,0 });
		mStanding_Position[4]->SetPosition({ -7,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ -7.5,-1.55f,0 });
		mStageRoute_main[1]->SetPosition({ 0,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ 2.5,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 12,0.3,1 });
		mStageRoute_main[1]->SetSize({ 12,0.3,1 });
		mStageRoute_main[2]->SetSize({ 12,0.3,1 });
		switch (max_stage)
		{
		case STAGE_3_1://未クリア
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,0 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			break;
		default://クリア済み
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,1 });
			break;
		}
		mSelectObject.emplace_back(mBackGround[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mBackGround[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mBackGround[STAGE_CASTLE]);
		mSelectObject.emplace_back(mFrontImage[STAGE_CASTLE]);
		mSelectObject.emplace_back(mFrontImage[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mStageImage[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mStageNum[STAGE_3_1]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mStanding_Position[2]);
		mSelectObject.emplace_back(mStanding_Position[3]);
		mSelectObject.emplace_back(mStanding_Position[4]);
		mSelectObject.emplace_back(mSister);
		break;
	case STAGE_3_2:
		mBackGround[STAGE_VOLCANO]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_CEMETERY]->SetPosition({ 7,0,0 });//Next Stage
		mBackGround[STAGE_CASTLE]->SetPosition({ -7,0,0 });//Before Stage
		mFrontImage[STAGE_CEMETERY]->SetPosition({ 7,mFrontImage[STAGE_CEMETERY]->Get_Position()->y,0 });
		mFrontImage[STAGE_VOLCANO]->SetPosition({ 0,mFrontImage[STAGE_VOLCANO]->Get_Position()->y,0 });
		//立ち位置調整
		mStanding_Position[0]->SetPosition({ -1.5f,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ 1.5f,-1.5f,0 });
		mStanding_Position[2]->SetPosition({ 5.5f,-1.5f,0 });
		mStanding_Position[3]->SetPosition({ 8.5f,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ -1,-1.55f,0 });
		mStageRoute_main[1]->SetPosition({ 3.5,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ 6,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 10,0.3,1 });
		mStageRoute_main[1]->SetSize({ 4,0.3,1 });
		mStageRoute_main[2]->SetSize({ 12,0.3,1 });
		mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
		mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
		mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
		switch (max_stage)
		{
		case STAGE_4_1:
			mStageRoute_main[1]->SetPosition({ 3.5,-1.55f,0 });
			break;
		default:
			mStageRoute_main[2]->Set_Color({ 1,1,1,1 });
			break;
		}
		mSelectObject.emplace_back(mBackGround[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mBackGround[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mBackGround[STAGE_CASTLE]);
		mSelectObject.emplace_back(mFrontImage[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mFrontImage[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mStageImage[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mStageNum[STAGE_3_2]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mStanding_Position[2]);
		mSelectObject.emplace_back(mStanding_Position[3]);
		mSelectObject.emplace_back(mSister);
		break;
	case STAGE_4_1:
		mBackGround[STAGE_CEMETERY]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_DEMONCASTLE]->SetPosition({ 7,0,0 });//Next Stage
		mBackGround[STAGE_VOLCANO]->SetPosition({ -7,0,0 });//Before Stage
		mFrontImage[STAGE_CEMETERY]->SetPosition({ 0,mFrontImage[STAGE_CEMETERY]->Get_Position()->y,0 });
		mFrontImage[STAGE_VOLCANO]->SetPosition({ -7,mFrontImage[STAGE_VOLCANO]->Get_Position()->y,0 });
		//立ち位置調整
		mStanding_Position[0]->SetPosition({ -1.5f,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ 1.5f,-1.5f,0 });
		mStanding_Position[2]->SetPosition({ -5.5f,-1.5f,0 });
		mStanding_Position[3]->SetPosition({ -8.5f,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ -7.5,-1.55f,0 });
		mStageRoute_main[1]->SetPosition({ 0,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ 2.5,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 12,0.3,1 });
		mStageRoute_main[1]->SetSize({ 12,0.3,1 });
		mStageRoute_main[2]->SetSize({ 12,0.3,1 });
		switch (max_stage)
		{
		case STAGE_4_1://未クリア
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,0 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
			break;
		default://クリア済み
			mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
			mStageRoute_main[2]->Set_Color({ 1,1,1,1 });
			break;
		}
		mSelectObject.emplace_back(mBackGround[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mBackGround[STAGE_DEMONCASTLE]);
		mSelectObject.emplace_back(mBackGround[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mFrontImage[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mFrontImage[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mStageImage[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mStageNum[STAGE_4_1]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mStanding_Position[2]);
		mSelectObject.emplace_back(mStanding_Position[3]);
		mSelectObject.emplace_back(mSister);
		break;
	case STAGE_4_2:
		mBackGround[STAGE_CEMETERY]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_DEMONCASTLE]->SetPosition({ 7,0,0 });//Next Stage
		mBackGround[STAGE_VOLCANO]->SetPosition({ -7,0,0 });//Before Stage
		mFrontImage[STAGE_CEMETERY]->SetPosition({ 0,mFrontImage[STAGE_CEMETERY]->Get_Position()->y,0 });
		mFrontImage[STAGE_DEMONCASTLE]->SetPosition({ 7,mFrontImage[STAGE_DEMONCASTLE]->Get_Position()->y,0 });
		//立ち位置調整
		mStanding_Position[0]->SetPosition({ -1.5f,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ 1.5f,-1.5f,0 });
		mStanding_Position[2]->SetPosition({ 7,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ -7.5,-1.55f,0 });
		mStageRoute_main[1]->SetPosition({ 0,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ 2.5,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 12,0.3,1 });
		mStageRoute_main[1]->SetSize({ 12,0.3,1 });
		mStageRoute_main[2]->SetSize({ 9,0.3,1 });
		mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
		mStageRoute_main[1]->Set_Color({ 1,1,1,1 });
		mStageRoute_main[2]->Set_Color({ 1,1,1,1 });
		mSelectObject.emplace_back(mBackGround[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mBackGround[STAGE_DEMONCASTLE]);
		mSelectObject.emplace_back(mBackGround[STAGE_VOLCANO]);
		mSelectObject.emplace_back(mFrontImage[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mFrontImage[STAGE_DEMONCASTLE]);
		mSelectObject.emplace_back(mStageImage[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mStageNum[STAGE_4_2]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mStanding_Position[2]);
		mSelectObject.emplace_back(mStanding_Position[3]);
		mSelectObject.emplace_back(mSister);
		break;
	case STAGE_BIGBOSS:
		mBackGround[STAGE_DEMONCASTLE]->SetPosition({ 0,0,0 });//Now Stage
		mBackGround[STAGE_CEMETERY]->SetPosition({ -7,0,0 });//Before Stage
		mFrontImage[STAGE_CEMETERY]->SetPosition({ -7,mFrontImage[STAGE_CEMETERY]->Get_Position()->y,0 });
		mFrontImage[STAGE_DEMONCASTLE]->SetPosition({ 0,mFrontImage[STAGE_DEMONCASTLE]->Get_Position()->y,0 });
		mStanding_Position[0]->SetPosition({ 0,-1.5f,0 });
		mStanding_Position[1]->SetPosition({ -5.5f,-1.5f,0 });
		mStanding_Position[2]->SetPosition({ -8.5f,-1.5f,0 });
		//道表示・位置調整
		mStageRoute_main[0]->SetPosition({ -6,-1.55f,0 });
		mStageRoute_main[1]->SetPosition({ 0,-1.55f,0 });
		mStageRoute_main[2]->SetPosition({ 2.5,-1.55f,0 });
		mStageRoute_main[0]->SetSize({ 12,0.3,1 });
		mStageRoute_main[1]->SetSize({ 12,0.3,1 });
		mStageRoute_main[2]->SetSize({ 9,0.3,1 });
		mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
		mStageRoute_main[1]->Set_Color({ 1,1,1,0 });
		mStageRoute_main[2]->Set_Color({ 1,1,1,0 });
		mBoss->SetPosition({ 0,0.7,0 });
		if (max_rank[STAGE_BIGBOSS] != RANK_NULL)
			mBoss->Set_Color({ 1,1,1,1 });
		mSelectObject.emplace_back(mBackGround[STAGE_DEMONCASTLE]);
		mSelectObject.emplace_back(mBackGround[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mFrontImage[STAGE_DEMONCASTLE]);
		mSelectObject.emplace_back(mFrontImage[STAGE_CEMETERY]);
		mSelectObject.emplace_back(mStageImage[STAGE_DEMONCASTLE]);
		mSelectObject.emplace_back(mStageNum[STAGE_BIGBOSS]);
		mSelectObject.emplace_back(mRank[max_rank[now_stage]]);
		for (int i = 0; i < 3; i++)
			mSelectObject.emplace_back(mStageRoute_main[i]);
		mSelectObject.emplace_back(mOverall_Map);
		mSelectObject.emplace_back(mOverall_Map_point);
		mSelectObject.emplace_back(mStanding_Position[0]);
		mSelectObject.emplace_back(mStanding_Position[1]);
		mSelectObject.emplace_back(mStanding_Position[2]);
		mSelectObject.emplace_back(mStanding_Position[3]);
		mSelectObject.emplace_back(mSister);
		mSelectObject.emplace_back(mBoss);
		mSelectObject.emplace_back(mFence);
		break;

	default:
		break;
	}
	this->ObjectInitialize();
	LoadText_flag = false;
}

void StageSelect::StageMove()
{
	if (mRank[max_rank[now_stage]]->Get_Color().a != 0 && mStageNum[now_stage]->Get_Color().a != 0 && mOverall_Map->Get_Color().a != 0 && mOverall_Map_point->Get_Color().a != 0) {
		mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,0 });
		mStageNum[now_stage]->Set_Color({ 1,1,1,0 });
		mOverall_Map->Set_Color({ 1,1,1,0 });
		mOverall_Map_point->Set_Color({ 1,1,1,0 });
		if (now_stage == STAGE_MINIBOSS || now_stage == STAGE_BIGBOSS)
			mBoss->Set_Color({ 1,1,1,0 });
	}
	Standing_PosMove();
	switch (now_stage)
	{
		//右移動
	case STAGE_1_2:
	case STAGE_3_2:
		StageRight_Normal();
		break;
	case STAGE_2_2:
	case STAGE_4_2://次がBoss戦の場合
		StageRight_BOSS();
		break;
		//左移動
	case STAGE_2_1:
	case STAGE_4_1:
		StageLeft_Normal();
		break;
	case STAGE_3_1:
		StageLeft_BOSS();
		break;
	case STAGE_MINIBOSS:
	case STAGE_BIGBOSS:
		switch (now_state)
		{
		case STATE_MOVELEFT:
			//妹を前のエリア(左側)に移動させる
			if (mSister->Get_Position()->x > -3.5 && mBackGround[now_pattern]->Get_Position()->x == 0) {
				mSister->SetPosition({ mSister->Get_Position()->x - 0.05f,mSister->Get_Position()->y,mSister->Get_Position()->z });
			}
			else if (mSister->Get_Position()->x < -3.5) {
				mSister->SetPosition({ -3.5,mSister->Get_Position()->y,0 });
			}
			//妹移動完了後、ステージをずらす
			if (mBackGround[now_pattern - 1]->Get_Position()->x < 0) {
				mBackGround[now_pattern - 1]->SetPosition({ mBackGround[now_pattern - 1]->Get_Position()->x + 0.1f,0,0 });
				mBackGround[now_pattern]->SetPosition({ mBackGround[now_pattern]->Get_Position()->x + 0.1f,0,0 });
				mStageImage[now_pattern]->SetPosition({ mStageImage[now_pattern]->Get_Position()->x + 0.1f,mStageImage[now_pattern]->Get_Position()->y,mStageImage[now_pattern]->Get_Position()->z });
				if (now_stage == STAGE_BIGBOSS)
					mFence->SetPosition({ mFence->Get_Position()->x + 0.1f,mFence->Get_Position()->y,mFence->Get_Position()->z });
				
				mFrontImage[now_pattern]->SetPosition({ mFrontImage[now_pattern]->Get_Position()->x + 0.1f,mFrontImage[now_pattern]->Get_Position()->y,0 });
				mFrontImage[now_pattern - 1]->SetPosition({ mFrontImage[now_pattern - 1]->Get_Position()->x + 0.1f,mFrontImage[now_pattern - 1]->Get_Position()->y,0 });
				for (int i = 0; i < 3; i++)
					mStageRoute_main[i]->SetPosition({ mStageRoute_main[i]->Get_Position()->x + 0.1f,-1.55f,0 });
				//妹最終地点に移動
				if (mSister->Get_Position()->x < 1.5f)
					mSister->SetPosition({ mSister->Get_Position()->x + 0.05f, mSister->Get_Position()->y, mSister->Get_Position()->z });
				else if (mSister->Get_Position()->x > 1.5f)//妹粛清
					mSister->SetPosition({ 1.5f,mSister->Get_Position()->y,mSister->Get_Position()->z });
			}
			else if (mBackGround[now_pattern]->Get_Position()->x > 0) {//背景調整
				mBackGround[now_pattern]->SetPosition({ 0,0,0 });
			}
			//背景・妹ともに移動完了後
			if (mBackGround[now_pattern]->Get_Position()->x == 0 && mSister->Get_Position()->x == 1.5f) {
				this->LoadText_flag = true;
				mStageImage[now_pattern]->SetPosition({ 0,-0.05,0 });
				mFence->SetPosition({ 0,0.1,0 });
				mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,1 });
				mStageNum[now_stage]->Set_Color({ 1,1,1,1 });
				mOverall_Map->Set_Color({ 1,1,1,1 });
				mOverall_Map_point->Set_Color({ 1,1,1,1 });
				mBoss->Set_Color({ 1,1,1,1 });
				Sound::instance().Stop(SOUND_LABEL_STAGE_WALK_SE);
				now_stage = static_cast<SelectStage>(now_stage - 1);
				this->StageMovement_flag = false;
				this->now_state = STATE_WAITING;
				StageChange();//現在のステージ背景確認
			}
			break;
		case STATE_MOVERIGHT:
			//妹を次のエリア(右側)に移動させる
			if (mSister->Get_Position()->x < 3.5 && mBackGround[now_pattern]->Get_Position()->x == 0) {
				mSister->SetPosition({ mSister->Get_Position()->x + 0.05f,mSister->Get_Position()->y,mSister->Get_Position()->z });
			}
			else if (mSister->Get_Position()->x > 3.5) {
				mSister->SetPosition({ 3.5,mSister->Get_Position()->y,0 });
			}
			//妹移動完了後、ステージをずらす
			if (mBackGround[now_pattern + 1]->Get_Position()->x > 0) {
				mBackGround[now_pattern + 1]->SetPosition({ mBackGround[now_pattern + 1]->Get_Position()->x - 0.1f,0,0 });
				mBackGround[now_pattern]->SetPosition({ mBackGround[now_pattern]->Get_Position()->x - 0.1f,0,0 });
				mStageImage[now_pattern]->SetPosition({ mStageImage[now_pattern]->Get_Position()->x - 0.1f,mStageImage[now_pattern]->Get_Position()->y,mStageImage[now_pattern]->Get_Position()->z });
				mFrontImage[now_pattern]->SetPosition({ mFrontImage[now_pattern]->Get_Position()->x - 0.1f,mFrontImage[now_pattern]->Get_Position()->y,0 });
				mFrontImage[now_pattern + 1]->SetPosition({ mFrontImage[now_pattern + 1]->Get_Position()->x - 0.1f,mFrontImage[now_pattern + 1]->Get_Position()->y,0 });
				for (int i = 0; i < 3; i++)
					mStageRoute_main[i]->SetPosition({ mStageRoute_main[i]->Get_Position()->x - 0.1f,-1.55f,0 });
				//妹最終地点に移動
				if (mSister->Get_Position()->x > -1.5f)
					mSister->SetPosition({ mSister->Get_Position()->x - 0.05f, mSister->Get_Position()->y, mSister->Get_Position()->z });
				else if (mSister->Get_Position()->x < -1.5f)//妹粛清
					mSister->SetPosition({ -1.5f,mSister->Get_Position()->y,mSister->Get_Position()->z });
			}
			else if (mBackGround[now_pattern]->Get_Position()->x < 0) {//背景調整
				mBackGround[now_pattern]->SetPosition({ 0,0,0 });
			}
			//背景・妹ともに移動完了後
			if (mBackGround[now_pattern]->Get_Position()->x == 0 && mSister->Get_Position()->x == -1.5f) {
				this->LoadText_flag = true;
				mStageImage[now_pattern]->SetPosition({ 0,-0.05,0 });
				mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,1 });
				mStageNum[now_stage]->Set_Color({ 1,1,1,1 });
				mOverall_Map->Set_Color({ 1,1,1,1 });
				mOverall_Map_point->Set_Color({ 1,1,1,1 });
				mBoss->Set_Color({ 1,1,1,1 });
				Sound::instance().Stop(SOUND_LABEL_STAGE_WALK_SE);
				now_stage = static_cast<SelectStage>(now_stage + 1);
				this->StageMovement_flag = false;
				this->now_state = STATE_WAITING;
				StageChange();//現在のステージ背景確認
			}
			break;
		default:
			break;
		}
	default:
		break;
	}
	int num = mSelectObject.size();
	for (auto a : mSelectObject) {
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void StageSelect::PointMove()
{
	//ランク・ステージ番号透明化処理
	if (mRank[max_rank[now_stage]]->Get_Color().a > 0 || mStageNum[now_stage]->Get_Color().a > 0) {
		mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,0 });
		mStageNum[now_stage]->Set_Color({ 1,1,1,0 });
	}
	switch (now_stage)
	{
		//右移動
	case STAGE_1_1:
	case STAGE_2_1:
	case STAGE_3_1:
	case STAGE_4_1:
		if (now_state == STATE_MOVERIGHT) {
			if (mSister->Get_Position()->x < 1.5f) {
				mSister->SetPosition({ mSister->Get_Position()->x + 0.05f,mSister->Get_Position()->y,mSister->Get_Position()->z });
			}
		}
		if (mSister->Get_Position()->x > 1.5f) {
			mSister->SetPosition({ 1.5f,-1.1f,0 });
			this->LoadText_flag = true;
			//透明化したランクを表示させる
			mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,1 });
			mStageNum[now_stage]->Set_Color({ 1,1,1,1 });
			Sound::instance().Stop(SOUND_LABEL_STAGE_WALK_SE);
			now_stage = static_cast<SelectStage>(now_stage + 1);
			this->PointMovement_flag = false;
			this->now_state = STATE_WAITING;
		}
		break;
		//左移動
	case STAGE_1_2:
	case STAGE_2_2:
	case STAGE_3_2:
	case STAGE_4_2:
		if (now_state == STATE_MOVELEFT) {
			if (mSister->Get_Position()->x > -1.5f) {
				mSister->SetPosition({ mSister->Get_Position()->x - 0.05f,mSister->Get_Position()->y,mSister->Get_Position()->z });
			}
		}
		if (mSister->Get_Position()->x < -1.5f) {
			mSister->SetPosition({ -1.5f,-1.1f,0 });
			this->LoadText_flag = true;
			//透明化したランクを表示させる
			mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,1 });
			mStageNum[now_stage]->Set_Color({ 1,1,1,1 });
			Sound::instance().Stop(SOUND_LABEL_STAGE_WALK_SE);
			now_stage = static_cast<SelectStage>(now_stage - 1);
			this->PointMovement_flag = false;
			this->now_state = STATE_WAITING;
		}
		break;
	default:
		break;
	}
}

void StageSelect::StageChange()
{
	switch (now_stage)
	{
	case STAGE_1_1:
	case STAGE_1_2:
		now_pattern = STAGE_MEADOW;
		break;
	case STAGE_2_1:
	case STAGE_2_2:
		now_pattern = STAGE_ICE;
		break;
	case STAGE_MINIBOSS:
		now_pattern = STAGE_CASTLE;
		break;
	case STAGE_3_1:
	case STAGE_3_2:
		now_pattern = STAGE_VOLCANO;
		break;
	case STAGE_4_1:
	case STAGE_4_2:
		now_pattern = STAGE_CEMETERY;
		break;
	case STAGE_BIGBOSS:
		now_pattern = STAGE_DEMONCASTLE;
		break;
	default:
		break;
	}
	StageSound();
	Sound::instance().Play(now_sound);
}

void StageSelect::SisterAnim()
{
	switch (now_state)
	{
	case STATE_WAITING:
		if (mSister->Get_Textur()->y != 0) {
			mSister->Set_Texture({ mSister->Get_Textur()->x,0,5,4 });
		}
		break;
	case STATE_MOVELEFT:
		if (mSister->Get_Textur()->y != 1) {
			mSister->Set_Texture({ mSister->Get_Textur()->x,1,5,4 });
		}
		break;
	case STATE_MOVERIGHT:
		if (mSister->Get_Textur()->y != 2) {
			mSister->Set_Texture({ mSister->Get_Textur()->x,2,5,4 });
		}
		break;
	default:
		break;
	}
	if (SisiterCounter == 16) {
		if (mSister->Get_Textur()->x == 4)
			SisterAnim_flag = true;
		if (mSister->Get_Textur()->x == 0)
			SisterAnim_flag = false;
		if (SisterAnim_flag)
			mSister->Set_Texture({ mSister->Get_Textur()->x - 1,mSister->Get_Textur()->y,5,4 });
		else
			mSister->Set_Texture({ mSister->Get_Textur()->x + 1,mSister->Get_Textur()->y,5,4 });
		SisiterCounter = 0;
	}
	SisiterCounter += 1;
}

void StageSelect::BossAnim()
{
	if (BossCounter == 16) {
		if (mBoss->Get_Textur()->x == 2)
			BossAnim_flag = true;
		if (mBoss->Get_Textur()->x == 0)
			BossAnim_flag = false;
		if (BossAnim_flag) {
			mBoss->Set_Texture({ mBoss->Get_Textur()->x - 1,0,6,2 });
		}
		else {
			mBoss->Set_Texture({ mBoss->Get_Textur()->x + 1,0,6,2 });
		}
		BossCounter = 0;
	}
	BossCounter += 1;
}

void StageSelect::StageSound()
{
	switch (now_pattern)
	{
	case STAGE_MEADOW:
		now_sound = SOUND_LABEL_STAGE_MEADOW_BGM;
		break;
	case STAGE_ICE:
		now_sound = SOUND_LABEL_STAGE_ICE_BGM;
		break;
	case STAGE_VOLCANO:
		now_sound = SOUND_LABEL_STAGE_VOLCANO_BGM;
		break;
	case STAGE_CEMETERY:
		now_sound = SOUND_LABEL_STAGE_CEMETERY_BGM;
		break;
	case STAGE_DEMONCASTLE:
		now_sound = SOUND_LABEL_STAGE_DEMONCASTLE_BGM;
		break;
	case STAGE_CASTLE:
		now_sound = SOUND_LABEL_STAGE_FORT_BGM;
		break;
	default:
		break;
	}
}

void StageSelect::ImageUpanddown()
{
	if (now_stage != STAGE_MINIBOSS && now_stage != STAGE_BIGBOSS) {
		if (Count == -50)//上
			UpDown_flag = true;
		if (Count == 50)//下
			UpDown_flag = false;
		if (UpDown_flag) {//上昇処理
			Count += 1.0f;
			Up_speed = 0.005f * SinF(Count);
			mStageImage[now_pattern]->SetPosition({ mStageImage[now_pattern]->Get_Position()->x,mStageImage[now_pattern]->Get_Position()->y + Up_speed,mStageImage[now_pattern]->Get_Position()->z });
		}
		if (!UpDown_flag) {//降下処理
			Count -= 1.0f;
			Down_speed = 0.005f * SinF(Count);
			mStageImage[now_pattern]->SetPosition({ mStageImage[now_pattern]->Get_Position()->x,mStageImage[now_pattern]->Get_Position()->y + Down_speed,mStageImage[now_pattern]->Get_Position()->z });
		}
		int num = mSelectObject.size();
		for (auto a : mSelectObject) {
			a->SetzBeffer(0.001f * num);
			num--;
		}
	}
}

void StageSelect::StageRight_Normal()
{
	//妹が目的方向に移動
	if (mSister->Get_Position()->x < 3.5f && mBackGround[now_pattern]->Get_Position()->x == 0)
		mSister->SetPosition({ mSister->Get_Position()->x + 0.05f,-1.1f,0 });
	else if (mSister->Get_Position()->x > 3.5)
		mSister->SetPosition({ 3.5,mSister->Get_Position()->y,0 });
	//妹移動完了後、ステージをずらす
	if (mBackGround[now_pattern + 1]->Get_Position()->x > 0) {
		mBackGround[now_pattern + 1]->SetPosition({ mBackGround[now_pattern + 1]->Get_Position()->x - 0.1f,0,0 });
		mBackGround[now_pattern]->SetPosition({ mBackGround[now_pattern]->Get_Position()->x - 0.1f,0,0 });
		mStageImage[now_pattern]->SetPosition({ mStageImage[now_pattern]->Get_Position()->x - 0.1f,mStageImage[now_pattern]->Get_Position()->y,mStageImage[now_pattern]->Get_Position()->z });
		mFrontImage[now_pattern]->SetPosition({ mFrontImage[now_pattern]->Get_Position()->x - 0.1f,mFrontImage[now_pattern]->Get_Position()->y,0 });
		mFrontImage[now_pattern + 1]->SetPosition({ mFrontImage[now_pattern + 1]->Get_Position()->x - 0.1f,mFrontImage[now_pattern + 1]->Get_Position()->y,0 });
		for (int i = 0; i < 3; i++)
			mStageRoute_main[i]->SetPosition({ mStageRoute_main[i]->Get_Position()->x - 0.1f,-1.55f,0 });
		//妹を目的座標に調整
		if (mSister->Get_Position()->x > -1.5f)
			mSister->SetPosition({ mSister->Get_Position()->x - 0.05f,-1.1f,0 });
		else if (mSister->Get_Position()->x < -1.5f)
			mSister->SetPosition({ -1.5f,-1.1f,0 });
	}
	else if (mBackGround[now_pattern]->Get_Position()->x < 0) {
		mBackGround[now_pattern]->SetPosition({ 0,0,0 });
	}
	//背景・妹ともに移動完了後
	if (mBackGround[now_pattern]->Get_Position()->x == 0 && mSister->Get_Position()->x == -1.5f) {
		this->LoadText_flag = true;
		mFrontImage[now_pattern]->SetPosition({ 0,mFrontImage[now_pattern]->Get_Position()->y,0 });
		mStageImage[now_pattern]->SetPosition({ 0,-0.05,0 });
		//表示
		mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,1 });
		mStageNum[now_stage]->Set_Color({ 1,1,1,1 });
		mOverall_Map->Set_Color({ 1,1,1,1 });
		mOverall_Map_point->Set_Color({ 1,1,1,1 });
		//ステージ更新
		Sound::instance().Stop(SOUND_LABEL_STAGE_WALK_SE);
		now_stage = static_cast<SelectStage>(now_stage + 1);
		//状態初期化
		this->StageMovement_flag = false;
		this->now_state = STATE_WAITING;
		StageChange();//現在のステージ背景確認
	}
}
void StageSelect::StageRight_BOSS()
{
	if (mSister->Get_Position()->x < 3.5 && mBackGround[now_pattern]->Get_Position()->x == 0)
		mSister->SetPosition({ mSister->Get_Position()->x + 0.05f,mSister->Get_Position()->y,mSister->Get_Position()->z });
	else if (mSister->Get_Position()->x > 3.5)
		mSister->SetPosition({ 3.5,mSister->Get_Position()->y,0 });
	//妹移動完了後、ステージをずらす
	if (mBackGround[now_pattern + 1]->Get_Position()->x > 0) {
		mBackGround[now_pattern + 1]->SetPosition({ mBackGround[now_pattern + 1]->Get_Position()->x - 0.1f,0,0 });
		mBackGround[now_pattern]->SetPosition({ mBackGround[now_pattern]->Get_Position()->x - 0.1f,0,0 });
		mStageImage[now_pattern]->SetPosition({ mStageImage[now_pattern]->Get_Position()->x - 0.1f,mStageImage[now_pattern]->Get_Position()->y,mStageImage[now_pattern]->Get_Position()->z });
		mFrontImage[now_pattern]->SetPosition({ mFrontImage[now_pattern]->Get_Position()->x - 0.1f,mFrontImage[now_pattern]->Get_Position()->y,0 });
		mFrontImage[now_pattern + 1]->SetPosition({ mFrontImage[now_pattern + 1]->Get_Position()->x - 0.1f,mFrontImage[now_pattern + 1]->Get_Position()->y,0 });
		for (int i = 0; i < 3; i++)
			mStageRoute_main[i]->SetPosition({ mStageRoute_main[i]->Get_Position()->x - 0.1f,-1.55f,0 });
		//妹最終地点に移動
		if (mSister->Get_Position()->x > 0)
			mSister->SetPosition({ mSister->Get_Position()->x - 0.05f, mSister->Get_Position()->y, mSister->Get_Position()->z });
		else if (mSister->Get_Position()->x < 0)//妹粛清
			mSister->SetPosition({ 0,mSister->Get_Position()->y,mSister->Get_Position()->z });
	}
	else if (mBackGround[now_pattern]->Get_Position()->x < 0) {//背景調整
		mBackGround[now_pattern]->SetPosition({ 0,0,0 });
	}
	//背景・妹ともに移動完了後
	if (mBackGround[now_pattern]->Get_Position()->x == 0 && mSister->Get_Position()->x == 0) {
		this->LoadText_flag = true;
		mFrontImage[now_pattern]->SetPosition({ 0,mFrontImage[now_pattern]->Get_Position()->y,0 });
		mStageImage[now_pattern]->SetPosition({ 0,-0.05,0 });
		//表示
		mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,1 });
		mStageNum[now_stage]->Set_Color({ 1,1,1,1 });
		mOverall_Map->Set_Color({ 1,1,1,1 });
		mOverall_Map_point->Set_Color({ 1,1,1,1 });
		Sound::instance().Stop(SOUND_LABEL_STAGE_WALK_SE);
		now_stage = static_cast<SelectStage>(now_stage + 1);
		this->StageMovement_flag = false;
		this->now_state = STATE_WAITING;
		StageChange();//現在のステージ背景確認
	}
}
void StageSelect::StageLeft_Normal()
{
	//妹を前のエリア(左側)に移動させる
	if (mSister->Get_Position()->x < 3.5f && mBackGround[now_pattern]->Get_Position()->x == 0)
		mSister->SetPosition({ mSister->Get_Position()->x + 0.05f,-1.1f,0 });
	else if (mSister->Get_Position()->x > 3.5f)
		mSister->SetPosition({ 3.5f,-1.1f,0 });
	//妹移動完了後、ステージをずらす
	if (mBackGround[now_pattern - 1]->Get_Position()->x < 0) {
		mBackGround[now_pattern - 1]->SetPosition({ mBackGround[now_pattern - 1]->Get_Position()->x + 0.1f,0,0 });
		mBackGround[now_pattern]->SetPosition({ mBackGround[now_pattern]->Get_Position()->x + 0.1f,0,0 });
		mStageImage[now_pattern]->SetPosition({ mStageImage[now_pattern]->Get_Position()->x + 0.1f,mStageImage[now_pattern]->Get_Position()->y,mStageImage[now_pattern]->Get_Position()->z });
		mFrontImage[now_pattern]->SetPosition({ mFrontImage[now_pattern]->Get_Position()->x + 0.1f,mFrontImage[now_pattern]->Get_Position()->y,0 });
		mFrontImage[now_pattern - 1]->SetPosition({ mFrontImage[now_pattern - 1]->Get_Position()->x + 0.1f,mFrontImage[now_pattern - 1]->Get_Position()->y,0 });
		for (int i = 0; i < 3; i++)
			mStageRoute_main[i]->SetPosition({ mStageRoute_main[i]->Get_Position()->x + 0.1f,-1.55f,0 });
		//妹を目的座標に調整
		if (mSister->Get_Position()->x < 1.5f)
			mSister->SetPosition({ mSister->Get_Position()->x + 0.05f,-1.1f,0 });
		else if (mSister->Get_Position()->x > 1.5f)
			mSister->SetPosition({ 1.5f,-1.1f,0 });
	}
	else if (mBackGround[now_pattern]->Get_Position()->x > 0) {//背景調整
		mBackGround[now_pattern]->SetPosition({ 0,0,0 });
	}
	//背景・妹ともに移動完了後
	if (mBackGround[now_pattern]->Get_Position()->x == 0 && mSister->Get_Position()->x == 1.5f) {
		this->LoadText_flag = true;
		mFrontImage[now_pattern]->SetPosition({ 0,mFrontImage[now_pattern]->Get_Position()->y,0 });
		mStageImage[now_pattern]->SetPosition({ 0,-0.05,0 });
		mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,1 });
		mStageNum[now_stage]->Set_Color({ 1,1,1,1 });
		mOverall_Map_point->Set_Color({ 1,1,1,1 });
		Sound::instance().Stop(SOUND_LABEL_STAGE_WALK_SE);
		now_stage = static_cast<SelectStage>(now_stage - 1);
		this->StageMovement_flag = false;
		mOverall_Map->Set_Color({ 1,1,1,1 });
		this->now_state = STATE_WAITING;
		StageChange();//現在のステージ背景確認
	}
}
void StageSelect::StageLeft_BOSS()
{
	if (mSister->Get_Position()->x > -3.5 && mBackGround[now_pattern]->Get_Position()->x == 0) {
		mSister->SetPosition({ mSister->Get_Position()->x - 0.05f,mSister->Get_Position()->y,mSister->Get_Position()->z });
	}
	else if (mSister->Get_Position()->x < -3.5) {
		mSister->SetPosition({ -3.5,mSister->Get_Position()->y,0 });
	}
	//妹移動完了後、ステージをずらす
	if (mBackGround[now_pattern - 1]->Get_Position()->x < 0) {
		mBackGround[now_pattern - 1]->SetPosition({ mBackGround[now_pattern - 1]->Get_Position()->x + 0.1f,0,0 });
		mBackGround[now_pattern]->SetPosition({ mBackGround[now_pattern]->Get_Position()->x + 0.1f,0,0 });
		mStageImage[now_pattern]->SetPosition({ mStageImage[now_pattern]->Get_Position()->x + 0.1f,mStageImage[now_pattern]->Get_Position()->y,mStageImage[now_pattern]->Get_Position()->z });
		mFrontImage[now_pattern]->SetPosition({ mFrontImage[now_pattern]->Get_Position()->x + 0.1f,mFrontImage[now_pattern]->Get_Position()->y,0 });
		mFrontImage[now_pattern - 1]->SetPosition({ mFrontImage[now_pattern - 1]->Get_Position()->x + 0.1f,mFrontImage[now_pattern - 1]->Get_Position()->y,0 });
		for (int i = 0; i < 3; i++)
			mStageRoute_main[i]->SetPosition({ mStageRoute_main[i]->Get_Position()->x + 0.1f,-1.55f,0 });
		//妹最終地点に移動
		if (mSister->Get_Position()->x < 0)
			mSister->SetPosition({ mSister->Get_Position()->x + 0.05f, mSister->Get_Position()->y, mSister->Get_Position()->z });
		else if (mSister->Get_Position()->x > 0)//妹粛清
			mSister->SetPosition({ 0,mSister->Get_Position()->y,mSister->Get_Position()->z });
	}
	else if (mBackGround[now_pattern]->Get_Position()->x > 0) {//背景調整
		mBackGround[now_pattern]->SetPosition({ 0,0,0 });
	}
	//背景・妹ともに移動完了後
	if (mBackGround[now_pattern]->Get_Position()->x == 0 && mSister->Get_Position()->x == 0) {
		this->LoadText_flag = true;
		mFrontImage[now_pattern]->SetPosition({ 0,mFrontImage[now_pattern]->Get_Position()->y,0 });
		mStageImage[now_pattern]->SetPosition({ 0,-0.05,0 });
		mRank[max_rank[now_stage]]->Set_Color({ 1,1,1,1 });
		mStageNum[now_stage]->Set_Color({ 1,1,1,1 });
		mOverall_Map->Set_Color({ 1,1,1,1 });
		mOverall_Map_point->Set_Color({ 1,1,1,1 });
		Sound::instance().Stop(SOUND_LABEL_STAGE_WALK_SE);
		now_stage = static_cast<SelectStage>(now_stage - 1);
		this->StageMovement_flag = false;
		this->now_state = STATE_WAITING;
		StageChange();//現在のステージ背景確認
	}
}

void StageSelect::StagePoint()
{
	switch (now_stage)
	{
		//テクスチャー(0=緑,1=青,2=赤,3=灰,4=紫)
	case STAGE_1_1://-1.85
	case STAGE_1_2:
		mOverall_Map_point->Set_Texture({ 0, 0, 5, 1 });
		mOverall_Map_point->SetPosition({ -1.85,1.5,0 });
		break;
	case STAGE_2_1://-1.1
	case STAGE_2_2:
		mOverall_Map_point->Set_Texture({ 1, 0, 5, 1 });
		mOverall_Map_point->SetPosition({ -1.1,1.5,0 });
		break;
	case STAGE_MINIBOSS://-0.375
		mOverall_Map_point->Set_Texture({ 4, 0, 5, 1 });
		mOverall_Map_point->SetPosition({ -0.375,1.5,0 });
		break;
	case STAGE_3_1:
	case STAGE_3_2:
		mOverall_Map_point->Set_Texture({ 2, 0, 5, 1 });
		mOverall_Map_point->SetPosition({ 0.375,1.5,0 });
		break;
	case STAGE_4_1:
	case STAGE_4_2:
		mOverall_Map_point->Set_Texture({ 3, 0, 5, 1 });
		mOverall_Map_point->SetPosition({ 1.1,1.5,0 });
		break;
	case STAGE_BIGBOSS:
		mOverall_Map_point->Set_Texture({ 4, 0, 5, 1 });
		mOverall_Map_point->SetPosition({ 1.85,1.5,0 });
		break;
	default:
		break;
	}
}

void StageSelect::Standing_PosMove()
{
	switch (now_stage)
	{
	case STAGE_1_2://右移動
	case STAGE_3_2://先：二つ
		if (mStanding_Position[2]->Get_Position()->x > -1.75f) {
			for (int i = 0; i < 5; i++)
				mStanding_Position[i]->SetPosition({ mStanding_Position[i]->Get_Position()->x - 0.1f,-1.5f,0 });
		}
		else if (mStanding_Position[2]->Get_Position()->x < -1.75f)
			mStanding_Position[2]->SetPosition({ -1.75f,-1.5f,0 });
		break;
	case STAGE_2_1://左移動
	case STAGE_4_1://先：二つ
		if (mStanding_Position[2]->Get_Position()->x < 1.75f) {
			for (int i = 0; i < 5; i++)
				mStanding_Position[i]->SetPosition({ mStanding_Position[i]->Get_Position()->x + 0.1f,-1.5f,0 });
		}
		else if (mStanding_Position[2]->Get_Position()->x > 1.75f)
			mStanding_Position[2]->SetPosition({ 1.75f,-1.5f,0 });
		break;
	case STAGE_2_2://右移動
	case STAGE_4_2://先：一つ
		if (mStanding_Position[2]->Get_Position()->x > 0) {
			for (int i = 0; i < 5; i++)
				mStanding_Position[i]->SetPosition({ mStanding_Position[i]->Get_Position()->x - 0.1f,-1.5f,0 });
		}
		else if (mStanding_Position[2]->Get_Position()->x > 0)
			mStanding_Position[2]->SetPosition({ 0,-1.5f,0 });
		break;
	case STAGE_3_1://左移動　先：一つ
		if (mStanding_Position[4]->Get_Position()->x < 0) {
			for (int i = 0; i < 5; i++)
				mStanding_Position[i]->SetPosition({ mStanding_Position[i]->Get_Position()->x + 0.1f,-1.5f,0 });
		}
		else if (mStanding_Position[4]->Get_Position()->x < 0)
			mStanding_Position[4]->SetPosition({ 0,-1.5f,0 });
		break;
	case STAGE_MINIBOSS:
	case STAGE_BIGBOSS:
		switch (now_state)
		{
		case STATE_MOVELEFT:
			if (mStanding_Position[2]->Get_Position()->x < 1.75f) {
				for (int i = 0; i < 5; i++)
					mStanding_Position[i]->SetPosition({ mStanding_Position[i]->Get_Position()->x + 0.1f,-1.5f,0 });
			}
			else if (mStanding_Position[2]->Get_Position()->x > 1.75f)
				mStanding_Position[2]->SetPosition({ 1.75f,-1.5f,0 });
			break;
		case STATE_MOVERIGHT:
			if (mStanding_Position[4]->Get_Position()->x > -1.75f) {
				for (int i = 0; i < 5; i++)
					mStanding_Position[i]->SetPosition({ mStanding_Position[i]->Get_Position()->x - 0.1f,-1.5f,0 });
			}
			else if (mStanding_Position[4]->Get_Position()->x < -1.75f)
				mStanding_Position[4]->SetPosition({ -1.75f,-1.5f,0 });
			break;
		default:
			break;
		}
	default:
		break;
	}
}

void StageSelect::Rord_PosMove()
{
	switch (now_stage)
	{
	case STAGE_1_2://右移動
	case STAGE_3_2://先：二つ
		for (int i = 0; i < 5; i++)
			mStageRoute_main[i]->SetPosition({ mStageRoute_main[0]->Get_Position()->x - 0.1f,-1.5f,0 });
		break;
	case STAGE_2_1://左移動
	case STAGE_4_1://先：二つ
		for (int i = 0; i < 5; i++)
			mStageRoute_main[i]->SetPosition({ mStageRoute_main[0]->Get_Position()->x + 0.1f,-1.5f,0 });
		break;
	case STAGE_2_2://右移動
	case STAGE_4_2://先：一つ
		for (int i = 0; i < 5; i++)
			mStageRoute_main[i]->SetPosition({ mStageRoute_main[0]->Get_Position()->x - 0.1f,-1.5f,0 });
		break;
	case STAGE_3_1://左移動　先：一つ
		for (int i = 0; i < 5; i++)
			mStageRoute_main[i]->SetPosition({ mStageRoute_main[0]->Get_Position()->x + 0.1f,-1.5f,0 });
		break;
	case STAGE_MINIBOSS:
	case STAGE_BIGBOSS:
	default:
		break;
	}
}

float StageSelect::SinF(float angle)
{
	float Radian = angle * (PI / 180);
	return sinf(Radian);
}

float StageSelect::Cosf(float angle)
{
	float Radian = angle * (PI / 180);
	return cosf(Radian);
}

void StageSelect::EventUpdate()
{
	switch (now_event)
	{
	case EVENT_NULL:

		break;
	case EVENT_LOAD_DISPLAY://道の発生イベント
		if (Event_flag) {
			Direct3D::Set_Alpha(true);
			Sound::instance().Play(SOUND_LABEL_LOAD_SE);
			Event_flag = false;
		}
		for (int i = 0; i < 3; i++) {
			switch (now_stage)
			{
			case STAGE_1_1:
				if (mStageRoute_main[0]->Get_Color().a < 1)
					mStageRoute_main[0]->Set_Color({ 1,1,1,mStageRoute_main[0]->Get_Color().a + 0.005f });
				else if (mStageRoute_main[0]->Get_Color().a > 1)
					mStageRoute_main[0]->Set_Color({ 1,1,1,1 });
				break;
			default:
				if (mStageRoute_main[i]->Get_Color().a < 1)
					mStageRoute_main[i]->Set_Color({ 1,1,1,mStageRoute_main[i]->Get_Color().a + 0.005f });
				else if (mStageRoute_main[i]->Get_Color().a > 1)
					mStageRoute_main[i]->Set_Color({ 1,1,1,1 });
				break;
			}
		}
		if (mStageRoute_main[0]->Get_Color().a == 1) {
			now_event = EVENT_NULL;
			FILE* fp;
			fopen_s(&fp, "assets/oni.dat", "r");
			for (int i = 0; i < 10; i++)
				fscanf_s(fp, "%d", &this->max_rank[i]);
			fclose(fp);
			if (max_rank[STAGE_1_1] != RANK_NULL)
				max_stage = STAGE_1_2;
			if (max_rank[STAGE_1_2] != RANK_NULL)
				max_stage = STAGE_2_1;
			if (max_rank[STAGE_2_1] != RANK_NULL)
				max_stage = STAGE_MINIBOSS;
			if (max_rank[STAGE_MINIBOSS] != RANK_NULL)
				max_stage = STAGE_3_1;
			if (max_rank[STAGE_3_1] != RANK_NULL)
				max_stage = STAGE_4_1;
			if (max_rank[STAGE_4_1] != RANK_NULL)
				max_stage = STAGE_BIGBOSS;
			this->LoadText_flag = true;
			Direct3D::Set_Alpha(false);
		}
		break;
	case EVENT_BOSS_MOVE://ボスの移動イベント
		if (Event_flag) {
			Direct3D::Set_Alpha(true);
			Sound::instance().Play(SOUND::SOUND_LABEL_STAGE_LILITHWALK_SE);
			Event_flag = false;
		}
		if (mBoss->Get_Position()->x < 4) {
			mBoss->SetPosition({ mBoss->Get_Position()->x + 0.05f,mBoss->Get_Position()->y + 0.0001f,0 });
		}
		else if (mBoss->Get_Position()->x > 4) {
			Sound::instance().Play(SOUND::SOUND_LABEL_STAGE_LILITHWALK_SE);
			mBoss->SetPosition({ 4,mBoss->Get_Position()->y,0 });
			now_event = EVENT_LOAD_DISPLAY;//道発生イベントへ
		}
		break;
	default:
		break;
	}
	int num = mSelectObject.size();
	for (auto a : mSelectObject) {
		a->SetzBeffer(0.001f * num);
		num--;
		a->Update();
	}
}
