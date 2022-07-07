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
	string UserName;	// 用户名
	string sRSAPriKey;	// 私钥
	string sRSAPubKey;	// 公钥
	double USD;			// 账户余额
	string Wallet;		// 钱包

	// 用户构造函数
	User();
	User(const string& name);

	// 析构函数
	~User();

	
	
	
	// 查询用户信息
	void info();
	// 用户付款给卖家
	Record PayTo(User &seller, double cost);

private:

	// 公钥文件路径
	string _pub_key_path;
	// 生成密钥对
	void _GenerateRSAkey();


};




#endif // !USER_H
