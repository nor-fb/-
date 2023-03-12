#include "Drop.h"
#include"Scene.h"
#include"GameTimer.h"
void Drop::Update()
{
	//指定フレーム間に目標地点(弾数、スコア)まで移動
	//目標まで減算
	if (Target_Distance.x != 0) {
		mPosition.x += MoveSpeed.x;
		Target_Distance.x -= fabsf(MoveSpeed.x);
	}
	if (Target_Distance.y != 0) {
		mPosition.y += MoveSpeed.y;
		Target_Distance.y -= fabsf(MoveSpeed.y);

	}
	//目標通過
	Target_Distance.x = Target_Distance.x < 0 ? 0 : Target_Distance.x;
	Target_Distance.y = Target_Distance.y < 0 ? 0 : Target_Distance.y;
	//if (Target_Distance.x < 0)
	//	Target_Distance.x = 0;
	//if (Target_Distance.y < 0)
	//	Target_Distance.y = 0;

	//サイズ
	mSize.x -= ChangeSize.x;
	mSize.y -= ChangeSize.y;

	mSize.x = mSize.x < 0 ?0: mSize.x;
	mSize.y = mSize.y < 0 ?0: mSize.y;

	//if (mSize.x > 0)
	//	mSize.x -= ChangeSize.x;
	//else
	//	mSize.x = 0;

	//if (mSize.y > 0)
	//	mSize.y -= ChangeSize.y;
	//else
	//	mSize.y = 0;

}

void Drop::Distance_Calculation(Float3 coordinate,Float3 pos)
{
	//敵死亡地点とスコア、弾数表示までの距離計算
	//スコアまでの距離(x,y)=スコア地点-敵死亡地点 (-なら+にする)
	//弾数までの距離(x,y)=弾数地点-敵死亡地点 (-なら+にする)
	Target_Distance.x = coordinate.x - pos.x;
	Target_Distance.y = coordinate.y - pos.y;
	if (Target_Distance.x < 0) {
		Target_Distance.x *= -1;
		Target_FlgX = true;
	}
	if (Target_Distance.y < 0) {
		Target_Distance.y *= -1;
		Target_FlgY = true;
	}
	//指定フレームに合わせて1フレームの移動距離を計算(後々計算時の警告を消せるようにする)
	MoveSpeed.x = Target_Distance.x / Specified_Frame;
	MoveSpeed.y = Target_Distance.y / Specified_Frame;

	if (Target_FlgX)
		MoveSpeed.x *= -1;
	if (Target_FlgY)
		MoveSpeed.y *= -1;
	//サイズ
	ChangeSize.x = mSize.x / Specified_Frame;
	ChangeSize.y = mSize.y / Specified_Frame;
}

DropBullet::DropBullet()
{
	mSize = { SCREEN_WIDTH_PIECE * 4.0f,SCREEN_HEIGHT_PIECE * 2.0f };
	mColor = { 1,1,1,1 };
	mRote = { 0,0,0 };
	mPosition = { 100,100,0};
	mTex = { 0,0,4,1 };

}

void DropBullet::Update()
{
	if (Active) {
		Drop::Update();

		if (Target_Distance.x == 0 && Target_Distance.y == 0) {
			Active = false;
			if (HealType) {
				Hpheal = true;
			}else
			CountBullet = true;
		}
	}
	GameObject::Update();
}

void DropBullet::Set_TYPE(eCANNON_TYPE type)
{
	Type = type;
	mModelData.mSRV = model[Type];
}

void DropBullet::Set_Active(Float3 pos)
{
	Active = true; 
	Target_FlgX = false;
	Target_FlgY = false;
	mPosition = pos;
	mTex.x = 0;
	mSize = { SCREEN_WIDTH_PIECE * 4.0f,SCREEN_HEIGHT_PIECE * 2.0f };
	Distance_Calculation({ SCREEN_WIDTH_PIECE * 20.5f,SCREEN_HEIGHT_PIECE * -10.9f,0.0f }, mPosition);
}

