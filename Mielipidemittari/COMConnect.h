#ifndef COMCONNECT_H
#define COMCONNECT_H
#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class COMConnect
{
public:

	COMConnect(char *portname);
	~COMConnect();

	int readPort(char *buffer, unsigned int bufsize);
	bool writePort(char *buffer, unsigned int bufsize);
	bool isConnected();


private:
	bool m_isConnected;
	HANDLE m_handler;
	COMSTAT m_status;
	DWORD m_errors;

};

#endif