#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include "Blockchain.h"
#include <iostream>
#include "rsa2048.h"

int main() {
    
    
    
    // 生成新用户
    User user1 = User("马云");
    User user2 = User("刘强东");
    User user3 = User("马化腾");

    // 生成记录表
    RecordList RL = RecordList();
    RecordList RL2 = RecordList();
    RecordList RL3 = RecordList();
    // 记录表添加记录
    user1.PayTo(user2, 27.53);
    RL.AppendRecordFromFile("./public/record.txt"); // 读取
    user1.PayTo(user2, 1111.1);
    RL.AppendRecordFromFile("./public/record.txt"); // 读取
    user2.PayTo(user1, 618.99);
    RL.AppendRecordFromFile("./public/record.txt"); // 读取
    user2.PayTo(user3, 234.1);
    RL2.AppendRecordFromFile("./public/record.txt"); // 读取
    user3.PayTo(user1, 9.66);
    RL3.AppendRecordFromFile("./public/record.txt"); // 读取
    user1.PayTo(user3, 9999);
    RL3.AppendRecordFromFile("./public/record.txt"); // 读取

    
    // 系统自动生成难度为3的区块链
    Blockchain BC(3);

    // 生成区块
    Block b1 = Block(1, RL);
    Block b2 = Block(2, RL2);
    Block b3 = Block(3, RL3);

    // 挖矿，尝试连入区块链
    BC.AppendBlock(b1);
    BC.AppendBlock(b2);
    BC.AppendBlock(b3);
    // 查看区块链信息
    BC.print();

    user1.info();
    user2.info();
    user3.info();

    return 0;
}