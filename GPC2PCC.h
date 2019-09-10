#pragma once
#include "Headers_and_appINFO.h"

class GPC2PCC
{
public:
	GPC2PCC();
	~GPC2PCC();

	bool IsRunning();

private:
	struct GPINPUT
	{
		bool beingPress = false;
		bool beenPressed[6] = { false };
		short assignedKey[6] = { 0x41 };
		float analogMagnitude = 0.00f;
		float shiftPoint = 0.90f;
		float up = 0.00f;
		float down = 0.00f;
		float left = 0.00f;
		float right = 0.00f;
	};

	bool noSecondGamePad;

	XINPUT_STATE gpStateForGP[2];

	INPUT keyboardKeysForGP[2][22];
	INPUT mouseButtonsForGP0[2];

	bool isLeftHandedForGP[2];
	float thumbRangeSlopeForGP[2];
	float maxMouseSpeedForGP0;

	GPINPUT GP_A[2];
	GPINPUT GP_B[2];
	GPINPUT GP_X[2];
	GPINPUT GP_Y[2];
	GPINPUT GP_DPAD_UP[2];
	GPINPUT GP_DPAD_DOWN[2];
	GPINPUT GP_DPAD_LEFT[2];
	GPINPUT GP_DPAD_RIGHT[2];
	GPINPUT GP_BACK[2];
	GPINPUT GP_START[2];
	GPINPUT GP_LEFT_SHOULDER[2];
	GPINPUT GP_RIGHT_SHOULDER[2];
	GPINPUT GP_LEFT_THUMB[2];
	GPINPUT GP_RIGHT_THUMB[2];
	GPINPUT GP_LEFT_TRIGGER[2];
	GPINPUT GP_RIGHT_TRIGGER[2];

	void SetupGPInputs();
	void SetupPCInputs();

	bool IsGP0Disconnected();
	void UpdateGPInput();
	void UpdatePCInput();

	void PC_MOUSE_BUTTON(GPINPUT * gpInput, char mouseNumber, bool isLeftHanded);
	void PC_MOUSE_MOVEMENT();
	void PC_KEYBOARD(char i, GPINPUT * gpInput, bool isGPInputActive, char keyNumber, char assignedKeyNumber);
	void PC_KEYBOARD(char i, char keyNumber1, char keyNumber2, char keyNumber3, char keyNumber4, char keyNumber5);
};

