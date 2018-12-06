/*
 * json_test.cpp
 *
 *  Created on: 2018年12月4日
 *      Author: Administrator
 */

#include "json_test.h"


using namespace std;

std::string get_id(const char *str)
{
	  Json::Reader reader;

	  Json::Value root;
	  std::string upload_id;

	  if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

	     upload_id = root["uploadid"].asString();  // 访问节点，upload_id = "UP000000"

	  }

	  return upload_id;
}

int ParseJsonFromString()

{

  const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";



  Json::Reader reader;

  Json::Value root;
  std::string upload_id;

  if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素

  {

     upload_id = root["uploadid"].asString();  // 访问节点，upload_id = "UP000000"

    int code = root["code"].asInt();    // 访问节点，code = 100

  }

  return 0;

}

//定义文件指针
FILE *openfile(uint32_t *len)
{
	char chFileIn3[100];
	FILE *fp;


	string chFileIn1 = "/mnt/extsd/recv.jpg";
   strcpy(chFileIn3, chFileIn1.c_str());


   fp = fopen(chFileIn3, "rb");

	if (fp == NULL )

	{

		printf("打开读取文件失败");

		  return	NULL;

	}
	fseek(fp,0L,SEEK_END);
	*len=ftell(fp);
	fclose(fp);

	fp = fopen(chFileIn3, "rb");

	printf("打开读取文件成功");
	return fp;
}
