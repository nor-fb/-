#pragma once
#include "GameObject.h"
enum FADE_TYPE {
	FADE_FADINGorDARKENING,//�Ó]���]�^�C�v
	FADE_SCALE,			   //�g��k���^�C�v
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
	//�����炪���C���œ����Ă��炤
	void Fade_Process();
	void Scale_Process();
private:
	void Fade_Intialize();	//�Ó]���]������
	void Scale_Initialize();//�g��k��������
	void Fade_In();			//���]����
	void Fade_Out();		//�Ó]����
	void Scale_Up();		//�X�P�[���g�又��
	void Scale_Down();		//�X�P�[���k������
	float Fade_Speed;		//�X�s�[�h�ϐ�
	FADE_TYPE now_fade;
	std::string Tex_Data[2];
	bool Initialize_flag = true;//�������t���O(Fade�̉摜�f�[�^�X�V)
	bool Switching_flag;		//�X�V�t���O(�V�[���̉摜�f�[�^�X�V)
	bool Finish_flag;			//�I���t���O
};