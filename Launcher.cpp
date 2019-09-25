#include "Launcher.h"

Launcher::Launcher()
{
	DisplayNotice();
	GetConfigFileName();
	GetConfigFileData();
	SetGPInputs();
}

void Launcher::DisplayNotice()
{
	std::cout << "NOTE GPC2PCC RUNS IN THE BACKGROUND! GPC2PCC can\n";
	std::cout << "be exit by pressing the Left Thumb Button + DPad\n";
	std::cout << "Down Button + Start Button on Controller1 or by\n";
	std::cout << "unplugging Controller1 from the Computer\n\n";

	std::cout << "(GPC2PCC can also be exit by going into the\n";
	std::cout << "\"Task Manager\", selecting GPC2PCC, and pressing\n";
	std::cout << "\"End Task\" but this may cause problems)\n\n";

	std::cout << "For more information, a copy of the ReedMe,\n";
	std::cout << "Manual, and the source code of this application\n";
	std::cout << "go to https://github.com/Stephen-Baxter/GPC2PCC\n\n";

	std::cout << "Please press any key to start . . .";
	_getch();
}

void Launcher::GetConfigFileName()
{
	onStartConfig = json::GetJSONData("onStartConfig.json");

	if (onStartConfig == JSON_FILE_NOT_FOUND)
	{
		json::SetJSONData("onStartConfig.json", json::SetObject("ON_START_CONFIG_FILE_NAME", json::SetString("defaultConfig")));

		onStartConfig = json::GetJSONData("onStartConfig.json");
	}
}

void Launcher::GetConfigFileData()
{
	configData = json::GetJSONData(json::GetString(json::Getobject("ON_START_CONFIG_FILE_NAME", onStartConfig) + ".json"));

	if (configData == JSON_FILE_NOT_FOUND) configData = json::GetJSONData("defaultConfig.json");

	if (configData == JSON_FILE_NOT_FOUND)
	{
		CreateMasterConfigFile();
		json::SetJSONData("defaultConfig.json", masterConfigFile);

		configData = json::GetJSONData("defaultConfig.json");
	}
}

void Launcher::SetGPInputs()
{
	gpMaxMouseSpeed = (float)json::GetNumber(json::Getobject("GP0", json::Getobject("MAX_MOUSE_SPEED", configData)));

	for (char i = 0; i < 2; i++)
	{
		gpIsLeftHanded[i] = json::GetBoolean(json::Getobject("GP" + std::to_string(i), json::Getobject("IS_LEFT-HANDED", configData)));
		gpThumbShiftPoint[i] = (float)json::GetNumber(json::Getobject("GP" + std::to_string(i), json::Getobject("SHIFT_POINT", configData)));
		gpThumbAngularRange[i] = (float)json::GetNumber(json::Getobject("GP" + std::to_string(i), json::Getobject("THUMB_STICK_ANGULER_RANGE", configData)));
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("THUMB_STICK_UP_DIRECTION", configData)))) >> std::hex >> gpThumbUp[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("THUMB_STICK_DOWN_DIRECTION", configData)))) >> std::hex >> gpThumbDown[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("THUMB_STICK_LEFT_DIRECTION", configData)))) >> std::hex >> gpThumbLeft[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("THUMB_STICK_RIGHT_DIRECTION", configData)))) >> std::hex >> gpThumbRight[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("PAST_SHIFT_POINT", configData)))) >> std::hex >> gpThumbAfterShift[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("A_BUTTON", configData)))) >> std::hex >> gpA[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("B_BUTTON", configData)))) >> std::hex >> gpB[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("X_BUTTON", configData)))) >> std::hex >> gpX[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("Y_BUTTON", configData)))) >> std::hex >> gpY[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("LEFT_SHOULDER_BUTTON", configData)))) >> std::hex >> gpLeftShoulder[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("RIGHT_SHOULDER_BUTTON", configData)))) >> std::hex >> gpRightShoulder[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("DIRECTIONAL_PAD_UP_BUTTON", configData)))) >> std::hex >> gpDpadUp[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("DIRECTIONAL_PAD_DOWN_BUTTON", configData)))) >> std::hex >> gpDPadDown[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("DIRECTIONAL_PAD_RIGHT_BUTTON", configData)))) >> std::hex >> gpDPadRight[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("DIRECTIONAL_PAD_LEFT_BUTTON", configData)))) >> std::hex >> gpDPadLeft[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("START_BUTTON", configData)))) >> std::hex >> gpStart[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("BACK_BUTTON", configData)))) >> std::hex >> gpBack[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("LEFT_THUMB_STICK_BUTTON", configData)))) >> std::hex >> gpLeftThumb[i];
		(std::stringstream)(json::GetString(json::Getobject("GP" + std::to_string(i), json::Getobject("RIGHT_THUMB_STICK_BUTTON", configData)))) >> std::hex >> gpRightThumb[i];
	}
}

