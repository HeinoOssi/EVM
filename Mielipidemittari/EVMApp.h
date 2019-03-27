#ifndef EVMAPP_H
#define EVMAPP_H
#include "DBConnect.h"

class EVMApp
{
public:

	void EVMRun();
	
	bool isActive() { return m_isActive; }

	EVMApp();
	~EVMApp();


private:
	bool m_isActive;

};

#endif
