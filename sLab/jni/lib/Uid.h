/*
 * Uid.h
 *
 *  Created on: 2020年5月20日
 *      Author: Administrator
 */

#ifndef JNI_LIB_UID_H_
#define JNI_LIB_UID_H_
#include <string>
namespace std {

class Uid {
public:
	Uid();
	virtual ~Uid();

	static string get_hex_string();
};

} /* namespace std */

#endif /* JNI_LIB_UID_H_ */
