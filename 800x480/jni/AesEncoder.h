/*
 * AesEncoder.h
 *
 *  Created on: 2019年1月22日
 *      Author: Administrator
 */

#ifndef JNI_AESENCODER_H_
#define JNI_AESENCODER_H_
#include "json/json.h"
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "ringbuf.h"
#include "aes/myaes256.h"
#include "md5/md5.h"

class AesEncoder {
public:
	AesEncoder();
	virtual ~AesEncoder();

	string pack(string& data);
	string pack(char* data);
	bool unPack(string& js,string& msg);
	string unPack(char* js,string& msg);

};
extern AesEncoder packager;

#endif /* JNI_AESENCODER_H_ */
