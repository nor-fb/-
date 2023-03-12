#include "Rogo.h"
#include"Input.h"
#include"GameTimer.h"
Rogo::Rogo()
{
	mBackGround = new Image("assets/White.png", { 0,0,0 }, { 8,5,0 });
	mTeamRogo = new Image(("assets/Rogo_Normal.png"), { 0,0,0 }, { 8,5,0 }, { 1,1,1 }, 0);
	mRogoScene.emplace_back(mBackGround);
	mRogoScene.emplace_back(mTeamRogo);
	int num = mRogoScene.size();
	for (auto a : mRogoScene) {
		a->Initialize();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Rogo::Initialize()
{
	if (CheckFile("assets/oni.dat")) {}
	else {
		FILE *fp;
		fopen_s(&fp, "assets/oni.dat", "w");
		for (int i = 0; i < 10; i++)
			fprintf(fp, "%d\n", max_rank[i]);
		fclose(fp);
	}
	Count = 0;
	this->Initialize_flag = false;
	this->Finish_flag = false;
}

void Rogo::Update()
{
	//やること
	//ロゴの表示
	//一定時間経過orボタン入力で終了してフェード処理
	if (Count > 360&&mTeamRogo->Get_Color().a==1) {
		this->Finish_flag = true;
		this->Fade_flag = true;
	}
	if (Input::instance().GetKeyboardTrigger(VK_RETURN) || Input::instance().GetButtonPress_Once(XINPUT_B)) {
		this->Finish_flag = true;
		this->Fade_flag = true;
	}
	if (mTeamRogo->Get_Color().a < 1)
		mTeamRogo->Set_Color({ 1,1,1,mTeamRogo->Get_Color().a + 0.005f });
	else if (mTeamRogo->Get_Color().a > 1)
		mTeamRogo->Set_Color({ 1,1,1,1 });
	Count++;
	int num = mRogoScene.size();
	for (auto a : mRogoScene) {
		a->Update();
		a->SetzBeffer(0.001f * num);
		num--;
	}
}

void Rogo::Draw()
{
	for (GameObject* obj : mRogoScene)
		obj->Draw();
}

void Rogo::Release()
{
	for (GameObject* obj : mRogoScene)
		obj->Release();
	mRogoScene.clear();
	mRogoScene.shrink_to_fit();
}