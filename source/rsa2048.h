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

	// 通过私钥文件加密
	std::vector<char> EncryptByPrikeyFile(const std::string& message, const std::string& pri_file);

	// 通过公钥文件解密
	std::string DecryptByPubkeyFile(char* cipher, uint32_t len, const std::string& pub_filename);

	// 通过私钥字符串加密
	std::vector<char> EncryptByPrikeyString(const std::string& message, const std::string& prikey);

	// 通过公钥字符串解密
	std::string DecryptByPubkeyString(char* cipher, uint32_t len, const std::string& pubkey);

	// 通过私钥文件生成签名
	std::vector<char> GenerateRsaSignByFile(const std::string& message, const std::string& pri_filename);

	// 通过公钥文件验证签名
	bool VerifyRsaSignByFile(char* sign, uint32_t sign_len, const std::string& pub_filename, const std::string& verify_str);

	// 通过私钥字符串生成签名
	std::vector<char> GenerateRsaSignByString(const std::string& message, const std::string& prikey);

	// 通过公钥字符串验证签名
	bool VerifyRsaSignByString(char* sign, uint32_t sign_len, const std::string& pubkey, const std::string& verify_str);



};

#endif

