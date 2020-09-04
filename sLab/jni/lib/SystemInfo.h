/*
 * SystemInfo.h
 *
 *  Created on: 2020年4月11日
 *      Author: Administrator
 */

#ifndef JNI_LIB_SYSTEMINFO_H_
#define JNI_LIB_SYSTEMINFO_H_
#include <string>

namespace std {

class SystemInfo {
public:
	SystemInfo();
	virtual ~SystemInfo();

	float  mem_usage();

};
extern SystemInfo systemInfo;

} /* namespace std */

#endif /* JNI_LIB_SYSTEMINFO_H_ */
