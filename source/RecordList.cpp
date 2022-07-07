/**
* Info: class "RecordList" with methods.
* autohr: Lu TianShuo
* Time: 2022/07/03
*
*/

#include <iostream>
#include <vector>
#include "RecordList.h"
#include "rsa2048.h"

using namespace std;

// 交易记录列表生成
RecordList::RecordList()
{

}


// 查询交易记录列表大小
int RecordList::size()
{
	return _vRL.size();
}

// 打印交易记录列表信息
void RecordList::print()
{
	vector<Record>::iterator iter = _vRL.begin();
    cout << "[Transaction records]:   size = " << size() << endl;
    while (iter != _vRL.end()) {
        iter->print();
        iter++;
    }
    cout << endl;
}

// 转换交易列表信息为String
string RecordList::toString()
{
    string rs;
    vector<Record>::iterator iter = _vRL.begin();
    while (iter != _vRL.end()) {
        rs += iter->toString();
        iter++;
    }
    return rs;
}


void RecordList::AppendRecordFromFile(string RecordFileName)
{
    RSATool RT;
    Record rc;
    cout << "[Reaction]: Loading record from file: " << RecordFileName << "... " << endl;
    bool isright = RT.LoadRecord(RecordFileName, rc);
    if (isright) {
        AppendRecord(rc);
    }
    else {
        cout << "[Error]: Please check the record!" << endl;
    }
    
}

// 插入新记录
void RecordList::AppendRecord(Record rc)
{
    // 增加RecordList里的解密函数，采用Public Key与Sign进行解签得到字符串与明文对比，确认交易真实性
    RSATool RT;
    char* sign = &rc.cripher_text[0];
    cout << "[Reaction]: Decrypting..." << endl;
    string dps = RT.DecryptByPubkeyString(sign, rc.cripher_text.size(), rc.pub_key);
    rc.clear_text.resize(dps.size());
    cout << "[Reaction]: Verifying..." << endl;
    bool isRight = (dps == rc.clear_text);
    if (isRight) {
        rc.status = 1;
        _vRL.push_back(rc);
        cout << "[Reaction]: Successfully add new record to RL. The sign is true!" << endl;
        rc.print();
        cout << endl;
    }
    else {
        cout << "[Error]: Failing add new record. Please check the public key!" << endl;
        cout << endl;
    }
}
