#include "Note.h"
#include "Input.h"
#include "XAudio2.h"
Note::Note()
{
	//NOTE初期化
	mnBackground = new Image("assets/Note/Status/Note_main.png", { 0,0,0.002f }, { 6.75,3.75,1 });
	mnBackFlame = new Image("assets/Note/Note/TextFlame.png", { 0,0,0.002f }, { 2,0.4,1 });
	mStatus = new Image("assets/Note/Note/Status.png", { 0,0.3f,0.002f }, { 1.5f,0.5,1 });
	mCannon = new Image("assets/Note/Note/Bullet.png", { -0.05,-0.2f,0.002f }, { 1.5f,0.5,1 });
	mEnemy = new Image("assets/Note/Note/Enemy.png", { -0.07,-0.7f,0.002f }, { 1.5f,0.5,1 });
	mOther = new Image("assets/Note/Note/Other.png", { -0.05,-1.2f,0.002f }, { 1.5f,0.5,1 });

	mgNote.emplace_back(mnBackground);
	mgNote.emplace_back(mnBackFlame);
	mgNote.emplace_back(mStatus);
	mgNote.emplace_back(mCannon);
	mgNote.emplace_back(mEnemy);
	mgNote.emplace_back(mOther);

	int num = mgNote.size();
	for (auto a : mgNote) {
		a->Initialize();
		a->SetzBeffer(0.001f * num);
		num--;
	}

	//STATUS初期化
	msBackground = new Image("assets/Note/Status/Note_sub.png", { 0,0,0.002f }, { 6.75,3.75,1 });
	msBackFlame = new Image("assets/Note/Note/TextFlame.png", { 0,0,0.002f }, { 2,0.4,1 });
	mPower = new Image("assets/Note/Note/Status_1.png", { -1.75f,1.25f,0.002f }, { 2,0.5,1 });
	mBullet = new Image("assets/Note/Note/Status_2.png", { -1.75f,0.75f,0.002f }, { 2,0.5,1 });
	mTension = new Image("assets/Note/Note/Status_3.png", { -1.75f,0.25f,0.002f }, { 2,0.5,1 });
	mScore = new Image("assets/Note/Note/Status_4.png", { -1.75f,-0.25f,0.002f }, { 2,0.5,1 });
	mPower_Comment = new Image("assets/Note/Status/Status01.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mBullet_Comment = new Image("assets/Note/Status/Status02.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mTension_Comment = new Image("assets/Note/Status/Status03.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mScore_Comment = new Image("assets/Note/Status/Status04.png", { 1.25,0,0.002f }, { 3.8,3,1 });

	mgStatus.emplace_back(msBackground);
	mgStatus.emplace_back(msBackFlame);
	mgStatus.emplace_back(mPower);
	mgStatus.emplace_back(mBullet);
	mgStatus.emplace_back(mTension);
	mgStatus.emplace_back(mScore);

	mPower_Comment->Initialize();
	mPower_Comment->SetzBeffer(0.004f);
	mBullet_Comment->Initialize();
	mBullet_Comment->SetzBeffer(0.004f);
	mTension_Comment->Initialize();
	mTension_Comment->SetzBeffer(0.004f);
	mScore_Comment->Initialize();
	mScore_Comment->SetzBeffer(0.004f);

	int num2 = mgStatus.size();
	for (int a = 0; a < mgStatus.size(); a++)
	{
		mgStatus[a]->Initialize();
		mgStatus[a]->SetzBeffer(0.001f * num2);

		if (mgStatus.size() - 2 < num2)
			num2--;
	}

	//大砲初期化
	mcBackground = new Image("assets/Note/Status/Note_sub.png", { 0,0,0.002f }, { 6.75,3.75,1 });
	mcBackFlame = new Image("assets/Note/Note/TextFlame.png", { 0,0,0.002f }, { 2.2,0.4,1 });
	mNormal = new Image("assets/Note/Note/Bullet_1.png", { -1.5f,1.25f,0.002f }, { 2,0.5,1 });
	mCake = new Image("assets/Note/Note/Bullet_2.png", { -1.5f,0.75f,0.002f }, { 2,0.5,1 });
	mDoll = new Image("assets/Note/Note/Bullet_3.png", { -1.5f,0.25f,0.002f }, { 2,0.5,1 });
	mAngel = new Image("assets/Note/Note/Bullet_4.png", { -1.5f,-0.25f,0.002f }, { 2,0.5,1 });
	mNormal_Comment = new Image("assets/Note/Status/Bullet_1.png", { 1.25,0,0.001f }, { 3.8,3,1 });
	mCake_Comment = new Image("assets/Note/Status/Bullet_2.png", { 1.25,0,0.001f }, { 3.8,3,1 });
	mDoll_Comment = new Image("assets/Note/Status/Bullet_3.png", { 1.25,0,0.001f }, { 3.8,3,1 });
	mAngel_Comment = new Image("assets/Note/Status/Bullet_4.png", { 1.25,0,0.001f }, { 3.8,3,1 });

	mgCannon.emplace_back(mcBackground);
	mgCannon.emplace_back(mcBackFlame);
	mgCannon.emplace_back(mNormal);
	mgCannon.emplace_back(mCake);
	mgCannon.emplace_back(mDoll);
	mgCannon.emplace_back(mAngel);

	mNormal_Comment->Initialize();
	mNormal_Comment->SetzBeffer(0.001f);
	mCake_Comment->Initialize();
	mCake_Comment->SetzBeffer(0.001f);
	mDoll_Comment->Initialize();
	mDoll_Comment->SetzBeffer(0.001f);
	mAngel_Comment->Initialize();
	mAngel_Comment->SetzBeffer(0.001f);

	int num3 = mgCannon.size();
	for (int a = 0; a < mgCannon.size(); a++)
	{
		mgCannon[a]->Initialize();
		mgCannon[a]->SetzBeffer(0.001f * num3);

		if (mgCannon.size() - 2 < num3)
			num3--;
	}

	//敵初期化
	meBackground = new Image("assets/Note/Status/Note_sub.png", { 0,0,0.002f }, { 6.75,3.75,1 });
	meBackFlame = new Image("assets/Note/Note/TextFlame.png", { 0,0,0.002f }, { 1.5,0.4,1 });
	mSmallslime = new Image("assets/Note/Note/Enemy_1.png", { -1.75f,1.25f,0.002f }, { 2,0.5,1 });
	mRareslime = new Image("assets/Note/Note/Enemy_2.png", { -1.75f,0.75f,0.002f }, { 2,0.5,1 });
	mBigslime = new Image("assets/Note/Note/Enemy_3.png", { -1.75f,0.25f,0.002f }, { 2,0.5,1 });
	mBomb = new Image("assets/Note/Note/Enemy_4.png", { -1.75f,-0.25f,0.002f }, { 2,0.5,1 });
	mBoss = new Image("assets/Note/Note/Enemy_5.png", { -1.75f,-0.75f,0.002f }, { 2,0.5,1 });
	mSmallslime_Comment = new Image("assets/Note/Status/Enemy_1.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mRareslime_Comment = new Image("assets/Note/Status/Enemy_2.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mBigslime_Comment = new Image("assets/Note/Status/Enemy_3.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mBomb_Comment = new Image("assets/Note/Status/Enemy_4.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mBoss_Comment = new Image("assets/Note/Status/Enemy_5.png", { 1.25,0,0.002f }, { 3.8,3,1 });

	mgEnemy.emplace_back(meBackground);
	mgEnemy.emplace_back(meBackFlame);
	mgEnemy.emplace_back(mSmallslime);
	mgEnemy.emplace_back(mRareslime);
	mgEnemy.emplace_back(mBoss);
	mgEnemy.emplace_back(mBigslime);
	mgEnemy.emplace_back(mBomb);

	mSmallslime_Comment->Initialize();
	mSmallslime_Comment->SetzBeffer(0.004f);
	mRareslime_Comment->Initialize();
	mRareslime_Comment->SetzBeffer(0.004f);
	mBoss_Comment->Initialize();
	mBoss_Comment->SetzBeffer(0.004f);
	mBigslime_Comment->Initialize();
	mBigslime_Comment->SetzBeffer(0.004f);
	mBomb_Comment->Initialize();
	mBomb_Comment->SetzBeffer(0.004f);

	int num4 = mgEnemy.size();
	for (int a = 0; a < mgEnemy.size(); a++)
	{
		mgEnemy[a]->Initialize();
		mgEnemy[a]->SetzBeffer(0.001f * num4);

		if (mgEnemy.size() - 2 < num4)
			num4--;
	}

	//その他
	moBackground = new Image("assets/Note/Status/Note_sub.png", { 0,0,0.002f }, { 6.75,3.75,1 });
	moBackFlame = new Image("assets/Note/Note/TextFlame.png", { 0,0,0.002f }, { 2.2,0.4,1 });
	mFever = new Image("assets/Note/Note/Other_1.png", { -1.75f,1.25f,0.002f }, { 2,0.5,1 });
	mRank = new Image("assets/Note/Note/Other_2.png", { -1.75f,0.75f,0.002f }, { 2,0.5,1 });
	mBrother = new Image("assets/Note/Note/Other_3.png", { -1.75f,0.25f,0.002f }, { 2,0.5,1 });
	mSister = new Image("assets/Note/Note/Other_4.png", { -1.75f,-0.25f,0.002f }, { 2,0.5,1 });
	mTricks = new Image("assets/Note/Note/Other_5.png", { -1.75f,-0.75f,0.002f }, { 2,0.5,1 });
	mFever_Comment = new Image("assets/Note/Status/Other01.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mRank_Comment = new Image("assets/Note/Status/Other02.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mBrother_Comment = new Image("assets/Note/Status/Other03.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mSister_Comment = new Image("assets/Note/Status/Other04.png", { 1.25,0,0.002f }, { 3.8,3,1 });
	mTricks_Comment= new Image("assets/Note/Status/Other05.png", { 1.25,0,0.002f }, { 3.8,3,1 });

	mgOther.emplace_back(moBackground);
	mgOther.emplace_back(moBackFlame);
	mgOther.emplace_back(mFever);
	mgOther.emplace_back(mRank);
	mgOther.emplace_back(mBrother);
	mgOther.emplace_back(mSister);
	mgOther.emplace_back(mTricks);

	mFever_Comment->Initialize();
	mFever_Comment->SetzBeffer(0.004f);
	mRank_Comment->Initialize();
	mRank_Comment->SetzBeffer(0.004f);
	mBrother_Comment->Initialize();
	mBrother_Comment->SetzBeffer(0.004f);
	mSister_Comment->Initialize();
	mSister_Comment->SetzBeffer(0.004f);
	mTricks_Comment->Initialize();
	mTricks_Comment->SetzBeffer(0.004f);

	int num5 = mgOther.size();
	for (int a = 0; a < mgOther.size(); a++)
	{
		mgOther[a]->Initialize();
		mgOther[a]->SetzBeffer(0.001f * num5);

		if (mgOther.size() - 2 < num5)
			num5--;
	}

	//切り替え時の暗転を防ぐために
	for (auto pObj : mgStatus)
		pObj->Update();
	for (auto pObj : mgCannon)
		pObj->Update();
	for (auto pObj : mgEnemy)
		pObj->Update();
	for (auto pObj : mgOther)
		pObj->Update();
}

void Note::Initialize()
{
	//初期化フラグOFF
	this->Initialize_flag = false;
	//終了フラグOFF
	this->Finish_flag = false;

	//初期化
	mnBackFlame->SetPosition({ -0.25f,mStatus->Get_Position()->y,0 });
	Select_Note = SELECT_NOTE2;
	msBackFlame->SetSize({ 2,0.4,1 });
	mnBackFlame->SetzBeffer((mgNote.size() - 1) * 0.001f);

}

void Note::SceneUpdate()
{
	switch (Select_Note)
	{
	case SelectONPosition::SELECT_NOTE2:
		NoteUpdate();
		break;
	case SelectONPosition::SELECT_STATUS:
		StatusUpdate();
		break;
	case SelectONPosition::SELECT_CANNON:
		CannonUpdate();
		break;
	case SelectONPosition::SELECT_ENEMY:
		EnemyUpdate();
		break;
	case SelectONPosition::SELECT_OTHER:
		OtherUpdate();
		break;
	}
}

void Note::NoteUpdate()
{
	if (Input::instance().GetKeyboardTrigger('W') || Input::instance().GetButtonPress_Once(XINPUT_UP))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case SelectONPosition::SELECT_STATUS:
			Select_pos = NOTE_OTHER;
			mnBackFlame->SetPosition({ -0.25f,mOther->Get_Position()->y,0 });
			mnBackFlame->SetzBeffer((mgNote.size() - 1) * 0.001f);
			break;
		case SelectONPosition::SELECT_CANNON:
			Select_pos = NOTE_STATUS;
			mnBackFlame->SetPosition({ -0.25f,mStatus->Get_Position()->y,0 });
			mnBackFlame->SetzBeffer((mgNote.size() - 1) * 0.001f);
			break;
		case SelectONPosition::SELECT_ENEMY:
			Select_pos = NOTE_CANNON;
			mnBackFlame->SetPosition({ -0.25f,mCannon->Get_Position()->y,0 });
			mnBackFlame->SetzBeffer((mgNote.size() - 1) * 0.001f);
			break;
		case SelectONPosition::SELECT_OTHER:
			Select_pos = NOTE_ENEMY;
			mnBackFlame->SetPosition({ -0.25f,mEnemy->Get_Position()->y,0 });
			mnBackFlame->SetzBeffer((mgNote.size() - 1) * 0.001f);
			break;
		}
	}
	if (Input::instance().GetKeyboardTrigger('S') || Input::instance().GetButtonPress_Once(XINPUT_DOWN))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case SelectONPosition::SELECT_STATUS:
			Select_pos = NOTE_CANNON;
			mnBackFlame->SetPosition({ -0.25f,mCannon->Get_Position()->y,0 });
			mnBackFlame->SetzBeffer((mgNote.size() - 1) * 0.001f);
			break;
		case SelectONPosition::SELECT_CANNON:
			Select_pos = NOTE_ENEMY;
			mnBackFlame->SetPosition({ -0.25f,mEnemy->Get_Position()->y,0 });
			mnBackFlame->SetzBeffer((mgNote.size() - 1) * 0.001f);
			break;
		case SelectONPosition::SELECT_ENEMY:
			Select_pos = NOTE_OTHER;
			mnBackFlame->SetPosition({ -0.25f,mOther->Get_Position()->y,0 });
			mnBackFlame->SetzBeffer((mgNote.size() - 1) * 0.001f);
			break;
		case SelectONPosition::SELECT_OTHER:
			Select_pos = NOTE_STATUS;
			mnBackFlame->SetPosition({ -0.25f,mStatus->Get_Position()->y,0 });
			mnBackFlame->SetzBeffer((mgNote.size() - 1) * 0.001f);
			break;
		}
	}
	if (Input::instance().GetKeyboardTrigger(VK_RETURN) || Input::instance().GetButtonPress_Once(XINPUT_B))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_DECISION_SE);
		switch (Select_pos)
		{
		case SelectONPosition::SELECT_STATUS:
			StatusIni();
			Select_Note = SELECT_STATUS;
			break;
		case SelectONPosition::SELECT_CANNON:
			CannonIni();
			Select_Note = SELECT_CANNON;
			break;
		case SelectONPosition::SELECT_ENEMY:
			EnemyIni();
			Select_Note = SELECT_ENEMY;
			break;
		case SelectONPosition::SELECT_OTHER:
			OtherIni();
			Select_Note = SELECT_OTHER;
			break;
		}
	}
	//オプションに戻る
	if (Input::instance().GetKeyboardTrigger(VK_SPACE) || Input::instance().GetButtonPress_Once(XINPUT_A))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_BACK_SE);
		this->Finish_flag = true;
		this->Initialize_flag = true;
	}
	for (auto pObj : mgNote)
		pObj->Update();
}

