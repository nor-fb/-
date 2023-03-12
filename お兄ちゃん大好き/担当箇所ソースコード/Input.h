#pragma once
#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib,"xinput.lib")
#include<iostream>
#include<time.h>
#include"singleton.h"

///Gamepad記述を失くしたXINPUT
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
/// enem型 BTS:入力情報用
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
///入力クラス
///</summary>
///<remarks>
///Xinputの基本処理を行っているクラス
///</remarks>
class Input:public singleton<Input>
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	explicit Input(token);
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Input() = default;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 接続確認
	/// </summary>
	void ConnectionCheck();
	/// <summary>
	/// 入力:トリガー *制限なし*
	/// </summary>
	/// <param name="trigger:入力トリガー(右・左)"></param>
	/// <returns></returns>
	bool GetTriggerPress(BYTE);
	/// <summary>
	/// 入力:トリガー *入力範囲制限*
	/// </summary>
	/// <param name="trigger:入力トリガー(右・左)"></param>
	/// <param name="num:入力範囲(0~255)"></param>
	/// <returns></returns>
	bool GetTriggerNumPress(BYTE,unsigned int);
	/// <summary>
	/// 入力:スティック *制限なし*
	/// </summary>
	/// <param name="stick:入力スティック(右・左)"></param>
	/// <param name="button:入力ボタン"></param>
	/// <returns></returns>
	bool GetStick(BYTE, WORD);
	/// <summary>
	/// 入力:ボタン *制限なし*
	/// </summary>
	/// <param name="button:入力ボタン"></param>
	/// <returns></returns>
	bool GetButtonPress(WORD);
	/// <summary>
	/// 入力:ボタン *一回押し限定*
	/// </summary>
	/// <param name="button:入力ボタン"></param>
	/// <returns></returns>
	bool GetButtonPress_Once(WORD);
	/// <summary>
	/// 振動 *タイマー型*
	/// </summary>
	/// <param name="rifgtmotor:右振動モーター数値(0~65535)"></param>
	/// <param name="leftmotor:左振動モーター数値(0~65535)"></param>
	/// <param name="timer:振動時間"></param>
	/// <returns></returns>
	bool TimerVibration(int, int, clock_t);
	//未実装
	bool GetButtonPress(WORD, bool);
private:
	/// <summary>
	/// 入力情報 保存場所指定
	/// </summary>
	/// <param name="Input_num:入力内容"></param>
	void Input_Conversion(WORD);
	/// <summary>
	/// 入力確認 *追加入力*
	/// </summary>
	void ButtonPush();
	/// <summary>
	/// 入力確認 *入力減少*
	/// </summary>
	void ButtonRelese();
	/// <summary>
	/// スティック→十字キー変換
	/// </summary>
	/// <param name="sstickX:スティックX軸"></param>
	/// <param name="sstickY:スティックY軸"></param>
	/// <param name="sDeadZone:スティックデッドゾーン"></param>
	/// <returns></returns>
	WORD StickConversion(SHORT, SHORT, SHORT);
	/// <summary>
	/// 振動 *開始処理*
	/// </summary>
	/// <param name="rightmotor:右振動モーター数値(0~65535)"></param>
	/// <param name="leftmotor:左振動モーター数値(0~65535)"></param>
	void Vibration(int, int);
	/// <summary>
	/// 振動 *終了処理*
	/// </summary>
	void UnVibration();

	bool Connection_Fg;	//振動ON・OFFフラグ
	bool RightCoversion;//右スティック変換フラグ
	bool LeftCoversion;	//左スティック変換フラグ
	WORD mKeyState;//変化したボタン
	WORD mOldKeyState;//前に入力されたボタン
	WORD Storage_num;//格納場所番号
	bool flag;
	clock_t now_time;//今の時間
	clock_t end_time;//経過後の時間
	bool OldKeystate[MAX_INPUT];//入力確認格納場所

public:
	bool GetKeyboardPress(int);
	bool GetKeyboardTrigger(int);
private:
	BYTE mKeyboardState[256];
	BYTE mOldKeyboardState[256];
};