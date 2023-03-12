#include "Title.h"
#include "Input.h"
#include "XAudio2.h"
#include "TextureDate.h"
Title::Title()
{
	mBackGround = new Image("assets/Title/TitleBack.png", { 0,0,0 }, { 7,3.75,1 });
	mTitle = new Image("assets/Title/TitleRogo.png", { 1.75,1.15,0 }, { 3,1.45,1 });
	mPressUI = new Image("assets/Title/Start.png", { 2.25,-0.75,0 }, { 1.5,0.25,1 });
	mStartUI = new Image("assets/Title/Beginning.png", { 2.25,-0.5,0 }, { 1.5,0.25,1 });
	mNextUI = new Image("assets/Title/Continued.png", { 2.25,-0.5,0 }, { 1.5,0.25,1 });
	mOptionUI = new Image("assets/Title/Option.png", { 2.25,-1.0,0 }, { 1.5,0.25,1 });
	mFinishUI = new Image("assets/Title/Game_End.png", { 2.25,-1.5,0 }, { 1.5,0.25,1 });
	mBackFlame = new Image("assets/Title/TextFlame.png", { 2,0,0 }, { 2.5,0.75,1 }, { 1,1,1 }, 1.5);

	//基礎オブジェクト
	mTitleObject.emplace_back(mBackGround);
	mTitleObject.emplace_back(mTitle);
	//選択肢初期化
	Select_pos = SELECT_START;
	Current_Title = TITLE_SCENE;
	//オブジェクト初期化
	this->ObjectInitialize();
}
void Title::Initialize()
{
	//初期化フラグOFF
	this->Initialize_flag = false;
	//終了フラグOFF
	this->Finish_flag = false;
	InitializePos_flag = false;

	Sound::instance().Play(SOUND_LABEL_TITLE_BGM);
	Sound::instance().Set_Volume(SOUND_LABEL_TITLE_BGM, 0.0f);
	Next_scene = SCENE_TITLE;
	Current_Title = TITLE_SCENE;
	Select_pos = SELECT_START;
}

void Title::Update()
{
	switch (Current_Title)
	{
	case TITLE_SCENE:
		TitleUpdate();
		break;
	case TITLE_MENU:
		MenuUpdate();
		break;
	default:
		break;
	}
	FlameAnim();
}

void Title::Draw()
{
	for (GameObject* obj : mTitleObject)
		obj->Draw();
}

void Title::Release()
{
	delete mBackGround;
	delete mTitle;
	delete mPressUI;
	delete mStartUI;
	delete mOptionUI;
	delete mFinishUI;
	delete mBackFlame;

}

