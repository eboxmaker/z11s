/*
 * MyAes256.h
 *
 *  Created on: 2019年1月22日
 *      Author: Administrator
 */

#ifndef JNI_AES_MYAES256_H_
#define JNI_AES_MYAES256_H_

#include "iostream"
#include "aes.h"

using namespace std;

//class MyAes256: public Aes256 {
//public:
//	//MyAes256(string key):Aes256(key){};
//
//	static string  encrypt(string& key, string& plain);
//	static string  decrypt(string& key, string& encrypted);
//
//	virtual ~MyAes256();
//};


class AesEncryptor{


public:
	AesEncryptor(string key,string iv);

	 string  encrypt(string strInfor);
	 string  encrypt(uint8_t* key, uint8_t* plain,uint32_t length);
	 string  decrypt(string strMessage);

	virtual ~AesEncryptor();




public:
	enum CipherMode_t{
		CBC_,
		ECB_,
		CTR_,
	};
	enum PaddingMode_t{
        // 摘要:
        //     不填充。
        None = 1,
        //
        // 摘要:
        //     PKCS #7 填充字符串由一个字节序列组成，每个字节填充该字节序列的长度。
        PKCS7 = 2,
        //
        // 摘要:
        //     填充字符串由设置为零的字节组成。
        Zeros = 3,
        //
        // 摘要:
        //     ANSIX923 填充字符串由一个字节序列组成，此字节序列的最后一个字节填充字节序列的长度，其余字节均填充数字零。
        ANSIX923 = 4,//不支持
        //
        // 摘要:
        //     ISO10126 填充字符串由一个字节序列组成，此字节序列的最后一个字节填充字节序列的长度，其余字节填充随机数据。
        ISO10126 = 5,//不支持
	};

public:
	CipherMode_t cipherMode;
	PaddingMode_t paddingMode;

	uint8_t key[32];
	uint8_t iv[16];

    struct AES_ctx ctx;
    uint8_t keyLength;
private:
    void Byte2Hex(const unsigned char* src, int len, char* dest);
    void Hex2Byte(const char* src, int len, unsigned char* dest);
    int  Char2Int(char c);
};
#endif /* JNI_AES_MYAES256_H_ */
