#include "GPC2PCC.h"
#include "Launcher.h"

GPC2PCC::GPC2PCC()
{
	SetupGPInputs();
	SetupPCInputs();

	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void GPC2PCC::SetupGPInputs()
{
	Launcher launcher;

	maxMouseSpeedForGP0 = launcher.gpMaxMouseSpeed;

	GP_A[0].assignedKey[1] = VK_VOLUME_UP;

	GP_B[0].assignedKey[1] = VK_VOLUME_DOWN;

	GP_Y[0].assignedKey[1] = VK_VOLUME_MUTE;

	for (char i = 0; i < 2; i++)
	{
		isLeftHandedForGP[i] = launcher.gpIsLeftHanded[i];

		thumbRangeSlopeForGP[i] = tanf((180.00f - launcher.gpThumbAngularRange[i]) * (float)PI / 360.00f);

		GP_A[i].assignedKey[0] = launcher.gpA[i];

		GP_B[i].assignedKey[0] = launcher.gpB[i];

		GP_X[i].assignedKey[0] = launcher.gpX[i];

		GP_Y[i].assignedKey[0] = launcher.gpY[i];

		GP_LEFT_SHOULDER[i].assignedKey[0] = launcher.gpLeftShoulder[i];

		GP_RIGHT_SHOULDER[i].assignedKey[0] = launcher.gpRightShoulder[i];

		GP_DPAD_UP[i].assignedKey[0] = launcher.gpDpadUp[i];
		GP_DPAD_DOWN[i].assignedKey[0] = launcher.gpDPadDown[i];
		GP_DPAD_LEFT[i].assignedKey[0] = launcher.gpDPadLeft[i];
		GP_DPAD_RIGHT[i].assignedKey[0] = launcher.gpDPadRight[i];

		GP_LEFT_THUMB[i].assignedKey[0] = launcher.gpLeftThumb[i];
		GP_LEFT_THUMB[i].assignedKey[1] = launcher.gpThumbUp[i];
		GP_LEFT_THUMB[i].assignedKey[2] = launcher.gpThumbDown[i];
		GP_LEFT_THUMB[i].assignedKey[3] = launcher.gpThumbLeft[i];
		GP_LEFT_THUMB[i].assignedKey[4] = launcher.gpThumbRight[i];
		GP_LEFT_THUMB[i].assignedKey[5] = launcher.gpThumbAfterShift[i];
		GP_LEFT_THUMB[i].shiftPoint = launcher.gpThumbShiftPoint[i];

		GP_RIGHT_THUMB[i].assignedKey[0] = launcher.gpRightThumb[i];
		GP_RIGHT_THUMB[i].assignedKey[1] = GP_LEFT_THUMB[i].assignedKey[1];
		GP_RIGHT_THUMB[i].assignedKey[2] = GP_LEFT_THUMB[i].assignedKey[2];
		GP_RIGHT_THUMB[i].assignedKey[3] = GP_LEFT_THUMB[i].assignedKey[3];
		GP_RIGHT_THUMB[i].assignedKey[4] = GP_LEFT_THUMB[i].assignedKey[4];
		GP_RIGHT_THUMB[i].assignedKey[5] = GP_LEFT_THUMB[i].assignedKey[5];
		GP_RIGHT_THUMB[i].shiftPoint = GP_LEFT_THUMB[i].shiftPoint;

		GP_START[i].assignedKey[0] = launcher.gpStart[0];
		GP_BACK[i].assignedKey[0] = launcher.gpBack[0];
	}
}

void GPC2PCC::SetupPCInputs()
{
	for (char j = 0; j < 2; j++)
	{
		mouseButtonsForGP0[j] = { 0 };
		mouseButtonsForGP0[j].type = INPUT_MOUSE;
		mouseButtonsForGP0[j].mi.mouseData = 0;
		mouseButtonsForGP0[j].mi.time = 0;
		mouseButtonsForGP0[j].mi.dwExtraInfo = 0;
	}

	for (char i = 0; i < 2; i++)
	{
		for (char j = 0; j < 22; j++)
		{
			keyboardKeysForGP[i][j] = { 0 };
			keyboardKeysForGP[i][j].type = INPUT_KEYBOARD;
			keyboardKeysForGP[i][j].ki.wScan = 0;
			keyboardKeysForGP[i][j].ki.time = 0;
			keyboardKeysForGP[i][j].ki.dwExtraInfo = 0;
		}
	}
}

GPC2PCC::~GPC2PCC()
{
	for (char i = 0; i < 2; i++)
	{
		RtlSecureZeroMemory(&gpStateForGP[i], sizeof(gpStateForGP[i]));

		for (char j = 0; j < 22; j++)
		{
			if (keyboardKeysForGP[i][j].ki.dwFlags == 0)
			{
				keyboardKeysForGP[i][j].ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &keyboardKeysForGP[i][j], sizeof(keyboardKeysForGP[i][j]));
			}
			keyboardKeysForGP[i][j] = { 0 };
		}
	}
	
	for (char j = 0; j < 2; j++)
	{
		if (mouseButtonsForGP0[j].mi.dwFlags == MOUSEEVENTF_LEFTDOWN)
		{
			mouseButtonsForGP0[j].mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &mouseButtonsForGP0[j], sizeof(mouseButtonsForGP0[j]));
		}
		if (mouseButtonsForGP0[j].mi.dwFlags == MOUSEEVENTF_RIGHTDOWN)
		{
			mouseButtonsForGP0[j].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			SendInput(1, &mouseButtonsForGP0[j], sizeof(mouseButtonsForGP0[j]));
		}
		mouseButtonsForGP0[j] = { 0 };
	}

	ShowWindow(GetConsoleWindow(), SW_SHOW);
	Beep(370, 100);
}

