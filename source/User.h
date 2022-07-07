/**
* Info: class "User" with its  defination of variables and methods.
* autohr: Lu TianShuo
* Time: 2022/07/03
*
*/

#ifndef USER_H
#define USER_H

#include <iostream>
#include "Record.h"

using namespace std;

class User {
public:
	string UserName;	// �û���
	string sRSAPriKey;	// ˽Կ
	string sRSAPubKey;	// ��Կ
	double USD;			// �˻����
	string Wallet;		// Ǯ��

	// �û����캯��
	User();
	User(const string& name);

	// ��������
	~User();

	
	
	
	// ��ѯ�û���Ϣ
	void info();
	// �û����������
	Record PayTo(User &seller, double cost);

private:

	// ��Կ�ļ�·��
	string _pub_key_path;
	// ������Կ��
	void _GenerateRSAkey();


};




#endif // !USER_H
