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

    // 区块链构造函数
    Blockchain();
    // 注意：难度不要设置太高不然你显卡就炸了
    Blockchain(uint32_t nDifficulty);

    // 添加区块
    void AppendBlock(Block bNew); 
    // 查询区块链大小
    int size();
    // 打印区块链
    void print();
    string toString();

private:
    // 区块链数据
    vector<Block> _vChain;
    // 难度级别
    uint32_t _nDifficulty;

    // 取最后区块
    Block _GetLastBlock() const;
    

};


#endif //BLOCKCHAIN_H
