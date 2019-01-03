/*
 * json_test.cpp
 *
 *  Created on: 2018年12月4日
 *      Author: Administrator
 */

#include "json_test.h"
#include "lib/itoa.h"
#include "globalVar.h"
string cutOneJsonString(RingBufInt8 *msg)
{

	char buf[msg->available()];
	string resault = "";
	bool start_flag = false;

	int counter = 0;
	int state = 0;
	while(1)
	{
		if(msg->available())
		{
			if(state == 0)
			{
				buf[counter] = msg->read();
				if(buf[counter] == '{')
				{
					state = 1;
					counter++;
					start_flag = true;
					LOGE("解析开始...");
				}
			}
			else
			{
				buf[counter] = msg->read();
				if(buf[counter] =='}')
				{
					//LOGE("接受到结束符");
					if(ParseJsonString(buf) == true)
					{
						LOGE("解析完成,size:%dbytes",counter);
						resault = buf;
						return resault;
					}
					else
					{
						LOGE("解析失败,继续尝试。。。");
					}
				}
				counter++;
			}
		}
		else
		{
			//LOGE("解析失败。。。");
			return resault;
		}

	}
}
bool ParseJsonString(char *str)
{
	  Json::Reader reader;

	  Json::Value root;
	  if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  return true;
	  }
	  else
		  return false;
}
JsonCmd_t getJsonCMD(const char * str)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonCmd_t cmd;

	  if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  cmd = (JsonCmd_t)root["cmd"].asInt();
	  }

	  return cmd;
}
string ParseCMDDoor1(char *str)
{
	  Json::Reader reader;

	  Json::Value root;
	  int value;
	  std::string val_str;
	  if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  value = (int)root["value"].asInt();

		  char temp[10];
		  itoa(value,temp);
		  val_str = temp;
	  }

	  return val_str;
}
string MakeCMDHeatbeat()
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDHeartbeat);
	  root["hello"] = Json::Value("123");
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
}
string MakeCMDDoor1Ack(int state)
{

}
string ParseCMDDoor2(char *str)
{
	  Json::Reader reader;

	  Json::Value root;
	  int value;
	  std::string val_str;
	  if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  value = (int)root["value"].asInt();

		  char temp[10];
		  itoa(value,temp);
		  val_str = temp;
	  }

	  return val_str;
}
string MakeCMDDoorPassword(char *str)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(3);
	  root["doorPwd"] = Json::Value(str);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
}
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
