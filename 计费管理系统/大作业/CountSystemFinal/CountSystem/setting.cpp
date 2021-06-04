#include "setting.h"
#include "transUtils.h"
#include <iomanip>

using namespace std;
setting::setting(const string& cardPath_, const string& infoPath_, const string& logPath_, const string& settingPath_, const int unit_, const double fee_, const double limit_, const bool writeFile_)
{
	strcpy_s(content.cardPath, cardPath_.c_str());
	strcpy_s(content.infoPath, infoPath_.c_str());
	strcpy_s(content.logPath, logPath_.c_str());
	strcpy_s(content.settingPath, settingPath_.c_str());
	content.unit = unit_;
	content.fee = fee_;
	content.limit = limit_;
	content.writeFile = writeFile_;

	ifstream ifile(content.settingPath);
	Content bufContent;

	if (!ifile.is_open()) return;

	ifile.read((char*)&bufContent, sizeof(Content));
	content = bufContent;

	if (content.writeFile) logFile.open(content.logPath, ios::app);
}
setting::~setting() {}
/*
ʹ�ô˺����ж��Ƿ�д��־
*/
bool setting::fileAvailable()
{
	static bool open = logFile.is_open();
	if (content.writeFile && !open) 
	{
		logFile.open(content.logPath,ios::ate);
		open = logFile.is_open();
	}
	return content.writeFile && open;
}
/*
��־ͷ �����ڲ����ã�
*/
void setting::headLog(const string& head)
{
	logFile << endl << SPLITELINE << head << endl;
}
/*
��־ʱ���
һ��������־β
*/
void setting::timeLog()
{
	if (!fileAvailable()) return;

	char date[TIMELENGTH] = { 0 };
	timeToString(time(NULL), date);

	logFile << DOWNLINE << date << endl;
}
void setting::addLog(const string& name, const string& pwd, const double balance)
{
	if (!fileAvailable()) return;

	headLog("�¿�����");

	logFile << "���ţ�" << name << endl;
	logFile << "���룺" << pwd << endl;
	logFile << "��" << balance << endl;
	
	timeLog();
}
void setting::displayHeadLog()
{
	if (!fileAvailable()) return;

	headLog("��ѯ");

	logFile << "����" << "\t" << "״̬" << "\t" << "���" << "\t" << "�ۼƳ�ֵ" << "\t\t" << "ʹ�ô���" << "\t\t" << "�ϴ�ʹ��ʱ��" << endl;
}
void setting::displayBodyLog(const string& name, const int status, const double balance, const double totalUse, const int useCount, const string& lastTime)
{
	if (!fileAvailable()) return;

	logFile << name << '\t';

	switch (status)
	{
	case USING:
		logFile << "�ϻ�\t";
		break;
	case UNUSE:
		logFile << "δ�ϻ�\t";
		break;
	case PAUSED:
		logFile << "ע��\t";
		break;
	default:
		logFile << "�쳣״̬\t";
		break;
	}

	streamDouble(balance);
	logFile << '\t';

	streamDouble(totalUse);
	logFile << "\t\t";

	logFile << useCount << "\t\t";

	logFile << lastTime << endl;
}
void setting::pauseLog(const string& name, const double chargeBack)
{
	if (!fileAvailable()) return;

	headLog("����");

	logFile << "���ţ�" << name << " ��ע��" << endl;
	logFile << "��";
	streamDouble(chargeBack);
	logFile << " �����" << endl;
	
	timeLog();
}
void setting::setUseLog(const string& name)
{
	if (!fileAvailable()) return;

	headLog("�ϻ�");

	logFile << "���ţ�" << name << " ���ϻ�" << endl;

	timeLog();
}
void setting::setUnuseLog(const string& name, const double charge)
{
	if (!fileAvailable()) return;

	headLog("�»�");

	logFile << "���ţ�" << name << " ���»�" << endl;
	logFile << "�˴��շѣ�";
	streamDouble(charge);
	logFile << " Ԫ" << endl;

	timeLog();
}
void setting::chargeLog(const string& name, const double charge)
{
	if (!fileAvailable()) return;

	headLog("��ֵ");

	logFile << "���ţ�" << name << endl;
	logFile << "��ֵ��";
	streamDouble(charge);
	logFile << " Ԫ" << endl;

	timeLog();
}
void setting::feeBackLog(const string& name, const double feeBack)
{
	if (!fileAvailable()) return;

	headLog("�˷�");

	logFile << "���ţ�" << name << endl;
	logFile << "�˷ѣ�";
	streamDouble(feeBack);
	logFile << " Ԫ" << endl;

	timeLog();
}
void setting::search1HeadLog(const string& name)
{
	if (!fileAvailable()) return;

	headLog("���Ѽ�¼��ѯ");

	logFile << "��ѯ���ţ�" << name << endl;

	logFile << SPLITELINE << SPLITELINE << endl;
	logFile << "����" << "\t\t" << "��ʼʱ��" << "\t\t\t" << "����ʱ��" << "\t\t\t" << "��������" << endl;
}
void setting::search1BodyLog(const double value, const string& sDate, const string& eDate, const int flag)
{
	if (!fileAvailable()) return;

	switch (flag)
	{
	case INFO_NEW:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << sDate << '\t' << "�¿�" << endl;
		break;
	case INFO_PAUSE:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << sDate << '\t' << "����" << endl;
		break;
	case INFO_CHARGE:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << sDate << '\t' << "��ֵ" << endl;
		break;
	case INFO_CUNSUME:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << eDate << '\t' << "����" << endl;
		break;
	case INFO_FEEBACK:
		streamDouble(value);
		logFile << "\t\t" << sDate << '\t' << sDate << '\t' << "�˿�" << endl;
		break;
	default:
		break;
	}
}
void setting::search2Log(const int sYear, const int sMonth, const int eYear, const int eMonth, const double income, const double expend)
{
	if (!fileAvailable()) return;

	headLog("ͳ����Ӫҵ��");

	logFile << "��ʼʱ�䣺" << sYear << "�� " << sMonth << "��" << endl;
	logFile << "����ʱ�䣺" << eYear << "�� " << eMonth << "��" << endl;

	logFile << "�����룺";
	streamDouble(income);
	logFile << " Ԫ" << endl;

	logFile << "��֧����";
	streamDouble(-expend);
	logFile << " Ԫ" << endl;

	logFile << "�����룺";
	streamDouble(income + expend);
	logFile << " Ԫ" << endl;

	timeLog();
}
void setting::search3HeadLog(const int year)
{
	if (!fileAvailable()) return;

	headLog("ͳ����Ӫҵ��");

	logFile << "ͳ����ݣ�" << year << "��" << endl;
	logFile << SPLITELINE << SPLITELINE << endl;
	logFile << "�·�" << "\t" << "������" << "\t\t" << "��֧��" << "\t\t" << "������" << endl;
}
void setting::search3BodyLog(const int month, const double income, const double expend)
{
	if (!fileAvailable()) return;

	logFile << month << "\t";

	streamDouble(income);
	logFile << "\t\t";

	streamDouble(-expend);
	logFile << "\t\t";

	streamDouble(income + expend);
	logFile << endl;
}
void setting::search3EndLog(const string& tag, const double income, const double expend)
{
	if (!fileAvailable()) return;

	logFile << tag << "\t";

	streamDouble(income);
	logFile << "\t\t";

	streamDouble(-expend);
	logFile << "\t\t";

	streamDouble(income + expend);
	logFile << endl;

	timeLog();
}
/*
�Ƿ�����־
���������file io��
*/
void setting::setWriteFile(const bool writeFile_)
{
	content.writeFile = writeFile_;
	if (writeFile_) logFile.open(content.logPath, ios::app);
	else if (logFile.is_open()) logFile.close();
	saveSetting();
}
void setting::saveSetting()
{
	ofstream ofile(content.settingPath, ios::binary | ios::ate);
	ofile.write((char*)&content, sizeof(content));
	ofile.close();
}
/*
���ļ��������С�����nλ��С��
*/
void setting::streamDouble(const double number)
{
	logFile << fixed << setprecision(1) << number;
}
