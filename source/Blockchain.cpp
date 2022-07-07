/**
* Info: class "Blockchain" with methods.
* autohr: Lu TianShuo
* Time: 2022/07/02
*
*/

#include "Blockchain.h"
#include <iostream>
#include <vector>

// ���������캯��
Blockchain::Blockchain()
{
    // ���ɴ����鲢�趨�Ѷȼ���
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = 3; // �Ѷ�Ĭ��Ϊ3
}

// ע�⣺�ѶȲ�Ҫ����̫�߲�Ȼ���Կ���ը��
Blockchain::Blockchain(uint32_t nDifficulty)
{
    // �ɵ����Ѷ�
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = nDifficulty; 
}

// �������
void Blockchain::AppendBlock(Block bNew)
{
    // ����ǰ���ϣֵ
    bNew.sPrevHash = _GetLastBlock().sHash;
    bNew.MineBlock(_nDifficulty);
    _vChain.push_back(bNew);
}

// ��ѯ��������С
int Blockchain::size() {
    return _vChain.size();
}

// ��ӡ������
void Blockchain::print()
{
    vector<Block>::iterator iter = _vChain.begin();
    std::cout << std::endl;
    std::cout << "---------------------------BlockChain's infomation-----------------------------" << std::endl;
    std::cout << "[BlockChain size]: " << size() << std::endl;
    std::cout << "[BlockChain ndifficuty]: " << _nDifficulty << std::endl;
    std::cout << std::endl;
    while (iter != _vChain.end()) {
        iter->print();
        iter++;
    }
    std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

string Blockchain::toString()
{
    stringstream ss;
    vector<Block>::iterator iter = _vChain.begin();
    ss<< std::endl;
    ss << "---------------------------BlockChain's infomation-----------------------------" << std::endl;
    ss << "[BlockChain size]: " << size() << std::endl;
    ss << "[BlockChain ndifficuty]: " << _nDifficulty << std::endl;
    ss << std::endl;
    while (iter != _vChain.end()) {
        ss << iter->toString();
        iter++;
    }
    ss << "-------------------------------------------------------------------------------" << std::endl;
    return ss.str();
}

// ȡ�������
Block Blockchain::_GetLastBlock() const
{
    return _vChain.back();
}