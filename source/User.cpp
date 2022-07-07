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

// 用户构造函数
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

// 析构函数
User::~User() {
}



// 查询用户信息
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


// 生成记录：用户付款给卖家
Record User::PayTo(User &seller, double cost)
{
	Record rc = Record(Wallet, seller.Wallet, cost);
	USD -= cost;
	seller.USD += cost;
	//vector<char>-->char*转换
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

// 生成密钥对
void User::_GenerateRSAkey() {
	string pub_key_path;
	RSATool RT;
	RT.GenerateRSAkey(sRSAPubKey, sRSAPriKey, UserName, pub_key_path,Wallet);
	_pub_key_path = pub_key_path;
}
