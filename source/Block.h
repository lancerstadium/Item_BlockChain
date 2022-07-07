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
    // 当前区块的哈希值字符串
    // 规定一个区块的hash必须以ndifficulty个0开头
    string sHash;   
    // 链接上一区块的哈希值字符串
    string sPrevHash;
    

    // 生成区块
    Block(uint32_t nIndexIn, const string& info);
    Block(uint32_t nIndexIn, RecordList& RL);   
    
    // 挖矿
    void MineBlock(uint32_t nDifficulty);   
    // 打印区块
    void print();
    string toString();

private:    // Use '_' to symbol private variables.

    // 区块编号：该区块唯一编号
    uint32_t _nIndex;
    // 工作量证明：表明获取这个区块总共计算了多少次
    uint32_t _nNonce;
    // 区块交易数据
    string _sData;
    // 区块生成时间
    time_t _tTime;

    // 计算哈希值
    string _CalculateHash() const;  
};

#endif //BLOCK_H
