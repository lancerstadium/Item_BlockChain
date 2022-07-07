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
	// ����
	string clear_text;
	// ����
	vector<char> cripher_text;
	// ��ҹ�Կ
	string pub_key;
	// ״̬: -1��ʾ��Ϣ�������δ¼�룬0��ʾ��Ϣ�����Ҵ�¼�룬1��ʾ¼��ɹ�
	int status;
	// ����ʱ��
	string ReturnTime();
	// ��Կ�ļ�·��
	string PubKey_Path;
	

	// �ղι��캯��
	Record();
	// ���׼�¼���캯��
	Record(const string& sell, const string& buy, double cost);
	// ΢���������������
	~Record();
	// �ظ����׼�¼
	void recovery();

	// ��ӡ���׼�¼
	void print();
	// ���ɽ����ַ���
	string toString();
	
	


private:
	// ����
	string _Seller;
	// ���
	string _Buyer;
	// ���׼۸�
	double _Value;
	// ����ʱ��
	time_t _Time;
	
	


};


#endif // !RECORD_H
