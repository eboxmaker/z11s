/*
 * Database.h
 *
 *  Created on: 2018年5月27日
 *      Author: Kwolve
 */

#ifndef JNI_DB_DATABASE_H_
#define JNI_DB_DATABASE_H_

#include <vector>
#include <string>
#include "sqlite3.h"

typedef struct{
	std::string fileName;
	std::string fullName;
	int displayTime;
}S_INFOS;


class Database {
public:
	Database(std::string path);
	virtual ~Database();
	bool recodeResult(std::string fileName,int dispTime);
	std::vector<S_INFOS> getRecodes();
	void clear();
	void remove(std::string fileName);
	void saveas(std::string path);
private:
	sqlite3* pDB;
	std::vector<S_INFOS> dbs;
};

#endif /* JNI_DB_DATABASE_H_ */
