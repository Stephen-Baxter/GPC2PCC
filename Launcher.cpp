#include "Launcher.h"

Launcher::Launcher()
{
	DisplayNotice();
	GetTempConfigFileName();
	GetTempConfigFile();
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

	std::cout << "For more information, a copy of the ReedMe, and\n";
	std::cout << "the source code of this application go to\n";
	std::cout << "https://github.com/Stephen-Baxter/GPC2PCC\n\n";

	std::cout << "Please press any key to start . . .";
	_getch();
}

void Launcher::GetTempConfigFileName()
{
	configData.open(".G2PconfigList");

	if (!configData)
	{
		configData.close();
		configData.open(".G2PconfigList", std::ios::app);//Creates a new .G2PconfigList
		configData << "default.G2Pconfig";
	}

	configData >> tempConfigFileName;

	configData.close();
}

void Launcher::GetTempConfigFile()
{
	configData.open(tempConfigFileName);

	if (!configData)
	{
		configData.close();
		configData.open("default.G2Pconfig");

		if (!configData)
		{
			configData.close();
			configData.open("default.G2Pconfig", std::ios::app);//Creates a new default.G2Pconfig

			CreateMasterConfigFile();
			for (char i = 0; i < 122; i++) configData << masterConfigFile[i] << std::endl;
		}
	}

	for (char i = 0; i < 122; i++) configData >> tempConfigFile[i];

	configData.close();
}

void Launcher::SetGPInputs()
{
	gpMaxMouseSpeed = std::stof(tempConfigFile[23]);

	for (char i = 0; i < 2; i++)
	{
		gpIsLeftHanded[i] = (tempConfigFile[19 + i] == "true");
		gpThumbShiftPoint[i] = std::stof(tempConfigFile[37 + i]);
		gpThumbAngularRange[i] = std::stof(tempConfigFile[41 + i]);
		(std::stringstream)tempConfigFile[45 + i] >> std::hex >> gpThumbUp[i];
		(std::stringstream)tempConfigFile[49 + i] >> std::hex >> gpThumbDown[i];
		(std::stringstream)tempConfigFile[53 + i] >> std::hex >> gpThumbLeft[i];
		(std::stringstream)tempConfigFile[57 + i] >> std::hex >> gpThumbRight[i];
		(std::stringstream)tempConfigFile[61 + i] >> std::hex >> gpThumbAfterShift[i];
		(std::stringstream)tempConfigFile[67 + i] >> std::hex >> gpA[i];
		(std::stringstream)tempConfigFile[71 + i] >> std::hex >> gpB[i];
		(std::stringstream)tempConfigFile[75 + i] >> std::hex >> gpX[i];
		(std::stringstream)tempConfigFile[79 + i] >> std::hex >> gpY[i];
		(std::stringstream)tempConfigFile[83 + i] >> std::hex >> gpLeftShoulder[i];
		(std::stringstream)tempConfigFile[87 + i] >> std::hex >> gpRightShoulder[i];
		(std::stringstream)tempConfigFile[91 + i] >> std::hex >> gpDpadUp[i];
		(std::stringstream)tempConfigFile[95 + i] >> std::hex >> gpDPadDown[i];
		(std::stringstream)tempConfigFile[99 + i] >> std::hex >> gpDPadRight[i];
		(std::stringstream)tempConfigFile[103 + i] >> std::hex >> gpDPadLeft[i];
		(std::stringstream)tempConfigFile[107 + i] >> std::hex >> gpStart[i];
		(std::stringstream)tempConfigFile[111 + i] >> std::hex >> gpBack[i];
		(std::stringstream)tempConfigFile[115 + i] >> std::hex >> gpLeftThumb[i];
		(std::stringstream)tempConfigFile[119 + i] >> std::hex >> gpRightThumb[i];
	}
}

