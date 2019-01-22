/*
 * MyAes256.h
 *
 *  Created on: 2019年1月22日
 *      Author: Administrator
 */

#ifndef JNI_AES_MYAES256_H_
#define JNI_AES_MYAES256_H_

#include "aes256.hpp"
#include "iostream"

using namespace std;

class MyAes256: public Aes256 {
public:
	//MyAes256(string key):Aes256(key){};

	static string  encrypt(string& key, string& plain);
	static string  decrypt(string& key, string& encrypted);

	virtual ~MyAes256();
};
#endif /* JNI_AES_MYAES256_H_ */
