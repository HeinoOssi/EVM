#ifndef EVMVOTE_H
#define EVMVOTE_H
#include <ctime>
#include <iostream>
class EVMVote
{
public:
	EVMVote();
	~EVMVote();


private:
	std::string m_Vote;
	int m_VoteCount;
	/*
	std::string m_Date;
	std::string m_time;
	*/

};

#endif
