#include <iostream>
#include <fstream>
#include <direct.h>
#include <openssl/evp.h>
#include <openssl/applink.c>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "rsa2048.h"
#include "sha256.h"
#include "Blockchain.h"

using namespace std;
using boost_iarchive = boost::archive::text_iarchive;
using boost_oarchive = boost::archive::text_oarchive;

#define KEY_LENGTH  2048             // ��Կ����

// Ѱ�ҹ�Կ�ļ�λ��
string RSATool::FindPubKeyPath(string UserName)
{
	string pub_key_file2 = "./public/pubkey_" + UserName + ".pem";
	return pub_key_file2;
}

// Ѱ�Ҽ�¼�ļ�λ��
string RSATool::FindRecordPath(Record rc)
{
	return "./public/record.txt";
}

//������ʽ��д����
namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive& ar, Record& rc, const unsigned int version)
		{
			ar
				& BOOST_SERIALIZATION_NVP(rc.clear_text)
				& BOOST_SERIALIZATION_NVP(rc.cripher_text)
				& BOOST_SERIALIZATION_NVP(rc.pub_key);
		}

		template <class Archive>
		void serialize(Archive& ar, Blockchain& bc, const unsigned int version)
		{
			ar
				& BOOST_SERIALIZATION_NVP(bc.toString);
		}

	}
}


// �����¼������
string RSATool::SaveRecord(const Record& rc)
{
	string folderPath = "./public";
	if (0 != access(folderPath.c_str(), 0))
	{
		// if this folder not exist, create a new one.
		if (mkdir(folderPath.c_str()) == 0) { // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
			cout << "[Reaction]: Directory successfully created." << endl;
		}
		else {
			cout << "[Error]: Directory can't created." << endl;
		}
	}
	// �����ɼ�¼RecordӦ�����ļ�����ʽ������ļ� ./public/new_records.txt
	// Ps: ������ʽӦ��Ϊ��"[Record](���׼�¼������); [Sign](ǩ��������); [Public Key](��Կ); "
	ofstream fout(FindRecordPath(rc));
	if (!fout) {
		cout << "[Error]: Can't write the file!" << endl;
	}
	else {
		// ���record���󵽴����ļ�
		boost_oarchive oa(fout);
		oa << BOOST_SERIALIZATION_NVP(rc);
		
		if (rc.status == 0) {
			cout << "[Reaction]: Successfully write record to the file!" << endl;
		}
		else {
			cout << "[Error]: Please check the record!" << endl;
		}
		fout.close();
		
	}
	cout << endl;

	return FindRecordPath(rc);
}

// ��ȡ��������
bool RSATool::LoadRecord(string RecordName, Record& rc)
{
	int count = 0;//���׼�¼����
	ifstream fin(RecordName);
	if (!fin) {
		cout << "[Error]: Can't read the file!" << endl;
		return false;
	}
	else {
		boost_iarchive ia(fin);
		ia >> BOOST_SERIALIZATION_NVP(rc);
		rc.recovery();
		fin.close();
		cout << "[Reaction]: Successfully read record list from the file!" << endl;
	}
	cout << endl;
	return true;
}

