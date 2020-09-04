/*
 * MyAes256.cpp
 *
 *  Created on: 2019年1月22日
 *      Author: Administrator
 */

#include "MyAes256.h"
#include <iostream>
#include <stdlib.h>
#include "utils/log.h"
#include "lib/base64.h"

AesEncryptor::AesEncryptor(string key,string iv):
	cipherMode(CBC),
	paddingMode(Zeros)
{

#if defined(AES256)
    keyLength =  key.length()>32?32:key.length();
#elif defined(AES192)
    keyLength =  key.length()>24?24:key.length();
#elif defined(AES128)
    keyLength =  key.length()>16?16:key.length();
#endif



    memset(this->key,0,keyLength);
    memset(this->iv,0,16);

	for(int i =0; i < keyLength; i++)
	{
		this->key[i] = key[i];
	}
	for(int i =0; i < iv.length(); i++)
	{
		this->iv[i] = iv[i];
	}
	LOGD("KEY:%s",this->key);
	LOGD("iv:%s",this->iv);

};
AesEncryptor::~AesEncryptor()
{

}
string  AesEncryptor::encrypt(string strInfor)
{
    int nLength = strInfor.length();
    int spaceLength = 16 - (nLength % 16);
    unsigned char* pBuffer = new unsigned char[nLength + spaceLength];
    memset(pBuffer, '\0', nLength + spaceLength);
    memcpy(pBuffer, strInfor.c_str(), nLength);

    //LOGE("需加密字符串(%d)：%s",nLength + spaceLength,strInfor.c_str());

    AES_init_ctx_iv(&ctx, (const uint8_t*)this->key, (const uint8_t*)this->iv);

    AES_CBC_encrypt_buffer(&ctx, pBuffer, nLength + spaceLength);

    // 这里需要把得到的字符数组转换成十六进制字符串
    char* pOut = new char[2 * (nLength + spaceLength)];
    memset(pOut, '\0', 2 * (nLength + spaceLength));
    Byte2Hex(pBuffer, nLength + spaceLength, pOut);

    string retValue(pOut);
    delete[] pBuffer;
    delete[] pOut;
    return retValue;

//    for(int i =0; i < plain.length(); i++)
//    {
//    	out += in[i];
//    	LOGE("i:%c",in[i]);
//    }
//    Base64::Encode(out, &result);
//	LOGE("%s",result.c_str());
//        for(int i = 0; i < encrypted_.size(); i++)
//        {
//        	char buf[20];
//        	sprintf(buf,"%02x",encrypted_[i]);
//        	enc += buf[0];
//        	enc += buf[1];
//        	enc += ' ';
//        	LOGE("%d:%02d",i,encrypted_[i]);
//
//        }
}

string  AesEncryptor::encrypt(uint8_t* key, uint8_t* in,uint32_t length)
{
//	string iv = "1234567890000000";
//    uint8_t iv_[16] ;
//    string out;
//
//    for(int i =0; i < iv.length(); i++)
//    {
//    	iv_[i] = iv[i];
//    }
//
//    struct AES_ctx ctx;
//    AES_init_ctx_iv(&ctx, (const uint8_t*)key, (const uint8_t*)iv_);
//    AES_CBC_encrypt_buffer(&ctx, in, length);
//
//    for(int i =0; i < length; i++)
//    {
//    	out += in[i];
//    }
//
//    return out;

}
string  AesEncryptor::decrypt(string strMessage)
{
    int nLength = strMessage.length() / 2;
    unsigned char* pBuffer = new unsigned char[nLength+1];
    memset(pBuffer, '\0', nLength+1);
    //LOGE("需解密字符串(%d)：%s",strMessage.length(),strMessage.c_str());
    Hex2Byte(strMessage.c_str(), strMessage.length(), pBuffer);

    AES_init_ctx_iv(&ctx, (const uint8_t*)this->key, (const uint8_t*)this->iv);
    AES_CBC_decrypt_buffer(&ctx, pBuffer, nLength);

    string retValue((char*)pBuffer);
    delete[] pBuffer;
    return retValue;
}



void AesEncryptor::Byte2Hex(const unsigned char* src, int len, char* dest) {
    for (int i=0; i<len; ++i) {
        sprintf(dest + i * 2, "%02X", src[i]);
    }
}

void AesEncryptor::Hex2Byte(const char* src, int len, unsigned char* dest) {
    int length = len / 2;
    for (int i=0; i<length; ++i) {
        dest[i] = Char2Int(src[i * 2]) * 16 + Char2Int(src[i * 2 + 1]);
    }
}

int AesEncryptor::Char2Int(char c) {
    if ('0' <= c && c <= '9') {
        return (c - '0');
    }
    else if ('a' <= c && c<= 'f') {
        return (c - 'a' + 10);
    }
    else if ('A' <= c && c<= 'F') {
        return (c - 'A' + 10);
    }
    return -1;
}
