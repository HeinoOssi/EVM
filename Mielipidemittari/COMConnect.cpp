#include "COMConnect.h"

COMConnect::COMConnect(char *portname)
{
	this->m_isConnected = false;
	this->m_handler = CreateFileA(static_cast<LPCSTR>(portname),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	// Look for errors
	if (this->m_handler == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) printf("%s not available\n", portname);
		else printf("Unknown error\n");

	}

	else {
		DCB dcbSerialParameters = { 0 };

		if (!GetCommState(this->m_handler, &dcbSerialParameters)) printf("Serial parameters not available\n");

		// Basic settings
		else {
			dcbSerialParameters.Parity = NOPARITY;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.BaudRate = CBR_9600;
			dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

			if (!SetCommState(m_handler, &dcbSerialParameters)) printf("Failed to set serial port parameters\n");
			else
			{
				this->m_isConnected = true;
				PurgeComm(this->m_handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(ARDUINO_WAIT_TIME);

			}
		}
	}
}

int COMConnect::readPort(char *buffer, unsigned int bufsize) {
	DWORD bytesRead;
	unsigned int toRead = 1;

	ClearCommError(this->m_handler, &this->m_errors, &this->m_status);

	if (this->m_status.cbInQue > 0) {
		if (this->m_status.cbInQue > bufsize) toRead = bufsize;
		else toRead = this->m_status.cbInQue;
	}

	if (ReadFile(this->m_handler, buffer, toRead, &bytesRead, NULL)) return bytesRead;

	return 0;

}

// TODO:
bool COMConnect::writePort(char *buffer, unsigned int bufsize) {
	// Maybe not required in this project?
	
	return false;
}
bool COMConnect::isConnected() {
	
	return this->m_isConnected;

}

COMConnect::~COMConnect()
{
	if (this->m_isConnected) {
		this->m_isConnected = false;
		CloseHandle(this->m_handler);

	}
}
