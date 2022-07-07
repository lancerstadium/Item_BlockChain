/**
* Info: class "Blockchain" with its  defination of variables and methods.
* autohr: Lu TianShuo
* Time: 2022/07/02
*
*/

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <vector>
#include "Block.h"

using namespace std;

class Blockchain {
public:

    // ���������캯��
    Blockchain();
    // ע�⣺�ѶȲ�Ҫ����̫�߲�Ȼ���Կ���ը��
    Blockchain(uint32_t nDifficulty);

    // �������
    void AppendBlock(Block bNew); 
    // ��ѯ��������С
    int size();
    // ��ӡ������
    void print();
    string toString();

private:
    // ����������
    vector<Block> _vChain;
    // �Ѷȼ���
    uint32_t _nDifficulty;

    // ȡ�������
    Block _GetLastBlock() const;
    

};


#endif //BLOCKCHAIN_H
