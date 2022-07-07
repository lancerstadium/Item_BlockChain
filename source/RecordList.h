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

	// ���׼�¼�б�����
	RecordList();

	// ��ѯ���׼�¼�б��С
	int size();
	// ��ӡ���׼�¼�б���Ϣ
	void print();
	// ת�������б���ϢΪString
	string toString();
	// �����¼�¼
	void AppendRecord(Record rNew);
	// ���ļ������¼��Ϣ
	void AppendRecordFromFile(string RecordFileName);

private:

	// ���׼�¼�б�����
	vector<Record> _vRL;


};


#endif // !RECORDLIST_H

