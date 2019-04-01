#include "DBConnect.h"


DBConnect::DBConnect(std::string t_address, std::string t_schema, std::string t_username, std::string t_password)
{
	try {
		this->driver = get_driver_instance();

		this->con = driver->connect(t_address, t_username, t_password);

		// If connection failed lets return
		if (!this->con) {
			std::cout << "Failed to connect to DB " << std::endl;
			return;
		}

		this->con->setSchema(t_schema);
	}
	catch (sql::SQLException &e) {
		std::cout << "ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}

}

void DBConnect::AddData(const char t_Vote, int t_VoteCount) {
	// TODO:
	// Kato onko oikein
	
	pstmt = con->prepareStatement("INSERT INTO test VALUES ", t_Vote, t_VoteCount);
	return;

}

DBConnect::~DBConnect()
{

}
