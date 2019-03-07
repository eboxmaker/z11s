/*
 * ad.h
 *
 *  Created on: 2019年3月7日
 *      Author: shentq
 */

#ifndef JNI_AD_H_
#define JNI_AD_H_

#include "objecttype.h"
#include <iostream>
#include "sqlite/database.h"

namespace std {

class Advertisement {
public:
	Advertisement();
	virtual ~Advertisement();
	bool add(string js);
	void remove(string fileName);
	void updateFileList();
	void getRecorder();
	bool checkFileAndDB();
	bool enable;
	int  idleTime;
	stringList list;
	std::vector<S_INFOS> dbs;

};
extern Advertisement gAdv;

} /* namespace std */

#endif /* JNI_AD_H_ */
