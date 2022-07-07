#define _CRT_SECURE_NO_WARNINGS
/**
* Info: class "User" with its methods.
* autohr: Lu TianShuo
* Time: 2022/07/03
*
*/


#include <iostream>
#include "rsa2048.h"
#include "User.h"
#include "sha256.h"


using namespace std;

// �û����캯��
User::User() 
{
	UserName = "None";
	USD = 0;
	_GenerateRSAkey();
	cout << "User " << UserName << " init. Welcome!" << endl;
}

User::User(const string& name) : UserName(name)
{
	USD = 0;
	_GenerateRSAkey();
	cout << "User " << UserName << " init. Welcome!" << endl;
}

// ��������
User::~User() {
}



// ��ѯ�û���Ϣ
void User::info()
{
	cout << endl;
	cout << "[User Infomation]: " << endl;
	cout << "[User Name]: " << UserName << endl;
	cout << "[Public Key]: "  << endl;
	cout << sRSAPubKey << endl;
	cout << "[Private Key]: " << endl;
	cout << sRSAPriKey << endl;
	cout << "[Account(USD)]: " << USD << endl;
	cout << "[Wallet)]: " << Wallet << endl;
	cout << endl;
}


// ���ɼ�¼���û����������
Record User::PayTo(User &seller, double cost)
{
	Record rc = Record(Wallet, seller.Wallet, cost);
	USD -= cost;
	seller.USD += cost;
	//vector<char>-->char*ת��
	RSATool RT;
	rc.cripher_text = RT.EncryptByPrikeyString(rc.toString(), sRSAPriKey);
	rc.pub_key = sRSAPubKey;
	rc.PubKey_Path = _pub_key_path;
	rc.status = 0;
	cout << endl;
	cout << "[Reaction]: New record inited!" << endl;
	rc.print();
	RT.SaveRecord(rc);
	return rc;
}

// ������Կ��
void User::_GenerateRSAkey() {
	string pub_key_path;
	RSATool RT;
	RT.GenerateRSAkey(sRSAPubKey, sRSAPriKey, UserName, pub_key_path,Wallet);
	_pub_key_path = pub_key_path;
}
