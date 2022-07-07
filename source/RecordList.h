/**
* Info: class "RecordList" with its  defination of variables and methods.
* autohr: Lu TianShuo
* Time: 2022/07/03
*
*/

#ifndef RECORDLIST_H
#define RECORDLIST_H

#include <iostream>
#include <vector>
#include "Record.h"

class RecordList {
public:

	// 交易记录列表生成
	RecordList();

	// 查询交易记录列表大小
	int size();
	// 打印交易记录列表信息
	void print();
	// 转换交易列表信息为String
	string toString();
	// 插入新记录
	void AppendRecord(Record rNew);
	// 从文件读入记录信息
	void AppendRecordFromFile(string RecordFileName);

private:

	// 交易记录列表数据
	vector<Record> _vRL;


};


#endif // !RECORDLIST_H

