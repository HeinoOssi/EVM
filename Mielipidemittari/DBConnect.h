#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <stdlib.h>
#include <iostream>

// MySQL C++ Connector Includes
#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

class DBConnect
{
public:
	DBConnect(std::string t_address, std::string t_user, std::string t_password);
	~DBConnect();
	
	bool isConnected() { return this->m_IsConnected; }

private:
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	bool m_IsConnected;



};

#endif
