#pragma once
#include "Headers_and_appINFO.h"

class Launcher
{
public:
	Launcher();

	bool gpIsLeftHanded[2];
	float gpMaxMouseSpeed;

	float gpThumbShiftPoint[2];
	float gpThumbAngularRange[2];
	short gpThumbUp[2];
	short gpThumbDown[2];
	short gpThumbLeft[2];
	short gpThumbRight[2];
	short gpThumbAfterShift[2];

	short gpA[2];
	short gpB[2];
	short gpX[2];
	short gpY[2];
	short gpLeftShoulder[2];
	short gpRightShoulder[2];
	short gpDpadUp[2];
	short gpDPadDown[2];
	short gpDPadRight[2];
	short gpDPadLeft[2];
	short gpStart[2];
	short gpBack[2];
	short gpLeftThumb[2];
	short gpRightThumb[2];

private:
	std::fstream configData;

	std::string masterConfigFile[122];

	std::string tempConfigFile[122];
	std::string tempConfigFileName;

	void DisplayNotice();
	void GetTempConfigFileName();
	void GetTempConfigFile();
	void SetGPInputs();

	void CreateMasterConfigFile();
};

