#include "Fade.h"

Fade::Fade()
{
	Tex_Data[FADE_FADINGorDARKENING] = "assets/Black.png";
	Tex_Data[FADE_SCALE] = "assets/Fade.png";
	mModelData.mSRV = Tex_Data[FADE_FADINGorDARKENING];
	mPosition = { 0,0,-1 };
	mSize = { 7,10 };
	mColor = { 1,1,1,0 };//‰Šú“§–¾
	mRote = { 0,0,0 };
	mTex = { 0,0,1,1 };
	now_fade = FADE_NULL;
	Fade_Speed = 120;
}

void Fade::Update()
{
	switch (now_fade)
	{
	case FADE_IN://–¾‚é‚­‚È‚é‚æ
		Fade_In();
		break;
	case FADE_OUT://ˆÃ‚­‚È‚é‚æ
		if (this->Initialize_flag)
			Fade_Intialize();
		Fade_Out();
		break;
	case FADE_SCALE_UP://‘å‚«‚­‚È‚é‚æ
		if (this->Initialize_flag)
			Scale_Initialize();
		Scale_Up();
		break;
	case FADE_SCALE_DOWN://¬‚³‚­‚È‚é‚æ
		Scale_Down();
		break;
	default:
		break;
	}
	GameObject::Update();
}


void Fade::Release()
{
	delete this;
}

void Fade::Fade_Process()
{
	//‰Šú‰»
	if (this->Initialize_flag&&!this->Finish_flag)
		Fade_Intialize();
	//Še€–Ú‚²‚Æ‚Ìˆ—
	switch (now_fade)
	{
	case FADE_NULL:	//ˆ—I—¹
		
		break;
	case FADE_IN:	//–¾“]
		Fade_In();
		break;
	case FADE_OUT:	//ˆÃ“]
		Fade_Out();
		break;
	default:
		break;
	}
	GameObject::Update();
}

void Fade::Scale_Process()
{
	//‰Šú‰»
	if (this->Initialize_flag&&!this->Finish_flag)
		Scale_Initialize();
	//Še€–Ú‚²‚Æ‚Ìˆ—
	switch (now_fade)
	{
	case FADE_NULL:	//ˆ—I—¹

		break;
	case FADE_SCALE_UP:	//Šg‘å
		Scale_Up();
		break;
	case FADE_SCALE_DOWN:	//k¬
		Scale_Down();
		break;
	default:
		break;
	}
	GameObject::Update();
}

void Fade::Fade_Intialize()
{
	mModelData.mSRV = Tex_Data[FADE_FADINGorDARKENING];
	mPosition = { 0,0,-1 };
	mSize = { 7,10 };
	mColor = { 1,1,1,0 };//‰Šú“§–¾
	mRote = { 0,0,0 };
	mTex = { 0,0,1,1 };
	Fade_Speed = 120;
	this->Initialize_flag = false;
	this->Switching_flag = false;
	this->Finish_flag = false;
	now_fade = FADE_OUT;
}

void Fade::Scale_Initialize()
{
	mModelData.mSRV = Tex_Data[FADE_SCALE];
	mPosition = { 0,0,-1 };
	mSize = { 0,0 };//‰Šú‚O
	mColor = { 1,1,1,1 };
	mRote = { 0,0,0 };
	mTex = { 0,0,1,1 };
	Fade_Speed = 60;
	this->Initialize_flag = false;
	this->Switching_flag = false;
	this->Finish_flag = false;
	now_fade = FADE_SCALE_UP;
}

void Fade::Fade_In()
{
	if (mColor.a > 0)
		mColor.a = mColor.a - (1 / Fade_Speed);
	if (mColor.a <= 0) {
		mColor.a = 0;
		this->Initialize_flag = true;
		this->Switching_flag = false;
		this->Finish_flag = true;
		now_fade = FADE_NULL;
	}
}

void Fade::Fade_Out()
{
	if (mColor.a < 1)
		mColor.a = mColor.a + (1 / Fade_Speed);
	if (mColor.a >= 1) {
		mColor.a = 1;
		now_fade = FADE_IN;
		Switching_flag = true;
	}
}

void Fade::Scale_Up()
{
	if (mSize.x < 32)
		mSize.x = mSize.x + (16 / Fade_Speed);
	if (mSize.y < 18)
		mSize.y = mSize.y + (9 / Fade_Speed);
	if (mSize.x > 32)
		mSize.x = 32;
	if (mSize.y > 18)
		mSize.y = 18;
	if (mSize.x == 32 && mSize.y == 18) {
		now_fade = FADE_SCALE_DOWN;
		Switching_flag = true;
	}
}

void Fade::Scale_Down()
{
	if (mSize.x > 0)
		mSize.x = mSize.x - (16 / Fade_Speed);
	if (mSize.y > 0)
		mSize.y = mSize.y - (9 / Fade_Speed);
	if (mSize.x < 0)
		mSize.x = 0;
	if (mSize.y < 0)
		mSize.y = 0;
	if (mSize.x == 0 && mSize.y == 0) {
		mColor.a = 0;
		this->Initialize_flag = true;
		this->Switching_flag = false;
		this->Finish_flag = true;
		now_fade = FADE_NULL;
	}
}