bool GPC2PCC::IsRunning()
{
	if (IsGP0Disconnected()) return false;
	
	UpdateGPInput();

	if (GP_DPAD_DOWN[0].beingPress and GP_LEFT_THUMB[0].beingPress and GP_START[0].beingPress) return false;

	UpdatePCInput();


	return true;
}

bool GPC2PCC::IsGP0Disconnected()
{
	for (char i = 0; i < 2; i++) RtlSecureZeroMemory(&gpStateForGP[i], sizeof(gpStateForGP[i]));

	noSecondGamePad = (XInputGetState(1, &gpStateForGP[1]) != ERROR_SUCCESS);

	return (XInputGetState(0, &gpStateForGP[0]) != ERROR_SUCCESS);
}

void GPC2PCC::UpdateGPInput()
{
	for (char i = 0; i < ((noSecondGamePad) ? 1 : 2); i++)
	{
		GP_A[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_A;
		GP_B[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_B;
		GP_X[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_X;
		GP_Y[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_Y;
		GP_DPAD_UP[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		GP_DPAD_DOWN[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		GP_DPAD_LEFT[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		GP_DPAD_RIGHT[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		GP_BACK[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
		GP_START[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_START;
		GP_LEFT_SHOULDER[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		GP_RIGHT_SHOULDER[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		GP_LEFT_THUMB[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
		GP_RIGHT_THUMB[i].beingPress = gpStateForGP[i].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;

		GP_LEFT_TRIGGER[i].beingPress = gpStateForGP[i].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		GP_RIGHT_TRIGGER[i].beingPress = gpStateForGP[i].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;

		float csGamepadSThumbLX = (float)gpStateForGP[i].Gamepad.sThumbLX + 0.50f;
		float csGamepadSThumbLY = (float)gpStateForGP[i].Gamepad.sThumbLY + 0.50f;
		float csGamepadSThumbRX = (float)gpStateForGP[i].Gamepad.sThumbRX + 0.50f;
		float csGamepadSThumbRY = (float)gpStateForGP[i].Gamepad.sThumbRY + 0.50f;

		GP_LEFT_THUMB[i].analogMagnitude = sqrt(csGamepadSThumbLY * csGamepadSThumbLY + csGamepadSThumbLX * csGamepadSThumbLX);
		GP_LEFT_THUMB[i].analogMagnitude = (GP_LEFT_THUMB[i].analogMagnitude > 32767.50f) ? 32767.50f : GP_LEFT_THUMB[i].analogMagnitude;

		GP_RIGHT_THUMB[i].analogMagnitude = sqrt(csGamepadSThumbRY * csGamepadSThumbRY + csGamepadSThumbRX * csGamepadSThumbRX);
		GP_RIGHT_THUMB[i].analogMagnitude = (GP_RIGHT_THUMB[i].analogMagnitude > 32767.50f) ? 32767.50f : GP_RIGHT_THUMB[i].analogMagnitude;

		GP_LEFT_THUMB[i].up = (csGamepadSThumbLY > 0.00f) ? csGamepadSThumbLY / GP_LEFT_THUMB[i].analogMagnitude : 0.00f;
		GP_LEFT_THUMB[i].down = (csGamepadSThumbLY < 0.00f) ? -csGamepadSThumbLY / GP_LEFT_THUMB[i].analogMagnitude : 0.00f;
		GP_LEFT_THUMB[i].left = (csGamepadSThumbLX < 0.00f) ? -csGamepadSThumbLX / GP_LEFT_THUMB[i].analogMagnitude : 0.00f;
		GP_LEFT_THUMB[i].right = (csGamepadSThumbLX > 0.00f) ? csGamepadSThumbLX / GP_LEFT_THUMB[i].analogMagnitude : 0.00f;
		
		GP_RIGHT_THUMB[i].up = (csGamepadSThumbRY > 0.00f) ? csGamepadSThumbRY / GP_RIGHT_THUMB[i].analogMagnitude : 0.00f;
		GP_RIGHT_THUMB[i].down = (csGamepadSThumbRY < 0.00f) ? -csGamepadSThumbRY / GP_RIGHT_THUMB[i].analogMagnitude : 0.00f;
		GP_RIGHT_THUMB[i].left = (csGamepadSThumbRX < 0.00f) ? -csGamepadSThumbRX / GP_RIGHT_THUMB[i].analogMagnitude : 0.00f;
		GP_RIGHT_THUMB[i].right = (csGamepadSThumbRX > 0.00f) ? csGamepadSThumbRX / GP_RIGHT_THUMB[i].analogMagnitude : 0.00f;

		GP_LEFT_THUMB[i].analogMagnitude = (GP_LEFT_THUMB[i].analogMagnitude > (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? ((GP_LEFT_THUMB[i].analogMagnitude - (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / (32767.50f - (float)XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) : 0.00f;
		GP_RIGHT_THUMB[i].analogMagnitude = (GP_RIGHT_THUMB[i].analogMagnitude > (float)XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? ((GP_RIGHT_THUMB[i].analogMagnitude - (float)XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) / (32767.50f - (float)XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) : 0.00f;
	}
}

void GPC2PCC::UpdatePCInput()
{
	PC_KEYBOARD(0, &GP_A[0], GP_DPAD_DOWN[0].beingPress && GP_LEFT_THUMB[0].beingPress && GP_A[0].beingPress, 19, 1);
	PC_KEYBOARD(0, &GP_B[0], GP_DPAD_DOWN[0].beingPress && GP_LEFT_THUMB[0].beingPress && GP_B[0].beingPress, 20, 1);
	PC_KEYBOARD(0, &GP_Y[0], GP_DPAD_DOWN[0].beingPress && GP_LEFT_THUMB[0].beingPress && GP_Y[0].beingPress, 21, 1);
	PC_MOUSE_BUTTON(&GP_LEFT_TRIGGER[0], 0, !isLeftHandedForGP[0]);
	PC_MOUSE_BUTTON(&GP_RIGHT_TRIGGER[0], 1, isLeftHandedForGP[0]);
	PC_MOUSE_MOVEMENT();

	for (char i = 0; i < ((noSecondGamePad) ? 1 : 2); i++)
	{
		PC_KEYBOARD(i, &GP_A[i], GP_A[i].beingPress, 0, 0);
		PC_KEYBOARD(i, &GP_B[i], GP_B[i].beingPress, 1, 0);
		PC_KEYBOARD(i, &GP_X[i], GP_X[i].beingPress, 2, 0);
		PC_KEYBOARD(i, &GP_Y[i], GP_Y[i].beingPress, 3, 0);
		PC_KEYBOARD(i, &GP_LEFT_SHOULDER[i], GP_LEFT_SHOULDER[i].beingPress, 4, 0);
		PC_KEYBOARD(i, &GP_RIGHT_SHOULDER[i], GP_RIGHT_SHOULDER[i].beingPress, 5, 0);
		PC_KEYBOARD(i, &GP_DPAD_DOWN[i], GP_DPAD_DOWN[i].beingPress, 6, 0);
		PC_KEYBOARD(i, &GP_DPAD_LEFT[i], GP_DPAD_LEFT[i].beingPress, 7, 0);
		PC_KEYBOARD(i, &GP_DPAD_RIGHT[i], GP_DPAD_RIGHT[i].beingPress, 8, 0);
		PC_KEYBOARD(i, &GP_DPAD_UP[i], GP_DPAD_UP[i].beingPress, 9, 0);
		PC_KEYBOARD(i, &GP_LEFT_THUMB[i], GP_LEFT_THUMB[i].beingPress, 10, 0);
		PC_KEYBOARD(i, &GP_RIGHT_THUMB[i], GP_RIGHT_THUMB[i].beingPress, 11, 0);
		PC_KEYBOARD(i, &GP_START[i], GP_START[i].beingPress, 12, 0);
		PC_KEYBOARD(i, &GP_BACK[i], GP_BACK[i].beingPress, 13, 0);
		PC_KEYBOARD(i, 14, 15, 16, 17, 18);
	}
}

void GPC2PCC::PC_MOUSE_BUTTON(GPINPUT * gpInput, char mouseNumber, bool leftHand)
{
	DWORD mouseButtonUp = (leftHand) ? MOUSEEVENTF_RIGHTUP : MOUSEEVENTF_LEFTUP;
	DWORD mouseButtonDown = (leftHand) ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_LEFTDOWN;

	if ((*gpInput).beingPress and not(*gpInput).beenPressed[0])
	{
		mouseButtonsForGP0[mouseNumber].mi.dwFlags = mouseButtonDown;
		SendInput(1, &mouseButtonsForGP0[mouseNumber], sizeof(mouseButtonsForGP0[mouseNumber]));
		(*gpInput).beenPressed[0] = true;
	}
	if (not(*gpInput).beingPress and (*gpInput).beenPressed[0])
	{
		mouseButtonsForGP0[mouseNumber].mi.dwFlags = mouseButtonUp;
		SendInput(1, &mouseButtonsForGP0[mouseNumber], sizeof(mouseButtonsForGP0[mouseNumber]));
		(*gpInput).beenPressed[0] = false;
	}
}

void GPC2PCC::PC_MOUSE_MOVEMENT()
{
	POINT cursor;
	GetCursorPos(&cursor);

	float thumbXPosition = 0.00f;
	float thumbYPosition = 0.00f;
	float magnitude = 0.00f;
	float cursorXPosition = cursor.x;
	float cursorYPosition = cursor.y;

	if (isLeftHandedForGP[0])
	{
		magnitude = GP_LEFT_THUMB[0].analogMagnitude;

		thumbYPosition = (GP_LEFT_THUMB[0].down > GP_LEFT_THUMB[0].up) ? -GP_LEFT_THUMB[0].down : GP_LEFT_THUMB[0].up;
		thumbXPosition = (GP_LEFT_THUMB[0].left > GP_LEFT_THUMB[0].right) ? -GP_LEFT_THUMB[0].left : GP_LEFT_THUMB[0].right;
	}
	else
	{
		magnitude = GP_RIGHT_THUMB[0].analogMagnitude;

		thumbYPosition = (GP_RIGHT_THUMB[0].down > GP_RIGHT_THUMB[0].up) ? -GP_RIGHT_THUMB[0].down : GP_RIGHT_THUMB[0].up;
		thumbXPosition = (GP_RIGHT_THUMB[0].left > GP_RIGHT_THUMB[0].right) ? -GP_RIGHT_THUMB[0].left : GP_RIGHT_THUMB[0].right;
	}

	cursorXPosition += thumbXPosition * maxMouseSpeedForGP0 * magnitude;
	cursorYPosition -= thumbYPosition * maxMouseSpeedForGP0 * magnitude;

	SetCursorPos((int)cursorXPosition, (int)cursorYPosition);
}

void GPC2PCC::PC_KEYBOARD(char i, GPINPUT* gpInput, bool isGPInputActive, char keyNumber, char assignedKeyNumber)
{
	if (isGPInputActive and not(*gpInput).beenPressed[assignedKeyNumber])
	{
		keyboardKeysForGP[i][keyNumber].ki.wVk = (*gpInput).assignedKey[assignedKeyNumber];
		keyboardKeysForGP[i][keyNumber].ki.dwFlags = 0;
		SendInput(1, &keyboardKeysForGP[i][keyNumber], sizeof(keyboardKeysForGP[i][keyNumber]));
		(*gpInput).beenPressed[assignedKeyNumber] = true;
	}
	if (not(isGPInputActive) and (*gpInput).beenPressed[assignedKeyNumber])
	{
		keyboardKeysForGP[i][keyNumber].ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &keyboardKeysForGP[i][keyNumber], sizeof(keyboardKeysForGP[i][keyNumber]));
		(*gpInput).beenPressed[assignedKeyNumber] = false;
	}
}

void GPC2PCC::PC_KEYBOARD(char i, char keyNumber1, char keyNumber2, char keyNumber3, char keyNumber4, char keyNumber5)
{
	float gpThumbX;
	float gpThumbY;

	if (isLeftHandedForGP[i])
	{
		gpThumbX = GP_RIGHT_THUMB[i].left + GP_RIGHT_THUMB[i].right;
		gpThumbY = GP_RIGHT_THUMB[i].down + GP_RIGHT_THUMB[i].up;

		PC_KEYBOARD(i, &GP_RIGHT_THUMB[i], GP_RIGHT_THUMB[i].analogMagnitude > 0.00f && GP_RIGHT_THUMB[i].up >= gpThumbX * thumbRangeSlopeForGP[i], keyNumber1, 1);
		PC_KEYBOARD(i, &GP_RIGHT_THUMB[i], GP_RIGHT_THUMB[i].analogMagnitude > 0.00f && GP_RIGHT_THUMB[i].down >= gpThumbX * thumbRangeSlopeForGP[i], keyNumber2, 2);
		PC_KEYBOARD(i, &GP_RIGHT_THUMB[i], GP_RIGHT_THUMB[i].analogMagnitude > 0.00f && GP_RIGHT_THUMB[i].left >= gpThumbY * thumbRangeSlopeForGP[i], keyNumber3, 3);
		PC_KEYBOARD(i, &GP_RIGHT_THUMB[i], GP_RIGHT_THUMB[i].analogMagnitude > 0.00f && GP_RIGHT_THUMB[i].right >= gpThumbY * thumbRangeSlopeForGP[i], keyNumber4, 4);
		PC_KEYBOARD(i, &GP_RIGHT_THUMB[i], GP_RIGHT_THUMB[i].analogMagnitude > GP_RIGHT_THUMB[i].shiftPoint, keyNumber5, 5);
	}
	else
	{
		gpThumbX = GP_LEFT_THUMB[i].left + GP_LEFT_THUMB[i].right;
		gpThumbY = GP_LEFT_THUMB[i].down + GP_LEFT_THUMB[i].up;

		PC_KEYBOARD(i, &GP_LEFT_THUMB[i], GP_LEFT_THUMB[i].analogMagnitude > 0.00f && GP_LEFT_THUMB[i].up >= gpThumbX * thumbRangeSlopeForGP[i], keyNumber1, 1);
		PC_KEYBOARD(i, &GP_LEFT_THUMB[i], GP_LEFT_THUMB[i].analogMagnitude > 0.00f && GP_LEFT_THUMB[i].down >= gpThumbX * thumbRangeSlopeForGP[i], keyNumber2, 2);
		PC_KEYBOARD(i, &GP_LEFT_THUMB[i], GP_LEFT_THUMB[i].analogMagnitude > 0.00f && GP_LEFT_THUMB[i].left >= gpThumbY * thumbRangeSlopeForGP[i], keyNumber3, 3);
		PC_KEYBOARD(i, &GP_LEFT_THUMB[i], GP_LEFT_THUMB[i].analogMagnitude > 0.00f && GP_LEFT_THUMB[i].right >= gpThumbY * thumbRangeSlopeForGP[i], keyNumber4, 4);
		PC_KEYBOARD(i, &GP_LEFT_THUMB[i], GP_LEFT_THUMB[i].analogMagnitude > GP_LEFT_THUMB[i].shiftPoint, keyNumber5, 5);
	}
}