void Note::StatusIni()
{
	//初期化
	Select_pos = STATUS_POWER;
	msBackFlame->SetPosition({ -2,mPower->Get_Position()->y, 0.002f });
	msBackFlame->SetSize({ 2,0.4,1 });
	msBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
}

void Note::StatusUpdate()
{
	if (Input::instance().GetKeyboardTrigger('W') || Input::instance().GetButtonPress_Once(XINPUT_UP))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case NoteComment::STATUS_POWER:
			Select_pos = STATUS_SCORE;
			msBackFlame->SetPosition({ -2,mScore->Get_Position()->y,0.002f });
			msBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
			break;
		case NoteComment::STATUS_BULLET:
			Select_pos = STATUS_POWER;
			msBackFlame->SetPosition({ -2,mPower->Get_Position()->y,0.002f });
			msBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
			break;
		case NoteComment::STATUS_TENSION:
			Select_pos = STATUS_BULLET;
			msBackFlame->SetPosition({ -2,mBullet->Get_Position()->y,0.002f });
			msBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
			break;
		case NoteComment::STATUS_SCORE:
			Select_pos = STATUS_TENSION;
			msBackFlame->SetPosition({ -2,mTension->Get_Position()->y,0.002f });
			msBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
			break;
		}
	}
	else if (Input::instance().GetKeyboardTrigger('S') || Input::instance().GetButtonPress_Once(XINPUT_DOWN))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case NoteComment::STATUS_POWER:
			Select_pos = STATUS_BULLET;
			msBackFlame->SetPosition({ -2,mBullet->Get_Position()->y,0.002f });
			msBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
			break;
		case NoteComment::STATUS_BULLET:
			Select_pos = STATUS_TENSION;
			msBackFlame->SetPosition({ -2,mTension->Get_Position()->y,0.002f });
			msBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
			break;
		case NoteComment::STATUS_TENSION:
			Select_pos = STATUS_SCORE;
			msBackFlame->SetPosition({ -2,mScore->Get_Position()->y,0.002f });
			msBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
			break;
		case NoteComment::STATUS_SCORE:
			Select_pos = STATUS_POWER;
			msBackFlame->SetPosition({ -2,mPower->Get_Position()->y,0.002f });
			msBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
			break;
		}
	}
	if (Input::instance().GetKeyboardTrigger(VK_SPACE) || Input::instance().GetButtonPress_Once(XINPUT_A))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_BACK_SE);
		Initialize();
		Select_pos = NOTE_STATUS;
	}
	mPower_Comment->Update();
	mBullet_Comment->Update();
	mTension_Comment->Update();
	mScore_Comment->Update();
	for (auto pObj : mgStatus)
		pObj->Update();
}

