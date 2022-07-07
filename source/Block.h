/**
* Info: class "Block" with its  defination of variables and methods.
* autohr: Lu TianShuo
* Time: 2022/07/02 
* 
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>
#include <iostream>
#include <sstream>
#include "RecordList.h"

using namespace std;

class Block {
public:
    // ��ǰ����Ĺ�ϣֵ�ַ���
    // �涨һ�������hash������ndifficulty��0��ͷ
    string sHash;   
    // ������һ����Ĺ�ϣֵ�ַ���
    string sPrevHash;
    

    // ��������
    Block(uint32_t nIndexIn, const string& info);
    Block(uint32_t nIndexIn, RecordList& RL);   
    
    // �ڿ�
    void MineBlock(uint32_t nDifficulty);   
    // ��ӡ����
    void print();
    string toString();

private:    // Use '_' to symbol private variables.

    // �����ţ�������Ψһ���
    uint32_t _nIndex;
    // ������֤����������ȡ��������ܹ������˶��ٴ�
    uint32_t _nNonce;
    // ���齻������
    string _sData;
    // ��������ʱ��
    time_t _tTime;

    // �����ϣֵ
    string _CalculateHash() const;  
};

#endif //BLOCK_H
