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
	bool AddData(char *t_Query);				// Function to add data into db
	DBConnect(std::string t_address, std::string t_schema,		// Constructor 
		std::string t_user, std::string t_password);
	~DBConnect();												// Destructor
	
	bool isConnected() { return this->m_IsConnected; }			// Returns true if connected

private:
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
	sql::PreparedStatement *pstmt;
	bool m_IsConnected;



};

#endif