void Note::CannonIni()
{
	//初期化
	Select_pos = CANNON_NORMAL;
	mcBackFlame->SetPosition({ -1.9,mNormal->Get_Position()->y,0.002f });
	msBackFlame->SetSize({ 1.5,0.4,1 });
	mcBackFlame->SetzBeffer((mgStatus.size() - 1) * 0.001f);
}

void Note::CannonUpdate()
{
	if (Input::instance().GetKeyboardTrigger('W') || Input::instance().GetButtonPress_Once(XINPUT_UP))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case NoteComment::CANNON_NORMAL:
			Select_pos = CANNON_ANGEL;
			mcBackFlame->SetPosition({-1.9,mAngel->Get_Position()->y,0.002f });
			mcBackFlame->SetzBeffer((mgCannon.size() - 1) * 0.001f);
			break;
		case NoteComment::CANNON_CAKE:
			Select_pos = CANNON_NORMAL;
			mcBackFlame->SetPosition({ -1.9,mNormal->Get_Position()->y,0.002f });
			mcBackFlame->SetzBeffer((mgCannon.size() - 1) * 0.001f);
			break;
		case NoteComment::CANNON_DOLL:
			Select_pos = CANNON_CAKE;
			mcBackFlame->SetPosition({ -1.9,mCake->Get_Position()->y,0.002f });
			mcBackFlame->SetzBeffer((mgCannon.size() - 1) * 0.001f);
			break;
		case NoteComment::CANNON_ANGEL:
			Select_pos = CANNON_DOLL;
			mcBackFlame->SetPosition({ -1.9,mDoll->Get_Position()->y,0.002f });
			mcBackFlame->SetzBeffer((mgCannon.size() - 1) * 0.001f);
			break;
		}
	}
	else if (Input::instance().GetKeyboardTrigger('S') || Input::instance().GetButtonPress_Once(XINPUT_DOWN))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case NoteComment::CANNON_NORMAL:
			Select_pos = CANNON_CAKE;
			mcBackFlame->SetPosition({ -1.9,mCake->Get_Position()->y,0.002f });
			mcBackFlame->SetzBeffer((mgCannon.size() - 1) * 0.001f);
			break;
		case NoteComment::CANNON_CAKE:
			Select_pos = CANNON_DOLL;
			mcBackFlame->SetPosition({ -1.9,mDoll->Get_Position()->y,0.002f });
			mcBackFlame->SetzBeffer((mgCannon.size() - 1) * 0.001f);
			break;
		case NoteComment::CANNON_DOLL:
			Select_pos = CANNON_ANGEL;
			mcBackFlame->SetPosition({ -1.9,mAngel->Get_Position()->y,0.002f });
			mcBackFlame->SetzBeffer((mgCannon.size() - 1) * 0.001f);
			break;
		case NoteComment::CANNON_ANGEL:
			Select_pos = CANNON_NORMAL;
			mcBackFlame->SetPosition({ -1.9,mNormal->Get_Position()->y,0.002f });
			mcBackFlame->SetzBeffer((mgCannon.size() - 1) * 0.001f);
			break;
		}
	}
	if (Input::instance().GetKeyboardTrigger(VK_SPACE) || Input::instance().GetButtonPress_Once(XINPUT_A))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_BACK_SE);
		Initialize();
		Select_pos = NOTE_STATUS;
	}

	mNormal_Comment->Update();
	mCake_Comment->Update();
	mDoll_Comment->Update();
	mAngel_Comment->Update();
	for (auto pObj : mgCannon)
		pObj->Update();
}

