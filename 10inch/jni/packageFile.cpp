/*
 * packageFile.cpp
 *
 *  Created on: 2018年12月21日
 *      Author: Administrator
 */
#include "base64.h"
#include "packageFile.h"
#include "utils/Log.h"

using namespace std;
using namespace std;
std::string GetFileName(char *str)
{
	Json::Reader reader;
	Json::Value root;
	std::string fileName;
	if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{

		fileName = root["name"].asString();  // 访问节点，upload_id = "UP000000"
	}
	return fileName;
}
bool SaveFile(char *str, char* directory)
{
	Json::Reader reader;
	Json::Value root;
	string fileName;
	string data;
	string dataout;
	string fileFullName;
	if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{

		fileName = root["name"].asString();  // 访问节点，upload_id = "UP000000"
		data = root["data"].asString();    // 访问节点，code = 100
		fileFullName = directory ;
		fileFullName +=  fileName;
		LOGE("%s",fileFullName.c_str());
	}
	else
	{
		return false;
	}
	Base64::Decode(data, &dataout);
	FILE *fp = fopen(fileFullName.c_str(), "w");
	if (fp != NULL)
	{
		int writeLength = fwrite(dataout.c_str(), sizeof(char), dataout.size(), fp);
	}
	else
	{
		return false;
	}
	if (fclose(fp) != 0) {
		return false;
	}
	return true;
}
