#pragma once

#include <iostream>
#include<vector>
#include <list>
using namespace std;
struct Element {
	int curTime;
	int id;
	int NumOfMessages;
	vector <int> TimeOfMessages;
};
class Server
{
private:
	vector<list<Element>> WhiteList;
	vector<list<Element>> BlackList;
	int time;
	int LifeTimeOfMessge;
	bool SearchInWHiteList(int NewElId);
	bool SearchInBlackList(int NewElId);
	void MoveToBlack(Element BadServer);
	void MoveToWhite(Element BadServer);
public:
	Server();
	~Server();
	void addElement(int NewElId, int CurTime);
	

};
