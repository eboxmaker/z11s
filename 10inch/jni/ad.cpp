/*
 * ad.cpp
 *
 *  Created on: 2019年3月7日
 *      Author: shentq
 */
#include "storage/StoragePreferences.h"
#include "utils/log.h"
#include "json/json.h"
#include "base64.h"
#include "readdir.h"

#include "ad.h"


Database dbAdv(AD_DB);

namespace std {

Advertisement gAdv;

Advertisement::Advertisement() {
	// TODO 自动生成的构造函数存根


}

Advertisement::~Advertisement() {
	// TODO 自动生成的析构函数存根
}
//#define AD_DIR		"/mnt/extsd/ad/"
void Advertisement::load(){

    //从系统变量存储区更新广告使能设置
    gAdv.idleTime = StoragePreferences::getInt("gAdv.idleTime", 20);
    gAdv.enable = StoragePreferences::getBool("gAdv.enable", true);
    //从数据库中更新广告信息
    updateList(dbList);

}

bool Advertisement::add(string js)
{
	Json::Reader reader;
	Json::Value root;
	string fileName = "";
	string fullName = "";
	int displayTime;
	bool ret;
	string dataout = "";
	unsigned long length;
	JsonStatus_t status;

	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		fileName = root["name"].asString();  // 访问节点，upload_id = "UP000000"
		displayTime = root["displayTime"].asInt();    // 访问节点，code = 100
		length = root["dataLength"].asLargestUInt();


		if(length != root["data"].asString().length())
		{
			LOGE("接收长度不匹配");
			return false;
		}
		fullName = AD_DIR ;
		fullName +=  fileName;
		Base64::Decode(root["data"].asString(), &dataout);
		if(creat_file(fullName,dataout.c_str(),dataout.size()) == false)
			return false;
	}
	else
	{
		return false;
	}
	ret =  dbAdv.recodeResult(fileName, displayTime);


	updateList(dbList);
	return ret;
}

void Advertisement::remove(string fileName)
{
	string fileFullName = AD_DIR + fileName;
	dbAdv.remove(fileName);
	rm_file(fileFullName);

	updateList(dbList);
	//updateFileList();
}
int	Advertisement::getNum(){
	return num;
}

void Advertisement::clear()
{
	string cmd  = "";
	cmd += "rm ";
	cmd += AD_DIR;
	cmd += "*";
	dbAdv.clear();
	int err = system(cmd.c_str());
	updateList(dbList);

}

void Advertisement::logDBList(){

	std::vector<S_INFOS> list;

	list = dbAdv.getRecodes();

	LOGD("打印数据库列表");
	for(int i = 0; i < list.size(); i++)
	{
		LOGD("%s    %d",list[i].fileName.c_str(),list[i].displayTime);
	}
}
void Advertisement::logFileList(){

	stringList str = getAdListFromFile();
	LOGD("打印文件列表");
	for(int i = 0; i < str.size(); i++)
	{
		LOGD("%s",str[i].c_str());
	}
}


void Advertisement::updateList(std::vector<S_INFOS> &list)
{
	syncAdFileAndDB();
	list.clear();
	list = dbAdv.getRecodes();
	num = list.size();
	for(int i = 0; i < list.size(); i++)
	{
		list[i].fullName = AD_DIR + list[i].fileName;
	}
}


stringList Advertisement::syncAdFileAndDB()//如果文件不存在，从数据库中删除对应条目，如果数据库中不存在，则删除文件
{
	stringList dbFileList,DirFileList;
	dbFileList = getAdListFromDB();
	DirFileList = getAdListFromFile();
	int ret = -1;

	//遍历所有数据库条目，如果查找到有丢失文件的条目，则删除
	for(int i = 0; i < dbFileList.size(); i++)//检查数据库中所有条目
	{
		ret = -1;
		for(int j = 0; j < DirFileList.size(); j++){//查找是否有对应的文件
			if(dbFileList[i] == DirFileList[j])//如果存在，则此条目正常，不需要从数据库中删除
				ret = 0;
		}
		if(ret == 0){//从目录中找到了对应的文件

		}
		else{//不存在，则从数据库中删除此条目
			dbAdv.remove(dbFileList[i]);//从数据库中删除
			LOGE("删除一条数据库：%s",dbFileList[i].c_str());
		}
	}
	//遍历所有文件，删除多余文件
	for(int i = 0; i < DirFileList.size(); i++)//检查文件夹中所有条目
	{
		ret = -1;
		for(int j = 0; j < dbFileList.size(); j++){//查找是否有对应的数据库记录
			if(dbFileList[i] == DirFileList[j])//如果存在，则此条目正常，不需删除此文件
			ret = 0;
		}

		if(ret == 0){//从目录中找到了对应的文件

		}
		else{//不存在，则删除此文件
			string fileFullName = AD_DIR + DirFileList[i];
			rm_file(fileFullName);
			LOGE("删除一个文件：%s",fileFullName.c_str());
		}
	}
	//检查
	dbFileList = getAdListFromDB();
	DirFileList = getAdListFromFile();
	if(dbFileList.size() == DirFileList.size()){
		for(int i = 0; i < dbFileList.size(); i++){
			LOGD("LIST:%s",dbFileList[i].c_str());
		}
		return dbFileList;
	}
	else{
		LOGD("LIST:ERR");
		return (stringList) NULL;
	}

}

stringList Advertisement::getAdListFromFile()
{
	stringList fileList;
	read_dir("/mnt/extsd/ad/",fileList);
	return fileList;
}
stringList Advertisement::getAdListFromDB()
{

	std::vector<S_INFOS> DBList;
	stringList  strDBFileList;
	DBList = dbAdv.getRecodes();
	for(int i = 0; i < DBList.size(); i++)
	{
		strDBFileList.push_back(DBList[i].fileName);
	}
	return strDBFileList;



}

} /* namespace std */
