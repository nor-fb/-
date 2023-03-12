#pragma once
#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib,"xinput.lib")
#include<iostream>
#include<time.h>
#include"singleton.h"

///Gamepad�L�q����������XINPUT
#define XINPUT_UP					 0x0001
#define XINPUT_DOWN					 0x0002
#define XINPUT_LEFT					 0x0004
#define XINPUT_RIGHT				 0x0008
#define XINPUT_START				 0x0010
#define XINPUT_BACK					 0x0020
#define XINPUT_LEFT_STICK_PUSH       0x0040
#define XINPUT_RIGHT_STICK_PUSH      0x0080
#define XINPUT_LEFT_SHOULDER		 0x0100
#define XINPUT_RIGHT_SHOULDER		 0x0200
#define XINPUT_A					 0x1000
#define XINPUT_B					 0x2000
#define XINPUT_X					 0x4000
#define XINPUT_Y					 0x8000
#define MAX_INPUT 16
/// <summary>
/// enem�^ BTS:���͏��p
/// </summary>
enum BTS {
	UP_CROSS,
	DOWN_CROSS,
	RIGHT_CROSS,
	LEFT_CROSS,
	A,
	B,
	X,
	Y,
	RIGHT_SH,
	LEFT_SH,
	RIGHT_STI,
	LEFT_STI,
	RIGHT_TRIGGER,
	LEFT_TRIGGER,
	START,
	BACK,
	RIGHT_STICK,
	LEFT_STICK
};
///<summary>
///���̓N���X
///</summary>
///<remarks>
///Xinput�̊�{�������s���Ă���N���X
///</remarks>
class Input:public singleton<Input>
{
public:
	/// <summary>
	/// ������
	/// </summary>
	explicit Input(token);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Input() = default;
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �ڑ��m�F
	/// </summary>
	void ConnectionCheck();
	/// <summary>
	/// ����:�g���K�[ *�����Ȃ�*
	/// </summary>
	/// <param name="trigger:���̓g���K�[(�E�E��)"></param>
	/// <returns></returns>
	bool GetTriggerPress(BYTE);
	/// <summary>
	/// ����:�g���K�[ *���͔͈͐���*
	/// </summary>
	/// <param name="trigger:���̓g���K�[(�E�E��)"></param>
	/// <param name="num:���͔͈�(0~255)"></param>
	/// <returns></returns>
	bool GetTriggerNumPress(BYTE,unsigned int);
	/// <summary>
	/// ����:�X�e�B�b�N *�����Ȃ�*
	/// </summary>
	/// <param name="stick:���̓X�e�B�b�N(�E�E��)"></param>
	/// <param name="button:���̓{�^��"></param>
	/// <returns></returns>
	bool GetStick(BYTE, WORD);
	/// <summary>
	/// ����:�{�^�� *�����Ȃ�*
	/// </summary>
	/// <param name="button:���̓{�^��"></param>
	/// <returns></returns>
	bool GetButtonPress(WORD);
	/// <summary>
	/// ����:�{�^�� *��񉟂�����*
	/// </summary>
	/// <param name="button:���̓{�^��"></param>
	/// <returns></returns>
	bool GetButtonPress_Once(WORD);
	/// <summary>
	/// �U�� *�^�C�}�[�^*
	/// </summary>
	/// <param name="rifgtmotor:�E�U�����[�^�[���l(0~65535)"></param>
	/// <param name="leftmotor:���U�����[�^�[���l(0~65535)"></param>
	/// <param name="timer:�U������"></param>
	/// <returns></returns>
	bool TimerVibration(int, int, clock_t);
	//������
	bool GetButtonPress(WORD, bool);
private:
	/// <summary>
	/// ���͏�� �ۑ��ꏊ�w��
	/// </summary>
	/// <param name="Input_num:���͓��e"></param>
	void Input_Conversion(WORD);
	/// <summary>
	/// ���͊m�F *�ǉ�����*
	/// </summary>
	void ButtonPush();
	/// <summary>
	/// ���͊m�F *���͌���*
	/// </summary>
	void ButtonRelese();
	/// <summary>
	/// �X�e�B�b�N���\���L�[�ϊ�
	/// </summary>
	/// <param name="sstickX:�X�e�B�b�NX��"></param>
	/// <param name="sstickY:�X�e�B�b�NY��"></param>
	/// <param name="sDeadZone:�X�e�B�b�N�f�b�h�]�[��"></param>
	/// <returns></returns>
	WORD StickConversion(SHORT, SHORT, SHORT);
	/// <summary>
	/// �U�� *�J�n����*
	/// </summary>
	/// <param name="rightmotor:�E�U�����[�^�[���l(0~65535)"></param>
	/// <param name="leftmotor:���U�����[�^�[���l(0~65535)"></param>
	void Vibration(int, int);
	/// <summary>
	/// �U�� *�I������*
	/// </summary>
	void UnVibration();

	bool Connection_Fg;	//�U��ON�EOFF�t���O
	bool RightCoversion;//�E�X�e�B�b�N�ϊ��t���O
	bool LeftCoversion;	//���X�e�B�b�N�ϊ��t���O
	WORD mKeyState;//�ω������{�^��
	WORD mOldKeyState;//�O�ɓ��͂��ꂽ�{�^��
	WORD Storage_num;//�i�[�ꏊ�ԍ�
	bool flag;
	clock_t now_time;//���̎���
	clock_t end_time;//�o�ߌ�̎���
	bool OldKeystate[MAX_INPUT];//���͊m�F�i�[�ꏊ

public:
	bool GetKeyboardPress(int);
	bool GetKeyboardTrigger(int);
private:
	BYTE mKeyboardState[256];
	BYTE mOldKeyboardState[256];
};