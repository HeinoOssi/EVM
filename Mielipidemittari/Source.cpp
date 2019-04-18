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

// Comment out if you want to enter password etc while
// establishing connection

//#define USERNAME 

char IncomingData[MAX_DATA_LENGTH];
// Make sure this is the same what Arduino uses
char *portname = "\\\\.\\COM";



int main(){
	// Temporary variables to get the COM port number
	std::string temp_address = "\\\\.\\COM";			
	std::string temp_string;							
	const char *temp_port;								

	std::cout << "Enter port number" << std::endl;
	std::cin >> temp_string;

	// Append temp_string so it looks like \\\\.\\COM#
	temp_address.append(temp_string);					
	temp_port = temp_address.c_str();

	// Use iterator to modify string to char*
	std::string::iterator p = temp_address.begin();		
	portname = &(*p);

	// Variables for sql database
	std::string t_address, t_schema, t_username,		
		t_password;

#ifdef USERNAME
	// Enter default values to avoid typing them all the time
	t_address = "localhost:3306";
	t_username = "root";
	t_password = "ENTER YOUR DB PASSWORD HERE";
	t_schema = "testi1";
#else

	// Ask for MySQL Database address, schema, username
	// and password
	// TODO: HIDE THE PASSWORD

	std::cout << "Enter Database hostname" << std::endl;
	std::cin >> t_address;
	std::cout << "Enter Database username" << std::endl;
	std::cin >> t_username;
	std::cout << "Enter Database password ( NOTE: The password is not hidden yet )" << std::endl;
	std::cin >> t_password;
	std::cout << "Enter Database schema" << std::endl;
	std::cin >> t_schema;
#endif
	
	// Creates a new DB connection
	DBConnect *DBC = new DBConnect(t_address,			
		t_schema, t_username, t_password);

	// Creates a new serial port connection
	COMConnect *EVM = new COMConnect(portname);							

	if (EVM->isConnected()) {
		system("CLS");
		std::cout << "Connected to Electronic Voting Machine" << std::endl;
	}

	else std::cout << "Theres probably an error with the port name, check that" << std::endl;

	while (EVM->isConnected()) {
		int readevm = EVM->readPort(IncomingData,		// Checks if theres something to read
		MAX_DATA_LENGTH);								// and puts it into incomingData
		puts(IncomingData);								// Prints it

		DBC->AddData(IncomingData);
		
		Sleep(10);

	}
	

}