void DropBullet::Set_Active(Float3 pos, bool hp)
{
	Active = true;
	Target_FlgX = false;
	Target_FlgY = false;
	Hpheal = false;
	HealType = true;
	mPosition = pos;
	mPosition.z += 0.0001f;
	mModelData.mSRV = model[4];
	mSize = { SCREEN_WIDTH_PIECE * 2.0f,SCREEN_HEIGHT_PIECE * 2.0f };
	Distance_Calculation({ SCREEN_WIDTH_PIECE * -20.5f,SCREEN_HEIGHT_PIECE * 10.9f,0.0f }, mPosition);
}

MagicStone::MagicStone()
{
	mSize = { SCREEN_WIDTH_PIECE * 2.5f,SCREEN_HEIGHT_PIECE * 2.5f };
	mColor = { 1,1,1,1 };
	mRote = { 0,0,0 };
	mPosition = { 100, 100, 0 };
	mTex = { 0,0,1,1 };
}

void MagicStone::Initialize()
{
	TimeCount = 0;
	CountScore = false;
	Active = false;
	flg = false;
	GameObject::Initialize();
}

void MagicStone::Set_Active()
{
	Active = true;
	Target_FlgX = false;
	Target_FlgY = false;
	TimeCount = 0;
	flg = true;
	mSize = { SCREEN_WIDTH_PIECE * 2.5f,SCREEN_HEIGHT_PIECE * 2.5f };
	Distance_Calculation({ SCREEN_WIDTH_PIECE * 20.0f,SCREEN_HEIGHT_PIECE * 12.0f,0.0f }, mPosition);

}

void MagicStone::Set_Active(Float3 pos)
{
	Active = true;
	Target_FlgX = false;
	Target_FlgY = false;
	mPosition = pos;
	flg = true;
	TimeCount = 0;
	mSize = { SCREEN_WIDTH_PIECE * 2.5f,SCREEN_HEIGHT_PIECE * 2.5f };
	Distance_Calculation({ SCREEN_WIDTH_PIECE * 20.0f,SCREEN_HEIGHT_PIECE * 12.0f,0.0f }, pos);
}

void MagicStone::Set_Active(Float3 pos, Float3 dis)
{
	Active = true;
	Target_FlgX = false;
	Target_FlgY = false;
	mPosition = pos;
	flg = false;
	TimeCount = 0;
	mSize = { SCREEN_WIDTH_PIECE * 3.0f,SCREEN_HEIGHT_PIECE * 3.0f };
	Distance_Calculation(dis, pos);
}

void MagicStone::Update()
{
	if (Active) {
		if (flg) {
			if (TimeCount > .2f)
				Drop::Update();

			TimeCount += GameTimer::instance().GetDeltaTime();

			if (Target_Distance.x == 0 && Target_Distance.y == 0) {
				CountScore = true;
				Active = false;
			}
		}
		else {
			if (Target_Distance.x != 0) {
				mPosition.x += MoveSpeed.x;
				Target_Distance.x -= fabsf(MoveSpeed.x);
			}
			if (Target_Distance.y != 0) {
				mPosition.y += MoveSpeed.y;
				Target_Distance.y -= fabsf(MoveSpeed.y);
			}

			//目標通過
			Target_Distance.x = Target_Distance.x < 0 ? 0 : Target_Distance.x;
			Target_Distance.y = Target_Distance.y < 0 ? 0 : Target_Distance.y;

			if (Target_Distance.x == 0 && Target_Distance.y == 0) {
				MoveSpeed = { 0,0,0, };
			}
		}
	}
	GameObject::Update();
}

Bomb::Bomb()
{
	TexDate.emplace_back("assets/Bomb.png");
	TexDate.emplace_back("assets/イラスト111.png");
	mModelData.mSRV = TexDate[0];
	anim[0].Initialize(eCategory::eBomb);
	anim[1].Initialize(eCategory::eBomb_Exploding);
	mTex = { 0,0,12,1 };
	BreakNumber = 0;
	Active = false;
	mPosition = { 100,100,-0.0001 };
}


