/*
 * AesEncoder.cpp
 *
 *  Created on: 2019年1月22日
 *      Author: Administrator
 */

#include "AesEncoder.h"
#include "json_test.h"
#include "lib/itoa.h"
#include "globalVar.h"
#include   <iostream>
#include "base64.h"

#include "security/SecurityManager.h"

#include "readdir.h"

#define KEY_LEN    32
#define TEXT_SIZE 100
#define ENC_SIZE  113


static string key =  "12345678900000001234567890000000";

AesEncoder::AesEncoder() {
	// TODO 自动生成的构造函数存根

}

AesEncoder::~AesEncoder() {
	// TODO 自动生成的析构函数存根
}

string AesEncoder::pack(string& data)
{
	string str;

	str = MyAes256::encrypt(key, data);
	Json::Value root;
	root["data"] = Json::Value(str);
	Json::FastWriter fw;
	string temp =  fw.write(root);
	LOGE("%s",temp.c_str());
	return temp;

}

string AesEncoder::pack(char* data)
{
	string str;
	string data_ = data;
	str = MyAes256::encrypt(key, data_);
	MD5 md5(str);
	Json::Value root;
	root["sign"] = Json::Value(md5.toStr());
	root["data"] = Json::Value(str);
	Json::FastWriter fw;
	string temp =  fw.write(root);
	LOGE("%s",temp.c_str());
	return temp;

}
bool AesEncoder::unPack(string& js,string& msg)
{
	  Json::Reader reader;
	  Json::Value root;

	  JsonStatus_t status;
	  string temp;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  temp = root["data"].asString();
		  msg = MyAes256::decrypt(key, temp);
		  return true;
	  }
	  return false;
}

string AesEncoder::unPack(char* data,string& msg)
{

}

AesEncoder packager;




