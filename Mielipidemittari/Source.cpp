#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "COMConnect.h"
#include "EVMApp.h"
#include "DBConnect.h"

/*
Electronic Voting Machine project.
Ouas
*/
// Replace the com port
// TODO: 
// - automatically search for the port where arduino is connected

char IncomingData[MAX_DATA_LENGTH];
char *portname = "\\\\.\\COM";				// Make sure this is the same what Arduino uses


int main(){
	//***************************************************
	// TODO: move these to separate function
	std::string temp_address = "\\\\.\\COM";
	std::string temp_string;
	const char *temp_port;

	std::cout << "Enter port number" << std::endl;
	std::cin >> temp_string;
	temp_address.append(temp_string);
	temp_port = temp_address.c_str();

	// Use iterator to modify string to char*
	std::string::iterator p = temp_address.begin();
	portname = &(*p);
	//***************************************************
	// SQL Connection
	
	COMConnect EVM(portname);
	EVMApp VotingMachineApp;

	if (EVM.isConnected()) std::cout << "Connected to Electronic Voting Machine" << std::endl;
	else std::cout << "Theres probably an error with the port name, check that" << std::endl;

	while (EVM.isConnected()) {
		// Check if theres something to read
		// TODO: everything
		int readevm = EVM.readPort(IncomingData, MAX_DATA_LENGTH);
		if (IncomingData != NULL) puts(IncomingData);
		
		// So, the application runs in here:
		VotingMachineApp.EVMRun();

		
		Sleep(100);

	}
	std::cin >> portname;

}