void Launcher::CreateMasterConfigFile()
{
	masterConfigFile[0] = "||GAME|PAD|CONTROLS|TO|PERSONAL|COMPUTER|CONTROLS";
	masterConfigFile[1] = "|2P||||||||||||||||||||||||||||||||||||||||||||||";
	masterConfigFile[2] = "PCC||||||||||||||||||||||||||||||||||||||||||||||";
	masterConfigFile[3] = "|";
	masterConfigFile[4] = "This|file|contains|the|settings|for|controler1|and|controler2.|If|this|file|or|\".G2PconfigList\"|cannot|be";
	masterConfigFile[5] = "found|in|the|same|directory|as|\"GPC2PCC.exe\"|then|GPC2PCC|will|create|a|new|ones.|To|create|a|new";
	masterConfigFile[6] = "\".G2Pconfig\"|copy|and|paste|this|file|into|the|same|directory|and|give|it|a|new|name|and|then|copy|and";
	masterConfigFile[7] = "past|the|file|name|(including|file|type)|into|the|\".G2PconfigList\"|file.|To|use|the|new|config|file|open";
	masterConfigFile[8] = "\".G2PconfigList\"|move|your|new|file|to|the|top|of|the|list|and|save|it|when|done.";
	masterConfigFile[9] = "|";
	masterConfigFile[10] = "All|of|the|key|codes|are|in|hexadecimal|and|can|be|fond|at";
	masterConfigFile[11] = "https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes";
	masterConfigFile[12] = "|";
	masterConfigFile[13] = "GPC2PCC|allows|Controler1|to|direct|the|movement|and|the|max|speed|of|the|mouse|pointer.";
	masterConfigFile[14] = "If|IS_LEFT-HANDED|is|set|to|\"true\"|then|the|left|thumb|stick|will|control|mouse|pointer|movement,|the";
	masterConfigFile[15] = "left|trigger|will|emulate|left|mouse|button|click,|and|the|right|trigger|will|emulate|right|mouse|click.";
	masterConfigFile[16] = "The|controls|are|switched|if|IS_LEFT-HANDED|is|set|to|\"false\".";
	masterConfigFile[17] = "|";
	masterConfigFile[18] = "Controler1|and|Controler2|are|set|to|IS_LEFT-HANDED";
	masterConfigFile[19] = "true";
	masterConfigFile[20] = "true";
	masterConfigFile[21] = "|";
	masterConfigFile[22] = "MAX_MOUSE_SPEED|for|Controler1";
	masterConfigFile[23] = "5.00";
	masterConfigFile[24] = "|";
	masterConfigFile[25] = "GPC2PCC|allows|the|Thumb|stick|that|is|not|being|used|for|mouse|movement|to|be|use|as|a|directional";
	masterConfigFile[26] = "pad|that|can|emulate|five|different|keys.";
	masterConfigFile[27] = "Keys|one|through|four|are|emulated|by|moving|the|thumb|stick|in|a|direction|within|an|angular|range";
	masterConfigFile[28] = "(examples:|if|THUMB_STICK_ANGULER_RANGE|is|set|to|135.00|degrees|then|each|direction|will|overlap";
	masterConfigFile[29] = "evenly|with|direction|next|to|it,|or|if|it|is|set|90.00|degrees|or|less|than|none|of|the|directions|will";
	masterConfigFile[30] = "overlap).";
	masterConfigFile[31] = "The|fifth|key|is|emulated|when|the|thumb|stick|is|moved|in|any|direction|past|a|\"shift\"|point|(this|is";
	masterConfigFile[32] = "great|for|a|game|that|require|a|second|key|to|be|pressed|to|make|the|player|run)(note:|if|SHIFT_POINT|is";
	masterConfigFile[33] = "less|than|zero|then|the|fifth|key|will|always|be|emulated|and|if|it|is|greater|than|one|then|it|will";
	masterConfigFile[34] = "never|be|emulated).";
	masterConfigFile[35] = "|";
	masterConfigFile[36] = "Controler1|and|Controler2|SHIFT_POINT";
	masterConfigFile[37] = "0.90";
	masterConfigFile[38] = "0.90";
	masterConfigFile[39] = "|";
	masterConfigFile[40] = "Controler1|and|Controler2|THUMB_STICK_ANGULER_RANGE";
	masterConfigFile[41] = "135.00";
	masterConfigFile[42] = "135.00";
	masterConfigFile[43] = "|";
	masterConfigFile[44] = "Controler1|and|Controler2|THUMB_STICK_UP_DIRECTION";
	masterConfigFile[45] = "0x26";
	masterConfigFile[46] = "0x26";
	masterConfigFile[47] = "|";
	masterConfigFile[48] = "Controler1|and|Controler2|THUMB_STICK_DOWN_DIRECTION";
	masterConfigFile[49] = "0x28";
	masterConfigFile[50] = "0x28";
	masterConfigFile[51] = "|";
	masterConfigFile[52] = "Controler1|and|Controler2|THUMB_STICK_LEFT_DIRECTION";
	masterConfigFile[53] = "0x25";
	masterConfigFile[54] = "0x25";
	masterConfigFile[55] = "|";
	masterConfigFile[56] = "Controler1|and|Controler2|THUMB_STICK_RIGHT_DIRECTION";
	masterConfigFile[57] = "0x27";
	masterConfigFile[58] = "0x27";
	masterConfigFile[59] = "|";
	masterConfigFile[60] = "Controler1|and|Controler2|PAST_SHIFT_POINT";
	masterConfigFile[61] = "0xA2";
	masterConfigFile[62] = "0xA2";
	masterConfigFile[63] = "|";
	masterConfigFile[64] = "Below|are|all|the|digital|buttons";
	masterConfigFile[65] = "|";
	masterConfigFile[66] = "Controler1|and|Controler2|A_BUTTON";
	masterConfigFile[67] = "0x41";
	masterConfigFile[68] = "0x41";
	masterConfigFile[69] = "|";
	masterConfigFile[70] = "Controler1|and|Controler2|B_BUTTON";
	masterConfigFile[71] = "0x42";
	masterConfigFile[72] = "0x42";
	masterConfigFile[73] = "|";
	masterConfigFile[74] = "Controler1|and|Controler2|X_BUTTON";
	masterConfigFile[75] = "0x58";
	masterConfigFile[76] = "0x58";
	masterConfigFile[77] = "|";
	masterConfigFile[78] = "Controler1|and|Controler2|Y_BUTTON";
	masterConfigFile[79] = "0x59";
	masterConfigFile[80] = "0x59";
	masterConfigFile[81] = "|";
	masterConfigFile[82] = "Controler1|and|Controler2|LEFT_SHOULDER_BUTTON";
	masterConfigFile[83] = "0x4C";
	masterConfigFile[84] = "0x4C";
	masterConfigFile[85] = "|";
	masterConfigFile[86] = "Controler1|and|Controler2|RIGHT_SHOULDER_BUTTON";
	masterConfigFile[87] = "0x52";
	masterConfigFile[88] = "0x52";
	masterConfigFile[89] = "|";
	masterConfigFile[90] = "Controler1|and|Controler2|DIRECTIONAL_PAD_UP_BUTTON";
	masterConfigFile[91] = "0x48";
	masterConfigFile[92] = "0x48";
	masterConfigFile[93] = "|";
	masterConfigFile[94] = "Controler1|and|Controler2|DIRECTIONAL_PAD_DOWN_BUTTON";
	masterConfigFile[95] = "0x4A";
	masterConfigFile[96] = "0x4A";
	masterConfigFile[97] = "|";
	masterConfigFile[98] = "Controler1|and|Controler2|DIRECTIONAL_PAD_RIGHT_BUTTON";
	masterConfigFile[99] = "0x4B";
	masterConfigFile[100] = "0x4B";
	masterConfigFile[101] = "|";
	masterConfigFile[102] = "Controler1|and|Controler2|DIRECTIONAL_PAD_LEFT_BUTTON";
	masterConfigFile[103] = "0x49";
	masterConfigFile[104] = "0x49";
	masterConfigFile[105] = "|";
	masterConfigFile[106] = "Controler1|and|Controler2|START_BUTTON";
	masterConfigFile[107] = "0x1B";
	masterConfigFile[108] = "0x1B";
	masterConfigFile[109] = "|";
	masterConfigFile[110] = "Controler1|and|Controler2|BACK_BUTTON";
	masterConfigFile[111] = "0x0D";
	masterConfigFile[112] = "0x0D";
	masterConfigFile[113] = "|";
	masterConfigFile[114] = "Controler1|and|Controler2|LEFT_THUMB_STICK_BUTTON";
	masterConfigFile[115] = "0xA1";
	masterConfigFile[116] = "0xA1";
	masterConfigFile[117] = "|";
	masterConfigFile[118] = "Controler1|and|Controler2|RIGHT_THUMB_STICK_BUTTON";
	masterConfigFile[119] = "0x12";
	masterConfigFile[120] = "0x12";
	masterConfigFile[121] = "|";
}
