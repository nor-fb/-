#pragma once
#include "GameObject.h"
enum FADE_TYPE {
	FADE_FADINGorDARKENING,//暗転明転タイプ
	FADE_SCALE,			   //拡大縮小タイプ
	FADE_IN,
	FADE_OUT,
	FADE_SCALE_UP,
	FADE_SCALE_DOWN,
	FADE_NULL,
};
class Fade :public GameObject
{
public:
	Fade();
	void Update();
	void Release();
	float Get_Color_a() { return this->mColor.a; }
	FADE_TYPE Get_NowFade() { return this->now_fade; }
	void Set_NowFade(FADE_TYPE type) { this->now_fade = type; }
	bool Get_Switching_flag() { return Switching_flag; }
	void Set_Switiching(bool n) { this->Switching_flag = n; }
	bool Get_Finish_flag() { return this->Finish_flag; }
	void Set_Finish_flag(bool n) { this->Finish_flag = n; }
	//こいつらがメインで動いてもらう
	void Fade_Process();
	void Scale_Process();
private:
	void Fade_Intialize();	//暗転明転初期化
	void Scale_Initialize();//拡大縮小初期化
	void Fade_In();			//明転処理
	void Fade_Out();		//暗転処理
	void Scale_Up();		//スケール拡大処理
	void Scale_Down();		//スケール縮小処理
	float Fade_Speed;		//スピード変数
	FADE_TYPE now_fade;
	std::string Tex_Data[2];
	bool Initialize_flag = true;//初期化フラグ(Fadeの画像データ更新)
	bool Switching_flag;		//更新フラグ(シーンの画像データ更新)
	bool Finish_flag;			//終了フラグ
};