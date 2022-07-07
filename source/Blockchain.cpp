/**
* Info: class "Blockchain" with methods.
* autohr: Lu TianShuo
* Time: 2022/07/02
*
*/

#include "Blockchain.h"
#include <iostream>
#include <vector>

// 区块链构造函数
Blockchain::Blockchain()
{
    // 生成创世块并设定难度级别
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = 3; // 难度默认为3
}

// 注意：难度不要设置太高不然你显卡就炸了
Blockchain::Blockchain(uint32_t nDifficulty)
{
    // 可调整难度
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = nDifficulty; 
}

// 添加区块
void Blockchain::AppendBlock(Block bNew)
{
    // 链接前块哈希值
    bNew.sPrevHash = _GetLastBlock().sHash;
    bNew.MineBlock(_nDifficulty);
    _vChain.push_back(bNew);
}

// 查询区块链大小
int Blockchain::size() {
    return _vChain.size();
}

// 打印区块链
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

// 取最后区块
Block Blockchain::_GetLastBlock() const
{
    return _vChain.back();
}