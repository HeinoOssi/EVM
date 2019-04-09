#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "COMConnect.h"
#include "DBConnect.h"

/*
Electronic Voting Machine project.
Ouas (OH, MK, R-ML)
*/
// TODO: 
// - automatically search for the port where arduino is connected

char IncomingData[MAX_DATA_LENGTH];
char *portname = "\\\\.\\COM";							// Make sure this is the same what Arduino uses

int main(){
	std::string temp_address = "\\\\.\\COM";			// Temporary
	std::string temp_string;							// Temporary string
	const char *temp_port;								// Temporary port char

	std::cout << "Enter port number" << std::endl;
	std::cin >> temp_string;
	temp_address.append(temp_string);					// Append temp_string so it looks like \\\\.\\COM#
	temp_port = temp_address.c_str();					// Char->string

	std::string::iterator p = temp_address.begin();		// Use iterator to modify string to char*
	portname = &(*p);

	// Ask for MySQL Database address, schema, username
	// and password
	// TODO: HIDE THE PASSWORD
	std::string t_address, t_schema, t_username,		// Variables for hostname, schema, user and pass
		t_password;
	std::cout << "Enter Database hostname" << std::endl;
	std::cin >> t_address;
	std::cout << "Enter Database username" << std::endl;
	std::cin >> t_username;
	std::cout << "Enter Database password ( NOTE: The password is not hidden yet )" << std::endl;
	std::cin >> t_password;
	std::cout << "Enter Database schema" << std::endl;
	std::cin >> t_schema;

	
	DBConnect *DBC = new DBConnect(t_address,			// Creates a new DB connection
		t_schema, t_username, t_password);
	COMConnect EVM(portname);							// Creates a new serial port connection

	if (EVM.isConnected()) {
		system("CLS");
		std::cout << "Connected to Electronic Voting Machine" << std::endl;
	}

	else std::cout << "Theres probably an error with the port name, check that" << std::endl;

	while (EVM.isConnected()) {
		int readevm = EVM.readPort(IncomingData,		// Checks if theres something to read
			MAX_DATA_LENGTH);							// and puts it into incomingData
		puts(IncomingData);								// Prints it
		printf(IncomingData);

		DBC->AddData(IncomingData);

		Sleep(1000);										// Sleeps for 100ms
	}
	

}