// ������Կ��
void RSATool::GenerateRSAkey(string& sRSAPubKey, string& sRSAPriKey, string UserName, string& pub_key_path, string &Wallet)
{

	size_t pri_len = 0; // ˽Կ����
	size_t pub_len = 0; // ��Կ����
	char* pri_key = nullptr; // ˽Կ
	char* pub_key = nullptr; // ��Կ

	// ����Ǯ��
	Wallet = sha256(UserName + to_string(rand()));
	Wallet.resize(16);

	// ������Կ��
	RSA* keypair = RSA_generate_key(KEY_LENGTH, RSA_3, NULL, NULL);

	BIO* pri = BIO_new(BIO_s_mem());
	BIO* pub = BIO_new(BIO_s_mem());

	// ����˽Կ
	PEM_write_bio_RSAPrivateKey(pri, keypair, NULL, NULL, 0, NULL, NULL);
	// ע��------���ɵ�1�ָ�ʽ�Ĺ�Կ
	//PEM_write_bio_RSAPublicKey(pub, keypair);
	// ע��------���ɵ�2�ָ�ʽ�Ĺ�Կ���˴�������ʹ�����֣�
	PEM_write_bio_RSA_PUBKEY(pub, keypair);

	// ��ȡ����  
	pri_len = BIO_pending(pri);
	pub_len = BIO_pending(pub);

	// ��Կ�Զ�ȡ���ַ���  
	pri_key = (char*)malloc(pri_len + 1);
	pub_key = (char*)malloc(pub_len + 1);

	BIO_read(pri, pri_key, pri_len);
	BIO_read(pub, pub_key, pub_len);

	pri_key[pri_len] = '\0';
	pub_key[pub_len] = '\0';

	sRSAPubKey = pub_key;
	sRSAPriKey = pri_key;
	string folderPath = "./public";
	if (0 != access(folderPath.c_str(), 0))
	{
		// if this folder not exist, create a new one.
		if (mkdir(folderPath.c_str()) == 0) { // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
			cout << "[Reaction]: Directory successfully created." << endl;
		}
		else {
			cout << "[Error]: Directory can't created." << endl;
		}
	}

	folderPath = "./" + UserName;
	if (0 != access(folderPath.c_str(), 0))
	{
		// if this folder not exist, create a new one.
		if (mkdir(folderPath.c_str()) == 0) { // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
			cout << "[Reaction]: Directory successfully created." << endl;
		}
		else {
			cout << "[Error]: Directory can't created." << endl;
		}
	}
	// ����Կд���ļ�
	string pub_key_file = "./" + UserName + "/pubkey.pem";
	std::ofstream pub_file(pub_key_file, std::ios::out);
	if (!pub_file.is_open())
	{
		perror("[Reaction]: pub key file open fail:");
		return;
	}
	pub_file << pub_key;
	pub_key_path = pub_key_file;
	pub_file.close();

	string pub_key_file2 = FindPubKeyPath(UserName);
	std::ofstream pub_file2(pub_key_file2, std::ios::out);
	if (!pub_file2.is_open())
	{
		perror("[Reaction]: pub key file open fail:");
		return;
	}
	pub_file2 << pub_key;
	pub_file2.close();

	// ��˽Կд���ļ�
	string pri_key_file = "./" + UserName + "/prikey.pem";
	std::ofstream pri_file(pri_key_file, std::ios::out);
	if (!pri_file.is_open())
	{
		perror("[Reaction]: pri key file open fail:");
		return;
	}
	pri_file << pri_key;
	pri_file.close();

	// �ͷ��ڴ�
	RSA_free(keypair);
	BIO_free_all(pub);
	BIO_free_all(pri);

	free(pri_key);
	free(pub_key);

}


// ͨ��˽Կ�ļ�����
std::vector<char> RSATool::EncryptByPrikeyFile(const std::string& message,
	const std::string& pri_file) {
	BIO* in = BIO_new(BIO_s_file());
	if (in == NULL) {
		std::cout << "BIO_new failed" << std::endl;
		return std::vector<char>();
	}
	BIO_read_filename(in, pri_file.c_str());

	RSA* rsa = PEM_read_bio_RSAPrivateKey(in, NULL, NULL, NULL);
	BIO_free(in);
	if (rsa == NULL) {
		std::cout << "PEM_read_bio_RSAPrivateKey failed" << std::endl;
		return std::vector<char>();
	}
	int size = RSA_size(rsa);
	std::vector<char> encrypt_data;
	encrypt_data.resize(size);
	int ret = RSA_private_encrypt(
		message.length(), (unsigned char*)message.c_str(),
		(unsigned char*)encrypt_data.data(), rsa, RSA_PKCS1_PADDING);
	RSA_free(rsa);
	if (ret == -1) {
		std::cout << "RSA_private_encrypt failed" << std::endl;
		return std::vector<char>();
	}
	return encrypt_data;
}

