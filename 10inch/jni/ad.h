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

#define AD_DIR		"/mnt/extsd/ad/"
#define AD_DB		"/mnt/extsd/advertisment.db"

namespace std {

class Advertisement {
public:
	Advertisement();
	virtual ~Advertisement();
	void load();


	void set_enable_temp(bool state);
	void set_enable(bool state);
	bool get_enable();

	void set_idleTime(int time);
	int get_idleTime();

	bool add(string js);
	void remove(string fileName);
	int	getNum();
	void clear();

	std::vector<S_INFOS> dbList;

	void logDBList();
	void logFileList();

private:
	void updateList(std::vector<S_INFOS> &list);//更新dbList
	stringList syncAdFileAndDB();//如果文件不存在，从数据库中删除对应条目，如果数据库中不存在，则删除文件
	stringList getAdListFromFile();
	stringList getAdListFromDB();

	int num;

	bool enable;
	int  idleTime;


};
extern Advertisement gAdv;

} /* namespace std */

#endif /* JNI_AD_H_ */