void Title::Input_Update()
{
	if (Next_scene == SCENE_OPTION)
		Next_scene = SCENE_TITLE;

	switch (Current_Title)
	{
	case TITLE_SCENE:
		if (Input::instance().GetKeyboardTrigger(VK_RETURN) || Input::instance().GetButtonPress_Once(XINPUT_B)) {
			Sound::instance().Play(SOUND_LABEL_TITLE_DECISION_SE);
			Current_Title = TITLE_MENU;
			InitializePos_flag = false;
		}
		break;
	case TITLE_MENU:
		if (Input::instance().GetKeyboardTrigger('W') || Input::instance().GetButtonPress_Once(XINPUT_UP)) {
			Sound::instance().Play(SOUND_LABEL_TITLE_CURSOR_SE);
			Float3* pos = mBackFlame->Get_Position();
			switch (Select_pos)
			{
			case SELECT_START:
				Select_pos = SELECT_END;
				*pos = *mFinishUI->Get_Position();
				break;
			case SELECT_END:
				Select_pos = SELECT_OPTION;
				*pos = *mOptionUI->Get_Position();
				break;
			case SELECT_OPTION:
				Select_pos = SELECT_START;
				*pos = *mStartUI->Get_Position();
				break;
			default:
				break;
			}
		}
		else if (Input::instance().GetKeyboardTrigger('S') || Input::instance().GetButtonPress_Once(XINPUT_DOWN)) {
			Sound::instance().Play(SOUND_LABEL_TITLE_CURSOR_SE);
			Float3* pos = mBackFlame->Get_Position();
			switch (Select_pos)
			{
			case SELECT_START:
				Select_pos = SELECT_OPTION;
				*pos = *mOptionUI->Get_Position();
				break;
			case SELECT_END:
				Select_pos = SELECT_START;
				*pos = *mStartUI->Get_Position();
				break;
			case SELECT_OPTION:
				Select_pos = SELECT_END;
				*pos = *mFinishUI->Get_Position();
				break;
			default:
				break;
			}
		}
		if (Input::instance().GetKeyboardTrigger(VK_RETURN) || Input::instance().GetButtonPress_Once(XINPUT_B)) {
			Sound::instance().Play(SOUND_LABEL_TITLE_DECISION_SE);
			switch (Select_pos)
			{
			case SELECT_START://ステージ選択画面へ
				this->Finish_flag = true;
				this->Fade_flag = true;
				if (this->max_rank[0] == RANK_NULL) {//1-1未クリア
					Next_scene = SCENE_STORY;
				}
				else {//ストーリー視聴済み
					Next_scene = SCENE_STAGESELECT;
				}
				//Next_scene = SCENE_STAGESELECT;
				break;
			case SELECT_OPTION://オプション画面へ
				this->Finish_flag = true;
				this->Fade_flag = true;
				Next_scene = SCENE_OPTION;
				break;
			case SELECT_END://終了処理
				this->Finish_flag = true;
				this->Fade_flag = true;
				Next_scene = SCENE_END;
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

void Title::TitleInitialize()
{
	//必要のない要素削除
	while (mTitleObject.back() != mTitle)
	{
		mTitleObject.pop_back();
	}
	//追加オブジェクト
	if (mTitleObject.back() == mTitle) {
		mTitleObject.emplace_back(mBackFlame);
		mTitleObject.emplace_back(mPressUI);
		this->ObjectInitialize();
	}
}

void Title::MenuInitialize()
{
	//選択肢初期化*初期位置はスタート*
	Select_pos = SELECT_START;
	//必要のない要素削除
	while (mTitleObject.back() != mTitle)
		mTitleObject.pop_back();
	FILE* fp=NULL;
	fopen_s(&fp, "assets/oni.dat", "r");

	for (int i = 0; i < 10; i++)
		fscanf_s(fp, "%d", &this->max_rank[i]);
	fclose(fp);

	for (int i = 0; i < 10; i++) {
		switch (this->max_rank[i])
		{
		case RANK_NULL:
			if (i == 9) {
				if (mTitleObject.back() == mTitle) {
					mTitleObject.emplace_back(mBackFlame);
					mTitleObject.emplace_back(mStartUI);
					mTitleObject.emplace_back(mOptionUI);
					mTitleObject.emplace_back(mFinishUI);
					this->ObjectInitialize();
				}
			}
			break;
		default:
			if (mTitleObject.back() == mTitle) {
				mTitleObject.emplace_back(mBackFlame);
				mTitleObject.emplace_back(mNextUI);
				mTitleObject.emplace_back(mOptionUI);
				mTitleObject.emplace_back(mFinishUI);
				this->ObjectInitialize();
			}
			i = 10;
			break;
		}
	}
}

void Title::TitleUpdate()
{
	//描画：タイトルロゴ、Press Button、立ち絵、背景
	//入力：ボタンが押されたらTitle_Menuへ遷移
	if (!InitializePos_flag) {
		TitleInitialize();
		Float3* pos = mBackFlame->Get_Position();
		*pos = *mPressUI->Get_Position();
		InitializePos_flag = true;
	}
	int num = mTitleObject.size();
	for (auto a : mTitleObject) {
		a->Update();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Title::MenuUpdate()
{
	//描画：タイトルロゴ、三種の選択肢、立ち絵、背景
	//入力：上下系入力で三種の選択肢を選択
	//		Aボタンでその選択通りに進む
	if (!InitializePos_flag) {
		MenuInitialize();
		Float3* pos = mBackFlame->Get_Position();
		*pos = *mStartUI->Get_Position();
		mBackFlame->SetSize({ 2,0.5,1 });
		InitializePos_flag = true;
	}
	int num = mTitleObject.size();
	for (auto a : mTitleObject) {
		a->Update();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Title::ObjectInitialize()
{
	int num = mTitleObject.size();
	for (auto a : mTitleObject) {
		a->Initialize();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Title::FlameAnim()
{
	//表示・非表示切り替え
	if (mBackFlame->Get_Color().a == 2)
		FlameBlinking_Flag = true;
	if (mBackFlame->Get_Color().a == 1)
		FlameBlinking_Flag = false;

	switch (FlameBlinking_Flag)
	{
	case true://透明化
		mBackFlame->Set_Color({ 1,1,1,mBackFlame->Get_Color().a - 0.01f });
		if (mBackFlame->Get_Color().a < 1) {
			mBackFlame->Set_Color({ 1,1,1,1 });
			FlameBlinking_Flag = false;
		}
		break;
	case false://可視化
		mBackFlame->Set_Color({ 1,1,1,mBackFlame->Get_Color().a + 0.01f });
		if (mBackFlame->Get_Color().a > 2) {
			mBackFlame->Set_Color({ 1,1,1,2 });
			FlameBlinking_Flag = true;
		}
		break;
	default:
		break;
	}
	int num = mTitleObject.size();
	for (auto a : mTitleObject) {
		a->SetzBeffer(0.001f * num);
		num--;
	}
}
