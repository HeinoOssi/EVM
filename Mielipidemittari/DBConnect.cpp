#include "DBConnect.h"
#define _CRT_SECURE_NO_WARNINGS

DBConnect::DBConnect(std::string t_address, std::string t_schema, std::string t_username, std::string t_password)
{
	try {
		this->driver = get_driver_instance();
		this->con = driver->connect(t_address,						// Creates the connection to DB
			t_username, t_password);								// with given strings

		if (!this->con) {											// If the connection for some reason fails
			std::cout << "Failed to connect to DB " << std::endl;	// theres no point to continue in this 
			return;													// function
		}
		this->con->setSchema(t_schema);								// Set given schema to con variable
		m_IsConnected = true;

	}
	catch (sql::SQLException &e) {
		std::cout << "ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}


}

void DBConnect::AddData(char *t_Vote, int t_VoteCount) {
	// TODO:
	// TABLE NAME USER; COLUMN NAMES VOTE, VOTECOUNT;
	char t_InsertData[] = "INSERT INTO user (vote, votecount) VALUES ('%s', '%d')";
	char t_Query[128];											// Temporary query char
	sprintf_s(t_Query, t_InsertData, t_Vote, t_VoteCount);		// Appends all given data into t_Query
	std::cout << t_Query;									

}

DBConnect::~DBConnect()
{
	// Delete everything from memory.
	delete this->con;
	delete this->stmt;
	delete this->res;
	delete this->pstmt;
	m_IsConnected = false;
}
