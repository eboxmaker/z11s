/*
 * ad.cpp
 *
 *  Created on: 2019年3月7日
 *      Author: shentq
 */

#include "ad.h"
#include "json_test.h"
#include <fstream>
#include "base64.h"
#include <dirent.h>
#include <unistd.h>
#include "readdir.h"

namespace std {

Advertisement gAdv;

Advertisement::Advertisement() {
	// TODO 自动生成的构造函数存根

}

Advertisement::~Advertisement() {
	// TODO 自动生成的析构函数存根
}
//#define AD_DIR		"/mnt/extsd/ad/"

bool Advertisement::add(string js)
{
	Json::Reader reader;
	Json::Value root;
	string fileName;
	int displayTime;
	bool ret;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		fileName = root["name"].asString();  // 访问节点，upload_id = "UP000000"
		displayTime = root["displayTime"].asInt();    // 访问节点，code = 100
	}
	else
	{
		return false;
	}
	for(int i = 0; i < list.size(); i++)
	{
		if(fileName == list[i].fileName)
			dbAdv.remove(fileName);
	}
	ret =  dbAdv.recodeResult(fileName, displayTime);
	//updateFileList();
	updateRecode();
	return ret;
}

void Advertisement::remove(string fileName)
{
	string fileFullName = AD_DIR + fileName;
	dbAdv.remove(fileName);
	if(is_access(fileFullName))
	{
		rm_file(fileFullName);
	}
	else
	{
		LOGD("文件不存在");
	}
	updateRecode();
	//updateFileList();
}
void Advertisement::updateRecode()
{
	list.clear();
	list = dbAdv.getRecodes();
	for(int i = 0; i < list.size(); i++)
	{
		list[i].fullName = AD_DIR + list[i].fileName;
		LOGD("列表：%s",list[i].fullName.c_str());
	}
}

void Advertisement::updateFileList()
{

//
//    DIR    *dir;
//    struct    dirent    *ptr;
//    dir = opendir(AD_DIR); ///open the dir
//
//    list.clear();
//    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
//    {
//        string fullNmae = AD_DIR;
//    	if(ptr->d_type == 8)
//    	{
//    		fullNmae += ptr->d_name;
//    		list.push_back(fullNmae.c_str());
//    	}
//
//    	LOGE("d_type:%d d_name: %s\n", ptr->d_type,ptr->d_name);
//    }
//    closedir(dir);
//    return ;
}

bool Advertisement::checkFileAndDB()
{
//	updateFileList();
//	LOGD("DB文件数量：%d",dbs.size());
//	for(int i = 0; i < dbs.size();i++)
//	{
//    	LOGD("name = %s,value = %d",dbs[i].fileName.c_str(),dbs[i].displayTime);
//
//	}
//	LOGD("LIST文件数量：%d",list.size());
//	for(int i = 0; i < list.size();i++)
//	{
//    	LOGD("name = %s",list[i].c_str());
//	}
}

} /* namespace std */
