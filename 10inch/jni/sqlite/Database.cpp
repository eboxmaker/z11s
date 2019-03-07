/*
 * Database.cpp
 *
 *  Created on: 2018年5月27日
 *      Author: Kwolve
 */

#include "Database.h"
#include "utils/Log.h"
#include "uart/ProtocolData.h"
#include "uart/ProtocolParser.h"



bool Database::recodeResult(std::string fileName,int displayTime) {
	std::string sqltestr ="";
	char temp[10];
	sprintf(temp,"%d",displayTime);
	sqltestr += "insert into recode(fileName,displayTime) values('"+fileName+"',"+
			temp+");";

	char* errmsg;

	LOGD("sqlite exec :%s",sqltestr.c_str());
	if(pDB != NULL){
		int ret = sqlite3_exec(pDB,sqltestr.c_str(),0,0, &errmsg);
		if(ret != SQLITE_OK){
			LOGD("sqlite exec err:%s",errmsg);
			return false;
		}
	}
	return true;
}

std::vector<S_INFOS> Database::getRecodes() {
	const char* cmd = "select * from recode";
	char** result;
	int nRow;
	int nCol;
	char* errmsg;
	dbs.clear();
	dbs.empty();
	int ret = sqlite3_get_table(pDB, cmd, &result, &nRow, &nCol, &errmsg);
	if(ret != SQLITE_OK){
		LOGD("select * form recode ret:%s",errmsg);
		return dbs;
	}
	std::string strOut;
   int nIndex = nCol;
   S_INFOS info;
   for(int i=0;i<nRow;i++)
   {
	   info.fileName = result[nIndex];
	   ++nIndex;
	   info.displayTime = atoi(result[nIndex]);
	   ++nIndex;
	   dbs.push_back(info);
   }
   LOGD("read size nRow %d",nRow);
   LOGD("read size dbs.size %d",dbs.size());

	sqlite3_free_table(result);
	return dbs;
}

Database::Database(std::string path) {
	// TODO 自动生成的构造函数存根
	int ret = sqlite3_open(path.c_str(), &pDB);
	if(ret != SQLITE_OK){
		LOGD("open sqlite ret:%d",ret);
		pDB = NULL;
		return;
	}
	const char* cmd = "CREATE TABLE IF NOT EXISTS recode(fileName,displayTime);";
	char* errmsg;
	sqlite3_exec(pDB,cmd,0,0, &errmsg);
	if(ret != SQLITE_OK){
		LOGD("create table ret:%s",errmsg);
	}
}

Database::~Database() {
	// TODO 自动生成的析构函数存根
	sqlite3_free(pDB);
}
void Database::remove(std::string name) {
	std::string sqltestr ="";
	sqltestr += "DELETE FROM recode WHERE fileName = '"+name+"';";
	LOGD("sql语句：%s",sqltestr.c_str());

	char* errmsg;
	int ret = sqlite3_exec(pDB,sqltestr.c_str(),0,0, &errmsg);
	if(ret != SQLITE_OK){
		LOGD("sql语句失败:%s",errmsg);
	}
	else
	{
		LOGD("sql语句成功:%s",errmsg);
	}
}
void Database::clear() {
	const char* cmd = "DELETE  FROM recode";
	char* errmsg;
	int ret = sqlite3_exec(pDB,cmd,0,0, &errmsg);
	if(ret != SQLITE_OK){
		LOGD("create DELETE ret:%s",errmsg);
	}
}

void Database::saveas(std::string path) {
}
