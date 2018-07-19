#include "stdafx.h"
#include "Server.h"
#include <iostream>
#include<vector>
#include <list>
using namespace std;

Server::Server()
{
	time = 0;
	LifeTimeOfMessge = 2000;
	WhiteList.reserve(1009);
	BlackList.reserve(1009);
}
Server::~Server() {}
void Server::addElement(int NewElId, int CurTime)
{
	time += CurTime;
	if (!SearchInWHiteList(NewElId))
	{
		if (!SearchInBlackList(NewElId));
		{
			int Hash = NewElId % 1009;
			Element New;
			New.id = NewElId;
			New.TimeOfMessages.push_back(time);
			New.NumOfMessages = 1;

			WhiteList[Hash].push_back(New);
		}

	}

}
bool Server::SearchInWHiteList(int NewElId)
{
	int Hash = NewElId % 1009;
	auto it = WhiteList[Hash].begin();
	for (it = WhiteList[Hash].begin(); it != WhiteList[Hash].end(); ++it)
		if (it->id == NewElId) break;
	if (it == WhiteList[Hash].end()) return false;
	it->NumOfMessages++;
	it->TimeOfMessages.push_back(time);
	while ((time - it->TimeOfMessages[0]) > LifeTimeOfMessge)
	{
		it->TimeOfMessages.erase(it->TimeOfMessages.begin());
		it->NumOfMessages--;
	}
	if (it->NumOfMessages == 50)
	{
		WhiteList[Hash].erase(it);
		MoveToBlack(*it); 
	}
	return true;

}
bool Server::SearchInBlackList(int NewElId)
{
	int Hash = NewElId % 1009;
	auto it = BlackList[Hash].begin();
	for (it = BlackList[Hash].begin(); it != BlackList[Hash].end(); ++it)
		if (it->id == NewElId) break;
	if (it == BlackList[Hash].end()) return false;
	it->NumOfMessages++;
	it->TimeOfMessages.push_back(time);
	while ((time - it->TimeOfMessages[0]) > LifeTimeOfMessge)
	{
		it->TimeOfMessages.erase(it->TimeOfMessages.begin());
		it->NumOfMessages--;
	}
	if (it->NumOfMessages< 50)
	{
		BlackList[Hash].erase(it);
		MoveToWhite(*it); 
	}
	return true;

}
void Server::MoveToBlack(Element BadServer) {

	int Hash = BadServer.id % 1009;
	BlackList[Hash].push_back(BadServer);
}
void Server::MoveToWhite(Element GoodServer) {

	int Hash = GoodServer.id % 1009;
	WhiteList[Hash].push_back(GoodServer);
}
