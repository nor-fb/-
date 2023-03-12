#include "Input.h"

using namespace std;
_XINPUT_STATE state;
_XINPUT_VIBRATION vibration;


Input::Input(token)
{
	Input::ConnectionCheck();
	//デッドゾーン
	if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}
	//変換フラグ
	Input::RightCoversion = true;
	Input::LeftCoversion = true;
	//
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;
	flag = true;
	mKeyState = 0;
	mOldKeyState = 0;
	for (int i = 0; i < MAX_INPUT; i++) {
		OldKeystate[i] = false;
	}
}

void Input::Update()
{
	// 前のフレームのキー状態を保存
	memcpy_s(mOldKeyboardState, sizeof(mOldKeyboardState), mKeyboardState, sizeof(mKeyboardState));

	GetKeyboardState(mKeyboardState);

	Input::ConnectionCheck();
	cout << state.Gamepad.wButtons << endl;
}

void Input::ConnectionCheck()
{
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		//Controller is connected
		Connection_Fg = true;
	}
	else
	{
		//Controller is not connected
		Connection_Fg = false;
	}
}

WORD Input::StickConversion(SHORT sstickX, SHORT sstickY, SHORT sDeadZone) {
	WORD wButtom = 0;
	//X軸
	if (sstickX >= sDeadZone) {
		wButtom = XINPUT_GAMEPAD_DPAD_RIGHT;
	}
	else if (sstickX <= -sDeadZone) {
		wButtom = XINPUT_GAMEPAD_DPAD_LEFT;
	}
	//Y軸
	if (sstickY >= sDeadZone) {
		wButtom = XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sstickY <= -sDeadZone) {
		wButtom = XINPUT_GAMEPAD_DPAD_DOWN;
	}
	return wButtom;
}

bool Input::GetStick(BYTE stick, WORD button)
{
	if (stick == RIGHT_STICK) {
		if (button == StickConversion(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) {
			return true;
		}
	}
	else if (stick == LEFT_STICK) {
		if (button == StickConversion(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) {
			return true;
		}
	}
	return false;
}

bool Input::GetTriggerPress(BYTE trigger)
{
	if (trigger == LEFT_TRIGGER) {
		if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			return true;
		}
	}
	else if (trigger == RIGHT_TRIGGER) {
		if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			return true;
		}
	}
	return false;
}

bool Input::GetTriggerNumPress(BYTE trigger, unsigned int num)
{
	if (trigger == LEFT_TRIGGER) {
		if (state.Gamepad.bLeftTrigger > num) {
			return true;
		}
	}
	else if (trigger == RIGHT_TRIGGER) {
		if (state.Gamepad.bRightTrigger > num) {
			return true;
		}
	}
	return false;
}

bool Input::GetButtonPress(WORD button)
{
	bool fg = false;
	if (state.Gamepad.wButtons&button) {
		mOldKeyState = state.Gamepad.wButtons;
		fg = true;
	}
	return fg;
}
bool Input::GetButtonPress(WORD button, bool stick)
{
	bool fg=false;
	if (stick) {
		
	}
	else {
		if (state.Gamepad.wButtons & button) {
			mOldKeyState = state.Gamepad.wButtons;
			fg = true;
		}
	}
	return false;
}

bool Input::GetButtonPress_Once(WORD button)
{
	if (state.Gamepad.wButtons&button) {
		if (OldKeystate[Storage_num]==false&&mOldKeyState!=button) {
			ButtonPush();
			return true;
		}
	}
	ButtonRelese();
	return false;
}

void Input::ButtonPush()
{
	if (state.Gamepad.wButtons != mOldKeyState) {//変化アリ
		if (state.Gamepad.wButtons > mOldKeyState) {
			mKeyState = state.Gamepad.wButtons - mOldKeyState;
			Input::Input_Conversion(mKeyState);
			OldKeystate[Storage_num] = true;
			mOldKeyState = state.Gamepad.wButtons;
		}
	}
}

void Input::ButtonRelese()
{
	if (state.Gamepad.wButtons != mOldKeyState) {//変化アリ
		if (state.Gamepad.wButtons < mOldKeyState) {
			mKeyState = mOldKeyState - state.Gamepad.wButtons;
			Input::Input_Conversion(mKeyState);
			OldKeystate[Storage_num] = false;
			mOldKeyState = state.Gamepad.wButtons;
		}
	}
}

void Input::Input_Conversion(WORD Input_num)
{
	switch (Input_num)
	{
	case XINPUT_UP:
		Storage_num = UP_CROSS;
		break;
	case XINPUT_DOWN:
		Storage_num = DOWN_CROSS;
		break;
	case XINPUT_RIGHT:
		Storage_num = RIGHT_CROSS;
		break;
	case XINPUT_LEFT:
		Storage_num = LEFT_CROSS;
		break;
	case XINPUT_A:
		Storage_num = A;
		break;
	case XINPUT_B:
		Storage_num = B;
		break;
	case XINPUT_X:
		Storage_num = X;
		break;
	case XINPUT_Y:
		Storage_num = Y;
		break;
	case XINPUT_RIGHT_SHOULDER:
		Storage_num = RIGHT_SH;
		break;
	case XINPUT_LEFT_SHOULDER:
		Storage_num = LEFT_SH;
		break;
	case XINPUT_RIGHT_STICK_PUSH:
		Storage_num = RIGHT_STI;
		break;
	case XINPUT_LEFT_STICK_PUSH:
		Storage_num = LEFT_STI;
		break;
	case XINPUT_START:
		Storage_num = START;
		break;
	case XINPUT_BACK:
		Storage_num = BACK;
		break;
	default:
		break;
	}
}

bool Input::TimerVibration(int rifgtmotor, int leftmotor, clock_t timer)
{
	Vibration(rifgtmotor, leftmotor);
	now_time = clock() / CLOCKS_PER_SEC;
	if (flag == true) {
		end_time = now_time + timer;
		flag = false;
	}
	if (now_time > end_time) {
		Input::UnVibration();
		flag = true;
		return false;
	}
	return true;
}

void Input::Vibration(int rightmotor, int leftmotor)
{
	vibration.wLeftMotorSpeed = leftmotor;
	vibration.wRightMotorSpeed = rightmotor;
	XInputSetState(0, &vibration);
}

void Input::UnVibration()
{
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;
	XInputSetState(0, &vibration);
}


bool Input::GetKeyboardPress(int vkey)
{
	return mKeyboardState[vkey] & 0x80;
}

bool Input::GetKeyboardTrigger(int vkey)
{
	return (mKeyboardState[vkey] & 0x80) != 0 && (mOldKeyboardState[vkey] & 0x80) == 0;
}
