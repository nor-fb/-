#include "Option.h"
#include "Input.h"
#include "XAudio2.h"
Option::Option()
{
	//初期化
	mBackGround = new Image("assets/Option/OptionBack.png", { 0,0,0.002f }, { 6.75,3.75,1 });
	//mSister=new Image("assets/Option/Game_sister_wait_anim0.png", { -2,-0.75,0 }, { 0.5,1,1 }, { 0,0,5,4 });
	mTitleBack = new Image("assets/Option/Title_Return.png", { 0,-0.5,0.001f }, { 2.5,0.5,1 });
	mStageSelectBack = new Image("assets/Option/StageSelect_Return.png", { 2,0,0.001f }, { 2,0.5,1 });
	mGameBack = new Image("assets/Option/Game_Return.png", { 2,0,0.001f }, { 2,0.5,1 });
	mNote = new Image("assets/Option/Note.png", { 2,-0.5,0.001f }, { 2,0.5,1 });
	mDate = new Image("assets/Option/Erase_Data.png", { 2,0,0.001f }, { 2,0.5,1 });
	mOptionLogo = new Image("assets/Option/Option.png", { 0,1.25,0.001f }, { 3,1,1 });
	mPauseLogo = new Image("assets/Option/Pause.png", { 0,1.25,0.001f }, { 1.5,0.5,1 });
	mBackFlame = new Image("assets/Option/TextFlame.png", { 2,0,0.0015f }, { 2.1,0.5,1 });

	//基礎オブジェクト
	mOptionObject.emplace_back(mBackGround);
	mOptionObject.emplace_back(mBackFlame);

	int num = mOptionObject.size();
	for (auto a : mOptionObject) {
		a->Initialize();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Option::Initialize()
{
	//初期化フラグOFF
	this->Initialize_flag = false;
	//終了フラグOFF
	this->Finish_flag = false;

	switch (BackScene)
	{
	case SCENE_TITLE:
		TitleInitialize();
		break;
	case SCENE_STAGESELECT:
		StageSelectInitialize();
		break;
	case SCENE_GAMESCENE:
		GameInitialize();
		break;
	default:
		break;
	}
	Update();
}

void Option::Update()
{
	switch (BackScene)
	{
	case SCENE_TITLE:
		TitleUpdate();
		break;
	case SCENE_STAGESELECT:
		StageSelectUpdate();
		break;
	case SCENE_GAMESCENE:
		GameUpdate();
		break;
	default:
		break;
	}
}

void Option::Draw()
{
	for (GameObject* obj : mOptionObject)
		obj->Draw();
}

void Option::Release()
{
	for (GameObject* obj : mOptionObject)
		obj->Release();
	mOptionObject.clear();
	mOptionObject.shrink_to_fit();
}


void Option::TitleInitialize()
{
	////選択肢初期化
	Select_pos = SELECT_BACK;
	//選択肢の座標を配置
	mBackFlame->SetSize({ 2.25,0.5,1 });
	mTitleBack->SetPosition({ 0,0,0 });
	mNote->SetPosition({ 0, -0.5, 0 });
	mDate->SetPosition({0, -1, 0});
	//初期状態に戻す
	while (mOptionObject.back() != mBackFlame)
		mOptionObject.pop_back();
	mBackFlame->SetPosition(*mTitleBack->Get_Position());
	//オブジェクト追加
	if (mOptionObject.back() == mBackFlame)
	{
		mOptionObject.emplace_back(mTitleBack);
		mOptionObject.emplace_back(mNote);
		mOptionObject.emplace_back(mDate);
		mOptionObject.emplace_back(mOptionLogo);
	}
	int num = mOptionObject.size();
	for (auto a : mOptionObject) {
		a->Initialize();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Option::TitleUpdate()
{
	//入力：上下系入力で選択肢を選択
	//		Aボタンでその選択通りに進む
	if (!this->Finish_flag) {
		if (Input::instance().GetKeyboardTrigger('W') || Input::instance().GetButtonPress_Once(XINPUT_UP))
		{
			Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
			switch (Select_pos)
			{
			case SelectOPosition::SELECT_BACK:
				Select_pos = SELECT_DELETE;
				mBackFlame->SetPosition(*mDate->Get_Position());
				break;
			case SelectOPosition::SELECT_NOTE:
				Select_pos = SELECT_BACK;
				mBackFlame->SetPosition(*mTitleBack->Get_Position());
				break;
			case SelectOPosition::SELECT_DELETE:
				Select_pos = SELECT_NOTE;
				mBackFlame->SetPosition(*mNote->Get_Position());
				break;
			}
		}
		else if (Input::instance().GetKeyboardTrigger('S') || Input::instance().GetButtonPress_Once(XINPUT_DOWN))
		{
			Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
			switch (Select_pos)
			{
			case SelectOPosition::SELECT_BACK:
				Select_pos = SELECT_NOTE;
				mBackFlame->SetPosition(*mNote->Get_Position());
				break;
			case SelectOPosition::SELECT_NOTE:
				Select_pos = SELECT_DELETE;
				mBackFlame->SetPosition(*mDate->Get_Position());
				break;
			case SelectOPosition::SELECT_DELETE:
				Select_pos = SELECT_BACK;
				mBackFlame->SetPosition(*mTitleBack->Get_Position());
				break;
			}
		}
		if (Input::instance().GetKeyboardTrigger(VK_RETURN) || Input::instance().GetButtonPress_Once(XINPUT_B))
		{
			Sound::instance().Play(SOUND_LABEL_OPTION_DECISION_SE);
			switch (Select_pos)
			{
			case SelectOPosition::SELECT_BACK:
				this->Next_scene = SCENE_TITLE;
				this->Finish_flag = true;
				this->Fade_flag = true;
				break;
			case SelectOPosition::SELECT_NOTE:
				this->Next_scene = SCENE_NOTE;
				this->Finish_flag = true;
				this->Fade_flag = true;
				break;
			case SelectOPosition::SELECT_DELETE:
				if (CheckFile("assets/oni.dat")) {
					remove("assets/oni.dat");
				}
				this->Next_scene = RESET;
				this->Finish_flag = true;
				this->Fade_flag = true;
				break;
			}
		}
		if (Input::instance().GetButtonPress_Once(XINPUT_A)) {
			//タイトルに戻る
			Sound::instance().Play(SOUND_LABEL_OPTION_BACK_SE);
			this->Next_scene = SCENE_TITLE;
			this->Finish_flag = true;
			this->Fade_flag = true;
		}
	}
	int num = mOptionObject.size();
	for (auto a : mOptionObject) {
		a->Update();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Option::StageSelectInitialize()
{
	//選択肢初期化
	Select_pos = SELECT_BACK;
	//選択肢の座標を配置
	mBackFlame->SetSize({ 2.75,0.5,1 });
	mStageSelectBack->SetPosition({ 0, 0, 0 });
	mNote->SetPosition({ 0, -0.5, 0 });
	mTitleBack->SetPosition({ 0, -1, 0 });
	//初期状態に戻す
	while (mOptionObject.back() != mBackFlame)
		mOptionObject.pop_back();
	mBackFlame->SetPosition(*mStageSelectBack->Get_Position());
	//オブジェクト追加
	if (mOptionObject.back() == mBackFlame)
	{
		mOptionObject.emplace_back(mStageSelectBack);
		mOptionObject.emplace_back(mNote);
		mOptionObject.emplace_back(mTitleBack);
		mOptionObject.emplace_back(mPauseLogo);
	}
	int num = mOptionObject.size();
	for (auto a : mOptionObject) {
		a->Initialize();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Option::StageSelectUpdate()
{
	//入力：上下系入力で選択肢を選択
	//Aボタンでその選択通りに進む
	if (!this->Finish_flag) {
		if (Input::instance().GetKeyboardTrigger('W') || Input::instance().GetButtonPress_Once(XINPUT_UP))
		{
			Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
			switch (Select_pos)
			{
			case SelectOPosition::SELECT_BACK:
				Select_pos = SELECT_TITLE;
				mBackFlame->SetPosition(*mTitleBack->Get_Position());
				break;
			case SelectOPosition::SELECT_NOTE:
				Select_pos = SELECT_BACK;
				mBackFlame->SetPosition(*mStageSelectBack->Get_Position());
				break;
			case SelectOPosition::SELECT_TITLE:
				Select_pos = SELECT_NOTE;
				mBackFlame->SetPosition(*mNote->Get_Position());
				break;
			}
		}
		else if (Input::instance().GetKeyboardTrigger('S') || Input::instance().GetButtonPress_Once(XINPUT_DOWN))
		{
			Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
			switch (Select_pos)
			{
			case SelectOPosition::SELECT_BACK:
				Select_pos = SELECT_NOTE;
				mBackFlame->SetPosition(*mNote->Get_Position());
				break;
			case SelectOPosition::SELECT_NOTE:
				Select_pos = SELECT_TITLE;
				mBackFlame->SetPosition(*mTitleBack->Get_Position());
				break;
			case SelectOPosition::SELECT_TITLE:
				Select_pos = SELECT_BACK;
				mBackFlame->SetPosition(*mStageSelectBack->Get_Position());
				break;
			}
		}
		if (Input::instance().GetKeyboardTrigger(VK_RETURN) || Input::instance().GetButtonPress_Once(XINPUT_B))
		{
			Sound::instance().Play(SOUND_LABEL_OPTION_DECISION_SE);
			switch (Select_pos)
			{
			case SelectOPosition::SELECT_BACK:
				//ステージセレクトに戻る
				this->Next_scene = SCENE_STAGESELECT;
				this->Finish_flag = true;
				//this->Fade_flag = true;
				break;
			case SelectOPosition::SELECT_NOTE:
				//ノートへ
				this->Next_scene = SCENE_NOTE;
				this->Finish_flag = true;
				this->Fade_flag = true;
				break;
			case SelectOPosition::SELECT_TITLE:
				//タイトルへ
				this->Next_scene = SCENE_TITLE;
				this->Finish_flag = true;
				this->Fade_flag = true;
				break;
			}
		}
		if (Input::instance().GetButtonPress_Once(XINPUT_A)) {
			//ステージセレクトに戻る
			Sound::instance().Play(SOUND_LABEL_OPTION_BACK_SE);
			this->Next_scene = SCENE_STAGESELECT;
			this->Finish_flag = true;
			//this->Fade_flag = true;
		}
	}
	int num = mOptionObject.size();
	for (auto a : mOptionObject) {
		a->Update();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Option::GameInitialize()
{
	//選択肢初期化
	Select_pos = SELECT_BACK;
	//選択肢の座標を配置
	mBackFlame->SetSize({ 2.75,0.5,1 });
	mGameBack->SetPosition(Float3(0, 0.5, 0));
	mNote->SetPosition(Float3(0, 0, 0));
	mStageSelectBack->SetPosition(Float3(0, -0.5, 0));
	mTitleBack->SetPosition(Float3(0, -1.0, 0));
	//初期状態に戻す
	while (mOptionObject.back() != mBackFlame)
		mOptionObject.pop_back();
	mBackFlame->SetPosition(*mGameBack->Get_Position());

	//オブジェクト追加
	if (mOptionObject.back() == mBackFlame)
	{
		mOptionObject.emplace_back(mGameBack);
		mOptionObject.emplace_back(mNote);
		mOptionObject.emplace_back(mTitleBack);
		mOptionObject.emplace_back(mStageSelectBack);
		mOptionObject.emplace_back(mPauseLogo);
	}
	int num = mOptionObject.size();
	for (auto a : mOptionObject) {
		a->Initialize();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Option::GameUpdate()
{
	//入力：上下系入力で選択肢を選択
	//Aボタンでその選択通りに進む
	if (!this->Finish_flag) {
		if (Input::instance().GetKeyboardTrigger('W') || Input::instance().GetButtonPress_Once(XINPUT_UP))
		{
			Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
			switch (Select_pos)
			{
			case SelectOPosition::SELECT_BACK:
				Select_pos = SELECT_TITLE;
				mBackFlame->SetPosition(*mTitleBack->Get_Position());
				break;
			case SelectOPosition::SELECT_NOTE:
				Select_pos = SELECT_BACK;
				mBackFlame->SetPosition(*mGameBack->Get_Position());
				break;
			case SelectOPosition::SELECT_STAGE:
				Select_pos = SELECT_NOTE;
				mBackFlame->SetPosition(*mNote->Get_Position());
				break;
			case SelectOPosition::SELECT_TITLE:
				Select_pos = SELECT_STAGE;
				mBackFlame->SetPosition(*mStageSelectBack->Get_Position());
				break;
			}
		}
		else if (Input::instance().GetKeyboardTrigger('S') || Input::instance().GetButtonPress_Once(XINPUT_DOWN))
		{
			Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
			switch (Select_pos)
			{
			case SelectOPosition::SELECT_BACK:
				Select_pos = SELECT_NOTE;
				mBackFlame->SetPosition(*mNote->Get_Position());
				break;
			case SelectOPosition::SELECT_NOTE:
				Select_pos = SELECT_STAGE;
				mBackFlame->SetPosition(*mStageSelectBack->Get_Position());
				break;
			case SelectOPosition::SELECT_STAGE:
				Select_pos = SELECT_TITLE;
				mBackFlame->SetPosition(*mTitleBack->Get_Position());
				break;
			case SelectOPosition::SELECT_TITLE:
				Select_pos = SELECT_BACK;
				mBackFlame->SetPosition(*mGameBack->Get_Position());
				break;
			}
		}
		if (Input::instance().GetKeyboardTrigger(VK_RETURN) || Input::instance().GetButtonPress_Once(XINPUT_B))
		{
			Sound::instance().Play(SOUND_LABEL_OPTION_DECISION_SE);
			switch (Select_pos)
			{
			case SelectOPosition::SELECT_BACK:
				this->Next_scene = SCENE_GAMESCENE;
				this->Finish_flag = true;
				//this->Fade_flag = true;
				break;
			case SelectOPosition::SELECT_NOTE:
				this->Next_scene = SCENE_NOTE;
				this->Finish_flag = true;
				this->Fade_flag = true;
				break;
			case SelectOPosition::SELECT_STAGE:
				this->Next_scene = SCENE_STAGESELECT;
				this->Finish_flag = true;
				this->Fade_flag = true;
				break;
			case SelectOPosition::SELECT_TITLE:
				this->Next_scene = SCENE_TITLE;
				this->Finish_flag = true;
				this->Fade_flag = true;
				break;
			}
		}
		if (Input::instance().GetButtonPress_Once(XINPUT_A)) {
			//ゲームシーンに戻る
			Sound::instance().Play(SOUND_LABEL_OPTION_BACK_SE);
			this->Next_scene = SCENE_GAMESCENE;
			this->Finish_flag = true;
			//this->Fade_flag = true;
		}
	}
	int num = mOptionObject.size();
	for (auto a : mOptionObject) {
		a->Update();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

Option::~Option()
{
	delete mBackGround;         //背景
	delete mTitleBack;          //タイトルに戻る
	delete mStageSelectBack;    //ステージセレクトに戻る
	delete mGameBack;           //ゲームシーンに戻る
	delete mNote;               //ノートを開く
	delete mDate;               //データ消去
	delete mOptionLogo;         //オプションロゴ
	delete mPauseLogo;          //ポーズロゴ
	delete mBackFlame;          //選択肢可視化フレーム
}