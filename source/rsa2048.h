#pragma   once 
#ifndef RSA2048_H
#define RSA2048_H

#include "Record.h"
#include <iostream>

class RSATool {


public:
	string FindPubKeyPath(string UserName);

	string FindRecordPath(Record rc);

	string SaveRecord(const Record& rc);

	bool LoadRecord(string RecordName, Record& rc);

	void GenerateRSAkey(string& sRSAPubKey, string& sRSAPriKey, string UserName, string& pub_key_path, string& Wallet);

	// ͨ��˽Կ�ļ�����
	std::vector<char> EncryptByPrikeyFile(const std::string& message, const std::string& pri_file);

	// ͨ����Կ�ļ�����
	std::string DecryptByPubkeyFile(char* cipher, uint32_t len, const std::string& pub_filename);

	// ͨ��˽Կ�ַ�������
	std::vector<char> EncryptByPrikeyString(const std::string& message, const std::string& prikey);

	// ͨ����Կ�ַ�������
	std::string DecryptByPubkeyString(char* cipher, uint32_t len, const std::string& pubkey);

	// ͨ��˽Կ�ļ�����ǩ��
	std::vector<char> GenerateRsaSignByFile(const std::string& message, const std::string& pri_filename);

	// ͨ����Կ�ļ���֤ǩ��
	bool VerifyRsaSignByFile(char* sign, uint32_t sign_len, const std::string& pub_filename, const std::string& verify_str);

	// ͨ��˽Կ�ַ�������ǩ��
	std::vector<char> GenerateRsaSignByString(const std::string& message, const std::string& prikey);

	// ͨ����Կ�ַ�����֤ǩ��
	bool VerifyRsaSignByString(char* sign, uint32_t sign_len, const std::string& pubkey, const std::string& verify_str);



};

#endif