// ͨ����Կ�ļ�����
std::string RSATool::DecryptByPubkeyFile(char* cipher, uint32_t len,
	const std::string& pub_filename) {
	BIO* in = BIO_new(BIO_s_file());
	if (in == NULL) {
		std::cout << "BIO_new failed" << std::endl;
		return "";
	}
	BIO_read_filename(in, pub_filename.c_str());

	RSA* rsa = PEM_read_bio_RSA_PUBKEY(in, NULL, NULL, NULL);
	BIO_free(in);
	if (rsa == NULL) {
		std::cout << "PEM_read_bio_RSA_PUBKEY failed" << std::endl;
		return "";
	}

	int size = RSA_size(rsa);
	std::vector<char> data;
	data.resize(size);
	int ret =
		RSA_public_decrypt(len, (unsigned char*)cipher,
			(unsigned char*)data.data(), rsa, RSA_PKCS1_PADDING);
	RSA_free(rsa);
	if (ret == -1) {
		std::cout << "RSA_public_decrypt failed" << std::endl;
		return "";
	}
	std::string decrypt_data(data.begin(), data.end());
	return decrypt_data;
}


// ͨ��˽Կ�ַ�������
std::vector<char> RSATool::EncryptByPrikeyString(const std::string& message,
	const std::string& prikey) {
	BIO* in = BIO_new_mem_buf((void*)prikey.c_str(), -1);
	if (in == NULL) {
		std::cout << "BIO_new_mem_buf failed" << std::endl;
		return std::vector<char>();
	}

	RSA* rsa = PEM_read_bio_RSAPrivateKey(in, NULL, NULL, NULL);
	BIO_free(in);
	if (rsa == NULL) {
		std::cout << "PEM_read_bio_RSAPrivateKey failed" << std::endl;
		return std::vector<char>();
	}

	int size = RSA_size(rsa);
	std::vector<char> encrypt_data;
	encrypt_data.resize(size);
	int ret = RSA_private_encrypt(
		message.length(), (unsigned char*)message.c_str(),
		(unsigned char*)encrypt_data.data(), rsa, RSA_PKCS1_PADDING);
	RSA_free(rsa);
	if (ret == -1) {
		std::cout << "RSA_private_encrypt failed" << std::endl;
		return std::vector<char>();
	}

	return encrypt_data;
}

// ͨ����Կ�ַ�������
std::string RSATool::DecryptByPubkeyString(char* cipher, uint32_t len,
	const std::string& pubkey) {
	BIO* in = BIO_new_mem_buf((void*)pubkey.c_str(), -1);
	if (in == NULL) {
		std::cout << "BIO_new_mem_buf failed" << std::endl;
		return "";
	}

	RSA* rsa = PEM_read_bio_RSA_PUBKEY(in, NULL, NULL, NULL);
	BIO_free(in);
	if (rsa == NULL) {
		std::cout << "PEM_read_bio_RSA_PUBKEY failed" << std::endl;
		return "";
	}

	int size = RSA_size(rsa);
	std::vector<char> data;
	data.resize(size);
	int ret =
		RSA_public_decrypt(len, (unsigned char*)cipher,
			(unsigned char*)data.data(), rsa, RSA_PKCS1_PADDING);
	RSA_free(rsa);
	if (ret == -1) {
		std::cout << "RSA_public_decrypt failed" << std::endl;
		return "";
	}
	std::string decrypt_data(data.begin(), data.end());
	return decrypt_data;
}



