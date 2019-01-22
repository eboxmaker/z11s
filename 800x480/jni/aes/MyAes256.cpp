/*
 * MyAes256.cpp
 *
 *  Created on: 2019年1月22日
 *      Author: Administrator
 */

#include "MyAes256.h"
#include <iostream>
#include <stdlib.h>



//
//MyAes256::MyAes256() {
//	// TODO 自动生成的构造函数存根
//
//}

MyAes256::~MyAes256() {
	// TODO 自动生成的析构函数存根
}


string MyAes256::encrypt(string& key, string& plain)
{
    ByteArray key_;
    ByteArray plain_;
    ByteArray encrypted_;
    string enc;
    for(int i = 0; i < key.size(); i++)
    {
    	key_.push_back(key.c_str()[i]);
    }
    for(int i = 0; i < plain.size(); i++)
    {
    	plain_.push_back(plain.c_str()[i]);
    }


    Aes256 aes(key_);


    aes.encrypt_start(plain_.size(), encrypted_);
    aes.encrypt_continue(plain_, encrypted_);
    aes.encrypt_end(encrypted_);

    for(int i = 0; i < encrypted_.size(); i++)
    {
    	enc += encrypted_[i];
    }
    return enc;
}


string MyAes256::decrypt(string& key, string& encrypted)
{
    ByteArray key_;
    ByteArray encrypted_;
    ByteArray plain_;

    string plain;


    for(int i = 0; i < key.size(); i++)
    {
    	key_.push_back(key.c_str()[i]);
    }
    for(int i = 0; i < encrypted.size(); i++)
    {
    	encrypted_.push_back(encrypted.c_str()[i]);
    }



    Aes256 aes(key_);

    aes.decrypt_start(encrypted_.size());
    aes.decrypt_continue(encrypted_, plain_);
    aes.decrypt_end(plain_);
    for(int i = 0; i < plain_.size(); i++)
    {
    	plain += plain_[i];
    }
    return plain;

}
