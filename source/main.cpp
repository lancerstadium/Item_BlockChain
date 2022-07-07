#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include "Blockchain.h"
#include <iostream>
#include "rsa2048.h"

int main() {
    
    
    
    // �������û�
    User user1 = User("����");
    User user2 = User("��ǿ��");
    User user3 = User("����");

    // ���ɼ�¼��
    RecordList RL = RecordList();
    RecordList RL2 = RecordList();
    RecordList RL3 = RecordList();
    // ��¼����Ӽ�¼
    user1.PayTo(user2, 27.53);
    RL.AppendRecordFromFile("./public/record.txt"); // ��ȡ
    user1.PayTo(user2, 1111.1);
    RL.AppendRecordFromFile("./public/record.txt"); // ��ȡ
    user2.PayTo(user1, 618.99);
    RL.AppendRecordFromFile("./public/record.txt"); // ��ȡ
    user2.PayTo(user3, 234.1);
    RL2.AppendRecordFromFile("./public/record.txt"); // ��ȡ
    user3.PayTo(user1, 9.66);
    RL3.AppendRecordFromFile("./public/record.txt"); // ��ȡ
    user1.PayTo(user3, 9999);
    RL3.AppendRecordFromFile("./public/record.txt"); // ��ȡ

    
    // ϵͳ�Զ������Ѷ�Ϊ3��������
    Blockchain BC(3);

    // ��������
    Block b1 = Block(1, RL);
    Block b2 = Block(2, RL2);
    Block b3 = Block(3, RL3);

    // �ڿ󣬳�������������
    BC.AppendBlock(b1);
    BC.AppendBlock(b2);
    BC.AppendBlock(b3);
    // �鿴��������Ϣ
    BC.print();

    user1.info();
    user2.info();
    user3.info();

    return 0;
}