void Bomb::Initialize()
{
	effect = false;
	Active = false;
	BreakNumber = 0;
	animnum = 0;
	GameObject::Initialize();
}


void Bomb::Update()
{
	if (Active) {
		anim[animnum].Update();
		mTex.x=anim[animnum].Get_AnimTable();
		if (Target_Distance.x==0&&Target_Distance.y==0) {
			if (animnum == 0) {
				Sound::instance().Play(SOUND::SOUND_LABEL_CANNONBREAK_SE);
				animnum = 1;
				mModelData.mSRV = TexDate[1];
				mSize = { SCREEN_WIDTH_PIECE * 9.0f,SCREEN_HEIGHT_PIECE * 9.0f };
				game->GetCannon()->Set_BreakCannon(BreakNumber);
				mRote = { 0,0,90 };
			}
			if (animnum == 1 && mTex.x == 11) {
				Active = false;
				mPosition.x = 100;
				mPosition.y = 100;
			}
		}else
		Drop::Update();


	}
	GameObject::Update();
}

void Bomb::Set_Active(Float3 pos)
{
	effect = false;
	Active = true;
	mModelData.mSRV = TexDate[0];
	Target_FlgX = false;
	Target_FlgY = false;
	mPosition = { pos.x,pos.y,-0.0001f };
	anim[0].Reset();
	anim[1].Reset();
	animnum = 0;
	//場所でどこの大砲を破壊するか決める
	for (int i = 0; i < 6; i++) {
		if (mPosition.x < SCREEN_WIDTH_PIECE * -12.0f + (SCREEN_WIDTH_PIECE * 6.0f * i)) {
			BreakNumber = i;
			break;
		}
	}

	Float3 InitPos;
	const float y = SCREEN_HEIGHT_PIECE * -10.0f;
	switch (BreakNumber)
	{
	case 0://一番左
		InitPos = { SCREEN_WIDTH_PIECE * -12.8f,y };
		break;
	case 1:
		InitPos = { SCREEN_WIDTH_PIECE * -8.0f,y };
		break;
	case 2:
		InitPos = { SCREEN_WIDTH_PIECE * -2.8f,y };
		break;
	case 3:
		InitPos = { SCREEN_WIDTH_PIECE * 2.0,y };
		break;
	case 4:
		InitPos = { SCREEN_WIDTH_PIECE * 7.5f,y };
		break;
	case 5:
		InitPos = { SCREEN_WIDTH_PIECE * 12.6f,y };
		break;
	}

	Distance_Calculation(InitPos, mPosition);
	ChangeSize = {};
	mSize = { SCREEN_WIDTH_PIECE * 3.0f,SCREEN_HEIGHT_PIECE * 3.0f };
	mRote = { 0,0,0 };
}

void Bomb::Draw()
{
	if (Active) {
		GameObject::Draw();
	}
}

void Bomb::Set_Explosion(int num)
{
	const float y = SCREEN_HEIGHT_PIECE * -10.0f;
	switch (num)
	{
	case 0://一番左
		mPosition = { SCREEN_WIDTH_PIECE * -12.8f,y};
		break;
	case 1:
		mPosition = { SCREEN_WIDTH_PIECE * -8.0f,y };
		break;
	case 2:
		mPosition = { SCREEN_WIDTH_PIECE * -2.8f,y };
		break;
	case 3:
		mPosition = { SCREEN_WIDTH_PIECE * 2.0,y };
		break;
	case 4:
		mPosition = { SCREEN_WIDTH_PIECE * 7.5f,y };
		break;
	case 5:
		mPosition = { SCREEN_WIDTH_PIECE * 12.6f,y };
		break;
	}
	effect = false;
	Active = true;
	mModelData.mSRV = TexDate[1];
	Target_FlgX = false;
	Target_FlgY = false;
	anim[0].Reset();
	anim[1].Reset();
	animnum = 0;
	mPosition.z = -0.0001f*(num+1);
}
