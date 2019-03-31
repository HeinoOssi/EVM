#include "DBConnect.h"


DBConnect::DBConnect(std::string t_address, std::string t_username, std::string t_password)
{
	driver = get_driver_instance();

	con = driver->connect(t_address, t_username, t_password);

}


DBConnect::~DBConnect()
{

}
