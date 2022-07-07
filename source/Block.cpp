/**
* Info: class "Block" with methods.
* autohr: Lu TianShuo
* Time: 2022/07/02
*
*/

#include "Block.h"
#include "sha256.h"



using namespace std;


// ��������
Block::Block(uint32_t nIndexIn, const string& info) : _nIndex(nIndexIn), _sData(info)
{
    _nNonce = 0;
    _tTime = time(nullptr);
    sHash = _CalculateHash();
}


Block::Block(uint32_t nIndexIn, RecordList& RL) : _nIndex(nIndexIn)
{
    _nNonce = 0;
    _tTime = time(nullptr);
    _sData = RL.toString();
    sHash = _CalculateHash();
}

// �ڿ�
void Block::MineBlock(uint32_t nDifficulty)
{
    // ��ʼ�ڿ��Ѷ�ϵ��Ϊ��nDifficulty
    cout << "[Reaction]: Mining block " << _nIndex << " ..." << endl;
    // 1.��̬����һ��char�Ŀռ䲢��ʼ��Ϊ0
    char* cstr = new char[nDifficulty + 1];
    for (uint32_t i = 0; i < nDifficulty; ++i)
    {
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\0';

    string str(cstr);

    // 2.����ϣ��ǰ����մ��������ַ������бȽ�,ֱ���ҵ�ƥ����
    do
    {
        _nNonce++;
        sHash = _CalculateHash();
    } while (sHash.substr(0, nDifficulty) != str);

    // 3.һ���ҵ�ƥ��������һ����Ϣ��˵���ÿ��ѳɹ�����
    cout << "[Reaction]: Block mined: " << sHash << endl;
}

// ��ӡ����
void Block::print() {
    std::cout << "[Block ID]: " << _nIndex << std::endl;
    std::cout << "[Block sHash]: " << sHash << std::endl;
    std::cout << "[Transaction records]:" << std::endl;
    std::cout << _sData << endl;
    std::cout << std::endl;
}

string Block::toString() {
    stringstream ss;
    ss << "[Block ID]: " << _nIndex << std::endl;
    ss << "[Block sHash]: " << sHash << std::endl;
    ss << "[Transaction records]:" << std::endl;
    ss << _sData << endl;
    ss << std::endl;
    return ss.str();
}

// �����ϣֵ
inline string Block::_CalculateHash() const
{
    stringstream ss;
    ss << _nIndex << sPrevHash << _tTime << _sData << _nNonce;

    return sha256(ss.str());
}