void Launcher::CreateMasterConfigFile()
{
	masterConfigFile.push_back("{\"GPC2PCC\": {");
	masterConfigFile.push_back("	\"MOUSE_SETTING\": {");
	masterConfigFile.push_back("		\"IS_LEFT-HANDED\": {\"GP0\": true, \"GP1\": true},");
	masterConfigFile.push_back("		\"MAX_MOUSE_SPEED\": {\"GP0\": 5.00, \"GP1\": null}");
	masterConfigFile.push_back("	},");
	masterConfigFile.push_back("	\"THUMB_SETTING\": {");
	masterConfigFile.push_back("		\"SHIFT_POINT\": {\"GP0\": 0.90, \"GP1\": 0.90},");
	masterConfigFile.push_back("		\"THUMB_STICK_ANGULER_RANGE\": {\"GP0\": 135.00, \"GP1\": 135.00},");
	masterConfigFile.push_back("		\"THUMB_STICK_UP_DIRECTION\": {\"GP0\": \"0x26\", \"GP1\": \"0x26\"},       \"THUMB_STICK_DOWN_DIRECTION\": {\"GP0\": \"0x28\", \"GP1\": \"0x28\"},");
	masterConfigFile.push_back("		\"THUMB_STICK_LEFT_DIRECTION\": {\"GP0\": \"0x25\", \"GP1\": \"0x25\"},     \"THUMB_STICK_RIGHT_DIRECTION\": {\"GP0\": \"0x27\", \"GP1\": \"0x27\"},");
	masterConfigFile.push_back("		\"PAST_SHIFT_POINT\": {\"GP0\": \"0xA2\", \"GP1\": \"0xA2\"}");
	masterConfigFile.push_back("	},");
	masterConfigFile.push_back("	\"BUTTON_SETTING\": {");
	masterConfigFile.push_back("		\"A_BUTTON\": {\"GP0\": \"0x41\", \"GP1\": \"0x41\"},                       \"B_BUTTON\": {\"GP0\": \"0x42\", \"GP1\": \"0x42\"},");
	masterConfigFile.push_back("		\"X_BUTTON\": {\"GP0\": \"0x58\", \"GP1\": \"0x58\"},                       \"Y_BUTTON\": {\"GP0\": \"0x59\", \"GP1\": \"0x59\"},");
	masterConfigFile.push_back("		\"LEFT_SHOULDER_BUTTON\": {\"GP0\": \"0x4C\", \"GP1\": \"0x4C\"},           \"RIGHT_SHOULDER_BUTTON\": {\"GP0\": \"0x52\", \"GP1\": \"0x52\"},");
	masterConfigFile.push_back("		\"DIRECTIONAL_PAD_UP_BUTTON\": {\"GP0\": \"0x48\", \"GP1\": \"0x48\"},      \"DIRECTIONAL_PAD_DOWN_BUTTON\": {\"GP0\": \"0x4A\", \"GP1\": \"0x4A\"},");
	masterConfigFile.push_back("		\"DIRECTIONAL_PAD_RIGHT_BUTTON\": {\"GP0\": \"0x4B\", \"GP1\": \"0x4B\"},   \"DIRECTIONAL_PAD_LEFT_BUTTON\": {\"GP0\": \"0x49\", \"GP1\": \"0x49\"},");
	masterConfigFile.push_back("		\"START_BUTTON\": {\"GP0\": \"0x1B\", \"GP1\": \"0x1B\"},                   \"BACK_BUTTON\": {\"GP0\": \"0x0D\", \"GP1\": \"0x0D\"},");
	masterConfigFile.push_back("		\"LEFT_THUMB_STICK_BUTTON\": {\"GP0\": \"0xA1\", \"GP1\": \"0xA1\"},        \"RIGHT_THUMB_STICK_BUTTON\": {\"GP0\": \"0x12\", \"GP1\": \"0x12\"}");
	masterConfigFile.push_back("	}");
	masterConfigFile.push_back("}}");
}
