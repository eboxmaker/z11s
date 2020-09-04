/*
 * Uid.cpp
 *
 *  Created on: 2020年5月20日
 *      Author: Administrator
 */

#include "Uid.h"
//#include "stddef.h"
#include "security/securityManager.h"
#include "lib/itoa.h"
namespace std {

Uid::Uid() {
	// TODO 自动生成的构造函数存根

}

Uid::~Uid() {
	// TODO 自动生成的析构函数存根
}
string Uid::get_hex_string()
{
	typedef union
	{
		unsigned long long value;
		unsigned char bytes[8];
	}XdataULong_t;

	XdataULong_t id;
	unsigned char buf1[32];
	char buf2[32];

	bool ret = SECURITYMANAGER->getDevID(buf1);
//	for(int i = 0; i < 8; i++)
//	{
//        sprintf(buf2 + i * 2, "%02X", buf1[i]);
//	}

    sprintf(buf2 + 0 * 2, "%02X", buf1[6]);
    sprintf(buf2 + 1 * 2, "%02X", buf1[7]);
    sprintf(buf2 + 2 * 2, "%02X", buf1[4]);
    sprintf(buf2 + 3 * 2, "%02X", buf1[5]);
    sprintf(buf2 + 4 * 2, "%02X", buf1[2]);
    sprintf(buf2 + 5 * 2, "%02X", buf1[3]);
    sprintf(buf2 + 6 * 2, "%02X", buf1[0]);
    sprintf(buf2 + 7 * 2, "%02X", buf1[1]);

    string str = buf2;
	return str;
}


} /* namespace std */
