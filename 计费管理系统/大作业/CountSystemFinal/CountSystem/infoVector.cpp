#include "infoVector.h"
#include <fstream>

using namespace std;

infoVector::infoVector(const string& filename)
{
	ifstream ifile(filename);
	info bufInfo("BUFFINFO",0,0,0);

	if (!ifile.is_open()) return;

	while (true)
	{
		ifile.read((char*)&bufInfo, sizeof(info));
		if (ifile.eof()) break;
		infoV.push_back(bufInfo);
	}
}
infoVector::~infoVector(){}
void infoVector::addInfo(const string& name, const double charge, const int flag, const time_t& sDate,const time_t& eDate)
{
	info newInfo(name, charge, flag, sDate, eDate);
	saveInfo(&newInfo);
	infoV.push_back(newInfo);
}
vector<info>& infoVector::searchInfo(const string& name, const time_t& sDate, const time_t& eDate)
{
	infoSearch.clear();

	vector<info>::iterator it;
	for (it = infoV.begin(); it != infoV.end(); it++)
	{
		if (!name._Equal(it->name)) continue;
		if (it->sDate >= sDate && it->sDate < eDate) infoSearch.push_back(*it);
		if (it->sDate >= eDate) break; //info依据时间顺序存储，故当时间超出直接跳出
	}
	return infoSearch;
}
vector<info>& infoVector::searchInfo(const time_t& sDate, const time_t& eDate)
{
	infoSearch.clear();

	vector<info>::iterator it;
	for (it = infoV.begin(); it != infoV.end(); it++)
	{
		if (it->sDate >= sDate && it->sDate < eDate) infoSearch.push_back(*it);
		if (it->sDate >= eDate) break; //info依据时间顺序存储，故当时间超出直接跳出
	}
	return infoSearch;
}
void infoVector::resetPath(const string& path)
{
	infoV.clear();

	ifstream ifile(path);
	info bufInfo("BUFFINFO", 0, 0, 0);

	if (!ifile.is_open()) return;

	while (true)
	{
		ifile.read((char*)&bufInfo, sizeof(info));
		if (ifile.eof()) break;
		infoV.push_back(bufInfo);
	}
}
void infoVector::saveInfo(const info* pInfo, const string& path)
{
	ofstream ofile(path, ios::binary | ios::app);
	ofile.write((char*)pInfo, sizeof(info));
	ofile.close();
}