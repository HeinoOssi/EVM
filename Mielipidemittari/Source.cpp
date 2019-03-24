#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "COMConnect.h"
/*
Electronic Voting Machine project.
Ouas
*/
// Replace the com port
// TODO: 
// - automatically search for the port where arduino is connected
char *portname = "\\\\.\\COM1";
char IncomingData[MAX_DATA_LENGTH];

int main() {
	COMConnect EVM(portname);

	if (EVM.isConnected()) std::cout << "Connected to Electronic Voting Machine" << std::endl;
	else std::cout << "Theres probably an error with the port name, check that" << std::endl;

	while (EVM.isConnected()) {
		// Check if theres something to read
		int readevm = EVM.readPort(IncomingData, MAX_DATA_LENGTH);
		puts(IncomingData);
		Sleep(100);

	}
}
