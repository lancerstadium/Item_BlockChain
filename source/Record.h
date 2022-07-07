/**
* Info: class "Record" with its  defination of variables and methods.
* autohr: Lu TianShuo
* Time: 2022/07/03
*
*/

#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <vector>

using namespace std;

class Record {
public:
	// 明文
	string clear_text;
	// 暗文
	vector<char> cripher_text;
	// 买家公钥
	string pub_key;
	// 状态: -1表示信息不完成且未录入，0表示信息完整且待录入，1表示录入成功
	int status;
	// 返回时间
	string ReturnTime();
	// 公钥文件路径
	string PubKey_Path;
	

	// 空参构造函数
	Record();
	// 交易记录构造函数
	Record(const string& sell, const string& buy, double cost);
	// 微不足道的析构函数
	~Record();
	// 回复交易记录
	void recovery();

	// 打印交易记录
	void print();
	// 生成交易字符串
	string toString();
	
	


private:
	// 卖家
	string _Seller;
	// 买家
	string _Buyer;
	// 交易价格
	double _Value;
	// 交易时间
	time_t _Time;
	
	


};


#endif // !RECORD_H
