#include "GPC2PCC.h"

int main(int argc, char * argv[])
{
	SetConsoleTitleA("GPC2PCC");

	std::cout << "  GAME PAD CONTROLS TO PERSONAL COMPUTER CONTROLS\n";
	std::cout << " 2P                                              \n";
	std::cout << "PCC                                              \n";
	std::cout << "-------------------------------------------------\n";

	GPC2PCC gpc2pcc;

	while (gpc2pcc.IsRunning()) Sleep(1);


	return 0;
}
