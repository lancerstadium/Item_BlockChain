#define _CRT_SECURE_NO_WARNINGS
/**
* Info: class "Record" with its methods.
* autohr: Lu TianShuo
* Time: 2022/07/03
*
*/

#include <sstream>
#include <iostream>
#include "Record.h"

using namespace std;


// �ղι��캯��
Record::Record() 
{
	_Value = 0;
	status = -1;
	_Time = time(0);
}

// ���׼�¼���캯��
Record::Record(const string& sell, const string& buy,double cost) 
	:_Seller(sell), _Buyer(buy) ,_Value(cost)
{
	clear_text = toString();
	status = -1;
	_Time = time(nullptr);
}

// ΢���������������
Record::~Record()
{

}

// �ظ����׼�¼
void Record::recovery() 
{
	istringstream ss(clear_text);	// ������
	ss >> _Seller >> _Buyer >> _Value;
	status = 0;
}

string Record::ReturnTime() 
{
	struct tm* t = localtime(&_Time);
	char NOW[64];
	strftime(NOW, sizeof(NOW), "%Y-%m-%d %H:%M:%S", t);
	return NOW;
}

// ��ӡ���׼�¼
void Record::print()
{
	struct tm* t = localtime(&_Time);
	char NOW[64];
	strftime(NOW, sizeof(NOW), "%Y-%m-%d %H:%M:%S",t);
	cout.width(8);
	cout << "[record]: " << _Seller << " -> " << _Buyer << " :" << _Value << " USD. \t" << NOW << " Status: " << status << endl;
}


// ���ɽ����ַ���
string Record::toString()
{
	stringstream ss;
	_Time = time(0);
	struct tm t;
	localtime_s(&t, &_Time);
	char NOW[64];
	strftime(NOW, sizeof(NOW), "%Y-%m-%d %H:%M:%S", &t);
	cout.width(8);
	ss << _Seller << " " << _Buyer << " " << _Value << " " << NOW ;
	return ss.str();
}