// ͨ��˽Կ�ļ�����ǩ��
std::vector<char> RSATool::GenerateRsaSignByFile(const std::string& message,
	const std::string& pri_filename) {
	OpenSSL_add_all_algorithms();
	BIO* in = BIO_new(BIO_s_file());
	if (in == NULL) {
		std::cout << "BIO_new failed" << std::endl;
		return std::vector<char>();
	}
	BIO_read_filename(in, pri_filename.c_str());
	RSA* rsa = PEM_read_bio_RSAPrivateKey(in, NULL, NULL, NULL);
	BIO_free(in);

	if (rsa == NULL) {
		std::cout << "PEM_read_bio_RSAPrivateKey failed" << std::endl;
		return std::vector<char>();
	}
	unsigned int size = RSA_size(rsa);
	std::vector<char> sign;
	sign.resize(size);

	int ret =
		RSA_sign(NID_md5, (const unsigned char*)message.c_str(),
			message.length(), (unsigned char*)sign.data(), &size, rsa);
	RSA_free(rsa);
	if (ret != 1) {
		std::cout << "RSA_sign failed" << std::endl;
		return std::vector<char>();
	}
	return sign;
}

// ͨ����Կ�ļ���֤ǩ��
bool RSATool::VerifyRsaSignByFile(char* sign, uint32_t sign_len,
	const std::string& pub_filename,
	const std::string& verify_str) {
	OpenSSL_add_all_algorithms();
	BIO* in = BIO_new(BIO_s_file());
	if (in == NULL) {
		std::cout << "BIO_new failed" << std::endl;
		return false;
	}

	BIO_read_filename(in, pub_filename.c_str());

	RSA* rsa = PEM_read_bio_RSA_PUBKEY(in, NULL, NULL, NULL);

	if (rsa == NULL) {
		std::cout << "PEM_read_bio_RSA_PUBKEY failed" << std::endl;
		return false;
	}
	BIO_free(in);

	int ret =
		RSA_verify(NID_md5, (const unsigned char*)verify_str.c_str(),
			verify_str.length(), (unsigned char*)sign, sign_len, rsa);
	RSA_free(rsa);
	if (ret != 1) {
		std::cout << "RSA_verify failed" << std::endl;
		return false;
	}
	return true;
}



// ͨ��˽Կ�ַ�������ǩ��
std::vector<char> RSATool::GenerateRsaSignByString(const std::string& message,
	const std::string& prikey) {
	OpenSSL_add_all_algorithms();
	BIO* in = BIO_new_mem_buf((void*)prikey.c_str(), -1);
	if (in == NULL) {
		std::cout << "BIO_new_mem_buf failed" << std::endl;
		return std::vector<char>();
	}

	RSA* rsa = PEM_read_bio_RSAPrivateKey(in, NULL, NULL, NULL);
	BIO_free(in);

	if (rsa == NULL) {
		std::cout << "PEM_read_bio_RSAPrivateKey failed" << std::endl;
		return std::vector<char>();
	}
	unsigned int size = RSA_size(rsa);
	std::vector<char> sign;
	sign.resize(size);

	int ret =
		RSA_sign(NID_md5, (const unsigned char*)message.c_str(),
			message.length(), (unsigned char*)sign.data(), &size, rsa);
	RSA_free(rsa);
	if (ret != 1) {
		std::cout << "RSA_sign failed" << std::endl;
		return std::vector<char>();
	}
	return sign;
}

// ͨ����Կ�ַ�����֤ǩ��
bool RSATool::VerifyRsaSignByString(char* sign, uint32_t sign_len,
	const std::string& pubkey,
	const std::string& verify_str) {
	BIO* in = BIO_new_mem_buf((void*)pubkey.c_str(), -1);
	if (in == NULL) {
		std::cout << "BIO_new_mem_buf failed" << std::endl;
		return false;
	}

	RSA* rsa = PEM_read_bio_RSA_PUBKEY(in, NULL, NULL, NULL);
	BIO_free(in);

	if (rsa == NULL) {
		std::cout << "PEM_read_bio_RSA_PUBKEY failed" << std::endl;
		return false;
	}

	int ret =
		RSA_verify(NID_md5, (const unsigned char*)verify_str.c_str(),
			verify_str.length(), (unsigned char*)sign, sign_len, rsa);
	RSA_free(rsa);
	if (ret != 1) {
		std::cout << "RSA_verify failed" << std::endl;
		return false;
	}
	return true;
}