void Note::EnemyIni()
{
	//初期化
	Select_pos = ENEMY_SMALLSLIME;
	msBackFlame->SetSize({ 1.5,0.4,1 });
	meBackFlame->SetPosition({ -2.25,mSmallslime->Get_Position()->y,0.002f });
	meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
}

void Note::EnemyUpdate()
{
	if (Input::instance().GetKeyboardTrigger('W') || Input::instance().GetButtonPress_Once(XINPUT_UP))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case NoteComment::ENEMY_SMALLSLIME:
			Select_pos = ENEMY_BOSS;
			meBackFlame->SetPosition({ -2.25,mBoss->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		case NoteComment::ENEMY_RARESLIME:
			Select_pos = ENEMY_SMALLSLIME;
			meBackFlame->SetPosition({ -2.25,mSmallslime->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		case NoteComment::ENEMY_BOSS:
			Select_pos = ENEMY_BOMB;
			meBackFlame->SetPosition({ -2.25,mBomb->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		case NoteComment::ENEMY_BIGSLIME:
			Select_pos = ENEMY_RARESLIME;
			meBackFlame->SetPosition({ -2.25,mRareslime->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		case NoteComment::ENEMY_BOMB:
			Select_pos = ENEMY_BIGSLIME;
			meBackFlame->SetPosition({ -2.25,mBigslime->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		}
	}
	else if (Input::instance().GetKeyboardTrigger('S') || Input::instance().GetButtonPress_Once(XINPUT_DOWN))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case NoteComment::ENEMY_SMALLSLIME:
			Select_pos = ENEMY_RARESLIME;
			meBackFlame->SetPosition({ -2.25,mRareslime->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		case NoteComment::ENEMY_RARESLIME:
			Select_pos = ENEMY_BIGSLIME;
			meBackFlame->SetPosition({ -2.25,mBigslime->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		case NoteComment::ENEMY_BOSS:
			Select_pos = ENEMY_SMALLSLIME;
			meBackFlame->SetPosition({ -2.25,mSmallslime->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		case NoteComment::ENEMY_BIGSLIME:
			Select_pos = ENEMY_BOMB;
			meBackFlame->SetPosition({ -2.25,mBomb->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		case NoteComment::ENEMY_BOMB:
			Select_pos = ENEMY_BOSS;
			meBackFlame->SetPosition({ -2.25,mBoss->Get_Position()->y,0.002f });
			meBackFlame->SetzBeffer((mgEnemy.size() - 1) * 0.001f);
			break;
		}
	}
	if (Input::instance().GetKeyboardTrigger(VK_SPACE) || Input::instance().GetButtonPress_Once(XINPUT_A))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_BACK_SE);
		Initialize();
		Select_pos = NOTE_STATUS;
	}

	mSmallslime_Comment->Update();
	mRareslime_Comment->Update();
	mBoss_Comment->Update();
	mBigslime_Comment->Update();
	mBomb_Comment->Update();

	for (auto pObj : mgEnemy)
		pObj->Update();
}

void Note::OtherIni()
{
	//初期化
	Select_pos = OTHER_FEVER;
	msBackFlame->SetSize({ 1.5,0.4,1 });
	moBackFlame->SetPosition({ -1.95,mSmallslime->Get_Position()->y,0.002f });
	moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
}

void Note::OtherUpdate()
{
	if (Input::instance().GetKeyboardTrigger('W') || Input::instance().GetButtonPress_Once(XINPUT_UP))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case NoteComment::OTHER_FEVER:
			Select_pos = OTHER_TRICK;
			moBackFlame->SetPosition({ -1.95, mTricks->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		case NoteComment::OTHER_RANK:
			Select_pos = OTHER_FEVER;
			moBackFlame->SetPosition({ -1.95, mFever->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		case NoteComment::OTHER_BROTHER:
			Select_pos = OTHER_RANK;
			moBackFlame->SetPosition({ -1.95, mRank->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		case NoteComment::OTHER_SISTER:
			Select_pos = OTHER_BROTHER;
			moBackFlame->SetPosition({ -1.95, mBrother->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		case NoteComment::OTHER_TRICK:
			Select_pos = OTHER_SISTER;
			moBackFlame->SetPosition({ -1.95, mSister->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		}
	}
	else if (Input::instance().GetKeyboardTrigger('S') || Input::instance().GetButtonPress_Once(XINPUT_DOWN))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_CURSOR_SE);
		switch (Select_pos)
		{
		case NoteComment::OTHER_FEVER:
			Select_pos = OTHER_RANK;
			moBackFlame->SetPosition({ -1.95, mRank->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		case NoteComment::OTHER_RANK:
			Select_pos = OTHER_BROTHER;
			moBackFlame->SetPosition({ -1.95, mBrother->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		case NoteComment::OTHER_BROTHER:
			Select_pos = OTHER_SISTER;
			moBackFlame->SetPosition({ -1.95, mSister->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		case NoteComment::OTHER_SISTER:
			Select_pos = OTHER_TRICK;
			moBackFlame->SetPosition({ -1.95, mTricks->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		case NoteComment::OTHER_TRICK:
			Select_pos = OTHER_FEVER;
			moBackFlame->SetPosition({ -1.95, mFever->Get_Position()->y, 0.002f });
			moBackFlame->SetzBeffer((mgOther.size() - 1) * 0.001f);
			break;
		}
	}
	if (Input::instance().GetKeyboardTrigger(VK_SPACE) || Input::instance().GetButtonPress_Once(XINPUT_A))
	{
		Sound::instance().Play(SOUND_LABEL_OPTION_BACK_SE);
		Initialize();
		Select_pos = NOTE_STATUS;
	}

	mFever_Comment->Update();
	mRank_Comment->Update();
	mBrother_Comment->Update();
	mSister_Comment->Update();
	mTricks_Comment->Update();

	for (auto pObj : mgOther)
		pObj->Update();
}

void Note::Draw()
{
	switch (Select_Note)
	{
	case SelectONPosition::SELECT_NOTE2:
		for (auto pObj : mgNote)
			pObj->Draw();
		break;
	case SelectONPosition::SELECT_STATUS:
		for (auto pObj : mgStatus)
			pObj->Draw();
		switch (Select_pos)
		{
		case NoteComment::STATUS_POWER:
			mPower_Comment->Draw();
			break;
		case NoteComment::STATUS_BULLET:
			mBullet_Comment->Draw();
			break;
		case NoteComment::STATUS_TENSION:
			mTension_Comment->Draw();
			break;
		case NoteComment::STATUS_SCORE:
			mScore_Comment->Draw();
			break;
		}
		break;
	case SelectONPosition::SELECT_CANNON:
		for (auto pObj : mgCannon)
			pObj->Draw();
		switch (Select_pos)
		{
		case NoteComment::CANNON_NORMAL:
			mNormal_Comment->Draw();
			break;
		case NoteComment::CANNON_CAKE:
			mCake_Comment->Draw();
			break;
		case NoteComment::CANNON_DOLL:
			mDoll_Comment->Draw();
			break;
		case NoteComment::CANNON_ANGEL:
			mAngel_Comment->Draw();
			break;
		}
		break;
	case SelectONPosition::SELECT_ENEMY:
		for (auto pObj : mgEnemy)
			pObj->Draw();
		switch (Select_pos)
		{
		case NoteComment::ENEMY_SMALLSLIME:
			mSmallslime_Comment->Draw();
			break;
		case NoteComment::ENEMY_RARESLIME:
			mRareslime_Comment->Draw();
			break;
		case NoteComment::ENEMY_BOSS:
			mBoss_Comment->Draw();
			break;
		case NoteComment::ENEMY_BIGSLIME:
			mBigslime_Comment->Draw();
			break;
		case NoteComment::ENEMY_BOMB:
			mBomb_Comment->Draw();
		}
		break;
	case SelectONPosition::SELECT_OTHER:
		for (auto pObj : mgOther)
			pObj->Draw();
		switch (Select_pos)
		{
		case NoteComment::OTHER_FEVER:
			mFever_Comment->Draw();
			break;
		case NoteComment::OTHER_RANK:
			mRank_Comment->Draw();
			break;
		case NoteComment::OTHER_BROTHER:
			mBrother_Comment->Draw();
			break;
		case NoteComment::OTHER_SISTER:
			mSister_Comment->Draw();
			break;
		case NoteComment::OTHER_TRICK:
			mTricks_Comment->Draw();
			break;
		}
		break;
	}
}

Note::~Note() {        //ノート
	delete mnBackground;  //背景
	delete mnBackFlame;//選択肢可視化フレーム
	delete mStatus;  //ステータス
	delete mCannon;  //大砲
	delete mEnemy;  //敵
	delete mOther;  //その他

	//ステータス
	delete msBackground;  //背景
	delete msBackFlame;  //選択肢可視化フレーム
	delete mPower;  //体力
	delete mBullet;  //弾
	delete mTension;  //テンション
	delete mScore;  //スコア
	  //説明
	delete mPower_Comment;  //体力
	delete mBullet_Comment;  //弾
	delete mTension_Comment;  //テンション
	delete mScore_Comment;  //スコア


	//大砲
	delete mcBackground;  //背景
	delete mcBackFlame;  //選択肢可視化フレーム
	delete mNormal;  //通常弾
	delete mCake;  //ケーキ弾
	delete mDoll;  //人形弾
	delete mAngel;  //天使弾
	  //説明
	delete mNormal_Comment;  //通常弾
	delete mCake_Comment;  //ケーキ弾
	delete mDoll_Comment;  //人形弾
	delete mAngel_Comment;  //天使弾

	//敵
	delete meBackground;  //背景
	delete meBackFlame;  //選択肢可視化フレーム
	delete mSmallslime;  //小さいスライム
	delete mRareslime;  //レアスライム
	delete mBoss;  //ボス
	delete mBigslime;  //大きいスライム
	delete mBomb;  //爆弾兵
	  //説明
	delete mSmallslime_Comment;  //小さいスライム
	delete mRareslime_Comment;  //レアスライム
	delete mBoss_Comment;  //ボス
	delete mBigslime_Comment;  //大きいスライム
	delete mBomb_Comment;  //爆弾兵

	//その他
	delete moBackground;  //背景
	delete moBackFlame;  //選択肢可視化フレーム
	delete mFever;  //フィーバー
	delete mRank;  //ランク
	delete mBrother;  //兄
	delete mSister;  //妹
	delete mTricks;
	//説明
	delete mFever_Comment;  //フィーバー
	delete mRank_Comment;  //ランク
	delete mBrother_Comment;  //兄
	delete mSister_Comment;  //妹
	delete mTricks_Comment;
}

